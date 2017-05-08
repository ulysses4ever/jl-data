#This is code to take a gromacs .gro file and put it in .xml format for HOOMD
#Currently, code only outputs box specifications, particle positions, particle velocities, particle masses, charges, and types
#More work will have to be done to properly import topology (bond, angle, dihedral connectivities, etc)
#using Debug
module groread
export readGro
export readTop
export gro2xml
export nonbonded
export readFF
function readGro(filename)
	#function that reads a gro file of specified name and returns a tuple containing number of atoms, box size, and arrays of atom name, position, and velocity, and an array of atom labels
	#right now this assumes all atoms are their own molecules
	#need to change this so it checks for either 1, starting new molecule or just check for solvent
	#right now it basically just reads solvent
	f = open(filename)
	lines = readlines(f)
	natoms = parse(Int,lines[2])
	box = readdlm(IOBuffer(lines[end]))
	#name = Array(AbstractString,size(lines,1)-3,1)
	posvel = Array(Float64,size(lines,1)-3,6)
	labels = Array(AbstractString,size(lines,1)-3,1)
	for i = 3:size(lines,1)-1
		line = split(chomp(lines[i]))
		#name[i-2] = line[2]
		labels[i-2] = line[1]
		for j = 1:6
			posvel[i-2,j] = parse(Float64,line[j+size(line,1)-6])
		end
	end
	return (natoms,box,posvel,labels)
end

function conParse(conmat,bnum)
	#helper function for readTop that takes a matrix of constraints between bonds where the third column is constraint length and a starting index bnum, and returns a list of lines of the form "c" bnum, "c"bnum+1 with the bonds labeled and the indices labeled based on which constraint lengths match each other
	#this function is only useful if constraints are being tabulated the same as bonds are 
	ulist = unique(conmat[:,3])
	conlist = Array(Any,size(conmat,1),3)
	for i = 1:size(conmat,1)
		ind = findind(conmat[i,3],ulist)+bnum
		conlist[i,2] = round(Int,conmat[i,1])
		conlist[i,3] = round(Int,conmat[i,2])
		conlist[i,1] = "c"*string(ind)
	end
	return conlist
end

function findind(x::Float64,list::Array{Float64,1})
	#helper function that returns the (first) index of a float in a float array
	for i = 1:size(list,1)
		if list[i]==x
			return i
		end
	end
	return 0
end

