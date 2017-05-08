export FormulaState

type FormulaState
    disjunctions::Vector{Int} # number of branches on disjunctions
end

FormulaState() = FormulaState(Int[])
FormulaState(::Literal) = FormulaState()
function FormulaState(cl::Clause)
    list = Int[]
    count_disjunctions!(list, cl)
    FormulaState(list)
end

function _apply_!(list::Vector{Int}, clauses)
    for clause in clauses
        count_disjunctions!(list, clause)
    end
    nothing
end

count_disjunctions!(list, ::Literal) = nothing
count_disjunctions!(list, cl::And)   = _apply_!(list, cl.clauses)
count_disjunctions!(list, cl::Or)    = (push!(list, length(cl.clauses)); _apply_!(list, cl.clauses))
