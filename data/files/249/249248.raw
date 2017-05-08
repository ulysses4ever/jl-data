#MiscTools: Base definitions
#-------------------------------------------------------------------------------


#==Constants
===============================================================================#


#==Main Types
===============================================================================#
typealias DataWord UInt32
typealias Integer32 Union{Int32,UInt32}
typealias Integer8 Union{Int8,UInt8}


#==Basic functions
===============================================================================#
poweroftwo{T<:Integer}(v::T) = v == (T(1)<<Int(log2(v)))

#Compute # of bytes remaining within word boundary after writing given amount of bytes:
@assert(poweroftwo(sizeof(DataWord)), "Algorithms expect sizeof(DataWord) to be a power of two")
#bytesremaining(nbytes::Integer, ::Type{DataWord}) = mod(sizeof(DataWord)-nbytes, sizeof(DataWord))
bytesremaining(nbytes::Integer, ::Type{DataWord}) = (sizeof(DataWord)-Int(nbytes)) & (sizeof(DataWord)-1)

#Zero-out remaining bytes to a word boundary (after writing nbytes):
function zeroremaining{WORDT}(io::IO, nbytes::Integer, ::Type{WORDT})
	rmg = bytesremaining(nbytes, WORDT)
	for i in 1:rmg 
		write(io, UInt8(0))
	end
end


#==Write functions
===============================================================================#
@assert(DataWord<:Integer32, "Incorrect assumption: DataWord not 32-bits.")
writeword(io::IO, v::Integer8) = write(io, hton(DataWord(reinterpret(UInt8, v))))
writeword(io::IO, v::Integer32) = write(io, hton(v))
writeword(io::IO, v::Float64) = write(io, hton(v))
writeword(io::IO, v::Complex{Float64}) = write(io, hton(real(v)), hton(imag(v)))

function writeword{T<:Integer8}(io::IO, v::Vector{T})
	write(io, v)
	zeroremaining(io, length(v), DataWord)
end


#Last line
