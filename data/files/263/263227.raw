# --- list frequency of 2-node and 3-node motifs in a network
# ---  don't care about multiple representations of the same motif

# --- counts 2-node motif frequency in nw
function motifcount2(nw)
    n = length(nw[:,1])
    ret = zeros(Float64,9)
    for i=1:n
        for j=1:n
            ret[1+3*(1+nw[i,j])+(1+nw[j,i])] += 1
        end
    end
    ret /= n^2
end

# --- returns motif id from the edge list
function motifmap(ij,ji,ik,ki,jk,kj)
    nij = 3*(1+ij)+(1+ji)
    nik = 3*(1+ik)+(1+ki)
    njk = 3*(1+jk)+(1+kj)
    return 1+81*nij+9*nik+njk
end


# --- returns edge list from the motif id
function motifbackmap(motifnum)
    motifnum -= 1
    i = fld(motifnum,81)
    nij = fld(i,3)-1
    nji = mod(i,3)-1
    motifnum = mod(motifnum,81)
    i = fld(motifnum,9)
    nik = fld(i,3)-1
    nki = mod(i,3)-1
    i = mod(motifnum,9)
    njk = fld(i,3)-1
    nkj = mod(i,3)-1
    return (nij,nji,nik,nki,njk,nkj)
end


motifname = Dict();
motif2id = Dict();
id2motif = Dict();

id=0;
for ij=-1:1:1 for ji=-1:1:1 for ik=-1:1:1 for ki=-1:1:1 for jk=-1:1:1 for kj=-1:1:1
    mini = min(motifmap(ij,ji,ik,ki,jk,kj),motifmap(ji,ij,jk,kj,ik,ki),motifmap(kj,jk,ki,ik,ji,ij),motifmap(ik,ki,ij,ji,kj,jk),motifmap(jk,kj,ji,ij,ki,ik),motifmap(ki,ik,kj,jk,ij,ji))
    motifname[motifmap(ij,ji,ik,ki,jk,kj)] = mini
    if (!haskey(motif2id,mini))
        id += 1
        motif2id[mini] = id
        id2motif[id] = mini
    end
end end end end end end


# --- counts 3-node motif frequency in nw
function motifcount3(nw)
    n = length(nw[:,1])
#    ret = zeros(Float64,729)            # 3^6 edge combinations
    ret = zeros(Float64,138)            # 138 = # of distinct 3-motifs
    for i=1:n for j=1:n for k=1:n
        id = motif2id[motifname[motifmap(nw[i,j],nw[j,i],nw[i,k],nw[k,i],nw[j,k],nw[k,j])]]
        ret[id] += 1
    end end end
    ret /= n^3
end

