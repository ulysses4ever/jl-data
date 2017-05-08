context("FactNode parsing") do
""
  @fact TestRunner.to_dict(FactNode(18, "test name")) -->
    Dict("name" => "test name", "line" => 18, "result" => "test_not_run", "details" => "", "stacktrace" => "")

  @fact TestRunner.to_dict(FactNode(18, "test name", test_success)) -->
    Dict("name" => "test name", "line" => 18, "result" => "test_success", "details" => "", "stacktrace" => "" )

  @fact TestRunner.to_dict(FactNode(18,"test name", test_failure)) -->
    Dict("name" => "test name", "line" => 18, "result" => "test_failure", "details" => "", "stacktrace" => "" )

  @fact TestRunner.to_dict(FactNode(18,"test name", test_failure, "Test details")) -->
    Dict("name" => "test name", "line" => 18, "result" => "test_failure", "details" => "Test details", "stacktrace" => "")

end

context("FactsCollectionNode parsing") do
  @fact TestRunner.to_dict(FactsCollectionNode(10, "some facts group", [])) -->
    Dict(
    "name" => "some facts group",
    "line" => 10,
    "facts" => [], "contexts" => [], "factGroups" => []
    )

  @fact TestRunner.to_dict(FactsCollectionNode(1,"fg", [FactNode(18,"test node")])) -->
    Dict(
    "facts" => [Dict("name" => "test node", "line" => 18, "result" => "test_not_run", "details" => "", "stacktrace" => "")],
    "name" => "fg","line" => 1,
    "contexts" => [], "factGroups" => [])

  @fact TestRunner.to_dict(FactsCollectionNode(1,"fg", [ContextNode(10,"Context name", [])])) -->
    Dict(
    "contexts" => [Dict("name" => "Context name", "line" => 10, "facts" => [])],
    "name" => "fg", "line" => 1,
    "facts" => [], "factGroups" => [])

  @fact TestRunner.to_dict(FactsCollectionNode(1, "fg", [FactsCollectionNode(15, "Nested facts node", [])])) -->
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
    "facts" => [Dict("name" => "fact node", "line" => 3, "result" => "test_not_run", "details" => "", "stacktrace" => "")]
    )
end


context("Tree to JSON parsing") do

  sampleTestStructure = Vector{TestStructureNode}([
     FactsCollectionNode(7,"First facts group",
     [FactNode(8, "First group first test"),FactNode(9, "First group second failing test")]),
     FactsCollectionNode(12,"Second facts group",
     [FactNode(13,"Second group first test"),FactNode(14, "")]),
     FactsCollectionNode(17,"",
     [FactNode(18,""),FactNode(19,"")]),
     FactsCollectionNode(21,"",[])
   ])

end
