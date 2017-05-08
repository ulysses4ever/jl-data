using Graphs

metadata = [["label" => "test1", "value" => "test", "a" => ["x", "y"]], ["label" => "test2", "a" => ["y"]], ["label" => "test3", "a" => ["x", "y"]]]
P = [1 0.5 0.01; 0.5 1 0.02; 0.01 0.02 1]
g1 = filtergraph(metadata, P, "pval", x->x<0.015)
@test num_edges(g1) == 1
@test source(edges(g1)[1]).attributes["value"] == "test"
@test source(edges(g1)[1]).label == "test1"
@test target(edges(g1)[1]).label == "test3"

g2 = filtergraph(metadata, P, "pval", x->x<=0.02)
@test num_edges(g2) == 2

@test matchededges(g1, g2, "label") == 1
@test matchededges(g2, g2, "label") == 2

# make sure the directionality of the undirected edge specification does not effect things
srand(1)
g3 = filtergraph(metadata, P, "pval", x->x<0.9)
g4 = deepcopy(g3)
permutevertices!(vertices(g4))
@test matchededges(g4, g3, "label") == 3

srand(1)
permutevertices!(vertices(g1))
@test vertices(g1)[1].label == "test2"
@test vertices(g1)[1].attributes["a"] == ["y"]


srand(1)
enrichment, pval = permutationtest(x->matchededges(x, g2, "label"), g1)
@test pval > 0.6 # real value is 2/3
@test pval < 0.7
@test enrichment > 1.2

srand(1)
enrichment, pval = permutationtest(x->matchededges(x, g2, "label"), g2)
@test pval > 0.3 # real value is 1/3
@test pval < 0.4
@test enrichment > 1.2

srand(1)
enrichment, pval = permutationtest(x->matchededges(x, g1, "label"), g1)
@test pval > 0.3 # real value is 1/3
@test pval < 0.4
@test enrichment > 1.2


g5 = loadedgelist("edgelist.csv", "label")
@test num_vertices(g5) == 3
@test num_edges(g5) == 3
@test source(edges(g5)[1]).label == "a"
@test target(edges(g5)[1]).label == "b"


g6 = vertexinduce(vertices(g5)[1:2], g5)
@test num_edges(g6) == 1
@test num_vertices(g6) == 2
