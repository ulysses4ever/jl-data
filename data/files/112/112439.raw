#reload("CvGeom")
using CvGeom
#reload("CvGeom")
using Base.Test

# write your own tests here

# some test data for homogeneous points
# some finite points first
a = [1, 2];       a1 = [1, 2, 1];       a2 = a1*2.0;         a3 = [.5, 1, .5]
b = [-3, 2];      b1 = [-3, 2, 1];      b2 = b1*-0.5;        b3 = [1, -2/3, -1/3]
c = [1/3, 2/3];   c1 = [1/3, 2/3, 1];   c2 = [1,2,3];        c3 = c1

# a point at infinite
d1 = [-3, 2, 0];      d2 = [1.5, -1, 0];   d3 = [1, -2/3, 0]

ABC = [a b c]
ABC1 = [a1 b1 c1]
ABC2 = [a2 b2 c2]
ABC3 = [a3 b3 c3]
D = [d1 d2 d3]

@test hom(a) == a1
@test hom(b) == b1
@test hom(c) == c1
@test hom(ABC) == ABC1

aa = Set({a1, a2, a3})
bb = Set({b1, b2, b3})
cc = Set({c1, c2, c3})
dd = Set({d1, d2, d3})

function test_ihom(u::Vector, uu::Set)
  for ui = uu
    @test ihom(ui) == u
  end
end

test_ihom(a, aa)
test_ihom(b, bb)
test_ihom(c, cc)

@test ihom(ABC1) == ABC
@test ihom(ABC2) == ABC
@test ihom(ABC3) == ABC

function test_homNorm(u1::Vector, uu::Set)
  for ui = uu
    @test homNorm(ui) == u1
  end
end

test_homNorm(a1, aa)
test_homNorm(b1, bb)
test_homNorm(c1, cc)

function test_homNormRobust(u3::Vector, uu::Set)
  for ui = uu
    @test homNormRobust(ui) == u3
  end
end

test_homNormRobust(a3, aa)
test_homNormRobust(b3, bb)
test_homNormRobust(c3, cc)

function isHomEq2(a::Vector, b::Vector)
  if size(a) != size(b)
    return false
  end

  return homNormRobust(a) == homNormRobust(b)

end

function test_isHomEq(uu::Set, vv::Set)
  for ui = uu
    for uj = uu
      @test isHomEq2(ui, uj)
    end
    for vj = vv
      @test !isHomEq2(ui, vj)
    end
  end
end

test_isHomEq(aa, bb)
test_isHomEq(bb, cc)
test_isHomEq(cc, dd)
test_isHomEq(dd, aa)

p1 = [1,7.5]
p2 = [13,102]
p3 = [1,1]
p4 = [-3,24]
p5 = [11,-7]

points = [p1 p2 p3 p4 p5]
c,A,d = CvGeom.fitConic(points)

A*c

function conic(c::Vector)
  @assert length(c) == 6
  a,b,c,d,e,f = c
  C = [ a  b/2 d/2
       b/2  c  e/2
       d/2 e/2  f ]
  return C
end

C = conic(c)
hom(p1)' * C * hom(p1)

#@test CvGeom.isPointOnLine
