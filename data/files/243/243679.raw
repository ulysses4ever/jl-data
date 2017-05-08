# Internal utilities.

using DataStructures

export maxdepth, replacesubtree, randsubtree

# Return the maximum depth of a given program tree.
function maxdepth(f::Func)
    maximum(1 + [maxdepth(t) for t=f.args])
end
function maxdepth(t::Term) 0 end


# Find a given subtree within the parse tree and replace it with another given
# parse tree.
function replacesubtree(t::Func, oldst::Tree, newst::Tree)
    # FIXME Due to the Julia comparison semantics for immutable objects, this
    # function can't tell the difference between two identical subtrees, so it will
    # replace all of them.
    if is(t, oldst)
        return newst
    end
    # TODO We might be able to optimize this by checking if the result of the
    # recursive call is identical to the original and re-using the original,
    # but not sure it would actually save memory since immutables are copied on
    # call.
    targs = map(t.args) do arg
        replacesubtree(arg, oldst, newst)
    end
    ttype = typeof(t)
    ttype(targs...)
end
function replacesubtree(t::Term, oldst::Tree, newst::Tree)
    if is(t, oldst)
        return newst
    else
        return t
    end
end


# Choose a random subtree from a parse tree and return it.
function randsubtree(t::Func, funcprob::Float64)
    funcs = Stack(Func)
    terms = Stack(Term)
    stack = Stack(Tree)
    push!(stack, t)
    while length(stack) > 0
        current = pop!(stack)

        if typeof(current) <: Func
            push!(funcs, current)
            for arg = current.args
                push!(stack, arg)
            end
        elseif typeof(current) <: Term
            push!(terms, current)
        else
            error("Invalid tree element")
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

    pop!(found)
end
function randsubtree(t::Term, funcprob::Float64)
    t
end
