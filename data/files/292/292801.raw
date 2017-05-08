module BinarySearchTree

export BST, insert!, delete!, search, to_array, minimum, select, median

import Base: size, median, insert!, delete!

using Debug

abstract AbstractNode

immutable EmptyLeaf <: AbstractNode
end

# immutable Leaf{T} <: AbstractNode
# 	value::T
# end

type Node{T} <: AbstractNode
	value::T
	left_child::AbstractNode
	right_child::AbstractNode
	size::Int64
	count::Int64

	Node(value::T, left_child::AbstractNode, right_child::AbstractNode) = new(value, left_child, right_child, size(left_child) + size(right_child) + 1, 1)

end

Node{T}(value::T, left_child::AbstractNode, right_child::AbstractNode) = Node{T}(value, left_child, right_child)

type BST
	head::AbstractNode
end

BST() = BST(EmptyLeaf())

function splay!(root::Node, value::Real)

	function insert_left(node::AbstractNode)
		if left == EmptyLeaf()
			left = node
			return
		end
		current_node = left
		while current_node.right_child != EmptyLeaf()
			current_node.size += size(node)
			current_node = current_node.right_child
		end
		current_node.size += size(node)
		current_node.right_child = node
	end

	function insert_right(node::AbstractNode)
		if right == EmptyLeaf()
			right = node
			return
		end
		current_node = right
		while current_node.left_child != EmptyLeaf()
			current_node.size += size(node)
			current_node = current_node.left_child
		end
		current_node.size += size(node)
		current_node.left_child = node
	end

	function zig_zig!()
		new_middle = middle.left_child.left_child
		middle.left_child.size -= size(new_middle)
		middle.size -= size(new_middle)
		middle.left_child.left_child = EmptyLeaf()
		insert_right(rotate_right(middle))
		middle = new_middle
	end

	function zig!()
		new_middle = middle.left_child
		middle.size -= size(new_middle)
		middle.left_child = EmptyLeaf()
		insert_right(middle)
		middle = new_middle
	end

	function zag_zag!()
		old_size = size(left) + size(right) + size(middle)

		new_middle = middle.right_child.right_child
		middle.right_child.size -= size(new_middle)
		middle.size -= size(new_middle)
		middle.right_child.right_child = EmptyLeaf()
		insert_left(rotate_left(middle))
		middle = new_middle

	end

	function zag!()
		old_size = size(left) + size(right) + size(middle)

		new_middle = middle.right_child
		middle.size -= size(new_middle)
		middle.right_child = EmptyLeaf()
		insert_left(middle)

		middle = new_middle

	end

	function rotate_right(node::Node)

		pivot = node.left_child
		pivot.size = node.size

		node.left_child = pivot.right_child
		node.size = size(node.left_child) + size(node.right_child) + node.count

		pivot.right_child = node

		return pivot
	end

	function rotate_left(node::Node)

		pivot = node.right_child
		pivot.size = node.size

		node.right_child = pivot.left_child
		node.size = size(node.left_child) + size(node.right_child) + node.count

		pivot.left_child = node

		return pivot
	end

	function max(node::Node)
		if node.right_child==EmptyLeaf()
			return node.value
		end
		return max(node.right_child)
	end

	# max(leaf::EmptyLeaf) = Inf
	# min(leaf::EmptyLeaf) = -Inf


	function min(node::Node)
		if node.left_child==EmptyLeaf()
			return node.value
		end
		return min(node.left_child)
	end

	middle = root
	left = EmptyLeaf()
	right = EmptyLeaf()

	while true

		if value == middle.value
			left_child = middle.left_child
			right_child = middle.right_child
			insert_left(left_child)
			insert_right(right_child)
			middle.left_child = left
			middle.right_child = right
			middle.size += size(left) + size(right) - size(left_child) - size(right_child)

			return middle
		elseif value < middle.value
			if middle.left_child == EmptyLeaf()
				right_child = middle.right_child
				insert_right(right_child)
				middle.left_child = left
				middle.right_child = right
				middle.size += size(left) + size(right) - size(right_child)

				return middle
			elseif middle.left_child.left_child != EmptyLeaf() && value < middle.left_child.value
				zig_zig!()
			else
				zig!()

			end
		else # value > middle.value
			if middle.right_child == EmptyLeaf()
				left_child = middle.left_child
				insert_left(left_child)
				middle.left_child = left
				middle.right_child = right
				middle.size += size(left) + size(right) - size(left_child)
				return middle
			elseif middle.right_child.right_child != EmptyLeaf() && value > middle.right_child.value
				zag_zag!()

			else
				zag!()

			end
		end
	end
