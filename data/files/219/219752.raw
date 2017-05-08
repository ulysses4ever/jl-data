#The LLRBTree data structure, that allows us to acces keys in log2 time.
#Translated from code by Robert Sedgewick
module LLRBTrees

import Base: haskey, getindex, setindex!, delete!, minimum, maximum, push!, show, replace

export TreeNode, LLRBTree, getnodefrom_key, getmaxdepth, orderedpairs, levelorder,
         populate!, isleftleaf, isrightleaf, ischildleaf, isleaf, isred

type TreeNode{K,V}
    key:: Nullable{K}
    value:: Nullable{V}
    isRed:: Bool
    left:: TreeNode{K,V}
    right:: TreeNode{K,V}

    TreeNode() = method_exists(isless, (K,K) ) ? new(Nullable{K}(), Nullable{V}(), false) : error("keys must be comparable")
    TreeNode(key::K, value::V, isRed::Bool, left::TreeNode{K,V}, right::TreeNode{K,V}) =
    method_exists(isless, (K,K) ) ? new(key, value, isRed, left, right): error("keys must be comparable")
    TreeNode(key::K, value::V, isRed::Bool) = method_exists(isless, (K,K) ) ? new(key, value, isRed) : error("keys must be comparable")

end
# New nodes are always red so no method that explicitly assigns the color is neccessary
TreeNode{K,V}(key::K,value::V,left::TreeNode{K,V},right::TreeNode{K,V}) = TreeNode(key,value,true,left,right)
TreeNode{K,V}(key::K,value::V) = TreeNode{K,V}(key, value, true)
TreeNode{K,V}(key::K,value::V, isRed::Bool) = TreeNode{K,V}(key, value, isRed)

# To be able to have different instances of LLRB trees, we create a tree type
# that characterizes a tree by its root
type LLRBTree{K,V}
    root:: TreeNode{K,V}

    LLRBTree()=new()
    LLRBTree(node:: TreeNode{K,V}) = (tree = new(); tree.root=node; tree.root.isRed=false; tree)
    LLRBTree(key::K, value::V) = (tree=new(TreeNode(key,value)); tree.root.isRed=false; tree)
end

LLRBTree{K,V}(key::K,value::V) = LLRBTree{K,V}(key, value)
LLRBTree{K,V}(node::TreeNode{K,V}) = LLRBTree{K,V}(node)

function isleaf{K,V}(node::TreeNode{K,V})
    isnull( node.key )
end

function ischildleaf{K,V}(node::TreeNode{K,V}, left::Bool)
    if(left)
        if(!isdefined(node, :left))
            return true
        else
            return isnull(node.left.key)
        end
    else
        if(!isdefined(node, :right) )
            return true
        else
            return isnull(node.right.key)
        end
    end
end

isleftleaf{K,V}(node::TreeNode{K,V})= ischildleaf(node, true)
isrightleaf{K,V}(node::TreeNode{K,V}) = ischildleaf(node, false)

function isred{K,V}(node::TreeNode{K,V}, dirs::Symbol...)

    steps = length(dirs)
    isred = node.isRed
    foundleaf = 0
    foundundef = 0

    for i in 1:steps
        if(dirs[i]!= :left && dirs[i]!= :right)
            Base.error("Directions must be :left or :right")
        end

    end

    for i in 1:steps

        dirbool = dirs[i]== :left ? true : false

        if(isdefined(node, dirs[i]))
            node = dirbool ? node.left : node.right
            isred = node.isRed

            foundleaf = isnull(node.key) ? i : foundleaf
        else
            isred = false
            foundundef = i
            break
        end
    end

    overflow = (foundundef < steps && foundundef!=0)
    overflow |= (foundleaf < steps && foundleaf!=0)

    return  overflow ? Base.error("Directions move beyond leaves") : isred

end

