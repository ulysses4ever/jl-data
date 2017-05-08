function get_trace_index_shape(rect::Rectangle, shape::Shape)
    global level
    global trace_index
    #global max_level_quadtree
    global trace_index_fake_object

    index = get_index(rect, shape)
    push!(trace_index, index)

    if(level < max_level_quadtree[1] - 1 && index != -1)
        rect = split!(rect, index)
        level += 1
        get_trace_index_shape(rect, shape)
    else
        trace_index_fake_object = trace_index
        trace_index = Int64[]
        level = 0
        return trace_index_fake_object
    end
end
