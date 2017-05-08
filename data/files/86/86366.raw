#push!(LOAD_PATH,"/home/rachael/Analysis_and_run_code/hoomd")
#using groread
module mkhoomdscript
export scriptwrite
using groread
#ffdict = groread.readFF(fffile,"martini")

function scriptwrite(filename,xml,dt,T,tau,outname,fffile,topfile,rcut,steps,solvent="W")
#master function to write out a hoomd script assuming martini.itp for nonbonded interactions and tabulated functions for all defined intermolecular bonds
#right now assumes a lot about the integration that can either be changed directly here or I can make it a little more flexible on a later pass
#filename is the name of the filename to write (something.hoomd), xml is the name of the input xml file (that should already have been written using groread), dt is the timestep, T is the temperature in K, which currently gets converted to reduced temperature assuming Gromacs units, tau is the temperature coupling constant, and outname is the name to give to the hoomd output files, fffile is the name of the force field file, topfile is the name of the itp topology file, rcut is the LJ cutoff, solvent is the solvent molecule, defaults to W and currently only guaranteed to behave correctly for water
#steps is the number of timesteps to run for
	#initialize
	f = open(filename,"w")
	println(f,"from hoomd_script import *")
	println(f,"from math import *")
	println(f,"context.initialize()")
	println(f,"init.read_xml(filename=\"$xml\")")
	#define intramolecular bonds
	
	ffdict = readFF(fffile,"martini")
	(beadlist,bondlist,anglist,dihlist) = readTop(topfile)
	if solvent=="W"
		solvbead = "P4"
	end
	beads = unique([beadlist;solvbead])
	nblines = nonbonded(beads,ffdict,"martini")
	println(f,"lj = pair.slj(r_cut=$rcut)")
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
	btabwidth = length(blines)
	println(f,"btable = bond.table(width=$btabwidth)")
	close(bfile)
	for bond in bonds
		#constraints must be defined either from a table or as a tabulated "function" since they are "bonds" and bond.table specified ALL bonded pairs must be treated the same way, for now let's just tabulate because it's easier
		println(f,"btable.set_from_file('$bond','$bond.dat')")
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
	println(f,"\tV = C0+C1*cos(phi)+C2*cos(2.0*phi)+C3*cos(3.0*phi)+C4*cos(4.0*phi)+S1*cos(phi-pi/2.0)+S2*cos(2.0*phi-pi/2.0)+S3*cos(3.0*phi-pi/2.0)+S4*cos(4.0*phi-pi/2.0)")
	println(f,"\tT = C0-C1*sin(phi)-2.0*C2*sin(2.0*phi)-3.0*C3*sin(3.0*phi)-4*C4*sin(4.0*phi)-S1*sin(phi-pi/2.0)-2.0*S2*sin(2.0*phi-pi/2.0)-3.0*sin(3.0*phi-pi/2.0)-4.0*S4*sin(4.0*phi-pi/2.0)")
	println(f,"\treturn (V,T)")
        for dih = 1:size(dihlist,1)
		println(f,"dtable.dihedral_coeff.set('$(dihlist[dih,1])',func=type9, coeff=dict(C0=$(dihlist[dih,6]),C1=$(dihlist[dih,7]),C2=$(dihlist[dih,8]),C3=$(dihlist[dih,9]),C4=$(dihlist[dih,10]),S1=$(dihlist[dih,11]),S2=$(dihlist[dih,12]),S3=$(dihlist[dih,13]),S4=$(dihlist[dih,14])))")
	end	
	#println(f,"intermolecular under construction")
	#set up integration and run
	println(f,"all = group.all()")
	println(f,"integrate.mode_standard(dt=$dt)")
	redT = T*8.31451070*10.0^(-3)
	println(f,"integrate.nvt(group=all, T=$redT, tau = $tau)")
	println(f,"analyze.log(filename='$outname.log',quantities=['potential_energy','kinetic_energy','temperature','pressure'],period=100)")
	println(f,"run($steps)")
	close(f)
end


end
