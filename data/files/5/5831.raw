context("FactNode parsing") do

  @fact TestRunner.to_dict(FactNode(18,"test name")) -->
    Dict("name" => "test name", "line" => 18, "result" => nothing, "details" => nothing)

  @fact TestRunner.to_dict(FactNode(18,"test name", Nullable{Bool}(true))) -->
    Dict("name" => "test name", "line" => 18, "result" => true, "details" => nothing )

  @fact TestRunner.to_dict(FactNode(18,"test name", Nullable{Bool}(false))) -->
    Dict("name" => "test name", "line" => 18, "result" => false, "details" => nothing )

  @fact TestRunner.to_dict(FactNode(18,"test name", Nullable{Bool}(false), "Test details")) -->
    Dict("name" => "test name", "line" => 18, "result" => false, "details" => "Test details" )

end

context("FactsNode parsing") do
  @fact TestRunner.to_dict(FactsNode(10,"some facts group", [])) -->
    Dict(
    "name" => "some facts group",
    "line" => 10,
    "facts" => [], "contexts" => [], "factGroups" => []
    )

  @fact TestRunner.to_dict(FactsNode(1,"fg", [FactNode(18,"test node")])) -->
    Dict(
    "facts" => [Dict("name" => "test node", "line" => 18, "result" => nothing, "details" => nothing)],
    "name" => "fg","line" => 1,
    "contexts" => [], "factGroups" => [])

  @fact TestRunner.to_dict(FactsNode(1,"fg", [ContextNode(10,"Context name", [])])) -->
    Dict(
    "contexts" => [Dict("name" => "Context name", "line" => 10, "facts" => [])],
    "name" => "fg", "line" => 1,
    "facts" => [], "factGroups" => [])

  @fact TestRunner.to_dict(FactsNode(1, "fg", [FactsNode(15, "Nested facts node", [])])) -->
    Dict(
    "factGroups" => [Dict("name" => "Nested facts node", "line" => 15, "facts" => [], "contexts" => [], "factGroups" => [])],
    "name" => "fg", "line" => 1,
    "contexts" => [], "facts" => []
    )
end

context("ContextNode parsing") do

  @fact TestRunner.to_dict(ContextNode(1, "some context node", [])) -->
    Dict(
    "name" => "some context node",
    "line" => 1,
    "facts" => []
    )

  @fact TestRunner.to_dict(ContextNode(1, "c", [FactNode(3,"fact node")])) -->
    Dict(
    "line" => 1,
    "name" => "c",
    "facts" => [Dict("name" => "fact node", "line" => 3, "result" => nothing, "details" => nothing)]
    )
end


context("Tree to JSON parsing") do

  sampleTestStructure = Vector{TestStructureNode}([
     FactsNode(7,"First facts group",
     [FactNode(8, "First group first test"),FactNode(9, "First group second failing test")]),
     FactsNode(12,"Second facts group",
     [FactNode(13,"Second group first test"),FactNode(14, "")]),
     FactsNode(17,"",
     [FactNode(18,""),FactNode(19,"")]),
     FactsNode(21,"",[])
   ])
   
end
