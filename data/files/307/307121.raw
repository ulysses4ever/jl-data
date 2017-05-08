function retrieve!(quad::Quadtree, shape::Shape, number_of_points::Int64)

    trace_index_fake_object = get_trace_index_shape(quad.rect, shape)

        cont = 1

        for i = 1:length(quad.objects)
            push!(list_of_objects, quad.objects[i])
        end

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

        return nothing

    end

    return nothing
end