function getmaxdepth{K,V}(node::TreeNode{K,V}, depth=1)
      #We do a caching up of the number of recursions with the use of parameters and returns
      depthleft=depthright=depth
    if !isleftleaf(node)
          #("left in at $depth")
          depthleft = getmaxdepth(node.left, depth+1)
      end
    if !isrightleaf(node)
          #("right in at $depth")
          depthright = getmaxdepth(node.right, depth+1)
      end
      #("out at $depth")
      #([depthleft,depthright])
      return maximum([depthleft,depthright])
  end
  getmaxdepth(tree::LLRBTree) = getmaxdepth(tree.root)

function replace(original::ASCIIString, start::Int64, fin::Int64, string::ASCIIString)
    left = original[1:start]
    right = original[fin:end]
    return left*string*right
end

function show{K,V}(io::IO, tree::LLRBTree{K,V})

    if(isdefined(tree, :root))
        totalheight = getmaxdepth(tree)
        height = getmaxdepth(tree) < 5 ? totalheight : 5
        width = 2^(height +2)

        len = width * height * 2 + 2 |> Int
        stringtree = ""
        for i = 1:len
            stringtree*= i < len - 2 && i % width == 0 ? "\n" : " "
        end


        if(!isnull(tree.root.key))
            stringtree = showR(stringtree, Int(width / 2), 1, Int(width / 4), width, tree.root, " ")
        else
            stringtree = "No root"
        end
    else
            stringtree = "No root"
    end

    println(io, stringtree)
end

function showR(stringtree::ASCIIString, center::Int, row::Int, indent::Int, width::Int, node::TreeNode,
            edge::ASCIIString)

    if(indent%2 == 0)

        if (!isleftleaf(node))
            stringtree = showR(stringtree, center - indent, row + 2, Int(indent/2), width, node.left, " /");
        end

        valuestring = string(node.value.value)
        valuestring = node.isRed ? valuestring*"_r" : valuestring

        idx1 = Int( row * width + center - div( (length(valuestring) + 1) , 2 ) )
        idx2 = idx1 + length(valuestring) |> Int
        idx3 = idx1 - width |> Int
        if (idx2 < length(stringtree))
            stringtree = replace(stringtree, idx1, idx2 +1, valuestring)
            stringtree = replace(stringtree, idx3, idx3 + 3, edge)
        end

        if (!isrightleaf(node))
            stringtree = showR(stringtree, center + indent, row + 2, Int(indent/2), width, node.right, "\\ ")
        end
    end

    return stringtree
end

# The function that returns the node that corresponds to a certain key, below a root-node
# it returns a TreeLeaf when the root node is empty
function getnodefrom_key{K,V}(part::TreeNode{K,V}, key::K)
  # The recursive search for the key
    if get(part.key) == key
        return part
    elseif key < get(part.key)
        if( !isleftleaf(part) )
            getnodefrom_key(part.left, key)
        else
            return TreeNode{K,V}()
        end
    else
        if(!isrightleaf(part))
            getnodefrom_key(part.right, key)
        else
          return TreeNode{K,V}()
        end
    end
end
getnodefrom_key{K,V}(tree::LLRBTree{K,V}, key::K) = getnodefrom_key(tree.root, key)

haskey{K,V}(tree::LLRBTree{K,V}, key::K) =  !isleaf( getnodefrom_key(tree.root, key) )
haskey{K,V}(node::TreeNode{K,V}, key::K) = !isleaf( getnodefrom_key(node, key) )

# A getindex only that the indexes are keys and we get the value of the first node with the given key
function getindex{K,V}(node::TreeNode{K,V}, key::K)
    part::TreeNode{K,V} = getnodefrom_key(node,key)
    # Throw a KeyException if the key is node.left present

    if isleaf( part )
        throw(KeyError(key))
    else
        return part.value
    end
end

getindex{K,V}(tree::LLRBTree{K,V}, key::K) = getindex(tree.root, key)

