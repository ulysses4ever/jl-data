using StatsBase
function ludo()
finalSquare = 100
got = collect(1:finalSquare)
got[collect([1,4,9,28,21,51,80,71,98,95,93,87,64,
62,54,17])]=collect([18,14,31,84,42,67,100,91,79
,75,73,24,60,19,34,7])

values=Int64[]
square = 0
diceRoll = 0
n=0
while diceRoll != 6
  n +=1
  diceRoll=wsample(collect(1:6),[.25,.35,.05,.05,.15,.15],1)[1]#rand(1:6,1)[1]
  push!(values,Int64(diceRoll))#while body
end
while ((square != finalSquare) && (n<1000)) 
  diceRoll=wsample(collect(1:6),[.25,.35,.05,.05,.15,.15],1)[1]#rand(1:6,1)[1]
  push!(values,Int64(diceRoll))
  n+=1
  if (square+diceRoll) > finalSquare
    continue;
  else
  square += diceRoll
  square = got[square]
  #println("$diceRoll \t $square")
end
end
c=fill(0,7)
[c[i]=length(values[values.==i]) for i in collect(1:6)]
c[7]=n
 c'
  end
print("Game over!")
d=ludo()
for i in 1:500
  c=ludo()
  all(c.>0)?c:continue
    d=vcat(d,c)
    end 
using DataFrames
dice=DataFrame(y1=d[:,1],y2=d[:,2],y3=d[:,3],y4=d[:,4],y5=d[:,5],
  y6=d[:,6],x=d[:,7])
  println("$dice") 
beta(x::Array{Float64, 2},y::Array{Float64, 1})=inv(x'*x)*(x'*y)
convert(Array{Float64,2},dice)
X=[fill(1.0,length(dice[:x])) dice[:x]]
for u in [:y1,:y2,:y3,:y4,:y5]
y=map(log,dice[u]./dice[:y6])
println("$(beta(X,convert(Array{Float64,1},y)))")
end
    