function readTop(filename)
	#reads a .top or .itp file and returns an array of atoms including important properties, and arrays of bonds, angles, and dihedrals along with names (#s corresponding to index of atom in molecule
	f = open(filename)
	lines = readlines(f)
	close(f)
	aind = 1+find(lines .== "[ atoms ]\n")[1]
	bind = 1+find(lines .== "[ bonds ]\n")[1]
	cind = 1+find(lines .== "[ constraints ]\n")[1]
	anind = 1+find(lines .== "[ angles ]\n")[1]
	dind = 1+find(lines .== "[ dihedrals ]\n")[1]
	iind = 1+find(lines .=="; Sidechain improper dihedrals\n")[1]
	
	atomnamelist = Array(AbstractString,bind-aind)
	bondlist = Array(Any,anind-bind,3)
	anglist = Array(Any,dind-anind,4)
	dihlist = Array(Any,size(lines,1)-dind,14)
	ind = 1
	#@bp
	for i = aind:bind-2
	#parse atom	
		line = lines[i]
		if length(line) > 1 && line[1] != ';' #not an empty line or a comment
			atomnamelist[ind] = split(line)[2]
			ind += 1
		end
	end
	atomnamelist = atomnamelist[1:ind-1]
        #@bp
	bnum=0	
	ind = 1
	for i = bind:cind-2
	#parse bonds
		line = lines[i]
		if length(line) > 1 && line[1] != ';'
			bondlist[ind,:] = ["b"*split(line)[4] parse(Int,split(line)[1]) parse(Int,split(line)[2])]
			ind += 1
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#
			bnum = parse(Int,split(line)[4])+1 #track final bond number for constraint numbering purposes, right now we're assuming a fair bit about how the bonds and constraints are tabulated, so be careful if we change that
			#println(bnum)
		end
		#println(bnum)
	end
	#@bp
	#println(bnum)
	conmat = zeros(anind-2-cind,3)
	cmind = 1
	for i = cind:anind-2
		#parse constraints, let's symmetrize them with the ones that have matching constraint lengths so that we can apply tabulated bonds exactly the same as for the bonds
		#parse in all the constraints at once into a matrix tracking the beads involved and the constraint length
		
		line = lines[i]
		
		if length(line) > 1 && line[1]!= ';'
			conmat[cmind,1] = parse(Float64,split(line)[1])
			conmat[cmind,2] = parse(Float64,split(line)[2])
			conmat[cmind,3] = parse(Float64,split(line)[4])
			#ind+=1
			cmind+=1
		end
		#then have another function that returns constraints numbered with uniqueness
		#@bp
		#line = lines[i]
		#if length(line) > 1 && line[1] != ';'
		#	bondlist[ind,:] = ["c0" parse(Int,split(line)[1]) parse(Int,split(line)[2])]
		#	ind += 1
		#end
	end
	conlist = conParse(conmat,bnum)
	#@bp
	bondlist[ind:ind+size(conlist,1)-1,:] = conlist
	bondlist = bondlist[1:ind+size(conlist,1)-1,:]

	ind = 1
	for i = anind:dind-2
		#parse angles
		line = lines[i]
		if length(line) > 1 && line[1] != ';'
			anglist[ind,:] = ["a"*split(line)[5] parse(Int,split(line)[1]) parse(Int,split(line)[2]) parse(Int,split(line)[3]) ]
			ind += 1
		end
		
	end
	anglist = anglist[1:ind-1,:]

	#firstcurr = [0 0 0 0]
	dnum = 0
	ind = 1
	dind2 = 1
	for i = dind:size(lines,1)
		#parse dihedrals, this part may need to be heavily modified but right now assumes a single dihedral for each set of 4 atoms, we're going to need to pull out the dihedral parameters in addition to the dihedral names, each dihedral should have a set of 9 coefficients that can be used to set it properly in the mkhoomdscript file
		#fortunately, I think I can just staple that extra info onto the side of the dihlist
		#that means for now we are assuming TYPE NINE dihedrals, meaning there should be NINE entries per dihedral
		#so all we have to do is keep track of a second dihedral index and reset it if it hits 10 -> 1
		#assume impropers are identical and parse them the same way
		line = lines[i]
		if length(line) > 1 && line[1] != ';'
		
		if dind2 == 1
			dihlist[ind,1:5] = ["d"*string(dnum) parse(Int,split(line)[1]) parse(Int,split(line)[2]) parse(Int,split(line)[3]) parse(Int,split(line)[4])]
			dihlist[ind,6] = parse(Float64,split(line)[7])
			dnum += 1
			dind2 += 1
		elseif dind2 == 9
			dihlist[ind,dind2+5] = parse(Float64,split(line)[7])
			dind2 = 1
			ind += 1
		else
			dihlist[ind,dind2+5] = parse(Float64,split(line)[7])
			dind2 += 1
		end
		end
		#=if length(line) > 1 && line[1] != ';'
			curr = [parse(Int,split(line)[1]) parse(Int,split(line)[2]) parse(Int,split(line)[3]) parse(Int,split(line)[4])]
			if curr != firstcurr
				firstcurr = curr
				dihlist[ind,:] = ["d"*string(dnum) parse(Int,split(line)[1]) parse(Int,split(line)[2]) parse(Int,split(line)[3]) parse(Int,split(line)[4])]
			ind += 1
			dnum += 1
			end 
		end=#
	end
	#=
	firstcurr = [0 0 0 0]
	inum = 0
	for i = iind:size(lines,1)
		#parse impropers, see notes on dihedrals
		line = lines[i]
		
		if length(line) > 1 && line[1] != ';'
			curr = [parse(Int,split(line)[1]) parse(Int,split(line)[2]) parse(Int,split(line)[3]) parse(Int,split(line)[4])]
			if curr != firstcurr
				firstcurr = curr
				dihlist[ind,:] = ["i"*string(inum) parse(Int,split(line)[1]) parse(Int,split(line)[2]) parse(Int,split(line)[3]) parse(Int,split(line)[4])]
			ind+=1
			inum += 1
			end 
		end
		
	end
	=#
	
	dihlist = dihlist[1:ind-1,:]
	return (atomnamelist,bondlist,anglist,dihlist)

end

function is_solvent(label,solvent)
	#checks whether the label of a particle is in the form ####S where S is the solvent designation
	return ismatch(Regex("\\d+"*solvent),label)
end

function is_first(label,prev,first)
	#checks whether the label of a particle is equal to the first particle label and whether that's different from the label of the previous one
	return (label==first)&&(prev!=first)
end

