include("yeast_dyn.jl")
include("shuffle.jl")
include("coop.jl")
srand(1)

## listt = getpointattr(interc,selfact)
println("\n yeast's avg coop = ",cooppointattr(interc,selfact)[1])
## println("\n yeast's avg coop = ",coopbasinweighted(interc,selfact)[1]/length(selfact))

## --- a (wrong?) analytical model for mean cooperativity
## --- gamma = 2.5 is the best fit to the data for n=100
## --- with basin weighted averaging - coopbasinweighted()
function coop_anal(p,a)
return p^a + (1-p)^a
end

# --- calculate average cooperativity over random networks
tstart = time()
n = 11*3
selfact = rand(0:1,n)
n = length(selfact)
ne = 29*3                                # number of edges
ntotal = 100;                         # ensemble size
output = Array(Float64,0,4)
netdict = Dict();
for (np = 15*3:1:15*3+1)                      # scan np = 0 .. ne
    listc=Float64[]                    # list of cooperativity values
    lista=Float64[]                    # list of active node fractions
    notconn=0;
    nofp=0;
    samenw=0;
    interc = randomnkp(selfact,ne,np) # generate one sample with given (nkp)
    netdict = Dict();
    i=0
    while (i<ntotal)
#        (intersh,selfsh) = (switchnet(interc),selfact) # preserve in/out degrees
        (intersh,selfsh) = shufflenet(interc,selfact) # shuffle
        if (isconnected(symadj(intersh))) # check if connected
#            netkey=join(sort(real(eigvals(intersh+diagm(selfsh)))))
            netkey=join(reshape(intersh+diagm(selfsh),n*n,1))
#            if (haskey(netdict,netkey)) samenw += 1  # generated before
#            else
            netdict[netkey] = 1      # record this network
            (ncop,actratio) = coopattr(intersh,selfsh) # get cooperativity
##            (ncop,actratio) = cooppointattr(intersh,selfsh) # get cooperativity
##                (ncop,actratio) = coopbasinweighted(intersh,selfsh) # get cooperativity
            if (ncop >= 0.99)  # will return -1 if no nontrivial fp
                push!(listc,ncop)
                println(ncop)
                push!(lista,actratio) 
            else
                nofp += 1
            end
#                        end
        else
            notconn += 1
        end
    end
    println("\n", np/ne,"\t",mean(listc),"\t",std(listc),"\t",samenw,"\t",mean(lista))
    output = [output;[np/ne,mean(listc),std(listc),mean(lista)]']
end
tend = time()
println("time:",tend-tstart)
plot(output[:,1],output[:,2])