end

function splay_os!(root::Node, stat::Integer)

	function insert_left(node::AbstractNode)
		if left == EmptyLeaf()
			left = node
			target -= size(node)
			return
		end
		current_node = left
		while current_node.right_child != EmptyLeaf()
			current_node.size += size(node)
			current_node = current_node.right_child
		end
		current_node.size += size(node)
		current_node.right_child = node
		target -= size(node)
	end

	function insert_right(node::AbstractNode)
		if right == EmptyLeaf()
			right = node
			return
		end
		current_node = right
		while current_node.left_child != EmptyLeaf()
			current_node.size += size(node)
			current_node = current_node.left_child
		end
		current_node.size += size(node)
		current_node.left_child = node
	end

	function zig_zig!()
		old_size = size(left) + size(right) + size(middle)
		new_middle = middle.left_child.left_child
		middle.left_child.size -= size(new_middle)
		middle.size -= size(new_middle)
		middle.left_child.left_child = EmptyLeaf()
		insert_right(rotate_right(middle))
		middle = new_middle

	end

	function zig!()
		old_size = size(left) + size(right) + size(middle)

		new_middle = middle.left_child
		middle.size -= size(new_middle)
		middle.left_child = EmptyLeaf()
		insert_right(middle)
		middle = new_middle


	end

	function zag_zag!()
		old_size = size(left) + size(right) + size(middle)

		new_middle = middle.right_child.right_child
		middle.right_child.size -= size(new_middle)
		middle.size -= size(new_middle)
		middle.right_child.right_child = EmptyLeaf()
		insert_left(rotate_left(middle))
		middle = new_middle


	end

	function zag!()
		old_size = size(left) + size(right) + size(middle)

		new_middle = middle.right_child
		middle.size -= size(new_middle)
		middle.right_child = EmptyLeaf()
		insert_left(middle)
		middle = new_middle


	end

	function rotate_right(node::Node)

		pivot = node.left_child
		pivot.size = node.size

		node.left_child = pivot.right_child
		node.size = size(node.left_child) + size(node.right_child) + node.count

		pivot.right_child = node

		return pivot
	end

	function rotate_left(node::Node)

		pivot = node.right_child
		pivot.size = node.size

		node.right_child = pivot.left_child
		node.size = size(node.left_child) + size(node.right_child) + node.count

		pivot.left_child = node

		return pivot
	end

	function max(node::Node)
		if node.right_child==EmptyLeaf()
			return node.value
		end
		return max(node.right_child)
	end

	# max(leaf::EmptyLeaf) = Inf
	# min(leaf::EmptyLeaf) = -Inf


	function min(node::Node)
		if node.left_child==EmptyLeaf()
			return node.value
		end
		return min(node.left_child)
	end

	middle = root
	left = EmptyLeaf()
	right = EmptyLeaf()

	target = copy(stat)
	while true

		if size(middle.left_child) >= target
			if middle.left_child != EmptyLeaf() && size(middle.left_child.left_child) >= target
				zig_zig!()
			else
				zig!()
			end
		elseif size(middle.left_child) + middle.count < target
			if middle.right_child != EmptyLeaf() && size(middle.left_child) + middle.count + size(middle.right_child.left_child) + middle.right_child.count < target
				zag_zag!()
			else
				zag!()
			end
		else
			left_child = middle.left_child
			right_child = middle.right_child
			insert_left(left_child)
			insert_right(right_child)
			middle.left_child = left
			middle.right_child = right
			middle.size += size(left) + size(right) - size(left_child) - size(right_child)
			return middle
		end
	end
