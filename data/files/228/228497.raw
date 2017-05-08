module NetworkJ

    using Base.Collections

    export
        Graph, 
        empty_graph, 
        get_name, 
        get_index, 
        convert_index, 
        index_iter, 
        names_iter,
        name_list, 
        num_edges,
        neighbors,
        get_edges,

        add_edge!, 
        add_node!, 
        remove_node!,
        remove_edge!, 
        degree,

        subgraph, 
        ego_subgraph, 

        range_target, 
        tie_range,

        bfs, 
        connected_components,

        PriorityQueue, 
        enqueue!, 
        dequeue!

    include("types.jl")
    include("ranges.jl")
    include("subgraphs.jl")
    include("components.jl")

end