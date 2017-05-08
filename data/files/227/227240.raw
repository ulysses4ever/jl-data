##  ON BEST RANK-ONE APPROXIMATIONS OF TENSORS (arXiv 1112.5914v3)
##  alternating least-squares method
##  using Julia module: https://github.com/Jutho/TensorOperations.jl
##
##  to run from session:
##  cd("~/Desktop/-MATERIEL/2014-15-first/learning-julia/")
##  evalfile ("tensor-approx-als.jl")
##
##  ADJUSTABLE:

m = (3,4,5,3)						#  tensor size m
d = length (m)						#  d-mode tensor
max_iter = 8						#  limit iterations
signif = 7							#  digits of approximation to print

####################################################################################

using TensorOperations, IndexNotation

T = rand (m)

x0 = map (rand, m)						#  random initial point x0 with d "vector coordinates"
x0 = map (x -> x ./ norm(x), x0)		#  normalize each coordinate (or dimension), so x0 lies in S(m)
y = x0									#  y will store the update, as it is computed one dimension at a time

println ("initial point:")
for yi in y println (round (yi, signif)) end
println ("")

cmd = ""
iter = 0
t_tot = 0
while iter < max_iter && cmd != "q\n"
	s = time()

	x = ntuple (d, i ->						#  set x to y, also labeling each dimension
		begin
		INDEX = LabelList ([symbol('a' + i - 1)])
		y[i] [INDEX]
		end)

	y = Array (Any, d)						#  commpute each new vector coordinate of y
	for i in 1:d
		I = setdiff (1:d, i)
		Z = reduce (*, 1, x[I])				#  calculate Z 
											#  and label each dimension of T to accomplish the product
		INDEX = LabelList (map (i -> symbol('a' + i - 1), 1:d))

		y[i] = T [INDEX] * Z
		y[i] = scale (y[i], 1.0 / norm (y[i].data))		#  normalize to remain in S(m)
		end

	for yi in y println (round (yi.data, signif)) end		#  report time and new value
	t = time()
	println("computation time (sec): ", round (t-s, 2))
	t_tot += t-s
	
	if (cmd != "c\n") cmd = readline() 
	else print ('\n') end
	iter += 1
	end

println("total computation time (sec): ", round (t_tot, 1))
