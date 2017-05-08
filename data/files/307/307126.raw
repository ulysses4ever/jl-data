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
    push!(points_shape, Point(shape.bounds[1,:]))

    ## test if point inside quad or quad inside shape
    ## else do it \/
    if length(points_shape) == 4
        l = quad.x0
        r = quad.x1
        t = quad.y0
        b = quad.y1


        for i = 1:3
            x1 = points_shape[i].x
            y1 = points_shape[i].y
            x2 = points_shape[i+1].x
            y2 = points_shape[i+1].y

            m = (x2-x1) != 0 ? (y2-y1)/(x2-x1) : pi
            c = y1 - (m*x1)

            if m>0 && m!=pi
                top_intersection = (m*l  + c)
                bottom_intersection = (m*r  + c)
            else
                top_intersection = (m*r  + c)
                bottom_intersection = (m*l  + c)
            end

            if y1 < y2
                toptrianglepoint = y1
                bottomtrianglepoint = y2
            else
                toptrianglepoint = y2
                bottomtrianglepoint = y1
            end

            topoverlap = top_intersection > toptrianglepoint ? top_intersection : toptrianglepoint
            botoverlap = bottom_intersection < bottomtrianglepoint ? bottom_intersection : bottomtrianglepoint

            isinside = (topoverlap < botoverlap) && (!((botoverlap<t)||(topoverlap>b)))
            println(isinside)
        end
    end

end
