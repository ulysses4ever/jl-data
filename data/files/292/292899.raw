using Augustus
using FactCheck
include("../src/smith_normal_form.jl")

let 
  @facts "solve_gcd_equation" begin
    sge = SmithNormalForm.solve_gcd_equation
    sigma, tau, beta = sge(0, 95)
    @fact "With a0 == 0 and a1 == 0" sge(0, 0) => (0, 0, gcd(0, 0))
    @fact "With a0 == 0 and a1 > 0"  sge(0, 95) => (0, 1, gcd(0, 95))
    @fact "With a0 == 0 and a1 < 0"  sge(0, -95) => (0, -1, gcd(0, -95))
    @fact "With a0 > 0  and a1 == 0" sge(95, 0) => (1, 0, gcd(95, 0))
    @fact "With a0 < 0  and a1 == 0" sge(-95, 0) => (1, 0, gcd(-95, 0))
    for i in 1:200
      a0, a1 = rand(-100:100, 2)
      sigma, tau, beta = sge(a0, a1)
      @fact a0 % beta => 0
      @fact a1 % beta => 0
      @fact beta => gcd(a0, a1)
      @fact a0 * sigma + tau * a1 => beta
      sigma, tau, beta = sge(a1, a0)
      @fact a0 % beta => 0
      @fact a1 % beta => 0
      @fact beta => gcd(a1, a0)
      @fact a1 * sigma + tau * a0 => beta
    end
  end
end
##
## let
##   @facts "choose pivot" begin
##     cpc = SmithNormalForm.choose_pivot
##     x = [1 5 -1; 5 0 5; -6 0 0]
##     left = eye(Int, 3, 3)
##     @fact cpc(1, 1, x, left) => 1
##     @fact x => [1 5 -1; 5 0 5; -6 0 0]
##     @fact left => eye(Int, 3, 3)
##
##     @fact cpc(2, 2, x, left) => 2
##     @fact x => [5 0 5; 1 5 -1; -6 0 0]
##     @fact left => [0 1 0; 1 0 0; 0 0 1]
##
##     x = [1 0 -1; 5 0 5; -6 0 0]
##     left = eye(Int, 3, 3)
##     @fact cpc(2, 2, x, left) => 3
##     @fact x => [1 0 -1; 5 0 5; -6 0 0]
##     @fact left => eye(Int, 3, 3)
##   end
## end
##
## let
##   @facts "improve_pivot_col" begin
##     cpc = SmithNormalForm.choose_pivot
##     ipc = SmithNormalForm.improve_pivot_col
##     for trial in 1:100
##       x = rand(-10:10, rand(3:6), rand(4:6))
##
##       copyx = deepcopy(x)
##
##       for jt in 1:min(size(x))
##         nnz(x[:, jt]) == 0 && continue
##
##         x = deepcopy(copyx)
##         left = eye(Int, size(x, 1), size(x, 1))
##         u = cpc(jt, jt, x, left)
##         @fact "something wrong in choose pivot" u => jt
##         ipc(jt, jt, x, left)
##         @fact x[jt, jt] => not(0)
##         @fact nnz(x[:, jt]) => 1
##         @fact left * copyx => x
##
##         x = deepcopy(copyx)
##         x[jt, jt] = 0
##         @fact ipc(jt, jt, x, left) => :throws
##       end # loop over columns
##     end # loop over trials
##   end
## end
##
## let
##   @facts "improve_pivot_row" begin
##     cpc = SmithNormalForm.choose_pivot
##     ipc = SmithNormalForm.improve_pivot_row
##     for trial in 1:100
##       x = rand(-10:10, rand(3:6), rand(4:6))
##
##       copyx = deepcopy(x)
##
##       for t in 1:min(size(x))
##         nnz(x[t, :]) == 0 && continue
##
##         x = deepcopy(copyx)
##         right = eye(Int, size(x, 2), size(x, 2))
##         left = eye(Int, size(x, 1), size(x, 1))
##         u = cpc(t, t, x, left)
##         @fact "something wrong in choose pivot" u => t
##         ipc(t, t, x, right)
##         @fact x[t, t] => not(0)
##         @fact nnz(x[t, :]) => 1
##         @fact left * copyx * right => x
##
##         x = deepcopy(copyx)
##         x[t, t] = 0
##         @fact ipc(t, t, x, right) => :throws
##       end # loop over columns
##     end # loop over trials
##   end
## end

