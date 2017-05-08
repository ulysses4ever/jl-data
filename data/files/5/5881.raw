module TestRunner

export  get_tests_structure, run_all_tests, get_tests_structure_as_json, get_tests_results_as_json, children, line, name, result, details

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
function FactNode(line::Int, name::AbstractString, result::FactCheck.Result)
  if isa(result, FactCheck.Pending)
    r = Nullable{Bool}()
    details = "Pending"
  elseif isa(result, FactCheck.Error)
    r = false
    details = result.meta.msg*"\n"*sprint(showerror, result.err, result.backtrace)
  else
    r = isa(result, FactCheck.Success)
    details = result.meta.msg
  end
  FactNode(line, name, r, details)
end

function _fixLineNumbers(expressionTreeNode::Expr)
  for i in 1:length(expressionTreeNode.args)
      if isa(expressionTreeNode.args[i], LineNumberNode)
          expressionTreeNode.args[i] = LineNumberNode(expressionTreeNode.args[i].file, expressionTreeNode.args[i].line -1)
      elseif isa(expressionTreeNode.args[i], Expr)
        _fixLineNumbers(expressionTreeNode.args[i])
      end
  end
end

function _get_file_content(testFilePath::AbstractString)
      content = testFilePath |> readall
      parsedContent = "begin\n"*content*"\nend" |> parse
      _fixLineNumbers(parsedContent)
      parsedContent
end

function _get_tests_structure(expressionTreeNode::Expr, testsResults::Vector{FactCheck.Result} = FactCheck.Result[] , line = 0)
    result = Vector{TestStructureNode}()
    getName = (e) -> length(e.args)>2?e.args[3]:""
    for treeNode in expressionTreeNode.args
        if isa(treeNode, LineNumberNode)
            line = treeNode.line
        elseif isa(treeNode, Expr)
            if length(treeNode.args)>0 && treeNode.args[1] == :facts
                children = _get_tests_structure(treeNode.args[2], testsResults, line)
                node = FactsCollectionNode(line, getName(treeNode), children)
                push!(result, node)
            elseif length(treeNode.args)>0 && treeNode.args[1] == :context
                children = _get_tests_structure(treeNode.args[2], testsResults, line)
                node = ContextNode(line, getName(treeNode), children)
                push!(result, node)
            elseif length(treeNode.args)>0 && treeNode.args[1] == Symbol("@fact")
               node = isempty(testsResults)? FactNode(line, getName(treeNode)):FactNode(line, getName(treeNode),  pop!(testsResults))
               push!(result, node)
            else
                append!(result, _get_tests_structure(treeNode, testsResults, line))
            end
        end
    end
    result
end


get_tests_structure(testFilePath::AbstractString) = testFilePath |> _get_file_content |> _get_tests_structure

function _get_results(testFilePath::AbstractString)
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
  results |> reverse
end

function run_all_tests(testFilePath::AbstractString)
  results = _get_results(testFilePath)
  content = _get_file_content(testFilePath)
  _get_tests_structure(content, results)
end

children(node::FactNode) = Vector{TestStructureNode}()
children(node::TestStructureNode) =  node.children
line(node::TestStructureNode) = node.line
name(node::TestStructureNode) = node.name
result(node::FactNode) = node.result
details(node::FactNode) = node.details

include("TestRunnerJSON.jl")

get_tests_structure_as_json(testFilePath::AbstractString) = testFilePath |> get_tests_structure |> json

get_tests_results_as_json(testFilePath::AbstractString) = testFilePath |> run_all_tests |> json

end # module
