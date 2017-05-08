function ss{T <: Real}(y::Array{T})
        y | x -> (x .- mean(x)) .^ 2 | sum
end

function ss_by_col(responses::Matrix)
    mapslices(ss, responses, 1) | sum
end



function table{T <: Integer}(label::Vector{T}, mykeys::Vector{T})
    key_length = length(mykeys)
    counts = zeros(Int64, key_length)
    for i in label[1:length(label)]
        for j in 1:key_length
            if i == mykeys[j]
                counts[j] += 1
                break
            end
        end
    end
    (mykeys, counts)

end

table{T <: Integer}(label::Vector{T}) = table(label, unique(label))


function ss_ratio{T <: Integer}(v1::Vector{T}, v2::BitArray{1}, mykeys::Vector{T}) 
    d_value = table(v1, mykeys)[2]
    d1_value = table(v1[v2], mykeys)[2]
    d2_value = table(v1[!v2], mykeys)[2]
    n_true = sum(v2)
    n_false = sum(!v2)
    all_ss = 0.0
    nonempty = 0
    for i in 1:length(mykeys) 
        if d_value[i] != 0
            nonempty += 1
            all_ss = all_ss + (d1_value[i] ^ 2 / n_true + d2_value[i] ^ 2 / n_false) / d_value[i]
        end
    end
    all_ss / nonempty
end
ss_ratio{T <: Integer}(v1::Vector{T}, v2::BitArray{1}) = ss_ratio(v1, v2, unique(v1)) 

function ss_ratio{T <: Integer}(m1::Matrix{T}, v2::BitArray{1}, mykeys::Vector{T})
    ratio_sum = 0.0
    for i in 1:size(m1, 2)
        ratio_sum = ratio_sum + ss_ratio(m1[:, i], v2, mykeys) 
    end
    ratio_sum / size(m1, 2)
end


function ss_ratio{T <: Integer}(m1::Matrix{T}, v2::BitArray{1})
    np = size(m1, 2)
    mykeys = unique(m1[:, 1])
    for i in randperm(np)[1:min(10, np)]
        tmp = unique(m1[:, i])
        if length(tmp) > length(mykeys)
            mykeys = tmp
        end
    end
    ss_ratio(m1, v2, mykeys)
end








