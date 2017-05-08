#This is code to take a gromacs .gro file and put it in .xml format for HOOMD
#Currently, code only outputs box specifications, particle positions, particle velocities, particle masses, charges, and types
#More work will have to be done to properly import topology (bond, angle, dihedral connectivities, etc)

function readGro(filename)
	#function that reads a gro file of specified name and returns a tuple containing number of atoms, box size, and arrays of atom name, position, and velocity
	f = open(filename)
	lines = readlines(f)
	natoms = parse(Int,lines[2])
	box = readdlm(IOBuffer(lines[end]))
	name = Array(AbstractString,size(lines,1)-3,1)
	posvel = Array(Float64,size(lines,1)-3,6)
	for i = 3:size(lines,1)-1
		line = split(chomp(lines[i]))
		name[i-2] = line[2]
		for j = 1:6
			posvel[i-2,j] = parse(Float64,line[j+3])
		end
	end
	return (natoms,box,name,posvel)
end

function gro2xml(infile,outfile)
	(natoms,box,name,posvel) = readGro(infile)
	out = open(outfile,"w")
	println(out,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
	println(out,"<hoomd_xml version=\"1.6\">")
	println(out,"<!-- generated from file $infile by Julia code written by Rachael Mansbach -->")
	println(out,"<configuration time_step=\"0\" dimensions=\"3\">")
	println(out,"<box lx=\"$(box[1])\" ly=\"$(box[2])\" lz=\"$(box[3])>")
	println(out,"<type>")
	for i = 1:natoms
		println(out,name[i])
	end
	println(out,"</type>")
	println(out,"<position>")
	for i = 1:natoms
		println(out,"$(posvel[i,1]) $(posvel[i,2]) $(posvel[i,3])")
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

if size(ARGS,1) == 2
	gro2xml(ARGS[1],ARGS[2])
else
	println("Syntax: gro2xml <infilename> <outfilename>")
end