end


# function size(node::Node)
# 	return 1 + size(node.left_child) + size(node.right_child)
# end

# function size(l::EmptyLeaf)
# 	return 0::Integer
# end

function size(node::Node)
	return node.size
end

function size(l::EmptyLeaf)
	return 0::Integer
end


function to_array(node::Node)
	if node.left_child == EmptyLeaf() && node.right_child != EmptyLeaf()
		return [ones(node.count) * node.value, to_array(node.right_child)]
	elseif node.right_child == EmptyLeaf() && node.left_child != EmptyLeaf()
		return [to_array(node.left_child), ones(node.count) * node.value]
	elseif node.left_child == EmptyLeaf() && node.right_child == EmptyLeaf()
		return [ones(node.count) * node.value]
	else
		return [to_array(node.left_child), ones(node.count) * node.value, to_array(node.right_child)]
	end
end


function insert!(tree::BST, value::Real)
	if tree.head == EmptyLeaf()
		tree.head = Node(value, EmptyLeaf(), EmptyLeaf())
		return
	end

	old_size = size(tree.head)
	tree.head = splay!(tree.head, value)


	if tree.head.value < value
		left_child = tree.head
		right_child = tree.head.right_child
		left_child.size -= size(right_child)
		left_child.right_child = EmptyLeaf()
		new_head = Node(value, left_child, right_child)
		tree.head = new_head
	elseif tree.head.value > value
		right_child = tree.head
		left_child = tree.head.left_child
		right_child.size -= size(left_child)
		tree.head.left_child = EmptyLeaf()

		new_head = Node(value, left_child, right_child)
		tree.head = new_head
	elseif tree.head.value == value
		tree.head.size += 1
		tree.head.count += 1
	end


end

function insert!(tree::BST, values::Vector)
	for value in values
		insert!(tree, value)
	end
end

function check_size(node::Node)
	return (size(node) == length(to_array(node))) && check_size(node.left_child) && check_size(node.right_child)
end

function check_size(leaf::EmptyLeaf)
	return true
end

function delete!(tree::BST, value::Real)
	old_size = size(tree.head)
	tree.head = splay!(tree.head, value)

	if tree.head.value != value
		throw(ArgumentError("Tried to delete value not in tree"))
	end
	# println(tree.head.count)
	if tree.head.count > 1
		tree.head.size -= 1
		tree.head.count -= 1
	else
		if tree.head.right_child != EmptyLeaf()
			# splay minimum of right sub-tree to the top
			deleted_node = tree.head
			tree.head = splay_os!(deleted_node.right_child, 1)

			tree.head.left_child = deleted_node.left_child
			tree.head.size += size(deleted_node.left_child)

		else
			tree.head = tree.head.left_child
			
		end
	end
end

function delete!(tree::BST, value::Vector)
	for v in value
		delete!(tree, v)
	end
end

function search(tree::BST, value::Real)
	if tree.head == EmptyLeaf()
		return false
	end
	old_size = size(tree.head)
	tree.head = splay!(tree.head, value)

	return (value == tree.head.value)
end

function size(tree::BST)
	return size(tree.head)
end

function select(tree::BST, k::Integer)
	if (tree.head == EmptyLeaf())
		throw(ArgumentError("Cannot find median of empty tree"))
	end
	tree.head = splay_os!(tree.head, k)
	return tree.head.value
end

function median(tree::BST)
	s = size(tree)
	if s % 2 == 0
		return (select(tree, iceil(s / 2)) + select(tree, iceil(s / 2) + 1)) / 2
	else
		return select(tree, ifloor(s / 2) + 1)
	end
end

end