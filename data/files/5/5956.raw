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

using TestRunner: TestStructureNode, RootNode, FactsCollectionNode, FactNode, ContextNode

include("testComparisons.jl")

sampleTestsFilePath = "FileWithSampleTests.jl"
sampleExceptionFailingTestFilePath = "FileWithExceptionFailingTest.jl"

facts("Test handling tests") do
  context("File loading") do
      @fact TestRunner._get_file_content(sampleTestsFilePath) --> sampleTests
  end

  context("Structure parsing") do
   @fact TestRunner._get_tests_structure(sampleTests) --> Vector{TestStructureNode}([
                                                        FactsCollectionNode(6,"First facts group",
                                                        [FactNode(7, "First group first test"),FactNode(8, "First group second failing test")]),
                                                        FactsCollectionNode(11,"Second facts group",
                                                        [FactNode(12,"Second group first test"),FactNode(13, "")]),
                                                        FactsCollectionNode(16,"",
                                                        [FactNode(17,""),FactNode(18,"")]),
                                                        FactsCollectionNode(20,"",[])
                                                      ])

  @fact get_tests_structure(sampleTestsFilePath) --> RootNode(Vector{TestStructureNode}([
                                                       FactsCollectionNode(6,"First facts group",
                                                       [FactNode(7, "First group first test"),FactNode(8, "First group second failing test")]),
                                                       FactsCollectionNode(11,"Second facts group",
                                                       [FactNode(12,"Second group first test"),FactNode(13, "")]),
                                                       FactsCollectionNode(16,"",
                                                       [FactNode(17,""),FactNode(18,"")]),
                                                       FactsCollectionNode(20,"",[])
                                                     ])) "File structure parsing"
 end


  context("Tests running") do
    @pending run_all_tests(sampleTestsFilePath) --> RootNode( Vector{TestStructureNode}([
                                                         FactsCollectionNode(6, "First facts group",
                                                          [FactNode(7, "First group first test", test_success), FactNode(8, "First group second failing test", test_failure)]),
                                                         FactsCollectionNode(11,"Second facts group",
                                                          [FactNode(12, "Second group first test", test_success), FactNode(13, "", test_success)]),
                                                         FactsCollectionNode(16, "",
                                                          [FactNode(17, "", test_success), FactNode(18, "", test_failure)]),
                                                         FactsCollectionNode(20,"",[])
                                                       ])) "Tests running"
  end

  context("Exception handling") do
    message = "TestName\nDoge\n in f at $(abspath(sampleExceptionFailingTestFilePath)):2"
    @pending run_all_tests(sampleExceptionFailingTestFilePath) --> Vector{TestStructureNode}([FactsCollectionNode(3,"",[FactNode(4,"TestName", false, message)])])
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
