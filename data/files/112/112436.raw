using cv_geom
using Base.Test

# write your own tests here
@test 1 == 1

@test cv_geom.hom([1,2]) == [1,2,1]
@test cv_geom.hom([1 2 3 4; 2 2 1 2]) == [1 2 3 4; 2 2 1 2; 1 1 1 1]

@test cv_geom.ihom([3,2,1]) == [3,2]
@test cv_geom.ihom([1,2,3]) == [1/3, 2/3]
@test cv_geom.ihom([1 2 3 4; 4 5 8 7; 1 2 2 0.5]) == [1 1 3/2 8; 4 5/2 4 14]
