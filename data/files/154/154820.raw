#=
Bartłomiej Sadowski 
=#
include("mbisekcji.jl")
include("mstycznych.jl")
include("msiecznych.jl")

f1=x -> exp(1-x)-1
pf1=x->-exp(1-x)

f2=x -> x*exp(-x)
pf2=x->-exp(-x)*(x-1)

println("mbisekcji:\n",mbisekcji(f1,0.0,2.0,1/(10^5),1/(10^5)))
println("mstycznych\n",mstycznych(f1,pf1,0.5,1/(10^5),1/(10^5),300))
println("msiecznych\n",msiecznych(f1,0.5,0.51,1/(10^5),1/(10^5),30000))

println("mbisekcji:\n",mbisekcji(f2,-0.2,0.21,1/(10^5),1/(10^5)))
println("mstycznych\n",mstycznych(f2,pf2,-0.4,1/(10^5),1/(10^5),3000000))
println("msiecznych\n",msiecznych(f2,-0.2,-0.21,1/(10^5),1/(10^5),30000))
