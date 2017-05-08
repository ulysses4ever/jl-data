using IntervalsPablo

using FactCheck

r=Interval(-3,-.5)
s=Interval(2,4)



facts("funcionalidad del constructor y operaciones basicas") do

@fact r => Interval(-.5,-3)
@fact r+s => Interval(-1,3.5)
@fact r-s => Interval(-7,-2.5)
@fact r*s => Interval(-12,-1)
@fact r/s => Interval(-1.5,-.125)

end


