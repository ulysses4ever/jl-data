function check_height(node::TreeNode, prevheight::Int=0, height::Int=0, first::Bool=true)
    if( !node.isRed ) height += 1 end
    check=true

    if(!isa(node.left, TreeLeaf))
        check, prevheight = check_height(node.left, prevheight, height, first)
    end

    if(!check)
        return false, prevheight
    end

    if( isa(node.left, TreeLeaf) && isa(node.right, TreeLeaf))
        if (height != prevheight && !first)
            return false, prevheight
        end
        prevheight = height
    end
    first=false

    if(!isa(node.right, TreeLeaf))
        check, prevheight = check_height(node.right, prevheight, height, first)
    end

    return check, prevheight

end
check_height(tree::LLRBTree) = check_height(tree.root)[1]
