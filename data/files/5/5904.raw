module TestRunner

export  get_tests_structure, run_all_tests, get_tests_structure_as_json, get_tests_results_as_json,
        children, line, name, result, details, stacktrace,
        RESULT, test_success, test_failure, test_error, test_pending, test_not_run

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

_get_details(line::Int, result::FactCheck.Result) = _replace_line_number(line, sprint(show, result)) |> _strip_ascii_escape_codes
_replace_line_number(line::Int, s::AbstractString) = replace(s, r"line:(-?\d+)", "line:$line")
_strip_ascii_escape_codes(s::AbstractString) = replace(s, r"\x1b[^m]*m", "")

get_tests_structure(test_file_path::AbstractString) = test_file_path |> _get_file_content |> _get_tests_structure |> RootNode

_get_file_content(test_file_path::AbstractString) = test_file_path |> readall |> (content -> "begin\n" * content * "\nend") |> parse |> _fixLineNumbers!

function _fixLineNumbers!(expression_tree_node::Expr)
  map!(_fixLineNumbers!, expression_tree_node.args)
  expression_tree_node
end
_fixLineNumbers!(line_number_node::LineNumberNode) = LineNumberNode(line_number_node.file, line_number_node.line - 1)
_fixLineNumbers!(other) = other
_fixLineNumbers(expression_tree_node::Expr) = _fixLineNumbers!(deepcopy(expression_tree_node))

function _get_tests_structure(expression_tree_node::Expr, tests_results::Vector{FactCheck.Result} = FactCheck.Result[] , line::Int = 0)
    results = Vector{TestStructureNode}()
    for child_node in expression_tree_node.args
        line = get(_try_get_line(child_node), line)
        _procces_expression_tree_node(child_node, results, tests_results, line)
    end
    results
end

_try_get_line(node::LineNumberNode) = Nullable{Int}(node.line)
_try_get_line(_) = Nullable{Int}()

function _procces_expression_tree_node(tree_node::Expr, results::Vector{TestStructureNode}, tests_results::Vector{FactCheck.Result}, line::Int)
  length(tree_node.args)>0 || return

  get_name(expr::Expr) = length(expr.args)>2?expr.args[3]:""
  get_children(expr::Expr) = _get_tests_structure(expr.args[2], tests_results, line)
  get_fact_result!(rs::Vector{FactCheck.Result}) =  isempty(rs)?test_not_run:pop!(rs)
  dump_pending_test_result!(rs::Vector{FactCheck.Result}) = isempty(rs) || pop!(rs)
  create_custom_pending_details(expr::Expr) = "$(expr.args[2].args[1]) $(expr.args[2].head) $(expr.args[2].args[2])"

  if tree_node.args[1] == :facts
      node = FactsCollectionNode(line, get_name(tree_node), get_children(tree_node))
      push!(results, node)
  elseif tree_node.args[1] == :context
      node = ContextNode(line, get_name(tree_node), get_children(tree_node))
      push!(results, node)
  elseif  tree_node.args[1] == Symbol("@fact")
     node =  FactNode(line, get_name(tree_node), get_fact_result!(tests_results))
     push!(results, node)
  elseif tree_node.args[1] == Symbol("@pending")
      dump_pending_test_result!(tests_results)
      node = FactNode(line, get_name(tree_node), test_pending, create_custom_pending_details(tree_node) )
      push!(results, node)
  else
      append!(results, _get_tests_structure(tree_node, tests_results, line))
  end
end

_procces_expression_tree_node(_...) = nothing

function run_all_tests(test_file_path::AbstractString)
  results = _get_results(test_file_path)
  content = _get_file_content(test_file_path)
  _get_tests_structure(content, results) |> RootNode
end

function _get_results(test_file_path::AbstractString)
  original_allresults  = FactCheck.allresults
  FactCheck.clear_results()
  original_STDOUT = STDOUT
  (out_read, out_write) = redirect_stdout()

  evalfile(test_file_path)

  close(out_write)
  close(out_read)
  redirect_stdout(original_STDOUT)
  results = copy(FactCheck.allresults)
  empty!(FactCheck.allresults)
  append!(FactCheck.allresults, original_allresults)
  results |> reverse
end

children(_::FactNode) = Vector{TestStructureNode}()
children(node::TestStructureNode) =  node.children
line(_::RootNode) = 0
line(node::TestStructureNode) = node.line
name(_::RootNode) = "root"
name(node::TestStructureNode) = node.name
result(node::FactNode) = node.result
details(node::FactNode) = node.details
stacktrace(node::FactNode) = node.stacktrace

include("TestRunnerJSON.jl")

get_tests_structure_as_json(test_file_path::AbstractString) = test_file_path |> get_tests_structure |> json

get_tests_results_as_json(test_file_path::AbstractString) = test_file_path |> run_all_tests |> json

end # module
