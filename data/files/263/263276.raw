include("/home/akabakcioglu/tex/nese/jtb/calc/yeast_dyn.jl")
include("/home/akabakcioglu/tex/nese/jtb/calc/coop.jl")
include("/home/akabakcioglu/tex/nese/jtb/calc/shuffle.jl")
srand(1)

# --- calculate average cooperativity over random networks
scale = 1
n = 11*scale
nones = int(6*scale)
self = [ones(Int64,nones),zeros(Int64,n-nones)]
ne = 29*scale               # number of edges
numinit = 2^11              # num of initial cond for fp determination
ntotal = 10
output = Array(Float64,0,4)
listc=Float64[]                    # list of cooperativity values
lista=Float64[]                    # list of active node fractions
for np = 15*scale:1:15*scale
    inter = randomnkp(self,ne,np) # generate one sample with given (nkp)
    netdict = Dict();
    i=0
    while (i<ntotal)
        (intersh,selfsh) = shufflenet(inter,self) # shuffle
        if (isconnected(symadj(intersh))) # check if connected
            (ncop,actratio) = coopattr(intersh,selfsh,numinit)
            if ncop == 1
                i += 1                  # increase network count
                ## print output
                adj = intersh+diagm(selfsh)
                fp = open("110.alphaone","a")
                for ii=1:n
                    for jj=1:n
                        if adj[ii,jj] != 0
                            aij=adj[ii,jj]
                            write(fp,"$ii $jj $aij\n")
                        end
                    end
                end
                flush(fp)
                close(fp)
                print(".")
            end
        end
    end
end
