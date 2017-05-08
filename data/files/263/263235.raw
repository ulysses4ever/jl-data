include("yeast_dyn.jl")
include("shuffle.jl")
include("coop.jl")
include("motif.jl")
srand(1)

    
scale = 1
n = 11*scale
s = selfact;
for i=2:scale s = [s;selfact] end
selfact = s
n = length(selfact)
ne = 29*scale
np = 15*scale
interc = randomnkp(selfact,ne,np)
ntotal = 100000
nalpha = 16
amin = 0.5
alpha= amin + (1-amin)*[0:nalpha]/nalpha - 0.5*(1-amin)/nalpha # linspace(0,1,n)?
palpha = zeros(Float64,1+nalpha)
nmotif2=3^2
#nmotif3=3^6
nmotif3=138
ninit=2^11
listc = Array(Float64,0)
motifcoop = zeros(Float64,nmotif3,1+nalpha)
#interc = randomnkp(selfact,ne,np)
i=0
while (i<ntotal)
    (intersh,selfsh) = (switchnet(interc),selfact)
#    (intersh,selfsh) = shufflenet(interc,selfact)
    if (isconnected(symadj(intersh)))
#        (a,actratio) = cooppointattr(intersh,selfsh)
        (a,actratio) = coopattr(intersh,selfsh,ninit)
        push!(listc,a)
        if (a >= amin)      # returns -1 if no nontrivial attractor found
            na = 1+ifloor(nalpha*(a-amin)/(1-amin) + 0.5)
            palpha[na] += 1
            motifcoop[:,na] += motifcount3(intersh)
            i += 1
            if i%(ntotal/100)==0 print(".") end
        end
    end
end

palpha /= ntotal
writedlm("alphas.$n.$ne.$np.$ntotal.dat",listc,' ')
writedlm("motifcoop.$n.$ne.$np.$ntotal.dat",motifcoop',' ')
writedlm("palpha.$n.$ne.$np.$ntotal.dat",palpha,' ')
motifcoopnorm = similar(motifcoop)
for i=1:nmotif3
    motifcoopnorm[i,:] = motifcoop[i,:] ./ palpha'
end
writedlm("motifcoop_norm.$n.$ne.$np.$ntotal.dat",motifcoopnorm',' ')

## for i=1:nmotif3
##     readline()
##     plot(alpha,motifcoopnorm[i,:])
## end