function setindex!{K,V}(node::TreeNode{K,V}, value::V, key::K)
    part::TreeNode{K,V} = getnodefrom_key(node,key)
    # Throw a KeyException if the key is not present
    if isleaf( part )
        throw(KeyException(key))
    else
        part.value=Nullable(value)
    end
end
setindex!{K,V}(tree::LLRBTree{K,V}, key::K) = setindex!(tree.root, key)

function rotateleft{K,V}(node::TreeNode{K,V})

    if isrightleaf(node)
        error("The right part of the given node must be a node")
    end
    son=node.right

    if !isleftleaf(son)
        #("assign in between")
        node.right=son.left
    else
        node.right=TreeNode{K,V}()
    end
    son.left=node

    son.isRed=node.isRed
    node.isRed=true
    return son
end
function rotateright{K,V}(node::TreeNode{K,V})

    if isleftleaf(node)
        error("The left part of the given node must be a node")
    end
    son=node.left

    if !isrightleaf(son)
        node.left=son.right
    else
        node.left=TreeNode{K,V}()
    end
    son.right=node

    son.isRed=node.isRed
    node.isRed=true
    return son
end
function flipcolor!{K,V}(node::TreeNode{K,V})

    node.isRed = !node.isRed
    if !isleftleaf(node)
        node.left.isRed = !node.left.isRed
    end
    if !isrightleaf(node)
        node.right.isRed = !node.right.isRed
    end
end

function add_node{K,V}(node::TreeNode{K,V}, key::K, value::V)

    if isleaf(node)
        #("Add the node only when a leaf is found  ",tree)
        return TreeNode(key, value)
    end

    #put flipcolor here to get 2-3-4 trees

    if get(node.key) < key
        #("went right")
        node.right = !isrightleaf(node) ? node.right: TreeNode{K,V}()
        node.right = add_node(node.right, key, value)
    elseif get(node.key) > key
        #("went left")
        node.left = !isleftleaf(node) ? node.left: TreeNode{K,V}()
        node.left = add_node(node.left, key, value)
    else
        #("node was same")
        node.value = value
    end

    if ( isred(node, :right) && !isred(node, :left))
        #("Rotate left to prevent red node on right ", node)
        node=rotateleft(node)
    end

    if ( isred(node, :left) && isred(node, :left, :left) )
        #("Rotate right to prevent consecutive red nodes ", node)
        node=rotateright(node)
    end
    if isred(node, :left) && isred(node, :right)
        #("Split node with two red children")
        flipcolor!(node)
    end

    return node
end
# For trees and nodes as parameters; different name so the other one doesn't get used
push!{K,V}(tree::LLRBTree{K,V}, key::K, value::V) = (tree.root = isdefined(tree, :root)
? add_node(tree.root, key, value): TreeNode(key, value); tree.root.isRed=false; tree)

push!{K,V}(tree::LLRBTree{K,V}, node::TreeNode{K,V}) = push!(tree, node.key, node.value)

function populate!{K,V}(tree::LLRBTree{K,V}, N::Int64)
    keys = []

    for i in 1:N
        r::Int64 = rand(1:N*2+100)
        push!(tree, r, r )

        #rep_index = indexin([r], keys)
        #while rep_index != [0]
        #    deleteat!(keys, rep_index)
        #    rep_index = indexin([r], keys)
        #end

        push!(keys, r)
    end
    return keys
end

function moveredleft{K,V}(node::TreeNode{K,V})
    flipcolor!(node)

    if !isrightleaf(node)
        if ( isred(node, :right, :left) )
            node.right = rotateright(node.right)
            node = rotateleft(node)
            flipcolor!(node)
        end
    end
    return node
end

function moveredright{K,V}(node::TreeNode{K,V})
    flipcolor!(node)

    if ( isred(node, :left, :left) )
        node= rotateright(node)
        flipcolor!(node)
    end

    return node
end

function minimum{K,V}(node::TreeNode{K,V})
    while !isleftleaf(node)
        node=node.left
    end
    return node
