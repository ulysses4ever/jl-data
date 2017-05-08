##  ON BEST RANK-ONE APPROXIMATIONS OF TENSORS (arXiv 1112.5914v3)
##  alternating singular value decomposition method
##  using Julia module: https://github.com/Jutho/TensorOperations.jl
##
##  to run from session:
##  cd("~/Desktop/-MATERIEL/2014-15-first/learning-julia/")
##  evalfile ("tensor-approx-asvd.jl")
##
##  ADJUSTABLE:

m = (3,4,5)							#  tensor size 
d = length (m)						#  d-mode tensor
max_iter = 10						#  limit iterations
signif = 5							#  digits of approximation to print

####################################################################################

using TensorOperations, IndexNotation

T = rand (m)

x0 = map (rand, m)						#  random initial point x0 with d "vector coordinates"
x0 = map (x -> x ./ norm(x), x0)		#  normalize each coordinate (or dimension), so x0 lies in S(m)

x = ntuple (d, i -> 					#  x will store the update, as it is computed one dimension at a time
	begin								#  set x to x0, also labeling to each dimension
	INDEX = LabelList ([symbol('a' + i - 1)])
	x0[i] [INDEX]
	end)

println ("initial point:")
for xi in x println (round (xi.data, signif)) end
println ("")

cmd = ""
iter = 0
t_tot = 0
while iter < max_iter && cmd != "q\n"
	s = time()

# --> need to devise reordering of pairs here

	pairs = [p for p in combinations(1:d,2)]		#  take all pairs (i,j) in an evenly distributed order		

	for (i,j) in pairs								#  for each pair...
		I = setdiff (1:d, (i,j))
		Z = reduce (*, 1, x[I])						#  ...calculate Z

		INDEX = LabelList (map (i -> symbol('a' + i - 1), 1:d))

		m = T [INDEX] * Z							#  label each dimension of T to accomplish the product TxZ
		(U,S,V) = svd (m.data)						#  take SVD of the resulting 2-mode tensor (matrix)

		x[i].data = U[:,1]							#  iteration consists in replacement of the i and j direction
		x[j].data = V[:,1]							#  by the first left and right singular vectors.
		end

	for xi in x println (round (xi.data, signif)) end		#  report time and new value
	t = time()
	println("computation time (sec): ", round (t-s, 2))
	t_tot += t-s

	if (cmd != "c\n") cmd = readline() 
	else print ('\n') end
	iter += 1
	end

println("total computation time (sec): ", round (t_tot))
