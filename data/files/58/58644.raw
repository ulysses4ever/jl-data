using MeteoSwissRadarTools
using Base.Test


x1, y1 =  550000, 150000
x2, y2 =  555000, 156000

## wrong order
@test_throws ErrorException read_radar("test.gif", x2, y1, x1, y2)
@test_throws ErrorException read_radar("test.gif", x1, y2, x2, y1)

## out of range
@test_throws ErrorException read_radar("test.gif", 200, y1, x2, y2)
@test_throws ErrorException read_radar("test.gif", x1, y1, 1000, y1)
@test_throws ErrorException read_radar("test.gif", x1, -177, x2, y2)
@test_throws ErrorException read_radar("test.gif", x1, y1, x2, 500)

## no pixel selected
@test_throws ErrorException read_radar("test.gif", x1, y1, x1, y2)
@test_throws ErrorException read_radar("test.gif", x1, y1, x2, y1)


arr = read_radar("test.gif", x1, y1, x2, y2)
@test size(arr) == (5, 6)
