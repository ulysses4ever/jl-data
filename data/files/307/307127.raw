function retrieve(quad::Rectangle, bounds::Shape, returned_objects::Vector{Dict})
    global max_level_quadtree
    global retrieve_level
    global rect_bounds = quad
    global index
    global trace_index_fake_object
    global possible_candidates = Dict[]

    x_in = bounds.bounds[1,:1] > quad.x0 && bounds.bounds[1,:1] < quad.x1
    y_in = bounds.bounds[1,:2] > quad.y0 && bounds.bounds[1,:2] < quad.y1

    index = get_index(rect_bounds, bounds)
    if(x_in && y_in)
        rect_bounds = split!(rect_bounds, index)

        for i = 1:length(list_of_objects)

            isset = try
                a = list_of_objects[i]["trace_index"][retrieve_level]
                #print("TRUE - list_of_objects[$i][\"trace_index\"][$retrieve_level] = ")
                #println(a)
                #println("$list_of_objects[$i][\"trace_index\"][$retrieve_level]")
                true
            catch e
                #println("FALSE - list_of_objects[$i][\"trace_index\"][$retrieve_level]")
                #println("$list_of_objects[$i][\"trace_index\"][$retrieve_level]")
                false
            end

            isset_next = try
                index_fake = list_of_objects[i]["trace_index"][retrieve_level + 1]
                true
            catch e
                false
            end

            if(isset)
                #if(isset_next && list_of_objects[i]["trace_index"][retrieve_level + 1] == -1)
                if(isset_next)
                    if(index_fake = trace_index_fake_object[retrieve_level])
                        push!(returned_objects, list_of_objects[i])
                    end
                end

                #=
                if(list_of_objects[i]["trace_index"][retrieve_level] != index)
                    returned_objects[i] = Dict()
                end
                =#
            end

        end
        retrieve_level+=1
    end

    if(retrieve_level <= max_level_quadtree + 1)
        #println()
        retrieve(rect_bounds, bounds, returned_objects)
    end
end
