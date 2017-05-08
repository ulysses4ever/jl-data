#push!(LOAD_PATH,"/home/rachael/Analysis_and_run_code/hoomd")
#using groread
module mkhoomdscript
export scriptwrite
using groread
#ffdict = groread.readFF(fffile,"martini")

function scriptwrite(filename,xml,dt,T,tau,outname,fffile,topfile,rcut,steps,therm,rbuff;restart="restart.xml",gamma=0,per=100,rseed=1234,solvent="W",harmcons=0)
#master function to write out a hoomd script assuming martini.itp for nonbonded interactions and tabulated functions for all defined intermolecular bonds
#right now assumes a lot about the integration that can either be changed directly here or I can make it a little more flexible on a later pass
#filename is the name of the filename to write (something.hoomd), xml is the name of the input xml file (that should already have been written using groread), dt is the timestep, T is the temperature in K, which currently gets converted to reduced temperature assuming Gromacs units, tau is the temperature coupling constant, and outname is the name to give to the hoomd output files, fffile is the name of the force field file, topfile is the name of the itp topology file, rcut is the LJ cutoff, solvent is the solvent molecule, defaults to W and currently only guaranteed to behave correctly for water
#steps is the number of timesteps to run for
#therm is the thermometer to use; currently this works for nvt or dpd; if dpd is used, a non-zero gamma must also be supplied
	#initialize
