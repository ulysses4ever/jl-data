typealias Nucleotide Int

function compare(seq::Array{Nucleotide}, k::Int, start1::Int, start2::Int)
    for i=0:(k-1)
        s1_idx = (start1+i-1)%length(seq) + 1
        s2_idx = (start2+i-1)%length(seq) + 1
        #println(string("s1i=", s1_idx, "  s2i=", s2_idx))
        if seq[s1_idx] != seq[s2_idx]
            return false
        end
    end
    return true
end

function compare_rc(seq::Array{Nucleotide}, k::Int, start1::Int, start2::Int)
    # ignore palindromes
    if (((start1-1)%length(seq))+1) == (((start2+k)%length(seq))+1)
        #println(string("Ignoring possible palindrome for pos1=", start1, "  pos2=", start2,
        #               "  k=", k))
        return false
    end
    for i=0:(k-1)
        s1_idx = ((start1+i-1)%length(seq)) + 1
        s2_idx = ((start2+i-1)%length(seq)) + 1
        #s2_idx = ((2*length(seq)-start2-i+1)%length(seq)) + 1
        #println(string("reverse. s1i=", s1_idx, "  s2i=", s2_idx))
        if seq[s1_idx] != -seq[end - s2_idx + 1]
            return false
        end
    end
    return true
end

# return
function testk(seq::Array{Nucleotide}, k::Int, start1::Int, start2::Int, reverse::Bool)
    for pos1=start1:(length(seq)-k)
        if reverse
            for pos2=pos1+1:length(seq)-k
                if compare_rc(seq, k, pos1, pos2)
                    return false, pos1, pos2, reverse
                end
            end
        else
            reverse = false
            for pos2=pos1+1:length(seq)-k
                if compare(seq, k, pos1, pos2)
                    return false, pos1, pos2, reverse
                end
            end
            #println("starting reverse at pos1=", pos1, " pos2=", pos2)
            reverse = true
            for pos2=pos1+1:length(seq)-k
                if compare_rc(seq, k, pos1, pos2)
                    return false, pos1, pos2, reverse
                end
            end
            reverse=false
        end
    end
    return true, 1, 1, true
end

function findk(seq::Array{Nucleotide}; k_start::Int=1)
    result, start1, start2, reverse = false, 1, 2, false
    for k=k_start:(length(seq)-1)
        result, start1, start2, reverse = testk(seq, k, start1, start2, reverse)
        if result
            if reverse
                # Now need to check forward direction.
                result, start1, start2, reverse = testk(seq, k, start1, start2, reverse)
                if !result
                    continue
                end
            end
            return k, reverse
        else
            println(string("Found duplicate strand for k=", k,
                " at pos1=", start1, ", pos2=", start2, " reverse=", reverse))
        end
    end
    return length(seq)
end

bpmap = Dict{Any,Int}('A'=>1, 'T'=>-1, 'G'=>2, 'C'=>-2)
function loadsequence()
    f = open("sequence")
    seq = int([bpmap[x] for x in strip(readlines(f)[1])])
    close(f)
    return seq
end
