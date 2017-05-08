using groread
module mkhoomdscript
export scriptwrite

function scriptwrite(filename,xml,dt,redT,tau,outname)
#master function to write out a hoomd script assuming martini.itp for nonbonded interactions and tabulated functions for all defined intermolecular bonds
#right now assumes a lot about the integration that can either be changed directly here or I can make it a little more flexible on a later pass
	#initialize
	f = open(filename,"w")
	println(f,"from hoom_script import *")
	println(f,"context.initialize()")
	println(f,"init.read_xml(filename=\"$xml\"")
	#define intramolecular bonds

	#define intermolecular bonds

	#set up integration and run
	println(f,"all = group.all()")
	println(f,"integrate.mode_standard(dt=$dt)")
	println(f,"integrate.nvt(group=all, T=$redT, tau = $tau)")
	println(f,"analyze.log(filename='$outname.log',quantities=['potential_energy','kinetic_energy','temperature','pressure'],period=100)")
	
	close(f)
end


end
