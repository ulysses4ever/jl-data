function get_rectangle(shape::Shape)
    points_shape = Point[]

    for i = 1:length(shape.bounds[:,1])
        push!(points_shape, Point(shape.bounds[i,:]))
    end

    if length(points_shape) == 4 || length(points_shape) == 1
        return shape
    elseif length(points_shape) == 2
        ##TODO
    else ##length == 3 || >= 5
        x1 = points_shape[1].x
        y1 = points_shape[1].y
        x2 = points_shape[2].x
        y2 = points_shape[2].y

        if y2 != y1 && x2 != x1
            m1 = (y2-y1)/(x2-x1)
            m2 = -1/m
        elseif y2 == y1
            ## triangle is already on a base (x axis)


        else ## x2 == x1
            ## triangle is already on a base (y axis)
        end

    end


end
