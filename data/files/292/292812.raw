module BinarySearchTree

export BST, insert!, delete!, search, to_array, minimum

using Debug

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

function delete{T}(node::Node{T}, value::T)
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

function delete{T}(leaf::Leaf{T}, value::T)
	if value == leaf.value
		return EmptyLeaf()
	else
		throw(KeyError("Tried to delete wrong value from Leaf"))
	end
end

function delete{T}(leaf::EmptyLeaf, value::T)
	throw(KeyError("Tried to delete value from EmptyLeaf"))
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

function minimum{T}(node::Node{T})
	if node.left_child == EmptyLeaf()
		return node.value
	else
		return minimum(node.left_child)
	end
end

function minimum{T}(leaf::Leaf{T})
	return leaf.value
end

function to_array{T}(node::Node{T})
	if node.left_child == EmptyLeaf() && node.right_child != EmptyLeaf()
		return [node.value, to_array(node.right_child)]
	elseif node.right_child == EmptyLeaf() && node.left_child != EmptyLeaf()
		return [to_array(node.left_child), node.value]
	else
		return [to_array(node.left_child), node.value, to_array(node.right_child)]
	end
end

function to_array{T}(leaf::Leaf{T})
	return leaf.value
end


function insert!{T}(tree::BST, value::T)
	tree.head = insert(tree.head, value)
	tree.size += 1
end

function insert!{T}(tree::BST, values::Vector{T})
	for value in values
		tree.head = insert(tree.head, value)
		tree.size += 1
	end
end

function delete!{T}(tree::BST, value::T)
	tree.head = delete(tree.head, value)
	tree.size = tree.size - 1
end

function delete!(tree::BST, value::Vector)
	for v in value
		delete!(tree, v)
	end
end

function search{T}(tree::BST, value::T)
	return search(tree.head, value)
end

function to_array(tree::BST)
	return to_array(tree.head)
end

function minimum(tree::BST)
	return minimum(tree.head)
end

end