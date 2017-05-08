function check_height{K,V}(node::TreeNode{K,V}, prevheight::Int=0, height::Int=0, first::Bool=true)
    if( !node.isRed ) height += 1 end
    isbalanced=true
    if(!isleftleaf(node))
        isbalanced, prevheight = check_height(node.left, prevheight, height, first)
    end

    if(!isbalanced)
        return false, prevheight
    end

    if( isleftleaf(node) && isrightleaf(node))
        if (height != prevheight && !first)
            return false, prevheight
        end
        first=false
        prevheight = height
    end


    if(!isrightleaf(node))
        isbalanced, prevheight = check_height(node.right, prevheight, height, first)
    end

    return isbalanced, prevheight

end
check_height{K,V}(tree::LLRBTree{K,V}) = check_height(tree.root)[1]
