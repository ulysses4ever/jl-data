using MyQuadtree
#using Base.Test

## Quadtree used
quad = Quadtree(0,0,160,160)

## Shapes definition
shape2      = Shape([1 1; 1 79; 79 79; 79 1])
shape3333   = Shape([1 159; 1 151; 9 151; 9 159])
shape33333  = Shape([2 158; 2 157; 8 157; 8 158])
shape31422  = Shape([61 101; 61 104; 64 101; 64 104])
shape3143   = Shape([61 111; 61 119; 69 111; 69 119])
shape3      = Shape([10 90; 70 90; 70 150; 10 150])
shape1      = Shape([150 10; 90 10; 90 70; 150 70])
shape111    = Shape([141 10; 141 15; 150 15; 150 10])
shape12     = Shape([81 1; 119 1; 119 5; 81 5])
shape_big   = Shape([1 1; 1 159; 159 159; 159 1])
shape_      = Shape([71 79; 79 79; 79 71; 71 71])

## Point used to find if there are colisions
point_test      = Shape([62 103])
line_test       = Shape([23 85; 93 115])
triangle_test   = Shape([40 140; 70 140; 60 70])

## Insert the shapes onto the quadtree
#insert!(quad, shape2)     ## quad.nw.objects          [1 1;    1 79;   79 79;  79 1]
#insert!(quad, shape31422) ##                          [61 101; 61 104; 64 101; 64 104]
#insert!(quad, shape3333)  ## quad.sw.sw.sw.sw.objects [1 159;  1 151;  9 159;  9 151]
#insert!(quad, shape3143)  ## quad.sw.ne.se.sw.objects [61 111; 61 119; 69 111; 69 119]
#insert!(quad, shape3)     ## quad.sw.objects          [10 90;  70 90;  10 150; 70 150]
#insert!(quad, shape1)
#insert!(quad, shape111)
#insert!(quad, shape12)
#insert!(quad, triangle_test)
#insert!(quad, shape_big)
#insert!(quad, shape_)

## Insert random objects inside the tree and retrieve them
const MAX_SIZE = 5
k = 5
shapes_test = Array(Shape, 10^k)

@time for i = 1:10^k
    size2 = rand(1:MAX_SIZE)

    x1 = rand(1:(159-size2))
    x2 = x1+size2
    y1 = rand(1:(159-size2))
    y2 = y1+size2
    a = [x1 y1;
         x1 y2;
         x2 y2;
         x2 y1
        ]
    s = Shape(a)
    shapes_test[i] = s
end

@time for i = 1:10^k
    MyQuadtree.insert!(quad, shapes_test[i])
end

println(@time length(retrieve!(quad, shape_big)))
println(@time length(retrieve!(quad, triangle_test)))
println(@time length(retrieve!(quad, line_test)))
println(@time length(retrieve!(quad, shape33333)))
println(@time length(retrieve!(quad, point_test)))

nothing
