# Main functions of adaptative MCL algorithms
# Berkeley 2015 - Maxime Legrand

#Pkg.add("Gadfly")
using Gadfly
include("../plot_tools.jl")
include("../matrix_tools.jl")
include("mcl.jl")

##########################
# r-adaptative algorithm #
##########################

"""r-adaptative MCL algorithm
Input : A, input of MCL
    e, expansion coefficient
    p, number of iterations
    rmin, rmax, resp, such that the r tested are those in rmin:resp:rmax
Output : rspot, Array{Any,2} such that for each i in size(rspot,1) :
    - rspot[i,1] is the r-value used for MCL
    - rspot[i,2] is the number of clusters spotted by MCL(r=rspot[i,1])
    - rspot[i,3] is the output of MCL(r=rspot[i,1])"""
function rad_mcl(A; e=2, p=20, rmin=2, rmax=10, resp=0.1)
    rrange = [rmin:resp:rmax]
    routput = map(r -> mcl(A, e=e, r=r, p=p), rrange)
    rspot = Array(Any,0,3)
    nclust2 = mcl_card(routput[1])
    for i = 1:(length(rrange)-1)
        nclust1, nclust2 = nclust2, mcl_card(routput[i+1])
        if nclust1 < nclust2
            temp = Array(Any, 1, 3)
            temp[1, 1:2] = [rrange[i] nclust1]
            temp[1,3] = routput[i]
            rspot = vcat(rspot, temp)
        end
    end
    temp = Array(Any, 1, 3)
    temp[1, 1:2] = [rrange[end] nclust2]
    temp[1,3] = routput[end]
    rspot = vcat(rspot, temp)
    return rspot
end

##########################
# e-adaptative algorithm #
##########################

"""e-adaptative MCL algorithm
Input : A, input of MCL
    r, inflation coefficient
    p, number of iterations
    emin, emax, eesp, such that the e tested are those in emin:eesp:emax (eesp needs to be an integer)
Output : espot, Array{Any,2} such that for each i in size(espot,1) :
    - espot[i,1] is the e-value used for MCL
    - espot[i,2] is the number of clusters spotted by MCL(e=espot[i,1])
    - espot[i,3] is the output of MCL(e=espot[i,1])"""
function ead_mcl(A; r=3, p=20, emin=2, emax=10, eesp=1)
    erange = [emin:eesp:emax]
    eoutput = map(e -> mcl(A, e=e, r=r, p=p), erange)
    espot = Array(Any, 1, 3)
    nclust2 = mcl_card(eoutput[1])
    espot[1, 1:2] = [erange[1] nclust2]
    espot[1, 3] = eoutput[1]
    for i = 1:(length(erange)-1)
        nclust1, nclust2 = nclust2, mcl_card(eoutput[i+1])
        if nclust1 > nclust2
            temp = Array(Any, 1, 3)
            temp[1, 1:2] = [erange[i+1] nclust2]
            temp[1,3] = eoutput[i+1]
            espot = vcat(espot, temp)
        end
    end
    return espot
end

#################
# Leave one out #
#################



##########################
# Arbitrary assignations #
##########################
