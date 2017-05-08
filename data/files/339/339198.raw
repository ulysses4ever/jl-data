function normalized_adjMat(adjMat::SparseMatrixCSC)
    sums = sum(adjMat,1)
    I,J,V = findnz(adjMat)
    for idx in 1:length(V)
        V[idx] /= sums[J[idx]]
    end
    sparse(I,J,V)
end

function biPartSimRank(x::Int64, y::Int64, mat::SparseMatrixCSC)
    c = 0.8
    iteration = 5
    from_sim = eye(x)
    to_sim = eye(y)
    
    adj = normalized_adjMat(mat)
    adj_t = normalized_adjMat(mat')

    
    for k in 1:iteration
        
       from_sim = c * adj_t' * to_sim * adj_t

       for i in 1:x
           from_sim[i;i] = 1
       end


       to_sim   = c * adj' * from_sim * adj

       for i in 1:y
           to_sim[i;i] = 1
       end
        
        println(k)
    end
    
    return from_sim, to_sim
end

function getDim(filename::String)
    from_set = Set()
    to_set = Set()

    f = open(filename)
    for l in readlines(f)
        data = split(chomp(l), ",")
        push!(from_set,data[1])
        push!(to_set,data[2])
    end

    return length(from_set), length(to_set)
end

function createMat(filename::String, n::Int64, m::Int64)
    println("creating adjMat...")
    f = open(filename)
    adj = spzeros(n,m)

    from = Array(UTF8String, 0)
    to = Array(UTF8String, 0)
    
    for l in readlines(f)
        data = split(chomp(l), ",")
        if !(data[1] in from)
            push!(from,data[1])
        end
        from_id = findfirst(from,data[1])
        
        if !(data[2] in to)
            push!(to, data[2])
        end
       
        to_id = findfirst(to,data[2])
        adj[from_id; to_id] = 1
    end
    println("adjMat...done!!")
    
    return adj, from, to
end

function biSimrank()
    fname = "cake.csv"
    
    n,m = getDim(fname)
    mat, from, to = createMat(fname, n, m)
    from_sim , to_sim = biPartSimRank(n, m ,mat)
    return from_sim, to_sim, from, to
end

function writeResult(names,mat)
    for i in 1:length(names)
        for j in i+1:length(names)
            println(names[i]*","*names[j]*","*string(mat[i;j]))
        end
    end
end
    

from_sim, to_sim, from, to = biSimrank()

writeResult(from,from_sim)
writeResult(to,to_sim)


