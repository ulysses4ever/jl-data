#=
Bartłomiej Sadowski 
=#
include("mbisekcji.jl")
include("mstycznych.jl")
include("msiecznych.jl")

f=x -> sin(x)-((1/2)*x)^2
pf=x->cos(x)-x/2

println("mbisekcji:\n",mbisekcji(f,1.5,2.0,1/(2*10^5),1/(2*10^5)))
println("mstycznych\n",mstycznych(f,pf,1.5,1/(2*10^5),1/(2*10^5),300))
println("msiecznych\n",msiecznych(f,1.0,2.0,1/(2*10^5),1/(2*10^5),100))

println(f(0.0))