function readFF(fffile,fftype="martini")
	#function that reads a forcefield file of some type and packages all bead interactions into a dictionary of type Dict{Tuple{ASCIIString,ASCIIString},Tuple(Float64,Float64}}
	ffdict = Dict(("P5","P5") => (0.0,0.0))
	ff = open(fffile)
	fflines = readlines(ff)
	forcematch = r"\s+[a-zA-Z]+\d*\s+[a-zA-Z]+\d*\s+1\s+\d\.\d+E[-+]\d+\s+\d\.\d+E[-+]\d+.*" #regular expression to match a line of the form "  Na    SN0     1       0.15091E-00     0.16267E-02 ; intermediate"
	for line in fflines
		if ismatch(forcematch,line)
			#we have a parsable line
			spline = split(line)
			ffdict[(spline[1],spline[2])] = (float(spline[4]),float(spline[5]))
		end
	end
	close(ff)	
	return ffdict
end

function nonbonded(beadlist,ff,fftype="martini")
#function that returns all nonbonded interactions in an array of string elements
	n = length(beadlist)
	nonbonded_lines = Array(ASCIIString,round(Int,(n*(n+1)/2)))
	if fftype=="martini"
		#assume a forcefield has been read in that is a dictionary of (type1,type2):(c6,c12)
		#assume we've read in c6 and c12, we need epsilon and sigma
		#loop through all combinations of beads
		k = 1
		for i=1:n
			for j=i:n
				#check dictionary--both ways round, because only one way round is actually in the dictionary
				params = get(ff,(beadlist[i],beadlist[j]),0)
				if params == 0
					params = get(ff,(beadlist[j],beadlist[i]),0)
				end
				
				if params==0
					#throw an error, we didn't find this combination in the dictionary
					println("bead pair not found in forcefield: ($(beadlist[i]),$(beadlist[j]))")
					return 0
				end
				c6 = params[1]
				c12 = params[2]
				sigma = (c12/c6)^(1.0/6.0)
				eps = c6/(4*sigma^6)
				nbline = "lj.pair_coeff.set('$(beadlist[i])','$(beadlist[j])',epsilon=$eps,sigma=$sigma)"
				nonbonded_lines[k] = nbline
				k+=1
			end
		end
	end
	return nonbonded_lines
end

function getmasses(fffile,ff)
	#returns beads with their mass in a dictionary
	#currently only set up for martini force field
	massDict = Dict("P5"=> 1.0)
	f = open(fffile,"r")
	line = ""
	if ff=="martini"
		while line!="[ nonbond_params ]"
			line = strip(readline(f))
			if length(line) > 0
			if line[1]!=';'#ignore comments
				spline = split(line)
				if length(spline) == 6#ignore incorrect sections
					bead = spline[1]
					mass = float(spline[2])
					massDict[bead] = mass
				end
				
			end
			end
		end
	else
		println("Currently only works for Martini force field.")
		return Dict()
	end
	return massDict
end

function readGroProtein(solvent,grofile)
#function that pulls in the protein & parameters from a gro file
	grof = open(grofile,"r")
	flag = "BB"
	lines = readlines(grof)
	close(grof)
	i = 3
	while flag!=solvent
		spline = split(strip(lines[i]))
		flag = spline[2]
		i+=1
	end
	protein = Array(Any,(i-2)-2,9)
	protlines = lines[3:(i-2)]
	for j = 1:((i-2)-2)
		#convert to array of strings and floats for easier parsing
		protein[j,:] = split(strip(protlines[j]))
	end
	#return array and index 
	return (i-2,protein)
end

function ringToBeadGro(grofile,outgrofile,solvent="W")
#function that reads in a .gro file and replaces S beads in PHE with a single M1 bead (modifiable parameters)
#also replaces three beads of COP with M2
	(ind,protein) = readGroProtein(solvent,grofile)
	#	
end

function ringToBeadTop(topfile,outtopfile)
#function that reads in a .top or .itp file and replaces S beads in PHE with a single M1 bead (modifiable parameters)
#also replaces three beads of COP with M2
#bonds, angles, and dihedrals all need to be replaced as well
println("under construction")
end

