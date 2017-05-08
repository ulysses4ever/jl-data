module BinarySearchTree

export BST, insert!, delete!, search, to_array, minimum, select, median

import Base.size

abstract AbstractNode

immutable EmptyLeaf <: AbstractNode
end

immutable Leaf{T} <: AbstractNode
	value::T
end

immutable Node{T} <: AbstractNode
	value::T
	left_child::AbstractNode
	right_child::AbstractNode
	size::Int64

	Node(value::T, left_child::AbstractNode, right_child::AbstractNode) = new(value, left_child, right_child, size(left_child) + size(right_child) + 1)

end

Node{T}(value::T, left_child::AbstractNode, right_child::AbstractNode) = Node{T}(value, left_child, right_child)


type BST
	head::AbstractNode
	size::Int64
end

BST() = BST(EmptyLeaf(), 0::Int64)

function insert(node::Node, value::Real)
	if value < node.value
		return Node(node.value, insert(node.left_child, value), node.right_child)
	else
		return Node(node.value, node.left_child, insert(node.right_child, value))
	end
	return node
end

function insert(leaf::EmptyLeaf, value::Real)
	return Leaf(value)
end

function insert(leaf::Leaf, value::Real)
	if value < leaf.value
		return Node(leaf.value, Leaf(value), EmptyLeaf())
	else
		return Node(leaf.value, EmptyLeaf(), Leaf(value))
	end
end

function delete(node::Node, value::Real)
	# @bp
	if value < node.value
		return Node(node.value, delete(node.left_child, value), node.right_child)
	elseif value > node.value
		return Node(node.value, node.left_child, delete(node.right_child, value))
	elseif value == node.value
		if node.left_child == EmptyLeaf() && node.right_child != EmptyLeaf() # this works because EmtpyLeaf is a singleton
			return node.right_child
		elseif node.right_child == EmptyLeaf() && node.left_child != EmptyLeaf()
			return node.left_child
		elseif node.right_child == EmptyLeaf() && node.left_child == EmptyLeaf()
			return EmptyLeaf()
		else # neither child is empty
			new_val = minimum(node.right_child)
			return Node(new_val, node.left_child, delete(node.right_child, new_val))
		end
	else
		error("This shouldn't happen")
	end
end

function delete(leaf::Leaf, value::Real)
	if value == leaf.value
		return EmptyLeaf()
	else
		throw(KeyError("Tried to delete wrong value from Leaf"))
	end
end

function delete(leaf::EmptyLeaf, value::Real)
	throw(KeyError("Tried to delete value from EmptyLeaf"))
end

function search(node::Node, value::Real)
	if value == node.value
		return true
	elseif value < node.value
		return search(node.left_child, value)
	else
		return search(node.right_child, value)
	end
end

function search(leaf::Leaf, value::Real)
	return value == leaf.value
end

function search(leaf::EmptyLeaf, value::Real)
	return false
end

function size(node::Node)
	return node.size
end

function size(leaf::Leaf)
	return 1::Integer
end

function size(l::EmptyLeaf)
	return 0::Integer
end

function select(node::Node, k::Integer)
	if k == size(node.left_child) + 1
		return node.value
	elseif k <= size(node.left_child)
		return select(node.left_child, k)
	else
		return select(node.right_child, k - size(node.left_child) - 1)
	end
end

function select(leaf::Leaf, k::Integer)
	if k == 1
		return leaf.value
	else
		throw(KeyError("Select non-1st item from Leaf"))
	end
end

function minimum(node::Node)
	if node.left_child == EmptyLeaf()
		return node.value
	else
		return minimum(node.left_child)
	end
end

function minimum(leaf::Leaf)
	return leaf.value
end

function to_array(node::Node)
	if node.left_child == EmptyLeaf() && node.right_child != EmptyLeaf()
		return [node.value, to_array(node.right_child)]
	elseif node.right_child == EmptyLeaf() && node.left_child != EmptyLeaf()
		return [to_array(node.left_child), node.value]
	else
		return [to_array(node.left_child), node.value, to_array(node.right_child)]
	end
end

function to_array(leaf::Leaf)
	return leaf.value
end


function insert!(tree::BST, value::Real)
	tree.head = insert(tree.head, value)
end

function insert!(tree::BST, values::Vector)
	for value in values
		tree.head = insert(tree.head, value)
	end
end

function delete!(tree::BST, value::Real)
	tree.head = delete(tree.head, value)
end

function delete!(tree::BST, value::Vector)
	for v in value
		delete!(tree, v)
	end
end

function search(tree::BST, value::Real)
	return search(tree.head, value)
end

function to_array(tree::BST)
	return to_array(tree.head)
end

function size(tree::BST)
	return size(tree.head)
end

function select(tree::BST, k::Integer)
	return select(tree.head, k)
end

function median(tree::BST)
	s = size(tree)
	if s % 2 == 0
		return (select(tree, iceil(s / 2)) + select(tree, iceil(s / 2) + 1)) / 2
	else
		return select(tree, s / 2 + 1)
	end
end

function minimum(tree::BST)
	return minimum(tree.head)
end

end