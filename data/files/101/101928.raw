function isLeaf{K,V}(x::_Node{K,V})
    typeof(x) == Leaf{K,V}
end

function isEmpty(tree::BinaryTree)
    isLeaf(tree.root)
end

function insert{K,V}( tree::BinaryTree{K,V}, key::K, value::V )
    if isEmpty(tree)
        tree.root = Node(key, value)
    else
        iter = BinaryTreeIterator(tree)
        done = false
        while !done
            if key <= currentNode(iter).key
                if isLeaf(currentNode(iter).left)
                    currentNode(iter).left = Node( key, value )
                    done = true
                else
                    goLeft(iter)
                end
            else
                if isLeaf(currentNode(iter).right)
                    currentNode(iter).right = Node( key, value )
                    done = true
                else
                    goRight(iter)
                end
            end
        end
        rebalance( iter )
    end
end

function Base.find{K,V}( tree::BinaryTree{K,V}, key::K )
    iter = BinaryTreeIterator(tree)
    found = false
    if isEmpty(tree)
        return((iter,false))
    else
        while !found
            if key < currentNode(iter).key
                if !goLeft(iter)
                    break
                end
            elseif key > currentNode(iter).key
                if !goRight(iter)
                    break
                end
            else
                found = true
            end
        end
        return((iter, found))
    end
end

function goTo{K,V}( tree::BinaryTree{K,V}, key::K )
    iter, found = find(tree, key)
    iter.nodeStack = iter.nodeStack[map(x -> x.key >= key, iter.nodeStack)]
    return((iter, found))
end

function Base.get{K,V}(tree::BinaryTree{K,V}, key::K)
    iter, found = find( tree, key )
    if found
        return( currentNode(iter).value )
    else
        return( nothing )
    end
end

function hasKey{K,V}( tree::BinaryTree{K,V}, key::K )
    return(find(tree, key)[2])
end

function Base.delete!{K,V}( tree::BinaryTree{K,V}, key::K )
    iter, found = find( tree, key )
    if !found
        warn("Attempted to delete unmapped key " * string(key))
        return(false)
    end
    deletee = currentNode(iter)
    while goRight(iter)
    end
    deletee.key = currentNode(iter).key
    deletee.value = currentNode(iter).value
    goUp(iter)
    currentNode(iter).right = currentNode(iter).right.left #Do we have to delete explicitly? GC?
    rebalance(iter)
end

function Base.string(x::Node)
    return "Node(" * string(x.key) * ":" * string(x.value) * " - " * string(height(x)) * ")"
end
Base.print(io::IO, x::Node) = print(io, string(x))
Base.show(io::IO, x::Node) = print(io, string(x))

function Base.string(x::BinaryTreeIterator)
    return "BinaryTreeIterator(" * string(currentNode(x)) * " - " * string(length(x.nodeStack)) * ")"
end
Base.print(io::IO, x::BinaryTreeIterator) = print(io, string(x))
Base.show(io::IO, x::BinaryTreeIterator) = print(io, string(x))

function height( node::Leaf )
    return 0
end

function height{K,V}( node::Node{K,V} )
    return( max( height(node.left), height(node.right)) + 1 )
end

function balanceFactor{K,V}(node::Node{K,V})
    return(height(node.left) - height(node.right))
end

function balanceFactor(node::Leaf)
    return 0
end
