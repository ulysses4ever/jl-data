module TestRunner

export  get_tests_structure, run_all_tests, get_tests_structure_as_json, get_tests_results_as_json, children, line, name, result, details, test_success, test_failure, test_error, test_pending, test_not_run

using FactCheck

abstract TestStructureNode

@enum RESULT test_success test_failure test_error test_pending test_not_run

type RootNode <: TestStructureNode
  children::Vector{TestStructureNode}
end

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
    result::RESULT
    details::AbstractString
    stacktrace::AbstractString
end

FactNode(line::Int, name::AbstractString, result::RESULT) = FactNode(line, name, result, "")
FactNode(line::Int, name::AbstractString, result::RESULT, details::AbstractString) = FactNode(line, name, result, details, "")
FactNode(line::Int, name::AbstractString, result::FactCheck.Success) = FactNode(line, name, test_success, _get_details(line, result))
FactNode(line::Int, name::AbstractString, result::FactCheck.Pending) = FactNode(line, name, test_pending, _get_details(line, result))
FactNode(line::Int, name::AbstractString, result::FactCheck.Failure) = FactNode(line, name, test_failure, _get_details(line, result))
FactNode(line::Int, name::AbstractString, result::FactCheck.Error)   = FactNode(line, name, test_error,   _get_details(line, result), sprint(showerror, result.err, result.backtrace))
FactNode(line::Int, name::AbstractString) = FactNode(line, name, test_not_run)

_get_details(line::Int, result::FactCheck.Result) = replace(sprint(show, result), r"line:(-?\d+)", "line:$line")

function _fixLineNumbers(expressionTreeNode::Expr)
  for i in 1:length(expressionTreeNode.args)
      expressionTreeNode.args[i] = _fixLineNumbers(expressionTreeNode.args[i])
  end

  expressionTreeNode
end
_fixLineNumbers(lineNumberNode::LineNumberNode) = LineNumberNode(lineNumberNode.file, lineNumberNode.line - 1)
_fixLineNumbers(othernNode) = othernNode

_get_file_content(testFilePath::AbstractString) = testFilePath |> readall |> (content -> "begin\n" * content * "\nend") |> parse |> _fixLineNumbers

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

get_tests_structure(testFilePath::AbstractString) = testFilePath |> _get_file_content |> _get_tests_structure |> RootNode

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
  _get_tests_structure(content, results) |> RootNode
end

children(node::FactNode) = Vector{TestStructureNode}()
children(node::TestStructureNode) =  node.children
line(node::RootNode) = 0
line(node::TestStructureNode) = node.line
name(node::RootNode) = "root"
name(node::TestStructureNode) = node.name
result(node::FactNode) = node.result
details(node::FactNode) = node.details
stacktrace(node::FactNode) = node.stacktrace

include("TestRunnerJSON.jl")

get_tests_structure_as_json(testFilePath::AbstractString) = testFilePath |> get_tests_structure |> json

get_tests_results_as_json(testFilePath::AbstractString) = testFilePath |> run_all_tests |> json

end # module
