module IBFS
# Required packages

using DataArrays

include("DataTypes.jl")
include("Grids.jl")
include("Solvers.jl")


# filename = "ibfs.conf"
# println("Hello world!")

#     function config(filename_or_dict)

#     end

    function run()
        A = [[4.0,1.0] [1.0,3.0]]
        b = [1.0,2.0]
        x = [2.0,1.0]
        maxiter = 100
        eps = float(10^-6.0)
        x = Solvers.cg(A, b, x, maxiter, eps)
        xtrue = [1/11,7/11]
        println("Error: ")
        println(xtrue-x)
    end #fun
end # module