let
  @facts "get_min_max" begin
    x = [1 0 -1; 5 5 5; -6 0 0]
    @fact SmithNormalForm.get_min_max(x) => (7, 3)
    @fact SmithNormalForm.get_min_max(transpose(x)) => (3, 7)
    @fact SmithNormalForm.get_min_max(x[:]) => (7, 3)
    @fact SmithNormalForm.get_min_max(transpose(x)[:]) => (3, 7)
    x[7] = 0
    @fact SmithNormalForm.get_min_max(x) => (1, 3)
    @fact SmithNormalForm.get_min_max(transpose(x)) => (1, 7)
    @fact SmithNormalForm.get_min_max(x[:]) => (1, 3)
    @fact SmithNormalForm.get_min_max(transpose(x)[:]) => (1, 7)
  end
end

let
  @facts "check_nonzero" begin
    x = [1 0 -1; 5 5 5; -6 0 0]
    @fact SmithNormalForm.check_nonzero(x, 1) => false
    @fact SmithNormalForm.check_nonzero(x, 2) => false
    @fact SmithNormalForm.check_nonzero(x, 3) => false
    x = [0 0 0; 0 0 0; 0 0 0]
    @fact SmithNormalForm.check_nonzero(x, 1) => true
    @fact SmithNormalForm.check_nonzero(x, 2) => true
    @fact SmithNormalForm.check_nonzero(x, 3) => true
    x = [1 1 0; 0 0 0; 0 0 0]
    @fact SmithNormalForm.check_nonzero(x, 1) => false
    @fact SmithNormalForm.check_nonzero(x, 2) => true
    @fact SmithNormalForm.check_nonzero(x, 3) => true
    x = [1 0 0; 0 0 0; 1 0 0]
    @fact SmithNormalForm.check_nonzero(x, 1) => false
    @fact SmithNormalForm.check_nonzero(x, 2) => true
    @fact SmithNormalForm.check_nonzero(x, 3) => true
    x = [1 0 0; 0 0 0; 0 1 0]
    @fact SmithNormalForm.check_nonzero(x, 1) => true
    @fact SmithNormalForm.check_nonzero(x, 2) => true
    @fact SmithNormalForm.check_nonzero(x, 3) => true
    x = [1 0 1; 0 0 0; 0 0 0]
    @fact SmithNormalForm.check_nonzero(x, 1) => false
    @fact SmithNormalForm.check_nonzero(x, 2) => true
    @fact SmithNormalForm.check_nonzero(x, 3) => true
    x = [1 0 1; 0 0 0; 0 0 1]
    @fact SmithNormalForm.check_nonzero(x, 1) => false
    @fact SmithNormalForm.check_nonzero(x, 2) => true
    @fact SmithNormalForm.check_nonzero(x, 3) => false
    x = [1 0 0; 0 1 0; 0 0 1]
    @fact SmithNormalForm.check_nonzero(x, 1) => true
    @fact SmithNormalForm.check_nonzero(x, 2) => true
    @fact SmithNormalForm.check_nonzero(x, 3) => true
    x = [1 0 0; 0 1 1; 0 0 1]
    @fact SmithNormalForm.check_nonzero(x, 1) => true
    @fact SmithNormalForm.check_nonzero(x, 2) => false
    @fact SmithNormalForm.check_nonzero(x, 3) => false
  end
end

