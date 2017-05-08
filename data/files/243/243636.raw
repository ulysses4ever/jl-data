# Evolutionary operators.

export mutsubtree, mutpoint, crosssubtree

# ------------------------------------------------------------------------------
# Subtree-mutation
# Implements basic subtree mutatation. Chooses a random subtree, generates a
# new subtree with the same maximum depth as the previously chosen subtree,
# then inserts the newly generated subtree in place of the old one. Uses the
# grow method to create the new subtree.
# ------------------------------------------------------------------------------

function mutsubtree(t::Func, funcs::FuncTypes, consts::Consts, vars::Vars, funcprob::Float64)
    oldst = randsubtree(t, funcprob)
    newst = treegrow(funcs, consts, vars, maxdepth(oldst))
    replacesubtree(t, oldst, newst)
end
function mutsubtree(t::Term, funcs::FuncTypes, consts::Consts, vars::Vars, funcprob::Float64)
    treegrow(funcs, consts, vars, 2)
end
function mutsubtree(t::Tree, funcs::FuncTypes, consts::Consts, funcprob::Float64)
    mutsubtree(t, funcs, consts, vars(), funcprob)
end

# ------------------------------------------------------------------------------
# Point-mutation
# Implements point mutation. Traverses the tree and, at each node in the tree
# does one of two things. either replaces the node with some other, similar
# (equal arity) node, or does nothing. Note that this can result in several
# nodes, or (in theory) even the entire tree being replaced, but the structure
# will never change.
# ------------------------------------------------------------------------------

function mutpoint(t::Func, funcs::FuncTypes, terms::Terms, mutprob::Float64)
    matchfuncs = filter(funcs) do f
        arity(f) == arity(typeof(t))
    end |> collect
    if rand() < mutprob
        func = matchfuncs[rand(1:end)]
    else
        func = typeof(t)
    end
    subtrees = [mutpoint(st, funcs, terms, mutprob) for st=t.args]
    func(subtrees...)
end
function mutpoint(t::Term, funcs::FuncTypes, terms::Terms, mutprob::Float64)
    if rand() < mutprob
        term = terms[rand(1:end)]
    else
        term = t
    end
    term
end

# ------------------------------------------------------------------------------
# Cross-tree substitution
# ------------------------------------------------------------------------------

function crosssubtree(tleft::Func, tright::Func, funcprob::Float64)
    leftst = randsubtree(tleft, funcprob)
    rightst = randsubtree(tright, funcprob)
    (replacesubtree(tleft, leftst, rightst), replacesubtree(tright, rightst, leftst))
end
