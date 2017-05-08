using TestRunner
using FactCheck

sampleTests = quote
  using FactCheck

  facts("First facts group") do
    @fact 1 --> 1 "First group first test"
    @fact 2 --> 1 "First group second failing test"
  end

  facts("Second facts group") do
    @fact 1 --> 1 "Second group first test"
    @fact 2 --> 2 #Nameless fact
  end

  facts() do #Nameless group
    @fact 1 --> 1 #Nameless fact
    @fact 2 --> 1 #Failing nameless fact in nameless group
  end
  facts() do
  end
end

facts("Facts groups tests") do
  @fact TestRunner.get_facts_groups(sampleTests) --> [
                                                       ("First facts group", ["First group first test", "First group second failing test"]),
                                                       ("Second facts group", ["Second group first test", ""]),
                                                       ("", ["",""]),
                                                       ("",[])
                                                     ]
 @fact TestRunner._get_tests_structure(sampleTests) --> Vector{TestStructureNode}([
                                                      FactsNode(7,"First facts group",
                                                      [FactNode(8, "First group first test"),FactNode(9, "First group second failing test")]),
                                                      FactsNode(12,"Second facts group",
                                                      [FactNode(13,"Second group first test"),FactNode(14, "")]),
                                                      FactsNode(17,"",
                                                      [FactNode(18,""),FactNode(19,"")]),
                                                      FactsNode(21,"",[])
                                                    ])
end

facts("File loading tests") do
    @fact TestRunner.get_file_content("sampleTests.jl") --> sampleTests
end

facts("Children function tests") do
  @fact children(FactNode(42, "Test")) --> Vector{TestStructureNode}()
  @pending children(FactsNode(17,"", [FactNode(18,""),FactNode(19,"")])) --> Vector{TestStructureNode}([FactNode(18,""),FactNode(19,"")])
end

facts("JSON parsing tests") do
  include("TestRunnerJSON.tests.jl")
end

FactCheck.exitstatus()
