include("splay_tree.jl")
using BinarySearchTree

function bench(n::Integer)
	x = 1:n
	x_rand = x + rand(Float64, length(x))*length(x)

	t_low = BST()
	t_high = BST()

	insert!(t_high, x_rand)

	t1 = time()
	for i in 1:(length(x_rand)-1)
		insert!(t_low, x_rand[i])
		delete!(t_high, x_rand[i])
		median(t_low)
		median(t_high)
	end
	t2 = time()
	println(n, ",", t2-t1)
end

n_vals = 1000:100:10000

for n in n_vals
	bench(n)
end
