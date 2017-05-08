module RedBlackTrees

# # # # # # # # # # # # # # # # # # # # # # # # # # #
#
## Red Black balanced tree library ##
# 
#   > Created (Julienne Walker): August 23, 2003
#   > Modified (Julienne Walker): March 14, 2008
#   > Julia port (Pierre-Yves Gérardy): January 2014
# 
# This code is in the public domain. Anyone may
# use it or change it in any way that they see
# fit. The author assumes no responsibility for 
# damages incurred through use of the original
# code or any variations thereof.
# 
# It is requested, but not required, that due
# credit is given to the original author and
# anyone who has modified the code through a
# header comment, such as this one.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # #
#
## Notes regarding the Julia version: ##
#
# This a straight port of the original, including
# comments. The core functions have been translated
# line by line.
#
# * We use a small trick to keep the branchless
# child dispatch found in the original, which
# is based on 0-indexed arrays and the conflation
# of boolean and ints in C. 
#   Like the original, we use an array whose first
# and second elements are respectively the left and
# right node. 
#  In order to correct for the fact that Julia arrays 
# are 1-indexed, we use `(cmp(x,y) + 3) >> 1` and 
# `int(boolean) + 1` as indices. This should help
# the branch predictor of the CPU.
#
# * `jsw_rbdelete()` is not needed in Julia thanks to
# the garbage collector. It has thus been
# omitted.
#
# * the following functions have been renamed to conform to
# the Julia idiom.
#
#   * `jsw_rbfind()`   -> `Base.in()`
#   * `jsw_rbinsert()` -> `Base.push!()`
#   * `jsw_rberase()`  -> `Base.delete!()`
#   * `jsw_rb_assert`  -> `isvalid()`
#   * `jsw_rb_size`    -> `Base.length()`
#                      -> `Base.size()`
#
# * The iterators have been reworked to conform to the 
# Julia iterator protocol.
#  
# # # # # # # # # # # # # # # # # # # # # # # # # #

import Base.in, Base.push!, Base.delete!, 
  Base.length, Base.size,
  Base.start, Base.done, Base.next,
  Base.show

export RedBlackTree

const leaf = nothing

type RBNode{T}
  # tree::RedBlackTree{T}
  data::T
  red::Bool
  link::Array{Union(Nothing, RBNode{T}), 1}
end

typealias RBLNode{T} Union(Nothing, RBNode{T})

BNode{T}(data::T) = RBNode{T}(data, false, link(T))
RNode{T}(data::T) = RBNode{T}(data, true, link(T))

type DummyNode{T}
  data::Int
  red::Bool
  link::Array{RBLNode{T}, 1}
  DummyNode() = new(0, false, link(Int))
end

type RedBlackTree{T}
  root::RBLNode{T}
  size::Int
  # first::RBLNode{T}
  # last::RBLNode{T}
end

RedBlackTree(T::DataType) = RedBlackTree{T}(leaf, 0)

typealias RedblackTree RedBlackTree

abstract Direction
immutable Forward <: Direction; tree::RedBlackTree; end
immutable Backward <: Direction; tree::RedBlackTree; end

const left = 1
const right = 2

const opposite = (right, left) # opposite direction.

macro bool2side(b) :( int($(esc(b))) + 1 )  end
macro diff2side(n) :( ($(esc(n)) + 3) >> 1 ) end

link(T::Type) = RBLNode{T}[leaf, leaf]

# pseudo-pointer: don = Done(); don.e == false # :-)
type Done; e::Bool; Done() = new(false); end

# ???
copy(x) = x

# <summary>
# Checks the color of a red black node
# <summary>
# <param name="root">The node to check</param>
# <returns>`true` for a red node, `false` for a black node</returns>
isred(node::RBNode) = node.red
isred(::Nothing) = false

# <summary>
# Performs a single red black rotation in the specified direction
# This function assumes that all nodes are valid for a rotation
# <summary>
# <param name="root">The original root to rotate around</param>
# <param name="dir">The direction to rotate (0 = left, 1 = right)</param>
# <returns>The new root ater rotation</returns>
# <remarks>For jsw_rbtree.c internal use only</remarks>
function single_rotation(root::RBNode, dir::Int)
  other = opposite[dir]
  save = root.link[other]

  root.link[other] = save.link[dir]
  save.link[dir] = root
  root.red = true
  save.red = false

  save
end

