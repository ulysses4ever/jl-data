"Make sigint `ctrl-c` catchable from the command line"
catchable_sigint() = ccall(:jl_exit_on_sigint, Void, (Cint,), 0)

"A infinite iterator over 9 colors"
colorcycle() = cycle(ASCIIString["#" * hex(c) for c in palette("Set1", 9)])

"Convert a Matrix{T} into a Vector{Vector{T}} columnwise"
Base.convert{T}(::Type{Vector}, A::Matrix{T}) = Vector{T}[A[:,t] for t = 1:size(A, 2)]

"""Split a M x N Matrix into windows of size M x ws. 

**args**

 - A::Matrix{T} => matrix to split
 - ws::Int => window size
 - ss::Itn => step size

**returns**
 
 - Vector{Matrix{T}} => with length max(0, floor(Int, (length(x) - ws) / ss) + 1)
"""
function windows{T}(A::Matrix{T}, ws::Int, ss::Int=1)
    return Matrix{T}[A[:,t:t + ws - 1] for t = 1:ss:size(A, 2) - ws + 1]
end

"""Split a vector into windows of size ws. 

**args**

 - a::Vector{T} => vector to split
 - ws::Int => window size
 - ss::Itn => step size

**returns**

 - Vector{T} => with length max(0, floor(Int, (length(x) - ws) / ss) + 1)
"""
function windows{T}(a::Vector{T}, ws::Int, ss::Int=1)
    return Vector{T}[a[t:t + ws - 1] for t = 1:ss:length(a) - ws + 1]
end

"Flatten an array"
flatten{T}(a::Array{T,1}) = any(map(x->isa(x, Array), a)) ? flatten(vcat(map(flatten, a)...)) : a

flatten{T}(a::Array{T}) = reshape(a, prod(size(a)))

flatten(a) = a

"Count the number of occurences of each unique element in x"
function tally{I<:Integer}(x::Array{I})
    counts = zeros(I, maximum(x))
    for i in x
        counts[i] += 1
    end
    counts
end

"Find the most frequently occuring element in x"
countmax{I<:Integer}(x::Array{I}) = indmax(tally(x))
