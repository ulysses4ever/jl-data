typealias Document Dict{Int, Int}

type Corpus
    doc::Array{Document}
    D::Int
    W::Int
    function Corpus()
        new([], 0, 0)
    end
    function Corpus(D::Int, W::Int)
        new([Document() for d = 1 : D], D, W)
    end
end

function load_corpus(filename; W = 0, cstyle = false)
    f = open(filename)
    ln = readlines(f)
    D = length(ln)
    close(f)
    corpus = Corpus(D, W)
    for d = 1 : D
        str = split(ln[d])
        if cstyle
            str = str[2:end]
        end
        for s in str
            (w, c) = map(x->parse(Int, x), split(s, ":"))
            if cstyle
                w += 1
            end
            corpus.W = max(w, corpus.W)
            corpus.doc[d][w] = c
        end
    end
    corpus
end

function save_corpus(corpus::Corpus, filename, cstyle = false)
    f = open(filename, "w")
    offset = cstyle ? 1 : 0
    for d = 1 : corpus.D
        wc = collect(corpus.doc[d])
        if cstyle
            @printf(f, "%d ", length(wc))
        end
        for n = 1 : length(wc)-1
            @printf(f, "%d:%d ", wc[n][1]-offset, wc[n][2])
        end
        @printf(f, "%d:%d\n", wc[end][1]-offset, wc[end][2])
    end
    close(f)
end

function split_corpus_by_docs(corpus::Corpus, ratio::Float64)
    ind = randperm(corpus.D)
    D1 = round(Int, corpus.D * ratio)
    corpus1 = Corpus(D1, corpus.W)
    corpus2 = Corpus(corpus.D-D1, corpus.W)
    corpus1.doc = corpus.doc[ind[1:D1]]
    corpus2.doc = corpus.doc[ind[D1+1:end]]
    (corpus1, corpus2)
end

function split_corpus_by_words(corpus::Corpus, ratio::Float64)
    corpus1 = Corpus(corpus.D, corpus.W)
    corpus2 = Corpus(corpus.D, corpus.W)
    for d = 1 : corpus.D
        tw = []
        for (w, c) in corpus.doc[d]
            tw = vcat(tw, fill(w, c))
        end
        N = length(tw)
        tw = tw[randperm(N)]
        N1 = round(Int, N * ratio)
        for n = 1 : N1
            if get(corpus1.doc[d], tw[n], 0) == 0
                corpus1.doc[d][tw[n]] = 1
            else
                corpus1.doc[d][tw[n]] += 1
            end
        end
        for n = N1+1 : N
            if get(corpus2.doc[d], tw[n], 0) == 0
                corpus2.doc[d][tw[n]] = 1
            else
                corpus2.doc[d][tw[n]] += 1
            end
        end
    end
    (corpus1, corpus2)
end

function split_corpus(corpus::Corpus, ratio1::Float64, ratio2::Float64)
    (train, holdout) = split_corpus_by_docs(corpus, ratio1)
    (ho_train, ho_test) = split_corpus_by_words(holdout, ratio2)
    (train, ho_train, ho_test)
end
