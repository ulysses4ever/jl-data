using FastGaussTransforms
using Base.Test

# Evaluate the maximum error for the gauss transform of three sources
# as one of the sources is moved.
#
# Since the gauss transform is linear, this should be a sufficient test
# of the accuracy of the algorithm in general.
function maxerror(rtol)
   m = 0.0
   for xp in linspace(-10, 10, 1000)
    points = [0.0, 2.0, xp]
    values = ones(size(points))
    f = fastgausstransform(points, values, 0.5; rtol=rtol)
    s = slowgausstransform(points, values, 0.5)
    for x in linspace(-10, 10, 10000)
      delta = abs(evaluate(f, x) - evaluate(s, x))
      m = max(m, delta)
    end
   end
   return m
 end

 @test maxerror(eps(1.0)) <= 2*eps(3.0)
 @test maxerror(1e-8) < 3e-8
 @test maxerror(1e-3) < 3e-3
