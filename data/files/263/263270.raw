include("yeast_dyn.jl")
include("coop.jl")
include("shuffle.jl")
#srand(1)

## --- a (wrong?) analytical model for mean cooperativity
## --- gamma = 2.5 is the best fit to the data for n=100
## --- with basin weighted averaging - coopbasinweighted()
function coop_anal(p,a)
return p^a + (1-p)^a
end


# --- calculate average cooperativity over random networks
n = 11
n = length(selfact)
ne = 29                                # number of edges
ntotal = 50000;                        # ensemble size
listc=Float64[]                    # list of cooperativity values
lista=Float64[]                    # list of active node fractions
notconn=0;
nofp=0;
samenw=0;
for (np = 15:1:15)                     # scan np = 0 .. ne
#    interc = randomnkp(selfact,ne,np) # generate one sample with given (nkp)
    netdict = Dict();
    i=0
    while (i<ntotal)
        (intersh,selfsh) = (switchnet(interc),selfact) # preserve in/out degrees
#        (intersh,selfsh) = shufflenet(interc,selfact) # shuffle
        if (isconnected(symadj(intersh))) # check if connected
            netkey=join(sort(real(eigvals(intersh+diagm(selfsh)))))
            if (haskey(netdict,netkey)) samenw += 1  # generated before
            else
                i += 1                  # increase network count
                netdict[netkey] = 1      # record this network
                (ncop,actratio) = cooppointattr(intersh,selfsh) # get cooperativity
                if (ncop >= 0)    # will return -1 if no nontrivial fp
                    push!(listc,ncop)
                    push!(lista,actratio) 
                else nofp += 1 end
            end
        else notconn += 1 end
        if i%(ntotal/100)==0 print(".") end
    end
    println("\n same network count = ",samenw)
end
(bins,vals) = hist(listc)
#display(plot(bins,vals))


