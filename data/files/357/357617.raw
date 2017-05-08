module TestGraphTools

using Base.Test
using FactCheck

include("graph_tools.jl")


facts("Testing graph_tools.jl") do
	adjmx1 = [1 0; 0 1]
    g1 = MyDiGraph(adjmx1)
    @fact is_strongly_connected(g1) => false

    adjmx2 = [0 1; 1 1]
    cyclic_components2 = Array[[1, 2]]
    g2 = MyDiGraph(adjmx2)
    @fact is_strongly_connected(g2) => true
    @fact is_aperiodic(g2) => true
    @fact period(g2) => 1
    @fact cyclic_components(g2) => cyclic_components2

    adjmx3 = [0 1; 1 0]
    cyclic_components3 = Array[[1], [2]]
    g3 = MyDiGraph(adjmx3)
    @fact is_strongly_connected(g3) => true
    @fact is_aperiodic(g3) => false
    @fact period(g3) => 2
    @fact cyclic_components(g3) => cyclic_components3

    adjmx4 = [0 0 1 0 0 0
              1 0 0 0 0 0
              0 0 0 1 1 0
              0 1 0 0 0 0
              0 0 0 0 0 1
              0 0 0 1 0 0]
    cyclic_components4 = Array[[1, 4, 5], [2, 3, 6]]
    g4 = MyDiGraph(adjmx4)
    @fact is_strongly_connected(g4) => true
    @fact is_aperiodic(g4) => false
    @fact period(g4) => 2
    ccs = cyclic_components(g4)
    for cc in ccs
    	sort!(cc)
    end
    @fact ccs => cyclic_components4
end

end
