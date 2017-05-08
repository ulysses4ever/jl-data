function explode(cues)
    # Expands the cues. The cues must all be in an array, separated from one another
    # by an _
    cues_n =Array{Dict,1}[]
    vals = Set() # this stores the actual labels of the cues

    for cue in cues
        spl = split(cue,"_")
        dc = Dict(spl, rep(true, length(spl)))
        for key in keys(dc)
            push!(vals, key)
        end
        cues_n = vcat(cues_n,dc)
    end
    return(cues_n, vals)
end

function one_hot (cues, vals)
    # Builds the one-hot representation of the data
    M = int(zeros(length(cues),length(vals)))
    for (cue_i, cue) in enumerate(cues)
        for (val_i, val) in enumerate(vals)
            M[cue_i, val_i] = int(get(cue, val, 0))
        end
    end
    return (M)
end

function ortho_coding(words, gram=1, sep="_")
    # Split in letter sequences of size 1
    # It adds a # if gram > 1
    if gram > 1
        words = ["#$w#" for w in words]
    end
    return [join([w[i:i+gram-1] for i in (1:length(w)-gram+1)], sep) for w in words]
end

function ndl(data)

    totals = by(data, :Cues, df -> sum(df[:Frequency]))
    data = join(data, totals, on=:Cues)

    # Build cues from the cues Column
    cues = data[:Cues]
    cues, vals = explode(cues)

    M = one_hot(cues, vals)
    M = M.*data[:Frequency]

    # Make co-occurrence matrix C
    C = zeros(length(vals),length(vals))

    Mt = array(M')

    mapslices(Mt,1) do col
        for nz in find(col)
            C[:,nz] += col
        end
    end

    Ct = C'

    # Normalize
    Z = sum(Ct,1)
    C1 = Ct./Z

    # Build outcome matrix O
    X, valsx = explode(data[:Outcomes])
    X = one_hot(X, valsx)
    Xt = (X .* data[:Frequency])'

    Ot = (zeros(length(vals), length(valsx)))'

    for i in (1:size(Xt)[2])
        for nz in find(Mt[:,i])
            Ot[:,nz] += Xt[:,i]
        end
    end

    # Normalize

    O1 = (Ot ./ Z)'
    W = pinv(C1')*O1

    # Build data frame
    weights = convert(DataFrame, W)
    name = [symbol("$x ") for x in valsx]
    names!(weights, name)

    weights[:Cues] = collect(vals)
    return weights
end
