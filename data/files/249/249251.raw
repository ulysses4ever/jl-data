#Test code
#-------------------------------------------------------------------------------

using MiscTools

#No real test code yet... just demonstrate use:


#==Input data
===============================================================================#
filename = "./outfile.bin"


#==Tests
===============================================================================#
open(filename, "w") do io
	writeword(io, UInt32(5))
	writeword(io, Int32(-5))
	writeword(io, UInt8(5))
	writeword(io, Int8(-5))
	writeword(io, convert(Vector{UInt8}, "Output String"))
	writeword(io, UInt8(5))
	writeword(io, UInt8(5))
end


:Test_Complete
