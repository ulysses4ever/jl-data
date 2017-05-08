# Internal utilities.

using DataStructures

export replacesubtree

# Return the maximum depth of a given program tree.
function maxdepth(f::Func)
    maximum(1 + [maxdepth(getfield(f, a)) for a=funcargs(f)])
end

function maxdepth(t::Term) 0 end

# FIXME Due to the Julia comparison semantics for immutable objects, this
# function can't tell the difference between two identical subtrees, so it will
# replace all of them.
function replacesubtree(r::Func, oldst::Tree, newst::Tree)
    if is(r, oldst)
        return newst
    end
    # TODO We might be able to optimize this by checking if the result of the
    # recursive call is identical to the original and re-using the original,
    # but not sure it would actually save memory since immutables are copied on
    # call.
    rargs = map(r.args) do arg
        replacesubtree(arg, oldst, newst)
    end
    rtype = typeof(r)
    return rtype(rargs...)
end
function replacesubtree(r::Term, oldst::Tree, newst::Tree)
    if is(r, oldst)
        return newst
    else
        return r
    end
end

# Choose a random subtree
function randsubtree(r::Func, funcprob::Float64)
    node::Tree

    funcs = Stack(Func)
    terms = Stack(Term)

    stack = Stack(Tree)
    push!(stack, r)
    while length(stack) > 0
        current = pop!(stack)

        if typeof(current) <: Func
            push!(funcs, current)
        elseif typeof(current) <: Term
            push!(terms, current)
        else
            error("Invalid tree element")
        end

        for field = names(current)
            if !beginswith(string(field), "arg")
                continue
            end
            push!(stack, getfield(current, field))
        end
    end

    if rand() < funcprob
        choice = rand(1:length(funcs))
        found = funcs
    else
        choice = rand(1:length(terms))
        found = terms
    end

    while choice > 1
        choice -= 1
        pop!(found)
    end

    node = pop!(found)
    return node
end
function randsubtree(r::Term, funcprob::Float64)
    # TODO Should we still pick whether to return a func or term and then error
    # if we choose func? That seems like it would be brittle and create tricky
    # bugs, this way seems better in that sense.
    if funcprob == 1.0
        error("No valid nodes to return")
    end
    return r
end
function randsubtree(r::Term)
    randsubtree(r, 0.0)
end
