using Base.Test
include("bst.jl")
using BinarySearchTree

function test_insert_and_search{T}(x::Vector{T}, y::Vector{T})
	t = BST()
	i = 0
	for xi in x
		i += 1
		insert!(t, xi)
		@test size(t) == i
	end
	for xi in x
		@test(search(t, xi))
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


function test_delete{T}(x::Vector{T})
	t = BST()
	insert!(t, x)
	for i in 1:length(x)
		delete!(t, x[i])
		@test !search(t, x[i])
		@test size(t) == length(x) - i
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


test_insert_and_search(rand(1000), rand(1000))
test_insert_vector(rand(1000), rand(1000))
test_min()
test_delete(rand(10))
test_delete_vector(rand(10))

