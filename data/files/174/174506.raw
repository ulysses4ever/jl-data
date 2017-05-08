using Mustache
using GraphLayout
using DataFrames
using Colors

function Base.writemime(f::IO, ::MIME"image/svg+xml", nw::CommunityNetwork)

    A = adjacency_matrix(nw.graph)
    nx, ny = layout_spring_adj(full(A))

    scale = sqrt(length(nw.graph.vertices))/sqrt(200)
    trans(x) = scale*250.0*x+250.0


    #=
    first = Int[l.first for l in nw.graph.edges]
    second = Int[l.second for l in nw.graph.edges]

    edge_df=DataFrame(x1s=trans(nx[first]),
                    x2s=trans(nx[second]),
                    y1s=trans(ny[first]),
                    y2s=trans(ny[second]))


    node_df=DataFrame(xs=trans(nx),
                      ys=trans(ny))
    =#

    gedges = collect(nw.graph.edges)
    edges = Array(Dict{Any,Any}, length(gedges))
    for i in 1:length(gedges)
        edges[i] = {:x1s=>trans(nx[gedges[i].first]),
                    :x2s=>trans(nx[gedges[i].second]),
                    :y1s=>trans(ny[gedges[i].first]),
                    :y2s=>trans(ny[gedges[i].second])}
    end

    nodes = Array(Dict{Any,Any}, length(nw.graph.vertices))
    for i in 1:length(nw.graph.vertices)
        nodes[i] = {:xs=>trans(nx[i]),
                    :ys=>trans(ny[i]),
                    :color=>"hsl($(360/nw.n_comms*nw.labels[i]),100%,50%)"}
    end
    
    template = readall(joinpath(dirname(@__FILE__()), "graph_template.svg"))
    #XXX tx and ty are a hack because I always used node 1 as the target
    svg_string = render(template, edges=edges, nodes=nodes, tx=trans(nx[1]), ty=trans(ny[1]))

    # # if you don't want to reload the svg every time:
    # filename = joinpath(dirname(@__FILE__()), "graph_template.svg")
    # svg_string = render_from_file(filename, edges=edges, nodes=nodes)


    # debugging
    # println(svg_string)

    println(f,svg_string)
end
