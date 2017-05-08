include("yeast_dyn.jl")
include("coop.jl")


listt = getpointattr(interc,selfact)
natt = length(listt[1,:])
nc=0;
for (i=1:natt)
    nc += ncoop(listt[:,i],interc,selfact)
end
println("yeast's avg nc = ",nc/natt)

# --- generate a good random (n,k,p)_yeast network
function randomnet (intr,slf)
    n = length(slf)
    nw = similar(intr)                  # this will be the randomized version
    shf = shuffle(slf)                  # fix number of self degredating genes
    tl = tril(intr)                     # remove diag and join upper/lower triang
    tu = triu(intr)
    rect = tu[:,2:end]+tl[:,1:end-1]    # shuffle this
    rect = reshape(shuffle(reshape(rect,length(rect),1)[:,1]),n,n-1)
    rrect = [rect zeros(Int64,n)]       # now insert back the shuffled diagonal
    lrect = [zeros(Int64,n) rect]
    nw = tril(rrect - diagm(diag(rrect))) + triu(lrect-diagm(diag(lrect)))
    return (nw,shf)
end


# --- calculate the average cooperativity over random networks with yeast's (n,k,p) ---
listc=Float64[]
ntotal = 1000;
notconn=0;
for(i=1:ntotal)
    (intersh,selfsh) = randomnet(interc,selfact)
    if (isconnected(symadj(intersh)))
        listt = getpointattr(intersh,selfsh)
        natt = length(listt[1,:])
        ncop=0;
        for (i=1:natt)
            ncop += ncoop(listt[:,i],intersh,selfsh)
        end
        push!(listc,ncop/natt)
    else
        notconn += 1
    end
end
println(100*notconn/ntotal,"\% not connected") 
println("(avg,std) of nc over random networks = (",mean(listc),",",std(listc),")")