let
  @facts "check_same_magnitude" begin
    csm = SmithNormalForm.check_same_magnitude
    t = transpose
    @fact csm(  [4 0 0; 5 0 0; 1 0 0],  1, 2, 1)       => 1, 2
    @fact csm(t([4 0 0; 5 0 0; 0 3 0]), 1, 2, 1, true) => 1, 2
    @fact csm(  [4 9 1; 5 9 1; 9 9 3],  1, 2, 1)       => 1, 2
    @fact csm(t([4 9 1; 5 9 1; 9 4 1]), 1, 2, 1, true) => 1, 2
    @fact csm(  [4 0 0; 4 1 1; 5 0 0],  1, 2, 1)       => 1, 2
    @fact csm(t([4 0 0; 4 1 1; 0 6 0]), 1, 2, 1, true) => 1, 2
    @fact csm(  [4 1 0; 4 1 1; 0 0 7],  1, 2, 1)       => 1, 2
    @fact csm(t([4 1 0; 4 1 1; 0 8 0]), 1, 2, 1, true) => 1, 2
    @fact csm(  [4 0 1; 4 1 1; 9 0 0],  1, 2, 1)       => 1, 2
    @fact csm(t([4 0 1; 4 1 1; 0 8 0]), 1, 2, 1, true) => 1, 2
    @fact csm(  [4 1 1; 4 1 1; 0 0 7],  1, 2, 1)       => 1, 2
    @fact csm(t([4 1 1; 4 1 1; 0 6 0]), 1, 2, 1, true) => 1, 2
    @fact csm(  [4 1 1; 4 1 0; 5 0 0],  1, 2, 1)       => 2, 1
    @fact csm(t([4 1 1; 4 1 0; 0 4 0]), 1, 2, 1, true) => 2, 1
  end
end

let 
  @facts "check SNF, fixed matrices" begin
    snf = SmithNormalForm.smith_normal_form
    for (x, s, l, r) in [ ([1 0 -1; 5 5 5; -6 0 0], 
                           [1; 1; 30],
                           [1 0 0; 1 1 1; 0 6 5],
                           [1 -1 5; 0 1 -4; 0 -1 5]),
                          ([3 9 5; 15 5 -10; 6 -6 1],
                           [1; 1; 1440],
                           [1 0 0; -18 1 -2; -9655 537 -1075],
                           [2 72 -193; 0 -19 51; -1 -9 24]),
                          ([-4 4 4; 4 -4 4; 4 4 -4],
                           [4; 8; 8],
                           [0 0 1; 1 0 1; 1 1 0],
                           [1 -1 1; 0 1 0; 0 0 1]) ]
      smith, left, right = snf(x)
      is_integer(x) = eltype(x) <: Int
      @fact left => is_integer
      @fact right => is_integer
      @fact smith => is_integer
      @fact size(left) => 3, 3
      @fact size(right) => 3, 3
      @fact size(smith) => (3, )
      @fact smith => s
      @fact left => l
      @fact right => r
      @fact smith => s
    end
  end
end

# let
#   @facts "check SNF, random matrices" begin
#     function problems(n::Int; r1::Int=10, r2::Int=3)
#       function invertible(n::Int, range::Int=10)
#         n < 2 && error("Cannot have negative dimension")
#         cell = rand(-abs(range):abs(range), n, n)
#         while det(cell) == 0
#           cell = rand(-abs(range):abs(range), n, n)
#         end
#         cell
#       end
#       function smith(n::Int, range::Int=3)
#         result = ones(Int, n, )
#         result[1] = rand(1:range)
#         for i in 2:n
#           result[i] = result[i-1] * rand(1:range)
#         end
#         result
#       end
#       invertible(n) * diagm(smith(n)) * invertible(n)
#     end

#     snf = SmithNormalForm.smith_normal_form
#     for i in 1:10
#       matrix = problem(rand(2:10))
#     end

#   end
# end
