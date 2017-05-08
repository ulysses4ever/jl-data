using Base.Test
include("bst.jl")
using BinarySearchTree

function test_insert_and_search{T}(x::Vector{T}, y::Vector{T})
	t = BST()
	for xi in x
		insert!(t, xi)
	end
	for xi in x
		@test(search(t, xi))
	end
	for yi in y
		@test(!search(t, yi))
	end
	return true
end

function test_size(n)
	t = BST()
	x = rand(n)
	insert_many!(t, x)
	@test(t.size == n)
end

test_insert_and_search(rand(10), rand(10))
test_insert_and_search(rand(100), rand(100))
test_insert_and_search(rand(1000), rand(1000))
test_insert_and_search(rand(10000), rand(10000))

test_size(10)
test_size(100)
test_size(1000)
test_size(10000)

