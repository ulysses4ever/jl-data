function fscore(clusters,assigned)
    M = length(clusters)
    # relevant array indices for comparisons below
    upperTriInds = [[a,b] for a in 1:M, b in 1:M]
    upperTriInds = bool([x[2]>x[1] for x in upperTriInds])
    # pairwise comparisons for original clusters
    comp1 = [i==j for i in clusters, j in clusters]
    comp1 = reshape(comp1,prod(size(comp1)))
    comp1 = comp1[upperTriInds]
    # pairwise comparison for assigned labels
    comp2 = [i==j for i in assigned, j in assigned]
    comp2 = reshape(comp2,prod(size(comp2)))
    comp2 = comp2[upperTriInds]
    # detection theoretic numbers:
    TP = 0
    FP = 0
    FN = 0
    TN = 0
    for i=1:length(comp1)
        if (comp1[i]==true) & (comp2[i] == true)
            TP += 1
        elseif (comp1[i] == false) & (comp2[i] == true)
            FP += 1
        elseif (comp1[i] == true) & (comp2[i] == false)
            FN += 1
        else
            TN += 1
        end
    end
    # precision, recall, and f-measure
    p = TP/(TP+FP)
    r = TP/(TP+FN)
    gc()
    return (2*(p*r)/(p+r),p,r)
end

# function fscores(models,test,dims)
#     scores = Any[]
#     for i=1:length(models)
#         labels = classify(models[i],test,dims)
#         scores = cat(1,scores,fscore(test[7,:],labels))
#     end
#     return scores
# end

function fmean(models,test,dims,row)
    scores = Any[]
    for i=1:length(models)
        labels = classify(models[i],test,dims)
        scores = cat(1,scores,fscore(test[row,:],labels))
    end
    fs = [x[1] for x in scores];
    ps = [x[2] for x in scores];
    rs = [x[3] for x in scores];
    # means
    fm = median(fs)
    fl = percentile(fs,0.025)
    fu = percentile(fs,0.975)
    pm = median(ps)
    pl = percentile(fs,0.025)
    pu = percentile(fs,0.975)
    rm = median(rs)
    rl = percentile(fs,0.025)
    ru = percentile(fs,0.975)
    return (fm,fl,fu,pm,pl,pu,rm,rl,ru)
end