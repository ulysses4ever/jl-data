module KDTree

#A KDTree is a recursive data structure/geometric algorithm that
#impliements nearest-neighbor search in N log N time.

#Port of COS 226 KDTree implementation following the structure in tree.jl.
#https://github.com/JuliaLang/DataStructures.jl/blob/master/src/tree.jl

#Keys are array representations of (x,y) coordinates.

using Rect
import Base: haskey, getindex,setindex!, delete!

export

abstract Tree{K,V}

type EmptyKDTree{K,V} <: KDTree{K,V}
end

type TreeNode{K,V} <: KDTree{K,V}
        key::K
        val::V
        rect ##RECTANGLE
        lb::KDTree{K,V}
        rt::KDTree{K,V}
end

type KDTree{K,V}
       root::Tree{K,V}

       KDTree() = new(EmptyKDTree{K,V}())
end

haskey(t::EmptyKDTree{K,V}()) = false
haskey(t::KDTree,key) = haskey(t.root,key,true)

#t.key is the current node we are examining (Node x in the original Java implementation)
#key is the key we are ultimately looking for (key in original Java implementation)
function haskey(t::Treenode, key, orientation::Boolean)
        if isequal(t.key,key) #objectwise comparison since keys are likely to be 2-element arrays
                return true
        end

        #Orientation alternates at each level and governs whether we go to left/right tree or
        #top/bottom tree
        if orientation
                cmp = t.key[1] - key[1];
        else
                cmp = t.key[2] - key[2];
        end

        if cmp < 0
                return haskey(t.key.lb, key, !orientation);
        else
                return haskey(t.key.rt, key, !orientation);
        end
end

getindex(t::EmptyKDTree, k) = throw(KeyError(k))
getindex(t::KDTree,k,true) = t.root[k] #Start searching from the root with "true" orientation

function getindex(t::TreeNode, key,orientation)
        if isequal(t.key,key)
                return t.data
        end
        # Compare the keys
        if orientation
                cmp = t.key[1] - key[1];
        else
                cmp = t.key[2] - key[2];
        end
        # Return left-bottom key or right-top depending on key compare
        if cmp < 0
                return t.key.lb[key];
        else
                return t.key.rt[key];
        end
end

setindex!{K,V}(t::EmptyKDTree{K,V},v,k) = TreeNode{K,V}(k, v, t, t)
#Helper function to start the recursive calls
setindex!(t::KDTree,v,k, orientation) = (t.root = setindex!(t.root,v,k, true); t)

#Set index k to value v
function setindex!(t::TreeNode, v, k, orientation)
        #Update value if key is already in KDTree
        if isequals(t.key,k)
                t.data = v
        end

        #Compare keys
        if orientation
                cmp = t.key[1] - k[1];
        else
                cmp = t.key[2] - k[2];
        end

        if cmp < 0
                t.lb = setindex!(t.lb, v, k, !orientation)
        else
                t.rt = setindex!(t.rt, v, k, !orientation)
        end
        return t #I'm assuming it returns t
end

#Delete key k and its value v from the KDTree (via Hibbard delete?)

end
