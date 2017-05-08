using MatrixFunctions
using Base.Test

# Generate random matrices and round-trip them through MatrixFunction
for _ = 1:100
    nrow = rand(1:20)
    ncol = rand(1:20)
    matrix = rand(nrow, ncol)
    @test matrix == full(MatrixFunction(matrix))
end
