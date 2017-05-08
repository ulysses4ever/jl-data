using ClosedIntervals
#using ProgressMeter

# Create a random interval
function RandomInterval()
    return ClosedInterval(rand(),rand())
end


# TYPE I RANDOM INTERVAL GRAPHS

# Check if there's an edge from I to J
function is_edge_1(I::ClosedInterval, J::ClosedInterval)

    if in(right(I),J) || (in(left(J),I) && in(right(J),I))
        return true
    end

    return false
end

# Create the adj matrix of a Type I interval digraph from a list of
# intervals.
function make_matrix_1{T}(Jlist::Array{ClosedInterval{T},1})
    n = length(Jlist)
    A = zeros(Int,n,n)

    for i=1:n
        I = Jlist[i]
        for j=1:n
            J = Jlist[j]
            if i==j
                continue
            end
            if is_edge_1(I,J)
                A[i,j] = 1
            end
        end
    end
    return A
end


# Create the adjacency matrix of a type I random interval digraph
function make_matrix_1(n::Int)
    Jlist = [ RandomInterval() for _ in 1:n ]
    A = make_matrix_1(Jlist)
end

# Create the adj matrix of a Type II interval digraph from two lists
# of intervals.
function make_matrix_2{T}(
                          Ilist::Array{ClosedInterval{T},1},
                          Jlist::Array{ClosedInterval{T},1})

    n = length(Ilist)
    if n != length(Jlist)
        error("Interval lists must be same length")
    end

    A = zeros(Int,n,n)

    for i=1:n
        for j=1:n
            if !isempty(Ilist[i]*Jlist[j])
                A[i,j] = 1
            end
        end
    end
    return A
end

# Create the adj matrix of a random Type II interval digraph
function make_matrix_2(n::Int)
    Ilist = [ RandomInterval() for _ in 1:n ]
    Jlist = [ RandomInterval() for _ in 1:n ]
    return make_matrix_2(Ilist,Jlist)
end

# Convert a list of degrees into a vector counting how many vertices
# of that degree are present. Because Julia arrays are 1-based, the
# indexing is off by one. That is, the k'th entry in the output is the
# number of times we see the value k-1.
function degrees2counts(deglist)
    n = length(deglist)
    result = zeros(Int,n+1)
    for d in deglist
        result[d+1] += 1
    end
    return result
end

# Generate a bunch of random interval digraphs on n vertices and count
# how often we see each [out]degree, returned as a list in which entry
# k is the number of times we see a vertex with [out]degree k+1.
function degree_tally(method::Function, n::Int, reps::Int)
    h = zeros(Int,n+1)
    for k=1:reps
        A = method(n)
        d = sum(A,1)
        h += degrees2counts(d)
    end
    return h
end

# Same as above, but total iterations is reps*chucks
function degree_tally(method::Function, n::Int, reps::Int, chunks::Int)
    h = @parallel (+) for k=1:reps
        degree_tally(method, n, reps)
    end

    return h
end
