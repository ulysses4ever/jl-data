function retrieve!(quad::Quadtree, shape::Shape)
    global points_quad = Point[]
    global points_shape = Point[]
    cont = 0
    cont2 = 0
    global trace_index_fake_object = get_trace_index_shape(quad.rect, shape)
    halfquad_inside = false

    for i = 1:length(shape.bounds[:,1])
        push!(points_shape, Point(shape.bounds[i,:]))
    end

    if length(shape.bounds[:,1])-3 < 0
        array_aux_x = line_test.bounds[:,1]
        array_aux_y = line_test.bounds[:,2]
        push!(array_aux_x, minimum(array_aux_x))
        push!(array_aux_y, minimum(array_aux_y)+1)
        array_aux = [array_aux_x array_aux_y]
        shape_edited = Shape(array_aux)
    end

    function retrieve_inside!(quad::Quadtree, shape_test::Shape)
        xx = (maximum(quad.shape.bounds[:,1]) + minimum(quad.shape.bounds[:,1])) / 2
        yy = (maximum(quad.shape.bounds[:,2]) + minimum(quad.shape.bounds[:,2])) / 2

        for i = 1:length(quad.objects)
            push!(list_of_objects, quad.objects[i])
        end
        cont2 += 1
        println("level: ", cont)
        println(cont2, " - ", length(list_of_objects), " objects")




            #=
            if isdefined(quad, :ne)
            if isinside(quad.ne.rect, points_shape)
            cont += 1
            retrieve_inside!(quad.ne, shape_test)
            cont -= 1
            end
            end
            if isdefined(quad, :nw)
            if isinside(quad.nw.rect, points_shape)
            cont += 1
            retrieve_inside!(quad.nw, shape_test)
            cont -= 1
            end
            end
            if isdefined(quad, :sw)
            if isinside(quad.sw.rect, points_shape)
            cont += 1
            retrieve_inside!(quad.sw, shape_test)
            cont -= 1
            end
            end
            if isdefined(quad, :se)
            if isinside(quad.se.rect, points_shape)
            cont += 1
            retrieve_inside!(quad.se, shape_test)
            cont -= 1
            end
            end
            =#

        #println("begin of half-quad inside shape_test")
        for i = 0:length(shape.bounds[:,1])-3
            Area = 1/2*(-points_shape[2+i].y*points_shape[3+i].x + points_shape[1].y*(-points_shape[2+i].x + points_shape[3+i].x) + points_shape[1].x*(points_shape[2+i].y - points_shape[3+i].y) + points_shape[2+i].x*points_shape[3+i].y)

            s = 1/(2*Area)*(points_shape[1].y*points_shape[3+i].x - points_shape[1].x*points_shape[3+i].y + (points_shape[3+i].y - points_shape[1].y)*xx + (points_shape[1].x - points_shape[3+i].x)*yy)

            t = 1/(2*Area)*(points_shape[1].x*points_shape[2+i].y - points_shape[1].y*points_shape[2+i].x + (points_shape[1].y - points_shape[2+i].y)*xx + (points_shape[2+i].x - points_shape[1].x)*yy);

            #println(s>=0 && t>=0 && 1-s-t>=0)
            # Test whether half-quad is inside the shape_test
            # if < s>=0 && t>=0 && 1-s-t>=0 > then it is inside
            if s>=0 && t>=0 && 1-s-t>=0
                halfquad_inside = true
                if cont <= max_level_quadtree[1]

                    if isdefined(quad, :ne)
                        cont += 1
                        retrieve_inside!(quad.ne, shape_test)
                        cont -= 1
                    end
                    if isdefined(quad, :nw)
                        cont += 1
                        retrieve_inside!(quad.nw, shape_test)
                        cont -= 1
                    end
                    if isdefined(quad, :sw)
                        cont += 1
                        retrieve_inside!(quad.sw, shape_test)
                        cont -= 1
                    end
                    if isdefined(quad, :se)
                        cont += 1
                        retrieve_inside!(quad.se, shape_test)
                        cont -= 1
                    end
                    halfquad_inside = false
                    return nothing
                end

            else
                if isdefined(quad, :ne)
                    if isinside(quad.ne.rect, points_shape)
                        cont += 1
                        retrieve_inside!(quad.ne, shape_test)
                        cont -= 1
                    end
                end
                if isdefined(quad, :nw)
                    if isinside(quad.nw.rect, points_shape)
                        cont += 1
                        retrieve_inside!(quad.nw, shape_test)
                        cont -= 1
                    end
                end
                if isdefined(quad, :sw)
                    if isinside(quad.sw.rect, points_shape)
                        cont += 1
                        retrieve_inside!(quad.sw, shape_test)
                        cont -= 1
                    end
                end
                if isdefined(quad, :se)
                    if isinside(quad.se.rect, points_shape)
                        cont += 1
                        retrieve_inside!(quad.se, shape_test)
                        cont -= 1
                    end
                end

            end
        end
    end
    retrieve_inside!(quad, shape_edited)
end

function isinside(rect::Rectangle, points::Vector{Point})
    for i=1:length(points)
        xxx = points[i].x > rect.x0 && points[i].x < rect.x1
        yyy = points[i].y > rect.y0 && points[i].y < rect.y1

        if xxx && yyy
            return true
        else
            return false
        end
    end
    return false
end
