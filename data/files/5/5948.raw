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

include("testComparisons.jl")
sampleTestsFilePath = "FileWithSampleTests.jl"
facts("Test handling tests") do
  context("File loading") do
      @fact TestRunner.get_file_content(sampleTestsFilePath) --> sampleTests
  end

  context("Structure parsing") do
   @fact TestRunner._get_tests_structure(sampleTests) --> Vector{TestStructureNode}([
                                                        FactsCollectionNode(7,"First facts group",
                                                        [FactNode(8, "First group first test"),FactNode(9, "First group second failing test")]),
                                                        FactsCollectionNode(12,"Second facts group",
                                                        [FactNode(13,"Second group first test"),FactNode(14, "")]),
                                                        FactsCollectionNode(17,"",
                                                        [FactNode(18,""),FactNode(19,"")]),
                                                        FactsCollectionNode(21,"",[])
                                                      ])
  end

  context("Tests running") do
    @fact TestRunner.run_all_tests(sampleTestsFilePath) --> Vector{TestStructureNode}([
                                                         FactsCollectionNode(7,"First facts group",
                                                         [FactNode(8, "First group first test", true),FactNode(9, "First group second failing test", false)]),
                                                         FactsCollectionNode(12,"Second facts group",
                                                         [FactNode(13,"Second group first test", true),FactNode(14, "",true)]),
                                                         FactsCollectionNode(17,"",
                                                         [FactNode(18,"",true),FactNode(19,"",false)]),
                                                         FactsCollectionNode(21,"",[])
                                                       ])
  end

  context("Children acquiring") do
    @fact children(FactNode(42, "Test")) --> Vector{TestStructureNode}()
    @fact children(FactsCollectionNode(17,"", [FactNode(18,""),FactNode(19,"")])) --> Vector{TestStructureNode}([FactNode(18,""),FactNode(19,"")])
  end
end

facts("JSON parsing tests") do
  include("TestRunnerJSON.tests.jl")
end

FactCheck.exitstatus()
