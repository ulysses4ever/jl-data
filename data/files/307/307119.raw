function retrieve(quad::Vector{Quadtree}, returned_objects::Vector{Dict})
    #global trace_index_fake_object
    #global max_level_quadtree
    #global list_of_objects

    points = get_points_from_shape(point_test, returned_points)
    for cont = 1:length(points)

        trace_index_fake_object = get_trace_index_shape(quad, points[cont])
        #println(trace_index_fake_object)
        ##TODO tree - add on insert! - nao parece dificil
        @time for i = 1:length(list_of_objects)

            for retrieve_level = 1:max_level_quadtree
                #println(retrieve_level)

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
                    a = list_of_objects[i]["trace_index"][retrieve_level + 1]
                    true
                catch e
                    false
                end

                isset_point = try
                    a = trace_index_fake_object[retrieve_level]
                    true
                catch e
                    false
                end

                if(isset_point && isset && isset_next)
                    if(list_of_objects[i]["trace_index"][retrieve_level] == trace_index_fake_object[retrieve_level] && list_of_objects[i]["trace_index"][retrieve_level + 1] == -1)
                        global is_duplicate = begin
                            x = false
                            for f in returned_objects
                                if(list_of_objects[i] == f)
                                    x = true
                                end
                            end
                            x
                        end
                        if(is_duplicate == false)
                            push!(returned_objects, list_of_objects[i])
                        end
                    end
                end
            end
        end
    end
end
