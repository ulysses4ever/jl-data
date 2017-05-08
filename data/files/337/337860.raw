function get_corpus_frequencies(corpus, ngram; groupby = "words")
    # to get frequency of symbol x after ngram symbols
    ngram = ngram + 1
    if groupby == "chars"
        corpus = split(corpus, "")
    else
        corpus = split(corpus)
    end

    # find unique symbols
    unique_symbols = unique(corpus)
    # convert text to numbers
    corpus_numeric = text_to_numeric(corpus, unique_symbols);
    # create M
    dimensions = repeat([length(unique_symbols)], outer=[ngram])
    M = repeat(zeros(UInt16, 1), outer = dimensions)
    # get frequencies for ngram of text
    for i in 1:length(corpus)-ngram+1
        M[corpus_numeric[i:i+ngram-1]...] += 1
    end

    M
end

function choose_next_state(distribution, r)
    # only consider entries that are non-zero
    nonzero_entries = findn(distribution)

    distribution_nonzero = distribution[nonzero_entries]
    ranges = cumsum(distribution_nonzero)

    for (idx, range) in enumerate(ranges)
        if r < range
            return nonzero_entries[idx]
        end
    end
end

function trickle_down(current_state, M)
    none_worked = true
    for (idx, P) in enumerate(M)
        sigma = convert(Int, sum(P[current_state[idx:end]..., :][:]))
        if sigma != 0 # avoid division by 0 error
            distribution = P[current_state[idx:end]..., :][:] /
                           sum(P[current_state[idx:end]..., :][:])
            r = rand()
            next_word_idx = choose_next_state(distribution, r)
            none_worked = false
            break
        end
    end
    if none_worked
        # just choose next state at random
        next_word_idx = rand(1:length(M[1][current_state..., :][:]))
    end

    next_word_idx
end