# <summary>
# Performs a double red black rotation in the specified direction
# This function assumes that all nodes are valid for a rotation
# <summary>
# <param name="root">The original root to rotate around</param>
# <param name="dir">The direction to rotate (0 = left, 1 = right)</param>
# <returns>The new root after rotation</returns>
# <remarks>For jsw_rbtree.c internal use only</remarks>
function double_rotation(root::RBNode, dir::Int)
  other = opposite[dir]
  root.link[other] = single_rotation(root.link[other], other)
  single_rotation(root, dir)
end


# <summary>
# Search for a copy of the specified
# node data in a red black tree
# <summary>
# <param name="tree">The tree to search</param>
# <param name="value">The value to search for</param>
# <returns>`true` or `false` depending on success</returns>
function in{T}(data::T, tree::RedBlackTree{T})
  it = tree.root
  while it != leaf
    diff = cmp(data, it.data)
    if diff == 0
      return true
    end
    it = it.link[@diff2side diff]
  end
  return false
end

in{T}(::Any, tree::RedBlackTree{T}) = false


# <summary>
# Search for a copy of the specified
# node data in a red black tree
# <summary>
# <param name="tree">The tree to search</param>
# <param name="data">The data value to search for</param>
# <returns>
# The data value stored in the tree,
# or `nothing` if no data could be found
# </returns>
function Base.push!{T}(tree::RedBlackTree{T}, data::T)
  if tree.root == leaf
    # We have an empty tree; attach the
    # new node directly to the root
    tree.root = BNode(copy(data))
    tree.size = 1
  else
    # Set up our helpers
    # g, t: Grandparent & parent
    # p, q: Iterator & parent
    # head: False tree root
    head = t = DummyNode{T}()
    dir = last = left
    g = p = leaf;
    q = t.link[right] = tree.root;

    # Search down the tree for a place to insert
    while true
      if q == leaf
        # Insert a new node at the first null child
        p.link[dir] = q = RNode(copy(data))
        tree.size += 1

      elseif isred(q.link[left]) && isred(q.link[right]) 
        # Simple red violation: color flip
        q.red = true
        q.link[left].red = false
        q.link[right].red = false
      end

      if isred(q) && isred(p)
        # Hard red violation: rotations necessary
        dir2 = @bool2side (t.link[right] === g)

        if q == p.link[last]
          t.link[dir2] = single_rotation(g, opposite[last])
        else
          t.link[dir2] = double_rotation(g, opposite[last])
        end
      end

      # Stop working if we inserted a node. This
      # check also disallows duplicates in the tree
      diff = cmp(data, q.data)
      if diff == 0; break; end

      last = dir
      dir = @diff2side(diff)

      # Move the helpers down
      if g != leaf
        t = g
      end

      (g, p, q) = (p, q, q.link[dir])
    end

    # Update the root (it may be different)
    tree.root = head.link[right]
  end

  # Make the root black for simplified logic
  tree.root.red = false

  return data
end

# <summary>
# Remove a node from a red black tree
# that matches the user-specified data
# <summary>
# <param name="tree">The tree to remove from</param>
# <param name="value">The data value to search for</param>
# <returns>
# true if the value was removed successfully,
# false if the removal failed for any reason
# </returns>
# <remarks>
# The most common failure reason should be
# that the data was not found in the tree
# </remarks>
function delete!{T}(tree::RedBlackTree{T}, data::T)
  if tree.root != leaf
    head = DummyNode{T}() # False tree root
    f = leaf                  # Found item
    dir = right;

    # Set up our helpers (q, p, g)
    q = head
    g = p = leaf
    q.link[right] = tree.root

    # Search and push a red node down
    # to fix red violations as we go
    while q.link[dir] != leaf
      last = dir;

      # Move the helpers down
      (g, p, q) = (p, q, q.link[dir])
      diff = cmp (data, q.data)
      if diff == 0 ;; f = q ;; end
      dir = @diff2side(diff)

      # Save the node with matching data and keep
      # going; we'll do removal tasks at the end

      # Push the red node down with rotations and color flips
      if !(isred(q) || isred(q.link[dir]))
        if isred(q.link[opposite[dir]])
          p = p.link[last] = single_rotation(q, dir)
        elseif !isred(q.link[opposite[dir]])
          s = p.link[opposite[last]];

          if s != leaf
            if !( isred(s.link[opposite[last]]) || isred(s.link[last]) )
              # Color flip
              p.red = false
              s.red = true
              q.red = true
            else
              dir2 = @bool2side (g.link[right] == p)

              if isred(s.link[last])
                g.link[dir2] = double_rotation (p, last)
              elseif isred(s.link[opposite[last]]) 
                g.link[dir2] = single_rotation ( p, last )
              end

              # Ensure correct coloring
              q.red = g.link[dir2].red = true
              g.link[dir2].link[left].red = false
              g.link[dir2].link[right].red = false
            end
          end
        end
      end
    end

    # Replace and remove the saved node
    if f != leaf
      f.data = q.data;
      p.link[@bool2side (p.link[right] == q)] =
        q.link[@bool2side (q.link[left] == leaf)];
    end

    # Update the root (it may be different)
    tree.root = head.link[right];

    # Make the root black for simplified logic
    if tree.root != leaf
      tree.root.red = false
    end

    tree.size -= 1
  end
  data
