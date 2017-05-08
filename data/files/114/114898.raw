using DataFrames

export collocations, collostruction


#internal type for collocation
type Collo
    word::Int64
    counts::Dict{String, Int64} #counts of each collexeme when appearing with the node
    counts_total::Dict{String, Int64} #total counts of each collexeme
    set::Set{String} #set of collexemes
    total::Int64 #grand total of words

    #initialize it
    function Collo()
        new(0,Dict{String,Int64}(),Dict{String,Int64}(),Set{String}(), 0)
    end

    function Collo(word::Int64,counts::Dict{String,Int64}, counts_total::Dict{String,Int64}, set::Set{String},
        total::Int64)
        new(word, counts, counts_total, set,total)
    end
end

#internal type for storing collocations
type Collocation
    table = String{}
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


#get collocations frequencies
function _freq_colls(collo::Collo, word::String, words::Array{String}; context = 1, lower = true)
    counts=collo.counts
    counts_total=collo.counts_total
    word_c=collo.word
    set = collo.set

    # Make lower
    if lower == true
        map!((x) -> lowercase(x), words)
    end

    #total number of words
    total = length(words)

    #iterate and get counts from file
    for w in 1:total #Store in w each word
        if word==words[w]
            word_c +=1
            for (i in 1:context)
                if (w+i < total)
                    counts[words[w+i]] = get(counts,words[w+i],0)+1
                end
                if (w-i > 1)
                    counts[words[w-i]] = get(counts,words[w-i],0)+1
                end
            end
        end
    end

    #set of words
    for key in keys(counts)
        push!(set, key)
        for w in words
            if w ==key
                counts_total[key] = get(counts_total,key,0)+1
            end
        end
    end

    return Collo(word_c, counts,counts_total, set, total+collo.total)
end

function _freq_colls(collo::Collo, word::String, text::String; context = 1, lower = true)
    _freq_colls(collo, word, tokenize(text), context=context, lower=lower)
end


#function for adding dictionaries
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


#add collocations
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

function _test_colls(word::String, collos::Collo; test ="deltap")


    #Returns DataFrame
    df = DataFrame()

    #Vectors for storing nodes, collocations and pvalues
    word_pr = Float64[]
    pr_word = Float64[]
    fisher_values = Float64[]
    word_list = String[]
    pr_list = String[]

println("\nEvaluating colocations: $(length(keys(collos.counts)))")
    i = 0
    for pr in keys(collos.counts)
        print("$(i)-");i +=1;

        a = collos.counts[pr]
        c = collos.word-a
        b = collos.counts_total[pr]-a
        d= collos.total-b-a-c

        pv1,pv2 = deltap(a,b,c,d)
        push!(word_pr, pv1)
        push!(pr_word, pv2)

        #get fisher values
        if a*b*c*d != 0
            fv = fisher(a,b,c,d)
            push!(fisher_values, fv)
        else
            push!(fisher_values, 1)
        end

        push!(word_list, word)
        push!(pr_list, pr)

    end

    #builds DataFrame
    df["fisher p"]=fisher_values
    df["word -> colexeme"]=word_pr
    df["colexeme -> word"]=pr_word
    df["word"]=word
    df["colexeme"]=pr_list
    return df
end

function collocations(word::String, text::String; test = "deltap", context = 1, lower=true)
    fin = _test_colls(word, _freq_colls(Collo(), word, text, context= context, lower=lower), test=test)
    return sort(fin)
    #sort([(b,a) for (a,b) in fin])
end

function collocations(word::String, texts::Array{String}; test = "deltap",context = 1, lower=true)
    collo = Collo()

    i = 0
    println("Extracting colexemes: $(length( texts)))")
    for text in texts
        print("$(i)-"); i +=1

        collo = _freq_colls(collo,word, text, context=context, lower=lower)
    end

    fin = _test_colls(word, collo,test=test)
    return sort(fin)
    #sort([(b,a) for (a,b) in fin])


end


###################
#-----------------#
#-Collostructions-#
#-----------------#

function collostruction(texts::Array{}, compare::Array{}, test="deltap")
    words = [tokenize(text) for text in texts]
    w_compare = [tokenize(text) for text in compare]

    c_words::Dict{String, Int64}
    c_compare::Dict{String, Int64}

    for word in words
        c_words[word] = _table_freq(word, words)
    end

    for word in w_compare
        c_compare[word] = _table_freq(word, w_compare)
    end



end
