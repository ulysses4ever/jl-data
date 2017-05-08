function retrieve!(quad::Quadtree, shape_test::Shape)
    global points_shape = Point[]
    global points_shape_test = Point[]
    cont = 0
    cont2 = 0
    global trace_index_fake_object = get_trace_index_shape(quad.rect, shape_test)
    halfquad_inside = false

    for i = 1:length(quad.shape.bounds[:,1])
        push!(points_shape, Point(quad.shape.bounds[i,:]))
    end

    for i = 1:length(shape_test.bounds[:,1])
        push!(points_shape_test, Point(shape_test.bounds[i,:]))
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

        #println("begin of half-quad inside shape_test")
        for i = 0:length(shape_test.bounds[:,1])-3
            Area = 1/2*(-points_shape_test[2+i].y*points_shape_test[3+i].x + points_shape_test[1].y*(-points_shape_test[2+i].x + points_shape_test[3+i].x) + points_shape_test[1].x*(points_shape_test[2+i].y - points_shape_test[3+i].y) + points_shape_test[2+i].x*points_shape_test[3+i].y)

            s = 1/(2*Area)*(points_shape_test[1].y*points_shape_test[3+i].x - points_shape_test[1].x*points_shape_test[3+i].y + (points_shape_test[3+i].y - points_shape_test[1].y)*xx + (points_shape_test[1].x - points_shape_test[3+i].x)*yy)

            t = 1/(2*Area)*(points_shape_test[1].x*points_shape_test[2+i].y - points_shape_test[1].y*points_shape_test[2+i].x + (points_shape_test[1].y - points_shape_test[2+i].y)*xx + (points_shape_test[2+i].x - points_shape_test[1].x)*yy);

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
                for j = 1:length(points_shape_test)
                    if points_shape_test[j].x > xx &&
                        points_shape_test[j].x < quad.shape.bounds[:,1] &&
                        points_shape_test[j].y
                end

            end
        end

        if !halfquad_inside
            #println("begin of shape_test inside shape")
            for i = 1:length(quad.objects)
                push!(list_of_objects, quad.objects[i])
            end

            if isdefined(quad, :ne)
                if isinside(quad.ne.rect, points_shape_test)
                    cont += 1
                    retrieve_inside!(quad.ne, shape_test)
                    cont -= 1
                end
            end
            if isdefined(quad, :nw)
                if isinside(quad.nw.rect, points_shape_test)
                    cont += 1
                    retrieve_inside!(quad.nw, shape_test)
                    cont -= 1
                end
            end
            if isdefined(quad, :sw)
                if isinside(quad.sw.rect, points_shape_test)
                    cont += 1
                    retrieve_inside!(quad.sw, shape_test)
                    cont -= 1
                end
            end
            if isdefined(quad, :se)
                if isinside(quad.se.rect, points_shape_test)
                    cont += 1
                    retrieve_inside!(quad.se, shape_test)
                    cont -= 1
                end
            end

            println("end of shape_test inside shape")

        end

    end
    retrieve_inside!(quad, shape_test)
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
