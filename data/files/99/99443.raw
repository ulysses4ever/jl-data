using Base.Test

include("distance.jl")

function testDistance()
  # Test points
  points = [  42.352382 -71.078760;    # Boston
              42.374814 -71.118936;    # Cambridge
              42.372213 -71.098676;
              42.341482 -71.142330;
              42.346393 -71.566262;    # Marlborough
              42.260954 -71.817764;    # Worcester
              43.037195 -71.438946;
              43.060869 -70.752002;
              44.284042 -69.833654;    # Augusta, ME
              41.451010 -72.811856 ]   # Wallingford, CT

  dmat = buildDistanceMatrix(points, false)  # In km

  @test dmat[1,1] == 0.0
  @test abs(dmat[1,2] - 4.137) <= 0.1
  @test abs(dmat[1,3] - 2.746) <= 0.1
  @test dmat[1,5] == dmat[5,1]
  @test abs(dmat[10,1] - 175.0) <= 0.1
end

testDistance()