#rbuff is the radius for the neighborlist
#rseed is the random seed for velocity distribution initialization
#if harmcons is not 0, it should be passed an array of values consisting of bond index, k values, and r0 values for enforcing harmonic bonds on just those bonds listed in the array
	
	f = open(filename,"w")
	println(f,"from hoomd_script import *")
	println(f,"from math import *")
	println(f,"import random")
	println(f,"context.initialize()")
	println(f,"system = init.read_xml(filename=\"$xml\", restart = \"$restart\")")
	println(f,"n1 = nlist.cell(r_buff=$rbuff)")
	#define intramolecular bonds
	
	redT = T*8.31451070*10.0^(-3)
	ffdict = readFF(fffile,"martini")
	(beadlist,bondlist,anglist,dihlist) = readTop(topfile)
	if solvent=="W"
		solvbead = "P4"
	end
	beads = unique([beadlist;solvbead])
	nblines = nonbonded(beads,ffdict,"martini")
	println(f,"lj = pair.lj(r_cut=$rcut)")
	println(f,"lj.set_params(mode=\"shift\")")
	if therm == "dpd"
		println(f,"dpd = pair.dpd(r_cut=$rcut,T=$redT)")
		for i = 1:size(beads,1)
			for j = i:size(beads,1)
				println(f,"dpd.pair_coeff.set('$(beads[i])','$(beads[j])',A=0.0,gamma = $gamma)")
			end
		end
		println(f,"dpd.set_params(T=$redT)")
	end
	for line in nblines
		println(f,line)
	end
	
	#define intermolecular bonds
	#right now define bonds, and angles as tables to read in
	bonds = unique(bondlist[:,1])
	#assume that the name of the bond is the same as the name of table describing the bond
	#all tables must be the same length, so we can check the length of the first table and assume it's the correct length for all of them
	bfile = open("$(bonds[1]).dat","r")
	blines = readlines(bfile)
	close(bfile)
	btabwidth = length(blines)
	println(f,"btable = bond.table(width=$btabwidth)")
	if harmcons==0
	for bond in bonds
		#constraints must be defined either from a table or as a tabulated "function" since they are "bonds" and bond.table specified ALL bonded pairs must be treated the same way, for now let's just tabulate because it's easier
		println(f,"btable.set_from_file('$bond','$bond.dat')")
	end
	else
	
	#some of the bonds are set as harmonics instead
	#assume that the constraint starts at some index and continues in order
	cind1 = round(Int,harmcons[1,1])
	cindend = round(Int,harmcons[size(harmcons,1),1])
		println(f,"bharm = bond.harmonic(name=\"harm\")")
		for h = 1:(cind1-1)
			#all tabulated
			#println("tab $(bonds[h]),$h")
			println(f,"btable.set_from_file('$(bonds[h])','$(bonds[h]).dat')")
			println(f,"bharm.bond_coeff.set('$(bonds[h])',k=0.0,r0=0.0)")
		end
		for h = cind1:cindend
			#println("harm $(bonds[h]),$h")
			println(f,"btable.set_from_file('$(bonds[h])','dummy.dat')")
			println(f,"bharm.bond_coeff.set('$(bonds[h])',k=$(harmcons[h-cind1+1,2]),r0=$(harmcons[h-cind1+1,3]))")
		end
		for h = (cindend+1):size(bonds,1)
			#println("tab $(bonds[h]),$h")
			#all tabulated
			println(f,"btable.set_from_file('$(bonds[h])','$(bonds[h]).dat')")
			println(f,"bharm.bond_coeff.set('$(bonds[h])',k=0.0,r0=0.0)")

		end
	end
	angs = unique(anglist[:,1])
	#angles are treated exactly the same as bonds
	afile = open("$(angs[1]).dat","r")
	alines = readlines(afile)
	atabwidth = length(alines)
	println(f,"atable = angle.table(width=$atabwidth)")
	close(afile)
	for ang in angs
		println(f,"atable.set_from_file('$ang','$ang.dat')")
	end
	#define dihedrals as fitted sums of cosines, so as a tabulated FUNCTION as defined in HOOMD's tabulated bond section
	println(f,"dtable = dihedral.table(width=1000)")
	println(f,"def type9(phi,C0,C1,C2,C3,C4,S1,S2,S3,S4):")
	println(f,"\tV = C0+C1*(1+cos(phi))+C2*(1+cos(2.0*phi))+C3*(1+cos(3.0*phi))+C4*(1+cos(4.0*phi))+S1*(1+cos(phi-pi/2.0))+S2*(1+cos(2.0*phi-pi/2.0))+S3*(1+cos(3.0*phi-pi/2.0))+S4*(1+cos(4.0*phi-pi/2.0))")
	println(f,"\tT = C0-C1*sin(phi)-2.0*C2*sin(2.0*phi)-3.0*C3*sin(3.0*phi)-4*C4*sin(4.0*phi)-S1*sin(phi-pi/2.0)-2.0*S2*sin(2.0*phi-pi/2.0)-3.0*sin(3.0*phi-pi/2.0)-4.0*S4*sin(4.0*phi-pi/2.0)")
	println(f,"\treturn (V,T)")
        for dih = 1:size(dihlist,1)
		println(f,"dtable.dihedral_coeff.set('$(dihlist[dih,1])',func=type9, coeff=dict(C0=$(dihlist[dih,6]),C1=$(dihlist[dih,7]),C2=$(dihlist[dih,8]),C3=$(dihlist[dih,9]),C4=$(dihlist[dih,10]),S1=$(dihlist[dih,11]),S2=$(dihlist[dih,12]),S3=$(dihlist[dih,13]),S4=$(dihlist[dih,14])))")
	end	
	#println(f,"intermolecular under construction")
	#set up integration and run
	#initialize random velocity distribution
	println(f,"random.seed($rseed)")
	println(f,"px = py = pz = 0.0")
	println(f,"T = $redT")
	println(f,"for p in system.particles:")
	println(f,"\tmass = p.mass")
	println(f,"\tsigma = sqrt(T/mass)")
	println(f,"\tvx = random.gauss(0,sigma)")
	println(f,"\tvy = random.gauss(0,sigma)")
	println(f,"\tvz = random.gauss(0,sigma)")
	println(f,"\tp.velocity = (vx,vy,vz)")
	println(f,"\tpx += mass*vx")
	println(f,"\tpy += mass*vy")
	println(f,"\tpz += mass*vz")
	println(f,"px/= len(system.particles)")
	println(f,"py/= len(system.particles)")
	println(f,"pz/= len(system.particles)")
 	println(f,"for p in system.particles:")
	println(f,"\tmass = p.mass")
	println(f,"\tv = p.velocity")
	println(f,"p.velocity = (v[0] - px/mass, v[1] - py/mass,v[2]-pz/mass)")	
	println(f,"all = group.all()")
	println(f,"integrate.mode_standard(dt=$dt)")
	if therm == "dpd"
		println(f,"integrate.nve(group=all)")
	elseif therm == "nvt"
		println(f,"integrate.nvt(group=all, T=$redT, tau = $tau)")

	else
		println("Thermometer not recognized.  Behavior may be unpredictable.")
		println(f,"integrate.nvt(group=all, T=$redT, tau = $tau)")
	end
	println(f,"xml_restart = dump.xml(filename=\"$restart\",all=True,restart=True,period=$(per*100),phase=0)")
	println(f,"analyze.log(filename='$outname.log',quantities=['potential_energy','kinetic_energy','temperature','pressure'],period=$per,phase=0)")
	println(f,"dump.dcd(filename='$outname.dcd',period=$per,unwrap_full=True,phase=0)")
	println(f,"run($steps)")
	close(f)
end


end
