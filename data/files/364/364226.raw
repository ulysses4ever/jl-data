function retrieve!(shape::Shape, shape_test::Shape)
    global points_shape = Point[]
    global points_shape_test = Point[]

    for i = 1:length(shape.bounds[:,1])
        push!(points_shape, Point(shape.bounds[i,:]))
    end

    for i = 1:length(shape_test.bounds[:,1])
        push!(points_shape_test, Point(shape_test.bounds[i,:]))
    end

    println("begin of shape_test inside shape")
    println(get_index(shape.rect, shape_test))
    println("end of shape_test inside shape")


    println()


    println("begin of shape inside shape_test")
    if length(shape_test.bounds[:,1])>=3
        for k = 1:length(shape.bounds[:,1])
            for i = 0:length(shape_test.bounds[:,1])-3
                Area = 1/2*(-points_shape_test[2+i].y*points_shape_test[3+i].x + points_shape_test[1].y*(-points_shape_test[2+i].x + points_shape_test[3+i].x) + points_shape_test[1].x*(points_shape_test[2+i].y - points_shape_test[3+i].y) + points_shape_test[2+i].x*points_shape_test[3+i].y)

                s = 1/(2*Area)*(points_shape_test[1].y*points_shape_test[3+i].x - points_shape_test[1].x*points_shape_test[3+i].y + (points_shape_test[3+i].y - points_shape_test[1].y)*points_shape[k].x + (points_shape_test[1].x - points_shape_test[3+i].x)*points_shape[k].y)

                t = 1/(2*Area)*(points_shape_test[1].x*points_shape_test[2+i].y - points_shape_test[1].y*points_shape_test[2+i].x + (points_shape_test[1].y - points_shape_test[2+i].y)*points_shape[k].x + (points_shape_test[2+i].x - points_shape_test[1].x)*points_shape[k].y);

                println(s>=0 && t>=0 && 1-s-t>=0)
                if s>=0 && t>=0 && 1-s-t>=0
                    return "Found a collision (shape inside shape_test)"
                end
            end
        end
    end
    println("end of shape inside shape_test")

end