end

# <summary>
# Gets the number of nodes in a red black tree
# <summary>
# <param name="tree">The tree to calculate a size for</param>
# <returns>The number of nodes in the tree.</returns>
Base.length(tree::RedBlackTree) = tree.size

# <summary>
# Gets the number of nodes in a red black tree
# <summary>
# <param name="tree">The tree to calculate a size for</param>
# <returns>A singleton holding the number of nodes in the tree.</returns>
Base.size(tree::RedBlackTree) = (tree.size,)

## Iterators

# We use a stateful iterator, and slightly abuse the iterator 
# protocol in that it `done()` actually advances the pointer
# (it has to in order to do its job, anyway) and next just
# just returns the 


type RBTrav{T}
  tree::RedBlackTree{T}               # Paired tree
  it::RBLNode{T} # Current node
  path::Array{RBLNode{T},1} # Traversal path
  top::Uint                     # Top of traversal path stack
  function RBTrav(tree::RedBlackTree) 
    # println("Log $(int(ceil(log(2,tree.size + 1))) + 1)")
    len = int(ceil(log(2,tree.size + 1))) * 2
    N = new(
      tree, tree.root,
      Array(
        RBLNode{T},
        len,
      ), 0
    )
    for i = 1:len; N.path[i] = RNode(1000) end
    N
  end
end

# <summary>
# Initialize a traversal object. The user-specified
# direction determines whether to begin traversal at the
# smallest or largest valued node
# <summary>
# <param name="tree">The tree that the object will be attached to</param>
# <param name="dir">
# The direction to traverse (0 = ascending, 1 = descending)
# </param>
# <returns>A pointer to the smallest or largest data value</returns>
# <remarks>For RedBlackTrees.jl internal use only</remarks>

function _start{T}(tree::RedBlackTree{T}, dir::Int)
  RBTrav{T}(tree)
end

# <summary>
# Traverse a red black tree in the user-specified direction
# <summary>
# <param name="trav">The initialized traversal object</param>
# <param name="dir">
# The direction to traverse (0 = ascending, 1 = descending)
# </param>
# <returns>
# A pointer to the next data value in the specified direction
# </returns>
# <remarks>For RedBlackTrees.jl internal use only</remarks>
function move(trav::RBTrav, dir::Int)
  otherdir = opposite[dir]
  # println("trav.top: $(trav.top)")
  # sleep(0.2)
  # first iteration
  if trav.top == 0
    # println("First Iteration")
    trav.top = 1
    if trav.it != leaf
      # println("Not Leaf $(trav.it.data)")
      while trav.it.link[otherdir] != leaf
        # println("Not Leaf loop $(trav.it.data), $(trav.it.link[otherdir].data)")
        trav.path[trav.top] = trav.it
        trav.top += 1
        trav.it = trav.it.link[otherdir]
      end
      # println("$(map(tostr, trav.path)) TOP: trav.top")
    else println("leaf") end
  else
    otherdir = opposite[dir]
    if trav.it.link[dir] != leaf
      # Continue down this branch
      # println("down forward $(trav.it.data)/$(trav.it.link[dir].data)")
      trav.path[trav.top] = trav.it
      trav.top += 1
      trav.it = trav.it.link[dir]

      while trav.it.link[otherdir] != leaf
        # println("donw backwards  $(trav.it.data)/$(trav.it.link[dir].data)")
        trav.path[trav.top] = trav.it
        trav.top += 1
        trav.it = trav.it.link[otherdir];
      end
    else
      # Move to the next branch
      # println("move to the next branch +/+ $(tostr(trav.it))")
      local last

      while true
        if trav.top == 1
          trav.it = leaf
          break
        end

        last = trav.it
        trav.top -= 1
        # println("TOP: $(trav.top)")
        trav.it = trav.path[trav.top]
        last == trav.it.link[dir] || break
      end 
    end
  end

  return trav.it == leaf
end

# <summary>
# Initialize a traversal object to the smallest valued node
# <summary>
# <param name="direction">A direction wrapper tree that the object will be attached to</param>
# <returns>An iterator (Trav) object</returns>
function start(direction::Forward)
  _start(direction.tree, left); # Min value
