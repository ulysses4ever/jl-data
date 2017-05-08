push!(LOAD_PATH, "/Users/kevin/github/d4")
using Base.Test
using D4
import Iterators: subsets

# Test posrem
for modulus in [2, 3, 4, 5]
    for dividend in -10:10
        val = D4.posrem(dividend, modulus)
        @test val < modulus
        @test val >= 0

        pos_neg_val = dividend % modulus
        if pos_neg_val >= 0
            @test val == pos_neg_val
        else
            @test val == pos_neg_val + modulus
        end
    end
end


# Test kron
for b in [2,3,5,7,11]
    @test D4.kron(0, b) == 0
    squares = Set([])
    for a in 1:(b-1)
        push!(squares, (a ^ 2) % b)
    end
    for a in 1:(b-1)
        if a ∈ squares
            @test D4.kron(a, b) == 1
        else
            @test D4.kron(a, b) == -1
        end
    end
end


# Test factor
@test Set(D4.sqfactor(4 * 7)) == Set([-4, -7])
@test Set(D4.sqfactor(8 * 7)) == Set([-8, -7])
@test length(D4.sqfactor(16 * 7)) == 0
@test length(D4.sqfactor(3)) == 0
@test Set(D4.sqfactor(4 * 3)) == Set([-4, -3])
@test Set(D4.sqfactor(5)) == Set([5])
@test length(D4.sqfactor(-5)) == 0
@test Set(D4.sqfactor(-20)) == Set([-4, 5])


# The values of Uslow and U should be ***identical*** so long as
# we throw a fundamental discriminant at it.
function run_U_tests(range_object)
    bad_values = []
    for d in range_object
        if length(D4.sqfactor(d)) == 0
            continue
        end
        for Z in 1:1000
            @test D4.Cohen.Uslow(d, Z) == D4.Cohen.U(d, Z)
        end
    end
end

run_U_tests(-100:4:0)
run_U_tests(0:4:100)
run_U_tests(-99:4:0)
run_U_tests(1:4:100)


# Test the values of T
for D in -200:200
    D_fact = D4.sqfactor(D)
    if length(D_fact) == 0
        continue
    end

    # Values of T should be symmetric in dI and D
    # And the values of T should equal the values of Tslow
    for DD in subsets(D_fact)
        dI = prod(DD)
        for Y in 1:200
            # Symmetry
            @test D4.Cohen.T(1, 1, dI, D, Y) == D4.Cohen.T(1, 1, div(D, dI), D, Y)
            @test D4.Cohen.T(4, 4, dI, D, Y) == D4.Cohen.T(4, 4, div(D, dI), D, Y)
            @test D4.Cohen.T(8, 8, dI, D, Y) == D4.Cohen.T(8, 8, div(D, dI), D, Y)
            @test D4.Cohen.T(-4, -4, dI, D, Y) == D4.Cohen.T(-4, -4, div(D, dI), D, Y)

            @test D4.Cohen.T(1, 1, dI, D, Y) == D4.Cohen.Tslow(1, 1, dI, D, Y)
            @test D4.Cohen.T(4, 4, dI, D, Y) == D4.Cohen.Tslow(4, 4, dI, D, Y)
            @test D4.Cohen.T(8, 8, dI, D, Y) == D4.Cohen.Tslow(8, 8, dI, D, Y)
            @test D4.Cohen.T(-4, -4, dI, D, Y) == D4.Cohen.Tslow(-4, -4, dI, D, Y)
        end
    end
end
