#The following three functions multiply a matrix with a vector 
#their inputs are the two arrays to be multiplied and their output 
#is the result of the multiplication 

function Julia_multiply(a::Array{Float64,2},b::Array{Float64,1})
    @assert(length(b) == length(a[1,:])); 
    a*b
end

function inner_cols_multiply(a::Array{Float64,2},b::Array{Float64,1})
    num_rows = length(a[:,1]); 
    num_cols = length(a[1,:]); 
    c = zeros(Float64,num_rows); 
    @assert(length(b) == num_cols);
    
    for i in 1:num_rows
        for j in 1:num_cols
            c[i] += a[i,j]*b[j]; 
        end
    end
    c
end

function inner_rows_multiply(a::Array{Float64,2},b::Array{Float64,1})
    num_rows = length(a[:,1]); 
    num_cols = length(a[1,:]); 
    c = zeros(Float64,num_rows); 
    @assert(length(b) == num_cols);
    
    for j in 1:num_cols
        for i in 1:num_rows
            c[i] += a[i,j]*b[j]; 
        end
    end
    c
end 

#Check to see that the elements of two arrays are equal within a specified tolerance 
#The inputs are the two arrays to be compared with an optional tolerance input
#There are no outputs unless the arrays are found not to be equal 
function check_equal(a::Array{Float64,1},b::Array{Float64,1},tol = 1e-6)
    @assert(length(a) == length(b)); 
    
    error = abs(a-b); 
    @assert(maximum(error) < tol); 
end

#function which benchmarks the different multiplication functions for different sized arrays
#Input -- exponent (using base 2) of maximum size of matrix
#smallest matrix size is 8
#Ouputs:
#this_array	-- array containing size of each matrix
#this_Julia_time   -- performance times using Julia_multiply
#this_cols_time   -- performance times using inner_cols_multiply
#this_row_time    -- performance times using inner_rows_multiply

function evaluate_multiply_time(max_array::Int)
    srand(42); 
    #max_array = 4; 
    this_Julia_time = zeros(Float64,max_array-2); 
    this_cols_time = zeros(Float64,max_array-2); 
    this_rows_time = zeros(Float64,max_array-2); 
    this_array = zeros(Int,max_array-2);
    my_index = 1; 
    for i in 3:max_array
        N = 2^i; 
        this_array[my_index] = N;
        A = rand(Float64,N,N); 
        b = rand(Float64,N); 

	#ensure that the functions are compiled 
	Julia_multiply(A,b); 
	inner_cols_multiply(A,b); 
	inner_rows_multiply(A,b); 
        
        this_Julia_time[my_index] = @elapsed(Julia_multiply(A,b)); 
        this_cols_time[my_index] = @elapsed(inner_cols_multiply(A,b)); 
        this_rows_time[my_index] = @elapsed(inner_rows_multiply(A,b)); 
        
        my_index += 1;     
    end
    this_array, this_Julia_time, this_cols_time, this_rows_time;
end
