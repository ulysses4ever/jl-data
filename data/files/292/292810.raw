module BinarySearchTree

export BST, insert!, insert_many!, search

abstract AbstractNode

type EmptyLeaf <: AbstractNode
end

type Leaf{T} <: AbstractNode
	value::T
end

type Node{T} <: AbstractNode
	value::T
	left_child::AbstractNode
	right_child::AbstractNode
end

type BST
	head::AbstractNode
	size::Int64

end

BST() = BST(EmptyLeaf(), 0::Int64)

function insert{T}(node::Node{T}, value::T)
	if value < node.value
		node.left_child = insert(node.left_child, value)
	else
		node.right_child = insert(node.right_child, value)
	end
	return node
end

function insert{T}(leaf::EmptyLeaf, value::T)
	return Leaf{T}(value)
end

function insert{T}(leaf::Leaf{T}, value::T)
	if value < leaf.value
		return Node{T}(leaf.value, Leaf{T}(value), EmptyLeaf())
	else
		return Node{T}(leaf.value, EmptyLeaf(), Leaf{T}(value))
	end
end

function search{T}(node::Node{T}, value::T)
	if value == node.value
		return true
	elseif value < node.value
		return search(node.left_child, value)
	else
		return search(node.right_child, value)
	end
end

function search{T}(leaf::Leaf{T}, value::T)
	return value == leaf.value
end

function search{T}(leaf::EmptyLeaf, value::T)
	return false
end


function insert!{T}(tree::BST, value::T)
	tree.head = insert(tree.head, value)
	tree.size += 1
end

function insert_many!{T}(tree::BST, values::Vector{T})
	for value in values
		tree.head = insert(tree.head, value)
		tree.size += 1
	end
end

function delete!{T}(tree::BST, value::T)

end

function search{T}(tree::BST, value::T)
	return search(tree.head, value)
end

end