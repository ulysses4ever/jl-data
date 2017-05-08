interc = readdlm("/home/alkan/c/nese/jtb/Adj_matrix_yeast.dat",' ',Int64);

n = length(interc[:,1])                 # number of nodes
selfact = diag(interc)                  # yeast specific
interc -= diagm(selfact)                # interaction matrix


# --- generate the symmetric adjacency matrix with elements 0,1 ---
function symadj(m)
    n = length(m[:,1])
    ad = zeros(Int64,n,n)
    for (i=1:n) for (j=i+1:n)       # adjacency matrix - without diagonals
        ad[i,j] = m[i,j]==0 && m[j,i]==0 ? 0 : 1
        ad[j,i] = ad[i,j]
    end end
    return ad
end

## ad = symadj(interc)

## --- check connectivity -----------
function isconnected (adj)
    n = length(adj[:,1])                # number of nodes
    nsq = n*n
    dum = adj
    (sumprev,sumdum) = (0,0)
    for (i=1:n)
        dum = sign(dum + dum*adj)
        sumdum = sum(dum)
        if (sumdum == sumprev)
            break
        end
        sumprev = sumdum
    end
    return (sumdum==nsq)
end    

## --- node update function (integrator) -----------
function upd(s,intr,slf,n)
    sss = similar(s)
    inp = intr*s
    for (i=1:n)
        sss[i] = (inp[i]>0)?1:(inp[i]<0)?0:(slf[i]==0)?0:s[i]
    end
    return sss
end

## --- check fixed point ---
function isfixed (s,intr,slf,n)
    snew = upd(s,intr,slf,n)
    return (snew==s)
end


## ---- find point attractors of a small network ---
function getpointattr(intr,slf)
    n = length(slf)
    attrlist = zeros(Int64,n)                 # s=0 is always an attractor
    for (i=1:2^n-1)                           # visit each state except s=0
        s = digits(parseint(bits(i)))
        lens = length(s)
        if (lens < n)
            s = [s;zeros(Int64,n-lens)]
        end
        if (isfixed(s,intr,slf,n))
            attrlist = [attrlist s]
        end
    end
    return attrlist
end


## ---- find ALL attractors of a small network ---
## ---- by exhaustive search ---
## ---- output is the attractor list + periods ---
function getcycles(intr,slf)
    n = length(slf)
    nm1 = n-1
    attrlist = zeros(Int64,n)           # s=0 is always an attractor
    keyzeros = join(zeros(Int64,n))
    visdict = [keyzeros=>keyzeros] # add the zero fixed point to visited list
    attdict = [keyzeros=>1]    # values are the basin sizes
    for (i=1:2^n-1)            # visit each state except s=0
        skey = bits(i)[end-nm1:end]
        s = [int(skey[x])-48 for x = 1:n]
        if (!haskey(visdict,skey))      # if not seen this state before
            pathdict = Dict()
            while (!haskey(visdict,skey))   # generate a path starting here
                pathdict[skey] = "-"            
                visdict[skey] = "-"            
                s = upd(s,intr,slf,n)
                skey=join(s)         # join(s) == bits(i)[end-nm1:end]
            end
            attkey=visdict[skey]
            if (haskey(attdict,attkey)) # reached a known cycle or fp
                for (k in keys(pathdict))
                    visdict[k]=attkey 
                    attdict[attkey] += length(keys(pathdict)) # basin
                end
            else                        # this is a new cycle of fp
                for (k in keys(pathdict)) visdict[k] = skey end
                attdict[skey]=length(keys(pathdict)) # basin
                attrlist = [attrlist s]
            end
        end
    end
    basinlist = [attdict[join(attrlist[:,i])]/(2^n-1) for i in 1:length(attrlist[1,:])]
    return attrlist,basinlist
end



## ---- output is the attractor list + basin sizes ---
## ---- calculated from a subset of initial conditions ---
function getcyclessample(intr,slf,ninit)

    n = length(slf)
    nm1 = n-1
    attrlist = zeros(Int64,n)           # s=0 is always an attractor
    keyzeros = join(zeros(Int64,n))
    attdict = [keyzeros=>0]    # values are the basin sizes
    cyclen = [keyzeros=>1]    # values are the cycle lengths
    for (i=1:ninit)       # calculate basins using ninit initial states
        s = rand(0:1,n)
        skey = join(s)
        pathdict = Dict()
        pathlen = 1
        while (!haskey(attdict,skey) && !haskey(pathdict,skey))
            pathdict[skey] = pathlen
            pathlen += 1
            s = upd(s,intr,slf,n)
            skey=join(s)         # join(s) == bits(i)[end-nm1:end]
        end
        if (haskey(attdict,skey)) attdict[skey] += 1
        else                        # this is a new cycle of fp
            attdict[skey] = 1
            cyclen[skey] = pathlen - pathdict[skey]
            attrlist = [attrlist s]
        end
    end
    basinlist = [attdict[join(attrlist[:,i])]/ninit for i in 1:length(attrlist[1,:])]
    cyclelengthlist = [cyclen[join(attrlist[:,i])] for i in 1:length(attrlist[1,:])]
    return attrlist,basinlist,cyclelengthlist
end
    



function getcyclessample_backup(intr,slf,ninit)
    
    n = length(slf)
    nm1 = n-1
    attrlist = zeros(Int64,n)           # s=0 is always an attractor
    keyzeros = join(zeros(Int64,n))
    attdict = [keyzeros=>0]    # values are the basin sizes
    for (i=1:ninit)       # calculate basins using ninit initial states
        s = rand(0:1,n)
        skey = join(s)
        pathdict = Dict()
        while (!haskey(attdict,skey) && !haskey(pathdict,skey))
            pathdict[skey] = "-"
            s = upd(s,intr,slf,n)
            skey=join(s)         # join(s) == bits(i)[end-nm1:end]
        end
        if (haskey(attdict,skey)) attdict[skey] += 1 
        else                        # this is a new cycle of fp
            attdict[skey] = 1
            attrlist = [attrlist s]
        end
    end
    basinlist = [attdict[join(attrlist[:,i])]/ninit for i in 1:length(attrlist[1,:])]
    return attrlist,basinlist
end


