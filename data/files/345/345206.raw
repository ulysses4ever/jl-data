module SimpleBinaryManagementExample

export distance

const libex = joinpath(Pkg.dir("SimpleBinaryManagementExample"), "deps", "libex")
if !isfile(libex)
    error("library not found")
end

function distance(x::Float64, y::Float64)
    ccall((:squared_distance, libex), Float64, (Float64, Float64), x, y)
end

distance(x, y) = distance(convert(Float64, x), convert(Float64, y))

end # module
