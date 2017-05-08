require("Gaston")

step(x::Real) = rand()<0.5?x+1:x-1
step{T<:Real}(xs::Vector{T}) = map(step,xs)
step!{T<:Real}(xs::Vector{T}) = map!(step,xs)

N=64
steps=100

xs = zeros(Int,N)

means = [0.0]
vars = [0.0]

for t in 1:steps
  step!(xs)
  m = mean(xs)
  v = var(xs)
  push!(means,m)
  push!(vars,v)
end

Gaston.plot(0:steps,vars,"legend","variance",
            0:steps,0:steps,"legend","linear to t",
            "title", "random walk",
            "xlabel", "t",
            "ylabel", "x^2",
            "box", "top left")

print("press enter key to exit.")
readline(STDIN)