function gro2xml(infile,topfile,outfile,solvent="W",ff="martini",fffile="martini.itp")
	#currently assumes just one type of molecule + solvent
	(natoms,box,posvel,labels) = readGro(infile)
	(atomnamelist,bondlist,anglist,dihlist) = readTop(topfile)

	out = open(outfile,"w")
	println(out,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
	println(out,"<hoomd_xml version=\"1.6\">")
	println(out,"<!-- generated from file $infile and $topfile by Julia code written by Rachael Mansbach -->")
	if ff=="martini"
		massDict = getmasses(fffile,ff)
		#println(out,"<!--units of mass are 72 amu to get mass to O(1) for Martini -->")
	else
		massDict = getmasses(fffile,ff)
		println("Unknown force field. Behavior may be unexpected.")

	end
	println(out,"<configuration time_step=\"0\" dimensions=\"3\">")
	println(out,"<box lx=\"$(box[1])\" ly=\"$(box[2])\" lz=\"$(box[3])\"/>")
	
	println(out,"<type>")
	currindb = 1
	currinda = 1
	currindd = 1
	bondout = Array(Any,natoms,3)
	angout = Array(Any,natoms,4)
	dihout = Array(Any,natoms,5)
	prev = "0NOT"
	first = labels[1]
	listind = 1
	for i = 1:natoms
		if is_solvent(labels[i],solvent)
			if solvent=="W"
				println(out,"P4")
			else
				println("using a solvent other than water, behavior not established.")
			    	println(out,solvent)
			end
		else
			
			if is_first(labels[i],prev,first)
				
				bondout[currindb:currindb+size(bondlist,1)-1,1] = bondlist[:,1]
				bondout[currindb:currindb+size(bondlist,1)-1,2:3] = bondlist[:,2:3] + i-2 #fix for 0 indexing
				angout[currinda:currinda+size(anglist,1)-1,1] = anglist[:,1]
				angout[currinda:currinda+size(anglist,1)-1,2:4] = anglist[:,2:4] + i -2
				dihout[currindd:currindd+size(dihlist,1)-1,1] = dihlist[:,1]
				dihout[currindd:currindd+size(dihlist,1)-1,2:5] = dihlist[:,2:5] + i -2
				currindb += size(bondlist,1)
				currinda += size(anglist,1)
				currindd += size(dihlist,1)
				listind = 1
			end
			println(out,atomnamelist[listind])
			listind += 1
			prev = labels[i]
		end
	end
	println(out,"</type>")
	println(out,"<mass>")
	listind=1
	for i = 1:natoms
		
		if is_solvent(labels[i],solvent)
			if solvent=="W"
				println(out,massDict["P4"])
			else
				println("using a solvent other than water, behavior not established.")
			    	println(out,solvent)
			end
		else
			println(out,massDict[atomnamelist[listind]])
			listind+=1	
		end
	end
	println(out,"</mass>")
	bondout = bondout[1:currindb-1,:]
	angout = angout[1:currinda-1,:]
	dihout = dihout[1:currindd-1,:]
	println(out,"<bond>")
	for i = 1:size(bondout,1)
		println(out,"$(bondout[i,1]) $(string(bondout[i,2])) $(string(bondout[i,3]))")
	end
	println(out,"</bond>")
	println(out,"<angle>")
	for i = 1:size(angout,1)
		println(out,"$(angout[i,1]) $(string(angout[i,2])) $(string(angout[i,3])) $(string(angout[i,4]))")
	end
	println(out,"</angle>")
	println(out,"<dihedral>")
	for i = 1:size(dihout,1)
		println(out,"$(dihout[i,1]) $(string(dihout[i,2])) $(string(dihout[i,3])) $(string(dihout[i,4])) $(string(dihout[i,5]))")
	end
	println(out,"</dihedral>")
	println(out,"<position>")
	for i = 1:natoms
		#gromacs can have rounding errors such that some of the molecules are slightly out of the box
		#HOOMD is very very not okay with that! so we need to fix it
		if posvel[i,1] < 0.0
			posvel[i,1] = 0.0
		end
		if posvel[i,2] < 0.0
			posvel[i,2] = 0.0
		end
		if posvel[i,3] < 0.0
			posvel[i,3] = 0.0
		end
		if posvel[i,1] > box[1]
			posvel[i,1] = box[1]
		end
		if posvel[i,2] > box[2]
			posvel[i,2] = box[2]
		end
		if posvel[i,3] > box[3]
			posvel[i,3] = box[3]
		end
		#gromacs has origin at bottom left, hoomd has origin in center
		x = posvel[i,1]-box[1]/2
		y = posvel[i,2]-box[2]/2
		z = posvel[i,3]-box[3]/2
		
		#x = posvel[i,1]
		#y = posvel[i,2]
		#z = posvel[i,3]
		println(out,"$(x) $(y) $(z)")
	end
	println(out,"</position>")
	println(out,"<velocity>")
	for i = 1:natoms
		println(out,"$(posvel[i,4]) $(posvel[i,5]) $(posvel[i,6])")
	end
	println(out,"</velocity>")
	println(out,"</configuration>")
	println(out,"</hoomd_xml>")
	close(out)
end
end

if size(ARGS,1) == 3
	gro2xml(ARGS[1],ARGS[2],ARGS[3])
else
	println("Syntax: gro2xml <grofilename> <topfilename> <outfilename>")
end
