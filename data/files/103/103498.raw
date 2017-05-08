include("fmm.jl")
include("fmmcall.jl")
include("quadtree.jl")

N = 10
q = rand(N,1)
pos = rand(N,1) + im*rand(N,1)
phi_direct = complex(zeros(N))
phi_fmm = complex(zeros(N))


#Set up fmm infrastructure
levels = 4
tree = Array(quadtree.box,levels,4^(levels-1))
phi_direct = fmmcall.direct_eval(pos,q)