end
minimum(tree::LLRBTree) = minimum(tree.root)

function maximum{K,V}(node::TreeNode{K,V})
    while !isrightleaf(node)
        node=node.right
    end
    return node
end
maximum(tree::LLRBTree) = maximum(tree.root)

function fixup{K,V}(node::TreeNode{K,V})


    if isred(node, :right)
        node=rotateleft(node)
    end

    if(!isred(node, :left) && isred(node, :right) )
        node=rotateleft(node)
    end


    if(isred(node, :left) && isred(node, :left, :left) )
        node=rotateright(node)
    end

    if (isred(node, :left) && isred(node, :right) )
        flipcolor!(node)
    end

    return node
end

function deletemin{K,V}(node::TreeNode{K,V})

    if(!isleftleaf(node))

        if(!isred(node, :left) && !isred(node, :left, :left) )
            moveredleft(node)
        end

        node.left = deletemin(node.left)

        return fixup(node)
    else

        return TreeNode{K,V}()
    end
end

function delete_node{K,V}(node::TreeNode{K,V}, key::K)
    if key<node.key.value

        if !isleftleaf(node)

            if(!isred(node, :left) && !isred(node, :left, :left) )
                node=moveredleft(node)
            end

            node.left=delete_node(node.left, key)

        else
            Base.warn_once("Key not found:", key)
            return fixup(node)
        end

    else
        if(isred(node, :left))
            node=rotateright(node)
        end

        if (key==node.key.value && isrightleaf(node))
            return TreeNode{K,V}()
        end

        if !isrightleaf(node)

            if(!isred(node, :right) && !isred(node, :right, :left) )
                node=moveredright(node)
            end

            if key==node.key.value
                min = minimum(node.right)
                node.key=min.key
                node.value=min.value
                node.right=deletemin(node.right)
            else
                node.right=delete_node(node.right,key)
            end

        else
            Base.warn_once("Key not found:", key)
            return fixup(node)
        end
    end
    return fixup(node)
end


function delete!{K}(tree::LLRBTree, key::K)

    if( isdefined(tree, :root))
        if(! isleaf(tree.root) )
            tree.root = delete_node(tree.root, key)

            tree.root.isRed = false
        else
            Base.warn_once("Root cannot be leaf")
        end
    else
        Base.warn_once("Root cannot be leaf")
    end

    tree
end
delete!{K,V}(tree::LLRBTree, node::TreeNode{K,V}) = delete!(tree, node.key.value)



function levelorder{K,V}(tree::LLRBTree{K,V})
    queue = []
    push!(queue, tree.root)
    println("levelorder:  ")
    count = 20
    last20 = ones(1:20)

    while (!isempty(queue))
        node = shift!(queue)

        #Only print the first 20 values
        if(count>0)
            print(node.value.value,"  ")
        elseif count == 0
            print("...  ")
        end

        #Keep the last 20 entries to print later
        shift!(last20)
        #pop!(last20)
        push!(last20, node.value.value)
        #println(size(last20,1))

        if( !isleftleaf(node) )
            push!(queue, node.left)
        end
        if( !isrightleaf(node) )
            push!(queue, node.right)
        end

        count -= 1
    end

    if count < -19
        for i in 0:19
            print(last20[end-i]," ")
        end
    end
end


#Return an ordered list with recursion
# function inorder(node::TreePart, list=Any[])
#   if !isa(node, TreeLeaf)
#
#       if !isa(node.left, TreeLeaf)
#           #("Go down to the left first")
#           list = inorder(node.left, list)[2]
#       end
#
#       #("Push to the list when leftmost")
#       push!(list, [node.key, node.value])
#
#       if !isa(node.right, TreeLeaf)
#           #("Go right if no left")
#           list = inorder(node.right, list)[2]
#       end
#   end
#   #("Go up;  ",node,";  ",list)
#   return node, list
# end
# orderedpairs(tree::LLRBTree) = inorder(tree.root)[2]

end
