##TODO if it's a point, analise!

function get_points_from_shape(point_test::Shape, number_of_points::Int64)
    siz = length(point_test.bounds[:,1])
    y = Array(Function, siz)
    max_x = maximum(point_test.bounds[:,1])
    min_x = minimum(point_test.bounds[:,1])
    max_y = maximum(point_test.bounds[:,2])
    min_y = minimum(point_test.bounds[:,2])
    POINTS_X = number_of_points
    POINTS_Y = number_of_points
    spacing = (max_x - min_x) / POINTS_X
    returned_points = Shape[]

    for i = 1:siz
        reta_vertical = false

        if(i+1 <= siz && point_test.bounds[i,1] != point_test.bounds[i+1,1])
            a = (point_test.bounds[i,2] - point_test.bounds[i+1,2]) /
                (point_test.bounds[i,1] - point_test.bounds[i+1,1])
        elseif(i+1 > siz && point_test.bounds[i,1] != point_test.bounds[1,1])
            a = (point_test.bounds[i,2] - point_test.bounds[1,2]) /
                (point_test.bounds[i,1] - point_test.bounds[1,1])
        else
            a = 1
            reta_vertical = true
        end
        if(reta_vertical != true)
            b = (point_test.bounds[i,2] - a*(point_test.bounds[i,1]))
            y[i] = x -> a*x + b
        else
            b = point_test.bounds[i,1]
        end
    end

    for p = 0:POINTS_X
        greater = -Inf
        less = Inf

        for f = 1:length(y)
            if(isdefined(y,f))
                if(y[f](min_x + spacing*p) <= max_y && y[f](min_x + spacing*p) >= min_y)
                    greater = (y[f](min_x + spacing*p) > greater) ? y[f](min_x + spacing*p) : greater
                    less = (y[f](min_x + spacing*p) < less) ? y[f](min_x + spacing*p) : less
                    #println((min_x + spacing*p), " -> ", y[f](min_x + spacing*p))
                end
            end
        end

        spacing_y = (greater - less) / POINTS_Y
        if spacing_y == 0
            s = Shape([min_x+spacing*p less])
            push!(returned_points, s)
        else
            for p_y = 0:POINTS_Y
                s = Shape([min_x+spacing*p less+spacing_y*p_y])
                push!(returned_points, s)
            end
        end
    end
    return returned_points
end
