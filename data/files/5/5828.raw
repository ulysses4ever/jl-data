using JSON

json(rootNode::RootNode) = map(to_dict, children(rootNode)) |> JSON.json

function to_dict(factGroup::FactsCollectionNode)
  _children = factGroup |> children
  childFactGroups = filter(child -> isa(child, FactsCollectionNode), _children)
  childFacts = filter(child -> isa(child, FactNode), _children)
  childContexts = filter(child -> isa(child, ContextNode), _children)

  Dict(
    "name"       => factGroup |> name,
    "line"       => factGroup |> line,
    "factGroups" => map(to_dict, childFactGroups),
    "facts"      => map(to_dict, childFacts),
    "contexts"   => map(to_dict, childContexts)
  )
end

to_dict(contextNode::ContextNode) = Dict(
    "name"  => contextNode |> name,
    "line"  => contextNode |> line,
    "facts" => map(to_dict, children(contextNode))
  )

to_dict(factNode::FactNode) = Dict(
    "name"         => factNode |> name,
    "line"         => factNode |> line,
    "result"       => factNode |> result |> string,
    "details"      => factNode |> details,
    "stacktrace"   => factNode |> stacktrace
  )
