
##  ON BEST RANK-ONE APPROXIMATIONS OF TENSORS

using TensorOperations, IndexNotation
m = (3,4,5)			#  tensor size 
d = length (m)		#  d-mode tensor
T = rand (m)

function f(j)
	x = rand (m [j])
	x / norm(x)
	end
x0 = ntuple (d, f)		# random starting point

x = x0
for i in 1:d									# list of (d-1) mode tensors ("Z")f
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












