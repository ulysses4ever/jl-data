using JSON

function json(testStructureNodes::Array{TestRunner.TestStructureNode})
  treeDictionary = [to_dict(node) for node in testStructureNodes]
  JSON.json(treeDictionary)
end

function to_dict(factGroup::FactsCollectionNode)

  childFactGroups = filter(child -> isa(child, TestRunner.FactsCollectionNode), factGroup.children)
  childFacts = filter(child -> isa(child, TestRunner.FactNode), factGroup.children)
  childContexts = filter(child -> isa(child, TestRunner.ContextNode), factGroup.children)

  Dict(
    "name" => factGroup.name,
    "line" => factGroup.line,
    "factGroups" => [to_dict(node) for node in childFactGroups],
    "facts" => [to_dict(node) for node in childFacts],
    "contexts" => [to_dict(node) for node in childContexts]
  )
end

function to_dict(contextNode::ContextNode)
  Dict(
    "name" => contextNode.name,
    "line" => contextNode.line,
    "facts" => [to_dict(node) for node in contextNode.children]
  )
end

function to_dict(factNode::FactNode)
  Dict(
    "name" => factNode.name,
    "line" => factNode.line,
    "succeeded" => isnull(factNode.result)? nothing : get(factNode.result),
    "details" => isnull(factNode.details)? nothing : get(factNode.details)
  )
end
