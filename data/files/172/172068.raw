include("../mbr.jl")
m00 = MBR(0, 0, 0, 0);
expand(m00, 2, 2);
m0 = MBR(1, 1, 1, 1);
expandby(m0, 1, 1);
m1 = MBR(0, 2, 0, 2);
m2 = MBR(4, 8, 5, 9);
p = [1.7, 1.5]; #POINT(1.7 1.5)

p1 = [-5.95, 9.28];
p2 = [-0.11, 12.56];
p3 = [3.58, 11.79];
p4 = [-1.16, 14.71];

println(m0)
println (equals(m0, m1));
println (equals(m00, m1));
println (isnull(intersection(m1, m2)));
println (distance(m1, m2));
println (intersects(p1, p2, p3, p4))