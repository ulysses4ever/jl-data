module TestRunner

get_file_content(testFilePath::AbstractString) = testFilePath |> readall |> parse
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

end # module
