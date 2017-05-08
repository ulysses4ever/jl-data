function retrieve!(quad::Quadtree, shape_test::Shape)
    global points_shape = Point[]
    global points_shape_test = Point[]

    for i = 1:length(quad.shape.bounds[:,1])
        push!(points_shape, Point(shape.bounds[i,:]))
    end

    for i = 1:length(shape_test.bounds[:,1])
        push!(points_shape_test, Point(shape_test.bounds[i,:]))
    end

    cont = 1
    retrieve_inside!(quad::Quadtree, shape_test::Shape)
        trace_index2 = get_index(shape.rect, shape_test)

        if trace_index2 != -1

            if(cont <= max_level_quadtree[1] && isdefined(trace_index_fake_object, cont))

                if(isdefined(quad, :ne) && trace_index_fake_object[cont] == 1)
                    cont += 1
                    retrieve_inside!(quad.ne, shape)
                    cont -= 1
                end
                if(isdefined(quad, :nw) && trace_index_fake_object[cont] == 2)
                    cont += 1
                    retrieve_inside!(quad.nw, shape)
                    cont -= 1
                end
                if(isdefined(quad, :sw) && trace_index_fake_object[cont] == 3)
                    cont += 1
                    retrieve_inside!(quad.sw, shape)
                    cont -= 1
                end
                if(isdefined(quad, :se) && trace_index_fake_object[cont] == 4)
                    cont += 1
                    retrieve_inside!(quad.se, shape)
                    cont -= 1
                end

            end

            return "Found a collision (shape_test inside shape)"
        end

end
