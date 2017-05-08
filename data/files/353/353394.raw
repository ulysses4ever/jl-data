using Base.Test
include("splay_tree.jl")
using BinarySearchTree

function test_insert_and_search{T}(x::Vector{T}, y::Vector{T})
	t = BST()
	i = 0
	for xi in x
		i += 1
		insert!(t, xi)
		@test search(t, xi)
		@test size(t) == i
	end
	for xi in x
		@test search(t, xi)
	end
	for yi in y
		@test(!search(t, yi))
	end
end

function test_insert_vector(x::Vector, y::Vector)
	t = BST()
	insert!(t, x)
	@test size(t) == length(x)
	for xi in x
		@test search(t, xi)
	end
	for yi in y
		@test(!search(t, yi))
	end
end

function test_delete_duplicates{T}(x::Vector{T})
	t = BST()
	y = [x, x]
	insert!(t, y)
	for i in 1:length(x)
		delete!(t, y[i])
		@test search(t, y[i])
		@test size(t) == length(y) - i
		@test size(t) == length(to_array(t.head))
	end
	for i in (length(x)+1):(length(y) - 1)
		delete!(t, y[i])
		@test !search(t, y[i])
		@test size(t) == length(y) - i
		@test size(t) == length(to_array(t.head))

	end
end


function test_delete{T}(x::Vector{T})
	t = BST()
	insert!(t, x)
	for i in 1:length(x)
		delete!(t, x[i])
		@test !search(t, x[i])
		@test size(t) == length(x) - i
		if size(t) > 0
			@test size(t) == length(to_array(t.head))
		end
		for j in i+1:length(x)
			@test(search(t, x[j]))
		end

	end
end

function test_delete_vector{T}(x::Vector{T})
	t = BST()
	insert!(t, x)
	@test size(t) == length(x)
	delete!(t, x[length(x)/2:length(x)])
	@test size(t) == length(x) / 2 - 1
	for xi in x[length(x)/2:length(x)]
		@test !search(t, xi)
	end
end

function test_min()
	for i in 1:100
		t = BST()
		x = rand(100)
		insert!(t, x)
		@test minimum(t) == Base.minimum(x)
	end
end

function test_select()
	for i in 1:100
		t = BST()
		x = rand(100)
		insert!(t, x)
		xs = sort(x)
		for _ in 1:10
			j = rand(1:10)
			@test select(t, j) == xs[j]
		end
	end
end

function test_median()
	for i in 1:10
		t = BST()
		x = rand(1000)
		x = [x, x]
		insert!(t, x)
		@test_approx_eq median(t) Base.median(x)
		t = BST()
		x = rand(1001)
		insert!(t, x)
		@test_approx_eq median(t) Base.median(x)
	end
end

srand(123456789)
test_insert_and_search(rand(1000), rand(1000))
test_insert_vector(rand(1000), rand(1000))
test_select()
test_delete(rand(1000))
test_delete_duplicates(rand(1000))
test_delete_vector(rand(1000))
test_median()
