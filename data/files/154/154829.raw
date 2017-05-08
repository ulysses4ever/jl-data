#=Bartłomiej Sadowski =#
include("hilb.jl")
include("matcond.jl")


n=50
c=100000.0
aA=hilb(n)
bA=matcond(n,c)
x= Int64[1:n]
fill!(x,1)
b=aA*x
x_gauss=aA\b
x_tylda=(inv(aA)*b)
println("macierz hilberta:\n",aA)
println("x prawdziwe ",x)
println("b ",b)
println("x_gauss",x_gauss)
println("x_tylda",x_tylda)
println("wskaznik uwarunkowania", cond(aA))
println("rzad macierzy",rank(aA))


b=bA*x
x_gauss=bA\b
x_tylda=(inv(bA)*b)
println("macierz losowa ze wskaznikiem uwaunkowania ",c,"\n",bA)
println("x prawdziwe ",x)
println("b ",b)
println("x_gauss",x_gauss)
println("x_tylda",x_tylda)

println("wskaznik uwarunkowania", cond(bA))
println("rzad macierzy",rank(bA))

