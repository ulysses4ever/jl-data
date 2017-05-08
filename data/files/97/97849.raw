using EarthSphere

mylatdegree = Degree(45,0,0)
mylongdegree = Degree(25,0,0)
println(mylatdegree)
mylatlong = Earth_LatLong_Coord(mylatdegree,mylongdegree,"SW")
println(EarthSphere.sign_lat_long(mylatlong))
println(mylatlong)
my_sphere = convert(Spherical_Coord,mylatlong)
println(my_sphere)
myotherlat = Degree(45,0,0)
myotherlong = Degree(-25,0,0)
myotherlatlong = Earth_LatLong_Coord(myotherlat,myotherlong,"NW")
my_other_sphere = convert(Spherical_Coord,myotherlatlong)
mydistance = get_distance(my_sphere,my_other_sphere)
println(mydistance)

