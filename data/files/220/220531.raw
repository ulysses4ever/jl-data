using Distributions

 function jgibbs(N::Integer, thin::Integer)
 mat = Array(Float64,(N,2))
 x = y = 0.
 for i in 1:N
 for j in 1:thin
 x = rand(Gamma(3.,1./(y*y+4.))) #shape/scale
 y = rand(Normal(1./(x+1.),1./sqrt(2.(x+1.))))
 end
 mat[i,1] = x; mat[i,2] = y
 end
 mat
 end
