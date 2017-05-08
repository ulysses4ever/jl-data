
##  ON BEST RANK-ONE APPROXIMATIONS OF TENSORS
##  https://github.com/Jutho/TensorOperations.jl/blob/master/src/indexnotation.jl

using TensorOperations, IndexNotation

m = (3,4,5)			#  tensor size 
d = length (m)		#  d-mode tensor
T = rand (m)

x0 = map (rand, m)						# random initial point x0 in S(m) with d "coordinates" -- each itself a vector
x0 = map (x -> x ./ norm(x), x0)		# normalize each coordinate (or dimension) of x
y = x0									# y will store the iteration update of x, as it is computed one dimension at a time

while readline() != "x\n"
	for yi in y println (yi.data) end

	x = ntuple (d, i -> 					# set x to y, also assigning a label to each dimension
		begin
		INDEX = LabelList ([symbol('a' + i - 1)])
		y[i] [INDEX]
		end)

	y = Array (Any, d)
	for i in 1:d
		I = setdiff (1:d, i)
		Z = reduce (*, 1, x[I])				# calculate Z

		INDEX = LabelList (map (i -> symbol('a' + i - 1), 1:d))

		y[i] = T [INDEX] * Z				# assign label to each dimension of T to accomplish the product
		y[i] = scale (y[i], 1.0 / norm (y[i].data))
		end
	end

														for i in 1:d									# list of (d-1) mode tensors ("Z")
															fact = x [cat(1,1:(i-1),(i+1):d)]

															function g(j)
																ll = LabelList ([symbol('a'+j-1)])
																fact[j] [ll]
															end

															fact_typed = ntuple (length (fact), g)

														# maybe use mapreduce instead
															reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)])
															show (reduce (*, fact_typed[1], fact_typed[2:length(fact_typed)]))
															print("\n")

															T [l"a,b,c"] * z

--> but cannot norm(T [l"a,b,c"] * z) due to a type problem

end		


while ...
	y = deepcopy (x)k

s=time()
t=time()
println("elapsed time (sec): ", t-s)














function f(j)
	x = rand (m [j])
	x / norm(x)
	end
x0 = ntuple (d, f)		# random starting point

