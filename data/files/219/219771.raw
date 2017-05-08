using LLRBTrees
using FactCheck

include("checkheight.jl")

facts("Sample tree") do

    tree = LLRBTree()
    push!(tree, 1, "a")
    push!(tree, 2, "b")
    push!(tree, 3, "c")
    push!(tree, 4, "d")
    push!(tree, 5, "e")

    @fact tree --> check_height "Not balanced"

    @fact tree.root.left.key == 2 --> true "Tree wasn't built correctly"
    @fact tree.root.right.key == 5 --> true "Tree wasn't built correctly"
    @fact tree.root.left.right.key == 3 --> true "Tree wasn't built correctly"
    @fact tree.root.left.left.key == 1 --> true "Tree wasn't built correctly"

    delete!(tree,1)
    @fact tree.root.left.right.key == 1 --> true "Tree didn't delete correctly"

    delete(tree, 4)
    @fact tree.root.isRed --> false "Tree didn't delete correctly"

    delete(tree, 1)
    delete(tree, 3)
    delete(tree, 5)
    @fact typeof(tree.root)==LLRBTrees.TreeLeaf --> true "Tree didn't delete correctly"
end



FactCheck.exitstatus()
