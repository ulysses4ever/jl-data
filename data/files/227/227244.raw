##  linking external libraries examples
##  from manual section 1.21


ccall( (:clock, "libc"), Int32, ())					#  call a C library function taking no arguments


function gethostnam()								#  another example of same
	hostname = Array(Uint8, 128)
	ccall( (:gethostname, "libc"), Int32, (Ptr{Uint8}, Uint), hostname, length(hostname))
	return bytestring(convert(Ptr{Uint8}, hostname))
end
gethostnam()


function compute_dot(DX::Vector, DY::Vector)		#  call an LAPACK function
	assert(length(DX) == length(DY))
	n = length(DX)
	incx = incy = 1
	product = ccall( (:ddot_, "libLAPACK"), Float64, (Ptr{Int32}, Ptr{Float64}, Ptr{Int32}, Ptr{Float64}, Ptr{Int32}), &n, DX, &incx, DY, &incy)
	return product
end
compute_dot(([1.0, 5.0]), [6.0, 10.0])
