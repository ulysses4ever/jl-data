tested_file = "RoesserModels.jl"

#########################################################################################
# Test Functions
function test_validmodel()
  print_with_color(:blue, "Testing the creation of a valid Roesser model.\n")
  A1 = randn(3,3)
  A2 = randn(3,2)
  A3 = randn(2,3)
  A4 = randn(2,2)
  B1 = randn(3,1)
  B2 = randn(2,1)
  C1 = randn(1,3)
  C2 = randn(1,2)
  D = randn(1,1)
  system = RoesserModels.RoesserModel(A1, A2, A3, A4, B1, B2, C1, C2, D)
  @test system.A1 == A1
  @test system.A2 == A2
  @test system.A3 == A3
  @test system.A4 == A4
  @test system.B1 == B1
  @test system.B2 == B2
  @test system.C1 == C1
  @test system.C2 == C2
  @test system.D == D
end

function test_invalidhorizontal()
  print_with_color(:blue, "Testing the creation of a invalid Roesser model (Horizontal).\n")
  A1 = randn(3,2)
  A2 = randn(3,2)
  A3 = randn(2,3)
  A4 = randn(2,2)
  B1 = randn(3,1)
  B2 = randn(2,1)
  C1 = randn(1,3)
  C2 = randn(1,2)
  D = randn(1,1)
  @test_throws ErrorException RoesserModels.RoesserModel(A1, A2, A3, A4, B1, B2, C1, C2, D)
end

function test_invalidvertical()
  print_with_color(:blue, "Testing the creation of a invalid Roesser model (Vertical).\n")
  A1 = randn(3,3)
  A2 = randn(3,2)
  A3 = randn(2,3)
  A4 = randn(3,3)
  B1 = randn(3,1)
  B2 = randn(2,1)
  C1 = randn(1,3)
  C2 = randn(1,2)
  D = randn(1,1)
  @test_throws ErrorException RoesserModels.RoesserModel(A1, A2, A3, A4, B1, B2, C1, C2, D)
end

function test_invalid_io()
  print_with_color(:blue, "Testing the creation of a invalid Roesser model (IO).\n")
  A1 = randn(3,3)
  A2 = randn(3,2)
  A3 = randn(2,3)
  A4 = randn(2,2)
  B1 = randn(3,1)
  B2 = randn(2,1)
  C1 = randn(1,3)
  C2 = randn(1,2)
  D = randn(2,2)
  @test_throws ErrorException RoesserModels.RoesserModel(A1, A2, A3, A4, B1, B2, C1, C2, D)
end

function test_randommodel()
  print_with_color(:blue, "Testing the creation of a random model.\n")
  RoesserModels.randomsystem(3, 2, 1, 1)
end

function test_validcrsd()
  print_with_color(:blue, "Testing the creation of a CRSD model.\n")
  print_with_color(:blue, "Testing the creation of a valid Roesser model.\n")
  A1 = randn(3,3)
  A2 = randn(3,2)
  A3 = zeros(2,3)
  A4 = randn(2,2)
  B1 = randn(3,1)
  B2 = randn(2,1)
  C1 = randn(1,3)
  C2 = randn(1,2)
  D = randn(1,1)
  system = RoesserModels.CrsdRoesserModel(A1, A2, A4, B1, B2, C1, C2, D)
  @test system.A1 == A1
  @test system.A2 == A2
  @test system.A3 == A3
  @test system.A4 == A4
  @test system.B1 == B1
  @test system.B2 == B2
  @test system.C1 == C1
  @test system.C2 == C2
  @test system.D == D

end

function test_simulation()
  print_with_color(:blue, "Testing the simulation of a model.\n")
  u = load("test1.jld", "u")
  y_expected = load("test1.jld", "y")
  sys = load("test1.jld", "sys")
  A1 = sys["A1"]
  A2 = sys["A2"]
  A4 = sys["A4"]
  B1 = sys["B1"]
  B2 = sys["B2"]
  C1 = sys["C1"]
  C2 = sys["C2"]
  D = [sys["D"]]
  system = RoesserModels.CrsdRoesserModel(A1, A2, A4, B1, B2, C1, C2, D)
  y = RoesserModels.simulate(system, u)
  @test_approx_eq(y_expected, y)
end

#########################################################################################
# Support functions

#########################################################################################
# Test plan execution
print_with_color(:green, "\nTesting ", tested_file, "\n")
test_validmodel()
test_invalidhorizontal()
test_invalidvertical()
test_invalid_io()
test_randommodel()
test_validcrsd()
test_simulation()
print_with_color(:green, "File: ", tested_file, " has been tested \n")
