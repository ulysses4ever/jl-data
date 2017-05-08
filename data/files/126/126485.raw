function matrix_mul_1a(A::Array,x::Array)
    @assert typeof(A) == Array{Float64,2};
    @assert typeof(x) == Array{Float64,1};
    @assert size(A,2) == size(x,1);
    return A*x
end

function matrix_mul_1b(A::Array,x::Array)
    @assert typeof(A) == Array{Float64,2};
    @assert typeof(x) == Array{Float64,1};
    @assert size(A,2) == size(x,1);
    result = zeros(size(A,1));
    for i= 1:size(A,1)
        for j = 1:size(A,2)
            result[i] += A[i,j]*x[j]
        end
    end
    return result;
end

function matrix_mul_1c(A::Array,x::Array)
    @assert typeof(A) == Array{Float64,2};
    @assert typeof(x) == Array{Float64,1};
    @assert size(A,2) == size(x,1);
    result = zeros(size(A,1));
    for j = 1:size(A,2)
        for i= 1:size(A,1)
            result[i] += A[i,j]*x[j]
        end
    end
    return result;
end

A = rand(8,8);
b = rand(8);
println("1a_result: ", "\n", matrix_mul_1a(A,b), "\n", "1b_result: ", "\n",matrix_mul_1b(A,b),"1c_result: ", "\n", matrix_mul_1c(A,b));
println("1a_time: ", @elapsed(matrix_mul_1a(A,b)), "\n", "1b_time: ", @elapsed(matrix_mul_1b(A,b)), "\n", "1c_time: ", @elapsed(matrix_mul_1c(A,b)));

