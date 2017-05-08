using FactCheck
using LLRBTrees
#using LLRBVisualize

include("checkheight.jl")

function checktree{K,V}(tree::LLRBTree{K,V}, elements::Array{TreeNode{K,V},1})

    FactCheck.@fact tree --> check_height "not balanced"
    #order
    #no consecutive red nodes
    #left leaning

end
function randomscenarios(seed::Int=1, scenarios::Int=10, elNum=1000, var=10)
    #Fixed seed for reproducibility if seed=0 then random
    if(seed==0)
        seed=rand()
        srand(seed)
    else
        srand(seed)
    end


    FactCheck.facts("Test differents scenarios") do
        for i in 1:scenarios
            #Define a number of nodes that varies with scenario, and a random keyrange
            #that's at least as big as the number of nodes
            nodes = rand(elNum-var:elNum)
            mult = rand(1:var)
            keysmax = rand(mult*elNum:((mult+1)*elNum)+var)

            tree = LLRBTree{Int, ASCIIString}()
            keys = []
            elements = TreeNode{Int, ASCIIString}[]


            FactCheck.context("Add random values") do
                for i in 1:nodes
                    key = rand(mult*elNum:keysmax)
                    node = TreeNode(key, string(key) )
                    #println(node)
                    push!(tree, node)

                    indexes = Int[]
                    #Remove repeated notes
                    for j in 1:size(elements)[1]
                        nd = elements[j]
                        if nd.key ==  node.key.value
                            push!(indexes, j)
                        end
                    end
                    deleteat!(elements, indexes) #Remove repeated nodes
                    push!(elements, node)
                    push!(keys, node.key.value)

                    checktree(tree, elements)
                end
            end
            #println(keys)

            FactCheck.context("Search, min and max") do
                min = minimum(keys)
                max = maximum(keys)
                #FactCheck.@fact_throws KeyException tree[min] "getindex failed"
                FactCheck.@fact minimum(tree).key.value == min --> true "Minimum mismatch"
                FactCheck.@fact maximum(tree).key.value == max --> true "Maximum mismatch"


            end


            #vis=drawtree(tree)
            #img = SVG("test1.svg", 10cm, 10cm)
            #draw(img, vis)

            FactCheck.context("Remove keys not present") do
                lower = elNum + 1 + var
                upper = elNum + 1 + 2*var
                removesMax = rand(lower:upper)
                for i in lower:removesMax
                    #println("delete: ",i, " ", )
                    delete!(tree, i)
                    checktree(tree, elements)
                end
            end
            #println(tree)
            #vis=drawtree(tree)
            #img = SVG("test2.svg", 10cm, 10cm)
            #draw(img, vis)

            #Remove all keys in random order
            FactCheck.context("Remove all keys") do
                i=1 #for debugging
                while( size(elements)[1] > 0 )
                    checktree(tree, elements)

                    index = rand(1:size(elements)[1])

                    #Debugging
                    #println("removed ",elements[index])
                    #vis=drawtree(tree)
                    #img = SVG("test"*string(i)*".svg", 10cm, 10cm)
                    #draw(img, vis)
                    #i+=1

                    FactCheck.@fact isa(delete!( tree, elements[index].key.value ), LLRBTree{Int, ASCIIString}) --> true  "Did not return the tree with deleted node"
                    deleteat!(elements, index)
                    deleteat!(keys, index)
                end

                FactCheck.@fact isleaf(tree.root) -->  true "root was not leaf after deleting all keys"
            end

        end
    end
end
