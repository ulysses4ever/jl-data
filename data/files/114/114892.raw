module Collocations

#include("SimpleTok.jl")
#include("fisher.jl")

export collocations


import SimpleTokenizer: tokenize
import Stats: fisher

type Collo
    word::Int64
    counts::Dict{String, Int64}
    counts_total::Dict{String, Int64}
    set::Set{String}
    total::Int64
    function Collo()
        new(0,Dict{String,Int64}(),Dict{String,Int64}(),Set{String}(), 0)
    end

    function Collo(word::Int64,counts::Dict{String,Int64}, counts_total::Dict{String,Int64}, set::Set{String},
        total::Int64)
        new(word, counts, counts_total, set,total)
    end
end

function _table_freq(word::String, words::Array{String})
    total = 0
    for w in words
        if w == word
            total += 1
        end
    end
    return total
end

function _freq_colls(collo::Collo, word::String, words::Array{String}; context = 1, lower = true)
    counts=collo.counts
    counts_total=collo.counts_total
    word_c=collo.word
    set = collo.set

    #println(counts)
    #println(counts_total)
    #println(word_c)


    # Make lower
    if lower == true
        map!((x) -> lowercase(x), words)
    end

    total = length(words)

    for w in 1:total
        if word==words[w]
            word_c +=1
            if (w+1 < total)
                counts[words[w+1]] = get(counts,words[w+1],0)+1
            end
            if (w-1 > 1)
                counts[words[w-1]] = get(counts,words[w-1],0)+1
            end
        end
    end

    for key in keys(counts)
        push!(set, key)
        for w in words
            if w ==key
                counts_total[key] = get(counts_total,key,0)+1
                #count((x)->x==key, words)
            end
        end
    end

    return Collo(word_c, counts,counts_total, set, total+collo.total)
end

function _freq_colls(collo::Collo, word::String, text::String; context = 1, lower = true)
    _freq_colls(collo, word, tokenize(text), context=context, lower=lower)
end

function _sum_dicts(d1::Dict{String, Int64},d2::Dict{String, Int64})
    total = Dict{String, Int64}()
    for key in keys(d1)
        total[key]=d1[key]+get(d2,key,0)
    end

    for key in keys(d2)
        total[key]=d2[key]+get(d1,key,0)
    end
    return total
end


function _sum (collos::Array{Collo})
    total = Collo()
    for c in collos
        total.word +=c.word
        total.counts = _sum_dicts(total.counts, c.counts)
        total.counts_total = _sum_dicts(total.counts_total, c.counts_total)
        total.set = union(total.set, c.set)
        total.total += c.total
    end
    return total
end

function _test_colls(word::String, collos::Collo; p = 0.01, test ="deltap")
    pvalues = Dict{String, Float64}()

    for pr in keys(collos.counts)
        a = collos.counts[pr]
        b = collos.word-a
        c = collos.counts_total[pr]-a
        d = collos.total-a-b-c



        if test =="deltap"
            pv1 = a/(a+b)-c/(c+d)
            pv2 = a/(a+c)-c/(b+d)
            key1 = string(word, " -> ",pr)
            key2 = string(pr, " -> ", word)
            pvalues[key1] = pv1
            pvalues[key2] = pv2
        end
        if test =="fisher"
            if a*b*c*d != 0
                pv = fisher(a,b,c,d)
                pvalues[pr] = pv
            end
        end
    end

    return pvalues
end

function collocations(word::String, text::String; test = "deltap", context = 1,p=0.01, lower=true)
    fin = collect(_test_colls(word, _freq_colls(Collo(), word, text, context, lower), p, test))
    #return fin
    sort([(b,a) for (a,b) in fin])
end

function collocations(word::String, texts::Array{String}; test = "deltap",context = 1, p=0.01, lower=true)
    collo = Collo()

    for text in texts
        collo = _freq_colls(collo,word, text, context=context, lower=lower)
    end

    fin = collect(_test_colls(word, collo,p=p,test=test))
    #return fin
    sort([(b,a) for (a,b) in fin])
end

end
