module Tests

using MergedMethods
using Base.Test

module A

type T end

f(::T) = T
g(::T; kwargs...) = kwargs
h1(x::Int) = A
h2(x::Int) = A

end

module B

type T end

f(::T) = T
g(::T; kwargs...) = kwargs
h1(x::Int) = B
h2(x::Int) = B

end

@merge f A B

@test f(A.T()) == A.T
@test f(B.T()) == B.T

@kwmerge g A B

@test g(A.T(), a = 1) == Any[(:a, 1)]
@test g(B.T(), a = 1) == Any[(:a, 1)]

@merge h1 A B

@test h1(1) == A

@merge h2 B A

@test h2(1) == B

@test_throws ErrorException MergedMethods.pickmodule([], Tuple{})

end
