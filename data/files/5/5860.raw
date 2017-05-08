module TestRunner
export TestStructureNode,FactsNode,ContextNode,FactNode, get_tests_structure
import Base.==
abstract TestStructureNode

type FactsNode <: TestStructureNode
    line::Int
    name::AbstractString
    childs::Vector{TestStructureNode}
end
==(a::FactsNode,b::FactsNode) = a.line == b.line && a.name == b.name && a.childs == b.childs
type ContextNode <: TestStructureNode
    line::Int
    name::AbstractString
    childs::Vector{TestStructureNode}
end

type FactNode <: TestStructureNode
    line::Int
    name::AbstractString
    result::Nullable{Bool}
    details::Nullable{AbstractString}
end
FactNode(line::Int, name::AbstractString) = FactNode(line,name,Nullable{Bool}(),Nullable{AbstractString}())
FactNode(line::Int, name::AbstractString, result::Nullable{Bool}) = FactNode(line, name, result, Nullable{AbstractString}())
==(a::FactsNode, b::FactsNode) = a.line == b.line && a.name == b.name

function get_file_content(testFilePath::AbstractString)
      content = testFilePath |> readall
      "begin\n"*content*"\nend" |> parse
end
expand_expression(e::Expr) = map((arg -> typeof(arg) == Expr? expand_expression(arg):arg), e.args)

function find_subparts(tree::Array, a::Symbol, results::Array = [])
   if any(x -> x==a, tree)
     push!(results, tree)
   end
   for node in tree
     if typeof(node) <: Array
       find_subparts(node, a, results)
     end
   end
   results
end

function get_message(a::Array)
  message = last(a)
  typeof(message)<:AbstractString? message:""
end

get_facts(a::Array) = map(get_message, find_subparts(a, Symbol("@fact")))
function get_facts_groups(testFileContent::Expr)
  expanded_expression = testFileContent |> expand_expression
  facts_groups = find_subparts(expanded_expression, :facts)
  map( group -> (get_message(group), get_facts(group)) ,facts_groups)
end

function f(ex::Expr, line = 0)
    results = Vector{TestStructureNode}()
    for e in ex.args
        if isa(e, LineNumberNode)
            line = e.line
        elseif isa(e,Expr)
            if length(e.args)>0 && e.args[1] == :facts
                childs = f(e.args[2],line)
                node = FactsNode(line, length(e.args)>2?e.args[3]:"",childs)
                push!(results, node)
            elseif length(e.args)>0 && e.args[1] == :context
                childs = f(e.args[2],line)
                node = ContextNode(line, length(e.args)>2?e.args[3]:"",childs)
                push!(results, node)
            elseif length(e.args)>0 && e.args[1] == Symbol("@fact")
               node = FactNode(line, length(e.args)>2?e.args[3]:"")
               push!(results, node)
            else
                append!(results, f(e, line))
            end
        end
    end
    return results
end
_get_tests_structure(testFileContent::Expr) =  testFileContent |> f

get_tests_structure(testFilePath::AbstractString) = testFilePath |> get_file_content |> _get_tests_structure
end # module
