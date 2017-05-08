#=
@author titus 
=#
using   Base.Test
include("../mbr.jl")
mbr = MBR

m00 = mbr(0, 0, 0, 0);
expand(m00, 2, 2);
m0 = mbr(1, 1, 1, 1);
expandby(m0, 1, 1);
m1 = mbr(0, 2, 0, 2);
m2 = mbr(4, 8, 5, 9);
m3 = mbr(1.7, 5, 1.5, 9);
m4 = mbr(5, 8, 0, 2);
m5 = mbr(5, 8, 11, 9);
m6 = mbr(0, 2, 0, -2);
m7 = mbr(-2, 4, 1, -2);
m8 = mbr(-1, 1, 0, -1.5);
p = [1.7, 1.5]; #POINT(1.7 1.5)

exports = isdefined(:exports)?
    exports : Dict{ASCIIString,Function}()

exports["test mbr"] = function test_mbr()

  @test ==(equals(m0, m1), true);
  @test ==(equals(m00, m1), true);
  @test ==(intersects(m1, p), true);
  @test ==(intersects(m1, m2), false);
  @test ==(isnull(intersection(m1, m2)), true);
  @test ==(intersects(m1, m3), true);
  @test ==(intersects(m2, m3), true);

  m13 = intersection(m1, m3);
  m23 = intersection(m2, m3);
  _m13 = [1.7, 1.5, 2, 2];
  _m23 = [4, 5, 5, 9];

  @test ==(_m13, [m13.minx, m13.miny, m13.maxx, m13.maxy]);
  @test ==(_m23, [m23.minx, m23.miny, m23.maxx, m23.maxy]);

  @test ==(intersects(m1, mbr(_m13[1], _m13[3], _m13[2], _m13[4])), true);
  @test ==(intersects(m3, m4), true);
  @test ==(intersects(m2, m5), true);
  @test ==(intersects(m7, m6), true);
  @test ==(intersects(m6, m7), true);

  m67 = intersection(m6, m7);
  m76 = intersection(m7, m6);
  m78 = intersection(m7, m8);

  @test ==(equals(m67, m6), true);
  @test ==(equals(m67, m76), true);
  @test ==(equals(m78, m8), true);

  m25 = intersection(m2, m5);
  m34 = intersection(m3, m4);

  @test ==(width(m25), width(m5));
  @test ==(height(m25), 0.0);
  @test ==(width(m34),  0.0);
  @test ==(height(m34), 0.5);
  @test ==(distance(m3, m4), 0.0);
  @test ==(distance(m1, m2), hypot(2, 3));
  @test ==(distance(m1, m3), 0.0);

  p1 = [-5.95, 9.28];
  p2 = [-0.11, 12.56];
  p3 = [3.58, 11.79];
  p4 = [-1.16, 14.71];

  #intersects but segment are disjoint
  @test ==(intersects(p1, p2, p3, p4), true);
  @test ==(intersects( p1, p2, p3), false);
  @test ==(contains(m1, [1, 1]), true);

  mbr11 = mbr([1, 1], [1.5, 1.5]);
  mbr12 = mbr([1, 1], [2, 2]);
  mbr13 = mbr((1, 1), (2.000045, 2.00001));
  mbr14 = mbr([2.000045, 2.00001], [4.000045, 4.00001]);

  @test ==(contains(m1, mbr11), true);
  @test ==(contains(m1, mbr12), true);
  @test ==(contains(m1, mbr13), false);

  @test ==(disjoint(m1, mbr13), false); #false
  @test ==(disjoint(m1, mbr14), true); #true disjoint

  @test ==(contains(m1, [1.5, 1.5]), true);
  @test ==(contains(m1, 1.5, 1.5), true);
  @test ==(contains(m1, (2, 2)), true);

  @test ==(completely_contains(m1, mbr11), true);
  @test ==(completely_contains(m1, [1.5, 1.5]), true);
  @test ==(completely_contains(m1, 1.5, 1.5), true);
  @test ==(completely_contains(m1, [2, 2]), false);
  @test ==(completely_contains(m1, mbr12), false);
  @test ==(completely_contains(m1, mbr13), false);
end




