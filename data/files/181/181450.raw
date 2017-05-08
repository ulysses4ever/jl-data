## converting a Matrix{T} of size 1*N or N*1 in Julia to a Vector{T}  ##

a = [1,3,5];
b = a';

a_vec = [x::Int for x in a];
b_vec = [x::Int for x in b];

## vec is faster than reshape ##

const a = reshape([1:1000],1000,1);
typeof(a);
vec_a = [x::Int for x in a];
typeof(vec_a);
vec_aII = vec(a);
typeof(vec_aII);

squeeze(ones(3, 1));
squeeze(ones(1, 3));
