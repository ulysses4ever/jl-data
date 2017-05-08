module TestCSR

include(Pkg.dir("SparseMatrices", "src", "SparseMatrices.jl"))

using FactCheck

I = [1, 2, 1]
J = [1, 1, 3]
V = [1, 1, 2]

Ar = SparseMatrices.SparseMatrixCSR(I, J, V, 2, 3)
A_full = [1 0 2; 1 0 0]

facts("Test SparseMatrixCSR") do

    context("test A_mul_B!") do

        context("CSR*StridedVector") do
            x = [1, 2, 3]
            @fact Ar*x --> [7, 1]
            @fact Base.A_mul_B!(1.0, Ar, x, 0.0, [0, 0]) --> [7, 1]
            @fact Base.A_mul_B!(10.0, Ar, x, 0.0, rand(Int, 2)) --> [70, 10]
            @fact Base.A_mul_B!(10.0, Ar, x, 1.0, [1, 1]) --> [71, 11]
            @fact Base.A_mul_B!(rand(Int, 2), Ar, x) --> [7, 1]

            # check error throwing - Dimension mismatch for wrong size x or out
            @fact_throws DimensionMismatch Ar*[1, 2]
            @fact_throws DimensionMismatch Base.A_mul_B!(1.0, Ar, x, 0.0, [1, 1, 1])
        end

        context("CSR * StridedMatrix") do
            x = [1 2; 3 4; 5 6]
            @fact Ar*x --> [11 14; 1 2]
            @fact Base.A_mul_B!(1.0, Ar, x, 0.0, [0 0; 0 0]) -->  [11 14; 1 2]
            @fact Base.A_mul_B!(10.0, Ar, x, 0.0, rand(Int, 2, 2)) --> [110 140; 10 20]
            @fact Base.A_mul_B!(10.0, Ar, x, 1.0, [1 1; 1 1]) --> [111 141; 11 21]
            @fact Base.A_mul_B!(rand(Int, 2, 2), Ar, x) -->  [11 14; 1 2]

            # check error throwing - Dimension mismatch for wrong size x or out
            @fact_throws DimensionMismatch Ar*rand(Int, 2, 2)
            @fact_throws DimensionMismatch Base.A_mul_B!(1.0, Ar, x, 0.0, rand(Int, 3, 2))
            @fact_throws DimensionMismatch Base.A_mul_B!(1.0, Ar, x, 0.0, rand(Int, 2, 3))
        end

    end
end

end  # module
