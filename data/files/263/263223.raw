include("/home/alkan/c/nese/jtb/yeast_dyn.jl")

## ---- find number of coop nodes in a state ---
function ncoop (s,intr)
    n = length(s)
    act = intr*diagm(s) # keep only the columns for active nodes
    nc=0
    for (i=1:n)
#        if (abs(sum(act[i,:])) == sum(abs(act[i,:])))
        if (!in(1,act[i,:]) || !in(-1,act[i,:]))
            nc += 1
        end
    end
    return nc
end

## ---- find coop coef for ALL point attractors of a network ---
function cooppointattr (intr,slf)
    listt = getpointattr(intr,slf)[:,2:end] # first in the list is the zero attr
    ncop=Int64[];
    for (i=1:length(listt[1,:]))
        push!(ncop,ncoop(listt[:,i],intr))
    end
    if (length(ncop)==0)  return -1,-1  # no fixed point other than (0,..0)
    else return (mean(ncop)/n,mean(listt))
    end
end


## ---- find coop coef for sampled cycles of a network ---
function coopattr (intr,slf,ninit)
    n = length(slf)
    (listc,listb,listlen) = getcyclessample(intr,slf,ninit)
    listcop=Float64[];
    listact=Float64[];
    npointattr = 0;
    for (i=1:length(listc[1,:]))        # go over each attractor
        s = listc[:,i]
        if (sum(s) != 0)
            ncp = ncoop(s,intr)
            nac = sum(abs(intr)*s)
            period = 1
            s=upd(s,intr,slf,n)
            while (s != listc[:,i])
                ncp += ncoop(s,intr)
                nac += sum(abs(intr)*s)
                period += 1
                s=upd(s,intr,slf,n)
            end
            push!(listcop,ncp/period)
            push!(listact,nac/period)
            if (period==1) npointattr += 1 end
        end
    end
    if (length(listcop)==0)  return -1,-1,-1,-1 # no fixed point other than (0,..0)
    else                    # also returns the fracion of active nodes
        return (1.0*mean(listcop)/n,mean(listact)/n,length(listcop),npointattr) 
    end
end



## ---- find coop coef for sampled cycles weighted by basin size ---
function coopbasinweighted (intr,slf,ninit)
    n = length(slf)
    (listc,listb,listlen) = getcyclessample(intr,slf,ninit)
    listcop=Float64[];
    listact=Float64[];
    totalweight=0;
    for (i=1:length(listc[1,:]))
        s = listc[:,i]
        if (sum(s) != 0)                # exclude the zero attractor
            ncp = ncoop(s,intr)
            nac = sum(abs(intr)*s)
            period = 1
            s=upd(s,intr,slf,n)
            while (s != listc[:,i])
                ncp += ncoop(s,intr)
                nac += sum(abs(intr)*s)
                period += 1
                s=upd(s,intr,slf,n)
            end
            push!(listcop,listb[i]*ncp/period) # weigh with basin weight
            push!(listact,listb[i]*nac/period)
            totalweight += listb[i]            # excludes the zero attractor
        end
    end
    if (length(listcop)==0)  return -1,-1 # no fixed point other than (0,..0)
    else  return (sum(listcop)/(n*totalweight),sum(listact)/(n*totalweight))
    end
end



## ---- find coop coef for ALL cycles of a network ---
function coopattrall (intr,slf,ninit)
    n = length(slf)
    (listc,listb) = getcycles(intr,slf)
    listcop=Float64[];
    listact=Float64[];
    listlen=Float64[];
    for (i=1:length(listc[1,:]))        # go over each attractor
        s = listc[:,i]
        if (sum(s) != 0)
            ncp = ncoop(s,intr)
            nac = sum(abs(intr)*s)
            period = 1
            s=upd(s,intr,slf,n)
            while (s != listc[:,i])
                ncp += ncoop(s,intr)
                nac += sum(abs(intr)*s)
                period += 1
                s=upd(s,intr,slf,n)
            end
            push!(listcop,ncp/period)
            push!(listact,nac/period)
            push!(listlen,period)
        end
    end
    if (length(listcop)==0)  return -1,-1 # no fixed point other than (0,..0)
    else                    # also returns the fracion of active nodes
        return (1.0*mean(listcop)/n,mean(listact)/n) 
    end
end


