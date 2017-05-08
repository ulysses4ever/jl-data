module TestRunner

export TestStructureNode,FactsCollectionNode,ContextNode,FactNode, get_tests_structure, children, run_all, get_tests_structure_as_json, get_tests_results_as_json

using FactCheck

abstract TestStructureNode

type FactsCollectionNode <: TestStructureNode
    line::Int
    name::AbstractString
    children::Vector{TestStructureNode}
end

type ContextNode <: TestStructureNode
    line::Int
    name::AbstractString
    children::Vector{TestStructureNode}
end

type FactNode <: TestStructureNode
    line::Int
    name::AbstractString
    result::Nullable{Bool}
    details::Nullable{AbstractString}
end
FactNode(line::Int, name::AbstractString) = FactNode(line,name,Nullable{Bool}(),Nullable{AbstractString}())
FactNode(line::Int, name::AbstractString, result::Nullable{Bool}) = FactNode(line, name, result, Nullable{AbstractString}())
FactNode(line::Int, name::AbstractString, result::Bool) = FactNode(line, name, Nullable{Bool}(result), Nullable{AbstractString}())

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
                children = f(e.args[2],line)
                node = FactsCollectionNode(line, length(e.args)>2?e.args[3]:"",children)
                push!(results, node)
            elseif length(e.args)>0 && e.args[1] == :context
                children = f(e.args[2],line)
                node = ContextNode(line, length(e.args)>2?e.args[3]:"",children)
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

function f2(ex::Expr, r, line = 0)
    results = Vector{TestStructureNode}()
    for e in ex.args
        if isa(e, LineNumberNode)
            line = e.line
        elseif isa(e,Expr)
            if length(e.args)>0 && e.args[1] == :facts
                children = f2(e.args[2],r,line)
                node = FactsCollectionNode(line, length(e.args)>2?e.args[3]:"",children)
                push!(results, node)
            elseif length(e.args)>0 && e.args[1] == :context
                children = f2(e.args[2],r,line)
                node = ContextNode(line, length(e.args)>2?e.args[3]:"",children)
                push!(results, node)
            elseif length(e.args)>0 && e.args[1] == Symbol("@fact")
               node = FactNode(line, length(e.args)>2?e.args[3]:"", pop!(r))
               push!(results, node)
            else
                append!(results, f2(e, r, line))
            end
        end
    end
    results
end


_get_tests_structure(testFileContent::Expr) =  testFileContent |> f

get_tests_structure(testFilePath::AbstractString) = testFilePath |> get_file_content |> _get_tests_structure

get_tests_structure_with_results(testFilePath, results) = f2(get_file_content(testFilePath), reverse(results))

function get_results(testFilePath::AbstractString)
  temp  = FactCheck.allresults
  FactCheck.clear_results()
  original_STDOUT = STDOUT
  (out_read, out_write) = redirect_stdout()
  evalfile(testFilePath)
  close(out_write)
  close(out_read)
  redirect_stdout(original_STDOUT)
  results = copy(FactCheck.allresults)
  empty!(FactCheck.allresults)
  append!(FactCheck.allresults, temp)
  results
end

function run_all_tests(testFilePath::AbstractString)
  results = map(x -> isa(x, FactCheck.Success)?true:false ,get_results(testFilePath))
  get_tests_structure_with_results(testFilePath, results)
end


children(node::TestStructureNode) = isa(node, FactNode) ? Vector{TestStructureNode}() : node.children

include("TestRunnerJSON.jl")

get_tests_structure_as_json(testFilePath::AbstractString) = testFilePath |> get_tests_structure |> json

get_tests_results_as_json(testFilePath::AbstractString) = testFilePath |> run_all_tests |> json


end # module
