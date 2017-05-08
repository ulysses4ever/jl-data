"""get all groups"""
function getgrp(node_memory::Vector{Dict{Int,Int}})
    groups = Dict{Int,Vector{Int}}()
    for i=1:length(node_memory)
        for k in keys(node_memory[i])
            if haskey(groups, k)
                push!(groups[k], i)
            else
                groups[k] = [i]
            end
        end
    end
    collect(values(groups))
end

"""
calculate the entropy of a probility distribution
"""
function entropy(P::Vector{Float64})
    H = 0.0
    for i=1:length(P)
        # treat 0*log(0) as being equal to zero
        H += P[i] > 0.0 ? P[i]*log(P[i]) : 0.0
    end
    -H > 0 ? -H : 0.0
end

"""read groups from file"""
function readgrp(filename)
    groups = Vector{Int}[]
    f = open(filename, "r")
    for ll in eachline(f)
        push!(groups, [parse(Int, i) for i in split(chomp(ll))])
    end
    groups
end

"""write groups to file"""
function writegrp(filename, groups::Vector{Vector{Int}})
    f = open(filename, "w")
    for i=1:length(groups)
        for j=1:length(groups[i])-1
            print(f, groups[i][j],' ')
        end
        print(f, groups[i][end],'\n')
    end
    close(f)
end

"""read membership from file"""
function readmsp(filename)
    membership = Dict{Int, Vector{Int}}()
    f = open(filename, "r")
    for ll in eachline(f)
        entries = [parse(Int, i) for i in split(chomp(ll))]
        membership[entries[1]] = entries[2:end]
    end
    membership
end

"""write membership to file"""
function writemsp(filename, membership::Dict{Int, Vector{Int}})
    f = open(filename, "w")
    for k in sort(collect(keys(membership)))
        print(f, k, '\t')
        for j=1:length(membership[k])-1
            print(f, membership[k][j], ' ')
        end
        print(f, membership[k][end], '\n')
    end
    close(f)
end

"""transform membership to groups"""
function msp2grp(membership::Dict{Int, Vector{Int}})
    groups = Dict{Int, Vector{Int}}()
    for (k,v) in membership
        for i in v
            if haskey(groups, i)
                push!(groups[i], k)
            else
                groups[i] = [k]
            end
        end
    end
    collect(values(groups))
end

"""transform groups to membership"""
function grp2msp(groups::Vector{Vector{Int}})
    membership = Dict{Int, Vector{Int}}()
    for i=1:length(groups)
        for j=1:length(groups[i])
            if haskey(membership, groups[i][j])
                push!(membership[groups[i][j]], i)
            else
                membership[groups[i][j]] = [i]
            end
        end
    end
    membership
end
