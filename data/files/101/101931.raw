function goPrev(iter::BinaryTreeIterator)
    if !isLeaf(currentNode(iter).left)
        push!(iter.nodeStack, currentNode(iter).left)
        return(true)
    else
        return(false)
    end
end

function goNext(iter::BinaryTreeIterator)
    if isempty(iter.nodeStack)
        return(false)
    else
        node = pop!(iter.nodeStack) #remove currentNode
        if !isLeaf(node.right)
            push!(iter.nodeStack, node.right)
            while !isLeaf(currentNode(iter).left)
                push!(iter.nodeStack, currentNode(iter).left)
            end
        end
        return(!isempty(iter.nodeStack))
    end
end

function Base.start(tree::BinaryTree)
    iter = BinaryTreeIterator( tree )
    while goPrev(iter)
    end
    return( iter )
end

function Base.done( tree::BinaryTree, iter::BinaryTreeIterator )
    return( isempty(iter.nodeStack) )
end

function Base.next( tree::BinaryTree, iter::BinaryTreeIterator )
    node = iter.nodeStack[end]
    goNext(iter)
    return (node, iter)
end

function currentNode( iter::BinaryTreeIterator )
    if !isempty(iter.nodeStack)
        return( iter.nodeStack[end] )
    else
        return( nothing )
    end
end

function goLeft( iter::BinaryTreeIterator )
    if !isLeaf(currentNode(iter).left)
        push!( iter.nodeStack, currentNode(iter).left )
        return(true)
    else
        return(false)
    end
end

function goRight( iter::BinaryTreeIterator )
    if !isLeaf( currentNode(iter).right )
        push!( iter.nodeStack, currentNode(iter).right )
        return(true)
    else
        return(false)
    end
end

function goUp( iter::BinaryTreeIterator )
    if !isempty( iter.nodeStack )
        pop!( iter.nodeStack )
    end
    if !isempty( iter.nodeStack )
        return(true)
    else
        return(false)
    end
end

function goDown( iter::BinaryTreeIterator )
    if !isLeaf(currentNode(iter))
        if !isLeaf(currentNode(iter).left)
            goLeft( iter )
        elseif !isLeaf(currentNode(iter).right)
            goRight( iter )
        else
            return(false)
        end
    end
    return(true)
end

function rotateRight(iter::BinaryTreeIterator)
    root = currentNode(iter)
    pivot = root.left
    if goUp(iter)
        hinge = currentNode(iter)
        if root == hinge.left
            child = "left"
        else
            child = "right"
        end
    else #We are in the root of the tree
        child = "tree"
    end
    root.left = pivot.right
    pivot.right = root
    if child == "left"
        hinge.left = pivot
        goLeft(iter)
    elseif child == "right"
        hinge.right = pivot
        goRight(iter)
    else
        iter.tree.root = pivot
    end
end

function rotateLeft(iter::BinaryTreeIterator)
    root = currentNode(iter)
    pivot = root.right
    if goUp(iter)
        hinge = currentNode(iter)
        if root == hinge.left
            child = "left"
        else
            child = "right"
        end
    else #We are in the root of the tree
        child = "tree"
    end
    root.right = pivot.left
    pivot.left = root
    if child == "left"
        hinge.left = pivot
        goLeft(iter)
    elseif child == "right"
        hinge.right = pivot
        goRight(iter)
    else
        iter.tree.root = pivot
    end
end

function rebalance(iter::BinaryTreeIterator)
    goDown(iter) #one step down to newly inserted node
    while goUp(iter)
        if balanceFactor(currentNode(iter)) == 2 #We need to rebalance - left column
            if balanceFactor(currentNode(iter).left) == -1 #The "Left Right Case"
                if !goLeft(iter)
                    error("Couldn't go left, but I wanted to")
                else
                    rotateLeft(iter) #reduce to "Left Left Case"
                    goUp(iter)
                end
            end
            rotateRight(iter)
        elseif balanceFactor(currentNode(iter)) == -2 #  right column
            if balanceFactor(currentNode(iter).right) == 1 #The "Right Left Case"
                if !goRight(iter)
                    error("Couldn't go right, but I wanted to")
                else
                    rotateRight(iter) #reduce to "Right Right Case"
                    goUp(iter)
                end
            end
            rotateLeft(iter)
        end
    end
end
