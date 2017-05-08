module CSHEP2D

const libcshep2d= joinpath(dirname(@__FILE__), "../deps/src/libcshep2d.so")
if (Libdl.dlopen_e(libcshep2d) == C_NULL)
    error("CSHEP2D not properly installed. Run Pkg.build(\"CSHEP2D\")")
end

export CubicShepard2DInterpolator, valgradhes, valgrad

type CubicShepard2DInterpolator
	x
	y
	z
	lcell
	lnext
	xmin
	ymin
	dx
	dy 
	rmax
	rw
	nr
	a
end

function CubicShepard2DInterpolator(x::Vector{Float64}, y::Vector{Float64}, z::Vector{Float64}; nc::Int64=17, nw::Int64=30)
	length(x) == length(y) == length(z) || error("input vectors must be same size")
	# define all parameters of the call
	n = length(x)
	nr = round(Int, sqrt(n/3)) + 1
	lcell = zeros(Int64, nr*nr)
	lnext = zeros(Int64, n)
	xmin = Float64[0]
	ymin = Float64[0]
	dx = Float64[0]
	dy = Float64[0]
	rmax = Float64[0]
	rw = zeros(Int64, n)
	a = zeros(Int64, 9*n)
	ier = Int64[0]
	# exec call
	ccall((:cshep2_, libcshep2d), 
	        Ptr{Void}, 
	        (Ptr{Int64},   # N
	         Ptr{Float64}, # x
	         Ptr{Float64}, # y
	         Ptr{Float64}, # z
	         Ptr{Int64},   # nc
	         Ptr{Int64},   # nw
	         Ptr{Int64},   # nr
	         Ptr{Int64},   # lcell
	         Ptr{Int64},   # lnext
	         Ptr{Float64}, # xmin
	         Ptr{Float64}, # ymin
	         Ptr{Float64}, # dx
	         Ptr{Float64}, # dy
	         Ptr{Float64}, # rmax
	         Ptr{Int64},   # rw
	         Ptr{Int64},   # a
	         Ptr{Int64}),  # ier
	        &n, x, y, z, &nc, &nw, &nr, lcell, lnext, xmin, ymin, dx, dy, rmax, rw, a, ier)
	# rerurn waht is needed at a later stage
	CubicShepard2DInterpolator(x, y, z, lcell, lnext, xmin, ymin, dx, dy, rmax, rw, nr, a)
end

function valgrad(cs::CubicShepard2DInterpolator, xi::Vector{Float64}, yi::Vector{Float64})
	length(xi) == length(yi) || error("input vectors must be same size")
	c  = zeros(Float64, length(xi))
	cx = zeros(Float64, length(xi))
	cy = zeros(Float64, length(xi))
	c_tmp  = Float64[0.0]
	cx_tmp = Float64[0.0]
	cy_tmp = Float64[0.0]
	ier = Int64[0]
	for i = 1:length(xi)
		ccall((:cs2grd_, libcshep2d), 
		        Ptr{Void}, 
		        (Ptr{Float64}, # px -> xi
		         Ptr{Float64}, # py -> yi
		         Ptr{Int64},   # n
		         Ptr{Float64}, # x
		         Ptr{Float64}, # y
		         Ptr{Float64}, # z
		         Ptr{Int64},   # nr
		         Ptr{Int64},   # lcell
		         Ptr{Int64},   # lnext
		         Ptr{Float64}, # xmin
		         Ptr{Float64}, # ymin
		         Ptr{Float64}, # dx
		         Ptr{Float64}, # dy
		         Ptr{Float64}, # rmax
		         Ptr{Int64},   # rw
		         Ptr{Int64},   # a
		         Ptr{Float64}, # c
		         Ptr{Float64}, # cx
		         Ptr{Float64}, # cy
		         Ptr{Int64}),  # ier
		        &xi[i], &yi[i], &length(cs.x), cs.x, cs.y, cs.z, &(cs.nr), cs.lcell, cs.lnext, 
		         cs.xmin, cs.ymin, cs.dx, cs.dy, cs.rmax, cs.rw, cs.a, c_tmp, cx_tmp, cy_tmp, ier)
		c[i] = c_tmp[1]
		cx[i] = cx_tmp[1]
		cy[i] = cy_tmp[1]
	end
	return c, cx, cy
end

function valgradhes(cs::CubicShepard2DInterpolator, xi::Vector{Float64}, yi::Vector{Float64})
	length(xi) == length(yi) || error("input vectors must be same size")
	c  = zeros(Float64, length(xi))
	cx = zeros(Float64, length(xi))
	cy = zeros(Float64, length(xi))
	cxx = zeros(Float64, length(xi))
	cxy = zeros(Float64, length(xi))
	cyy = zeros(Float64, length(xi))
	c_tmp  = Float64[0.0]
	cx_tmp = Float64[0.0]
	cy_tmp = Float64[0.0]
	cxx_tmp = Float64[0.0]
	cxy_tmp = Float64[0.0]
	cyy_tmp = Float64[0.0]
	ier = Int64[0]
	for i = 1:length(xi)
		ccall((:cs2hes_, libcshep2d), 
		        Ptr{Void}, 
		        (Ptr{Float64}, # px -> xi
		         Ptr{Float64}, # py -> yi
		         Ptr{Int64},   # n
		         Ptr{Float64}, # x
		         Ptr{Float64}, # y
		         Ptr{Float64}, # z
		         Ptr{Int64},   # nr
		         Ptr{Int64},   # lcell
		         Ptr{Int64},   # lnext
		         Ptr{Float64}, # xmin
		         Ptr{Float64}, # ymin
		         Ptr{Float64}, # dx
		         Ptr{Float64}, # dy
		         Ptr{Float64}, # rmax
		         Ptr{Int64},   # rw
		         Ptr{Int64},   # a
		         Ptr{Float64}, # c
		         Ptr{Float64}, # cx
		         Ptr{Float64}, # cy
		         Ptr{Float64}, # cxx
		         Ptr{Float64}, # cxy
		         Ptr{Float64}, # cyy
		         Ptr{Int64}),  # ier
		        &xi[i], &yi[i], &length(cs.x), cs.x, cs.y, cs.z, &(cs.nr), cs.lcell, cs.lnext, 
		         cs.xmin, cs.ymin, cs.dx, cs.dy, cs.rmax, cs.rw, cs.a, c_tmp, cx_tmp,
		         cy_tmp, cxx_tmp, cxy_tmp, cyy_tmp, ier)
		c[i] = c_tmp[1]
		cx[i] = cx_tmp[1]
		cy[i] = cy_tmp[1]
		cxx[i] = cxx_tmp[1]
		cxy[i] = cxy_tmp[1]
		cyy[i] = cyy_tmp[1]
	end
	return c, cx, cy, cxx, cxy, cyy
end

end