end

# <summary>
# Initialize a traversal object to the largest valued node
# <summary>
# <param name="direction">A direction wrapper tree that the object will be attached to</param>
# <returns>An iterator (Trav) object</returns>
function start(direction::Backward)
  _start(direction.tree, right) # Max value
end

# <summary>
# Determine whether there's more data to ierate over. in ascending order.
# If it is the case, move the iterator forward.
# <summary>
# <param name="">A direction wrapper over a tree</param>
# <param name="trav">An iterator object</param>
# <returns>true if there's more data, false otherwise</returns>
function done(::Forward, trav::RBTrav)
  move(trav, right) # Toward larger items
end

# <summary>
# Determine whether there's more data to iterate over. in descending order. 
# If it is the case, move the iterator backward
# <summary>
# <param name="">A direction wrapper over a tree</param>
# <param name="trav">An iterator object</param>
# <returns>true if there's more data, false otherwise</returns>
function done(::Backward, trav::RBTrav)
  move(trav, left) # Toward smaller items
end

# <summary>
# Iteration: get the value of the current node (see `done()`).
# <summary>
# <param name="">
# A direction wrapper over a tree, present for compatibility with the iterator protocol.
# </param>
# <param name="trav">An iterator object</param>
# <returns>The current value</returns>
function next (::Direction, trav::RBTrav)
  trav.it.data, trav
end


############################################################################

############################################################################
############################################################################


############################################################################
############################################################################
############################################################################
############################################################################




############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################








############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
















############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################
############################################################################

# <summary>
# Validates a red back tree.
# <summary>
# <param name="tree">The tree to calculate a size for</param>
# <returns>true if the tree is valid, false otherwise.</returns>
isvalid{T}(tree::RedBlackTree{T}) = height(tree.root) > 0

height(::Nothing) = 1

function height(root::RBNode)
  lh = rh = 0

  ln = root.link[left];
  rn = root.link[right];

  # Consecutive red links
  if isred(root)
    if isred(ln) || isred(rn)
      println("Red violation")
      return 0
    end
  end

  lh = height(ln)
  rh = height(rn)

  # Invalid binary search tree
  if ( ( ln != leaf && ln.data >= root.data )
    || ( rn != leaf && rn.data <= root.data ) )
    println("Binary tree violation")
    return 0
  end

  # Black height mismatch
  if lh != 0 && rh != 0 && lh != rh
    println("Black violation")
    return 0
  end

  # Only count black children
  if lh != 0 && rh != 0
    return isred(root) ? lh : lh + 1
  else
    return 0
  end
end

function tostr(node)
  if node == leaf
    return "    "
  else
    return "$(node.red?'R':'b'): $(node.data)"
  end
end

import Base.show

function show(io::IO, tree::RedBlackTree)
  print(io, "$(typeof(tree))")
  # root = tree.root
  # height = int(ceil(log(2, tree.size + 1)))
  # acc = {}
  # fifo = {root}
  # leafs = [false]
  # print("ROOT: ")
  # if root == leaf
  #   print("leaf")
  # else
  #   println(" $(root.red?'R':'b'): $(root.data)----")
  # end
  # while !all(leafs)
  #   leafs = Bool[]
  #   # println("hl? $hasleaf $root")
  #   push!(acc, {})
  #   for i = 1:length(fifo)
  #     node = shift!(fifo)
  #     if node != leaf
  #       for n in node.link
  #         if n == leaf
  #           print("leaf   ")
  #         else
  #           print(" $(n.red?'R':'b'): $(n.data)    ")
  #         end
  #       end
  #     end
  #     # println(hasleaf)
  #     push!(acc[end], tostr(node))
  #     push!(fifo, node == leaf ? leaf : node.link[left])
  #     push!(fifo, node == leaf ? leaf : node.link[right])
  #     push!(leafs, node == leaf ? true : all( (l-> l==leaf), node.link))
  #   end
  #   println("")
  # end
  # for i = 1:length(acc)
  #   buf = {}
  #   space = max(height - i + 1, 1)
  #   push!(buf, repeat("  ", (space)^2))
  #   push!(buf, join(acc[i], repeat("       ", space)[1:end-3]))
  #   push!(buf, "\n")
  #   println(join(buf))
  # end
end

function show(io::IO, node::RBNode)
  print(io, "$(node.red ? 'r':'b'):$(node.data)")
  print(io, " [")
  print(io, node.link[left])
  print(io, ", ")
  print(io, node.link[right])
  print(io, "]")
end
end # module
