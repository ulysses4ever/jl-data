# Ryan Freedman
# Giant Oak June 2014
# MMPP code

# -------------------------
#   Start Type Definitions
# -------------------------

abstract total

# packages used
# for random numbers and specific distributions
using Distributions

# for switch cases, as they aren't implemented in julia yet
# didn't want to use if/elseif/else because they operate
# differently than switch
using Match

# for reading matlab data files
# i.e.) data.mat
using MAT

using Winston

# for timing purposes
time_precomp = time()

type prior <: total
    aL::Int32     # 1
    bL::Int32     # 1
    aD::Array     # zeros(1,7)+5
    aH::Array     # zeros(48,7)+1
    z00::Float64  # 9900
    z01::Float64  # 100
    z10::Float64  # 2500
    z11::Float64  # 7500
    aE::Int8      # 5
    bE::Float64   # 1//3
    MODE::Int8    # 0
end

type sample <: total
    L::Array
    Z::Array
    M::Array
    N0::Array
    NE::Array
    logp_NgLM::Array
    logp_NgLZ::Array
    logpC::Float64
    logpGD::Float64
end

# -------------------------
#    End Type Definitions
# -------------------------
# Start Sampling Functions
# -------------------------

    # to be implemented
    # N      : Data in
    # priors : Prior values structure
    # ITERS  : Number of iterations to go through
    # events : Events (???)
    # EQUIV  : [3,3]
    # return value : samples 

# NOTE: I changed the order of the arguments



function sensorMCMC(N::Array,priors::prior,events::Array,ITERS::Array=[50,25,10],EQUIV::Array=[3,3])
# samples = sensorMCMC(Data,priors,[Niter Nburn Nplot], events, EQUIV)
#    Data   : (Ntimes x 7*Nweeks) matrix of count data (assumed starting Sunday)
#    Priors : structure with parameter values of prior distributions
#    [...]  : Iteration controls: total # of iterations, # used for burn-in,
#               and # of iterations between plots
#    Events : binary matrix with known events marked (used for plotting)
#    Sharing: used to force parameter sharing, = [S1,S2]
#              S1 = force sharing of delta (day effect) among days
#              S2 = force sharing of eta (time of day) among *ays
#              Values: 1 (all days share),  2 (weekdays/weekends),  3 (none)

# Copyright (C) 2006 Alexander Ihler; distributable under GPL -- see README.txt

    if (length(events)==0)
        events = zeros(size(N),size(N))
    end

    @match length(ITERS) begin
        0 => temp = (25, 10, 100)
        1 => temp = (25, 10, ITERS[1])
        2 => temp = (25, ITERS[2], ITERS[1])
        3 => temp = (ITERS[3], ITERS[2], ITERS[1])
    end
    Nplot = temp[1]
    Nburn = temp[2]
    Niter = temp[3]
    # @printf "Running the Markov-modulated Poisson model...\n"
    # @printf "Data is %d days long with %d measurements per day;\n" size(N,2) size(N,1)
    # @match EQUIV[1] begin # d(t)
        # 1 => @printf "All days share total (per day) rate; "
        # 2 => @printf "Weekend/weekdays share total (per day) rate; "
        # 3 => @printf "Total (per day) rate unshared; "
    # end
    # @match EQUIV[1] begin # h(t)
        # 1 => @printf "All days share time profile.\n"
        # 2 => @printf "Weekend/weekdays share time profile.\n"
        # 3 => @printf "Time profile unshared.\n"
    # end
    # @printf "Running for %d iterations, with %d for burn-in and plotting every %d.\n" Niter Nburn Nplot
    Z=zeros(size(N)[1],size(N)[2])
    N0=max(N,1)
    NE=zeros(size(N)[1],size(N)[2])
    L=(N.+5)/2
    M=[.999 .5;.001 .5]
    Nd=7
    Nh=size(N,1)
    samples = sample(zeros(1),zeros(1),zeros(1),zeros(1),zeros(1),zeros(1),zeros(1),0,0)
    samples.L = zeros(size(L)[1],size(L)[2],Niter)
    samples.Z = zeros(size(Z)[1],size(Z)[2],Niter)
    samples.M = zeros(size(M)[1],size(M)[2],Niter)
    samples.N0 =zeros(size(N0)[1],size(N0)[2],Niter)
    samples.NE =zeros(size(NE)[1],size(NE)[2],Niter)
    samples.logp_NgLM = zeros(1,Niter)
    samples.logp_NgLZ = zeros(1,Niter)

    # MAIN LOOP: MCMC FunctionsOR INFERENCE
    x = Niter+Nburn
    for iter=1:x
        L = draw_L_N0(N0,priors,EQUIV)
        (Z,N0,NE) = draw_Z_NLM(N,L,M,priors)
        M = draw_M_Z(Z,priors)
        if (iter > Nburn)      # SAVE SAMPLES AFTER BURN IN
            samples.L[:,:,iter-Nburn] = L
            samples.Z[:,:,iter-Nburn] = Z
            samples.M[:,:,iter-Nburn] = M
            samples.N0[:,:,iter-Nburn] = N0
            samples.NE[:,:,iter-Nburn] = NE
            samples.logp_NgLM[iter-Nburn] = eval_N_LM(N,L,M,priors)
            samples.logp_NgLZ[iter-Nburn] = eval_N_LZ(N,L,Z,priors)
        end
        if (mod(iter,Nplot)==0 && iter > Nburn)  
            (logpC, logpGD, logpGDz) = logp(N,samples,priors,iter-Nburn,EQUIV)
            logpC=logpC/log(2)
            logpGD=logpGD/log(2)
            logpGDz=logpGDz/log(2)
            #@printf "\n  Est Marginal Likelihd: ln P(Data) = %.1f  (%.3f per time)\n" logpC logpC/length(N)
        end
    end
    q = logp(N,samples,priors,Niter,EQUIV)
    logpC = q[1]/log(2)
    logpGD = q[2]/log(2)
    logpGDz = q[3]/log(2)
    #@printf "\n  Est Marginal Likelihd: ln P(Data) = %.1f  (%.3f per time)\n" logpC logpC/length(N)
    samples.logpC = logpC
    samples.logpGD= logpGD
    return samples
end


# -------------------------
#  End Sampling Functions
# -------------------------
# Start Evaluation Functions
# -------------------------

# return value : tuple (logpC,logpGD,logpGDz) 

function logp(N,samples,priors,iter,EQUIV)
    # Gelfand-Dey Estimate
    tmp = samples.logp_NgLZ[1:iter]
    tmpm = mean(tmp)
    tmp = tmp .- tmpm
    logpGDz = log(1.0/mean(1.0./exp(tmp)))+tmpm

    # Gelfand-Dey Estimate, Margianalizing over Z
    tmp = samples.logp_NgLM[1:iter]
    tmpm = mean(tmp)
    tmp = tmp .- tmpm
    logpGD = log(1.0./mean(1.0./exp(tmp)))+tmpm

    Lstar = mean(samples.L[:,:,1:iter],3)
    Mstar = mean(samples.M[:,:,1:iter],3)
    logp_LMgN = zeros(1,iter)
    temp_Qq = [0] # weird thing about julia: empty arrays are of type Array{None}
    pop!(temp_Qq) # this makes it Array{Int64,0}
    # this comes up in the sum function, we cannot sum the elements of a 0-element array
    # if it has no element type
    # however if it has an element type then we can sum the elements
    # @printf "prior to first call\n"
    temp_test_x = eval_L_N0(Lstar,temp_Qq,priors,EQUIV) # NaN
    temp_test_y = eval_M_Z(Mstar,temp_Qq,priors) # -Inf
    # @printf "temptestx = %f, temptesty = %f \n" temp_test_x temp_test_y
    logp_LM = temp_test_x + temp_test_y
    logp_NgLM = eval_N_LM(N,Lstar,Mstar, priors)
    for ii = 1:iter
        # println("In the loop: iter number : $ii \n")
        tempx = eval_L_N0(Lstar,samples.N0[:,:,ii],priors,EQUIV)
        tempy = eval_M_Z(Mstar,samples.Z[:,:,ii],priors)
    end
    tmpm = mean(logp_LMgN)
    logp_LMgN = logp_LMgN .- tmpm
    logp_LMgN = log(mean(exp(logp_LMgN)) + 1e-99) + tmpm
    logpC = logp_NgLM + logp_LM - logp_LMgN
    # println("LMGN = $(logp_LMgN); NGLM = $(logp_NgLM); LM = $(logp_LM)")
    
    # there is a problem with logp_LM
    # there is also a problem with logp_LMgN

    # this is indicative of eval_L_N0 or eval_M_Z being incorrect
    # either that or the parameters Lstar,priors,Mstar, or samples

    # after looking at these params I don't think they are the issue
    # I can also eliminate passing the empty array (of type Array::None)
    # because no error/warning is thrown (I think)

    # Following the functions down a bit I determined that the NaN is a 
    # Inf - Inf when the function "misses"

    return (logpC,logpGD,logpGDz)
end

function eval_M_Z(M,Z,prior)
    z1 = M[1,2];
    z0 = M[2,1];
    # println("$M") # Problem is with M... it's not the same as it should be
    if (~isempty(Z))
        n0  = length(find(find_custom(0,Z[1:end - 1])))
        n1  = length(find(find_custom(1,Z[1:end - 1])))
        n01 = length(find(andit(find_custom(0,Z[1:end - 1]), find_custom(1,Z[2:end]))))
        n10 = length(find(andit(find_custom(1,Z[1:end - 1]), find_custom(0,Z[2:end]))))
    else
        # println("M21 = $(M[2,1]) M12 = $(M[1,2])")
        n01=0;
        n0=0;
        n10=0;
        n1=0; 
    end;
    retval = log(pdf(Beta(n01+prior.z01,n0-n01+prior.z00),z0) + 1e-99) + log(pdf(Beta(n10+prior.z10,n1-n10+prior.z11),z1) + 1e-99);
    # if retval == -Inf
    #     println("01: $(prior.z01) ;00: $(prior.z00) ;0: $(z0) ;10: $(prior.z10) ;11: $(prior.z11) ;1: $(z1)  <- MISS! \n")
    # end
    return retval
end




# 1st attempt at writing evalMZ and evalLN0, please ignore# return value : logp

# function eval_M_Z(M,Z,priors)
#     z1 = M[1,2]
#     z0 = M[2,1]
#     if  ~isempty(Z)
#         # @printf "Hit! \n"
#         n0  = length(find(find_custom(0,Z[1:end - 1])))
#         n1  = length(find(find_custom(1,Z[1:end - 1])))
#         n01 = length(find(andit(find_custom(0,Z[1:end - 1]), find_custom(1,Z[2:end]))))
#         n10 = length(find(andit(find_custom(1,Z[1:end - 1]), find_custom(0,Z[2:end]))))
#     else
#         @printf "Miss! \n"
#         println("M = $M")
#         # println("priors = Z00: $(priors.z00), Z01: $(priors.z01), Z10: $(priors.z10), Z1: $(z1), Z0: $(z0)")
#         n0,n1,n01,n10 = 0,0,0,0
#         # return 0
#     end
#     ret_val = log(pdf(Beta(n01+priors.z01,n0-n01+priors.z00),z0)) + log(pdf(Beta(n10+priors.z10,n1-n10+priors.z11),z1))
#     # ret_val is -Inf
#     # println("RETURNING M Z : $ret_val")
#     return ret_val
# end

# # return value : logp

function eval_L_N0(L,N0,priors,EQUIV)
    L0 = mean(L)
    Nd = 7
    Nh = size(L,1)
    D = zeros(Nd)
    A = zeros(Nh,Nd)
    for i = 1:Nd
        D[i] = mean(L[:,i]/L0)
    end
    for i = 1:Nd
        for j = 1:Nh
            A[j,i] = L[j,i]/(L0/D[i])
        end
    end
    # --------------- --------------- --------------- --------------- --------------- --------------- ---------------
    # --------------- --------------- ---------------    retval = 0   --------------- --------------- ---------------
    # --------------- --------------- --------------- --------------- --------------- --------------- ---------------
    ret_val = 0
    paD = priors.aD
    aD = zeros(1,Nd)
    paH = priors.aH
    aH = zeros(Nh,Nd)
    if  ~isempty(N0)
        for i = 1:Nd
            aD[i] = sum(sum(N0[:,i:Nd:end]))
        end
        for i = 1:Nd
            for j=1:Nh
                aH[j,i] = sum(sum(N0[j,i:Nd:end]))
            end
        end
    end
    @match EQUIV[1] begin
        1 => D, paD, aD = sum(D), sum(paD), sum(aD)
        2 => D, paD, aD = [D[1]+D[7],sum(D[2:6])],[paD[1]+paD[7],sum(paD[2:6])],[aD[1]+aD[7],sum(aD[2:6])]
    end
    @match EQUIV[2] begin
        1 => A, aH, paH = sum(A,2)/Nd, sum(aH,2), sum(paH,2)
        2 => A, aH, paH = [(A[:,1]+A[:,7])/2,sum(:,2:6,2)/5], [(aH[:,1]+aH[:,7])/2,sum(:,2:6,2)/5], [(paH[:,1]+paH[:,7])/2,sum(:,2:6,2)/5]
    end
    # --------------- --------------- --------------- --------------- --------------- --------------- ---------------
    # --------------- --------------- ---------------    retval = 0   --------------- --------------- ---------------
    # --------------- --------------- --------------- --------------- --------------- --------------- ---------------
    # i need to add the 1e-99 because julia does not have an infinity integrated with the distributions package...
    # @printf "\n ret_val1 LN0 = %f  " ret_val
    ret_val = log((pdf(Gamma(sum(N0) + priors.aL,1/(length(N0)+priors.bL)),L0)) + 0.00001)
    # --------------- --------------- --------------- --------------- --------------- --------------- ---------------
    # --------------- --------------- ---------------   retval = ??   --------------- --------------- ---------------
    # --------------- --------------- --------------- --------------- --------------- --------------- ---------------
    # @printf "\n ret_val2 LN0 = %f " ret_val
    # @printf "\n Nd = %f" Nd # always 7
    # println("paD = $paD") # always [5,5,5...]
    ret_val = ret_val + dirlnpdf(D/Nd,aD+paD)
    # println("ret_val = $ret_val \n D = $D \n aD = $aD \n")
    # println("D/Nd = $(D/Nd) \n aD+paD = $(aD+paD)")
    # @printf "\n ret_val3 LN0 = %f " ret_val
    for i=1:size(A,2)
        ret_val = ret_val + dirlnpdf(A[:,i]/Nh,aH[:,i]+paH[:,i])
        # println("ret_val = $ret_val \n A[:,i]/Nh = $(A[:,i]/Nh) \n aH[:,i]+paH[:,i] = $(aH[:,i]+paH[:,i]) \n")
        # println("return value = $ret_val, i = $i")
    end
    # println("\n ret_valf L N0 = $ret_val")
    return ret_val
end

# return value : logp

function eval_N_LZ(N,L,Z,priors)
    ret_val = 0
    for t=1:length(N)
        if(N[t] != -1)
            if (Z[t] == 0)
                ret_val = ret_val + log(poisspdf(N[t],L[t]))
            else
                ret_val = ret_val + log(sum(poisspdf(0:N[t],L[t] .* nbinpdf(N[t]:-1:0,priors.aE,priors.bE/(1+priors.bE)))))
            end
        end
    end
    return ret_val
end

# return value : logp 

function eval_N_LM(N,L,M,priors)
    #M = [1 1;1 1] # WARNING!!!! NEED TO REMOVE!!!!!!
    temp_M = [M[1] M[2];M[3] M[4]]

    (pRIOR, po, p) = (temp_M^100 .* [1,0], zeros(2,length(N)), zeros(2,length(N)))
    (pRIOR, po, p) = ([1,0], zeros(2,length(N)), zeros(2,length(N)))
    for t=1:length(N)
        if N[t] != -1
            po[1,t] = poisspdf(N[t],L[t])
            po[2,t] = sum(poisspdf(0:N[t],L[t])) .* nbinpdf(N[t]:-1:0,priors.aE,priors.bE/(1+priors.bE))[1]
        else
            po[1,t],po[2,t] = 1,1
        end
    end
    p[:,1] = pRIOR .* po[:,1]
    sp=sum(p[:,1])
    ret_val = log(sp)
    p[:,1]=p[:,1]/sp
    for t=2:length(N)
        p[:,t] = (temp_M * p[:,t-1]).*po[:,t]
        sp = sum(p[:,t])
        ret_val = ret_val + log(sp)
        p[:,t] = p[:,t]/sp
     end
    return ret_val
end

# -----------------------
# End Evaluation Functions
# -----------------------
#   Start PDF Functions
# -----------------------

# return value : p 

function dirpdf(X,A)
    k = length(X)
    if  k == 1
        p = 1
        return p
    end
    logp = sum((A.-1).*log(X.+0.000001)) - sum(log(gamma(A).+0.000001)) + log(gamma(sum(A)).+0.000001)
    p = exp(logp)
    return p
end

# return value : logp

function dirlnpdf(X,A)
    if length(X) == 1
        return 1
    end
    retval = sum((A.-1).*log(X .+ 0.000001))
end

# return value : p 

function poisspdf(X,L)
    lnp = - L .- log(gamma(X+1)).+log(L).*X
    p = exp(lnp)
    return p
end

# return value : lnp

function poisslnpdf(X,L)
    lnp = -L .-log(gamma(X+1)) +log(L).*X
    return lnp
end

# return value : p

function nbinpdf(X,R,P)
    lnp = log(gamma(X+R)) .- log(gamma(R)) - log(gamma(X+1)) .+ log(P).*R + log(1-P).*X
    p = exp(lnp)
    return p
end

# return value : lnp

function nbinlnpdf(X,R,P)
    lnp = log(gamma(X+R)) .- log(gamma(R)) .- log(gamma(X+1)) .+ log(P).*R .+ log(1-P).*X
    return lnp
end

# ----------------------
#    End PDF Functions
# ----------------------
# Start Drawing Functions
# ----------------------

# return value : [Z,N0,NE]

function draw_Z_NLM(N,L,M,priors)
    N0 = N
    NE = 0*N
    Z=0*N
    ep = 1e-50
    #-----------------------------------------------------------------
    #-----------------------------------------------------------------
    PRIOR = M^100 * [1;0]
    po=zeros(2,length(N))
    p=zeros(2,length(N))
    for t=1:length(N)
        if (N[t]!=-1)
            po[1,t] = poisspdf(N[t],L[t])+ep
            po[2,t] = sum( poisspdf(0:N[t],L[t]) .* nbinpdf(N[t]:-1:0,priors.aE,priors.bE/(1+priors.bE)) )+ep
        else
            po[1,t]=1
            po[2,t]=1
        end
    end
    #-----------------------------------------------------------------
    #-----------------------------------------------------------------
    p[:,1] = PRIOR .* po[:,1]
    p[:,1]=p[:,1]/sum(p[:,1])
    for t=2:length(N)
        p[:,t] = (M*p[:,t-1]).*po[:,t]
        p[:,t]= p[:,t]/sum(p[:,t])
    end
    #---------------------------------------------------------------------
    #---------------------------------------------------------------------
    # Do backward sampling
    for t=length(N):-1:1
        if (rand(1)[1] > p[1,t])                           # if event at time t
            if (N[t]!=-1)
                Z[t] = 1
                # likelihood of all possible event/normal combinations (all
                # possible values of N(E)
                ptmp = poisslnpdf(0:N[t],L[t]) + nbinlnpdf(N[t]:-1:0,priors.aE,priors.bE/(1+priors.bE))
                ptmp=ptmp.-maximum(ptmp)        # WARNING!!!!!!
                ptmp=exp(ptmp)
                ptmp=ptmp/sum(ptmp)
                N0[t] = minimum(find(find_ge(rand(1)[1],cumsum(ptmp)))).-1  # WARNING!!!!!!
                NE[t] = N[t]-N0[t]                              # and compute NE
            else
                Z[t]=1
                N0[t]=rand(Poisson(L[t]))
                NE[t]=rand(NegativeBinomial(priors.aE,priors.bE/(1+priors.bE)))
            end
        else
            if (N[t]!=-1)
                Z[t] = 0
                N0[t] = N[t]
                NE[t]=0              # no event at time t
            else
                Z[t]=0
                N0[t]=rand(Poisson(L[t]))
                NE[t]=0
            end
        end
        ptmp = zeros(2,1)
        ptmp[Z[t]+1] = 1     # compute backward influence
        if (t>1)
            p[:,t-1] = p[:,t-1].*(M'*ptmp)
            p[:,t-1]=p[:,t-1]/sum(p[:,t-1])
        end
    end
    return (Z,N0,NE)
end

function find_ge(value,A::Array)
    ret_val = zeros(A)
    index = 1
    for i in A
        if i >= value
            ret_val[index] = 1
        end
        index = index + 1
    end
    return ret_val
end

# return value : 

function draw_M_Z(Z,priors)
    # GIVEN Z, SAMPLE M
    n01 = length(find(andit(find_custom(0,Z[1:end-1]),find_custom(1,Z[2:end]))))
    n0 = length(find(find_custom(0,Z[1:end-1])))
    n10 = length(find(andit(find_custom(1,Z[1:end-1]),find_custom(0,Z[2:end]))))
    n1 = length(find(find_custom(1,Z[1:end-1])))
    z0 = rand(Beta(n01+priors.z01,n0-n01+priors.z00))
    z1 = rand(Beta(n10+priors.z10,n1-n10+priors.z11))
    M = [1-z0 z1; z0 1-z1]
    return M
end

function find_custom(value,A::Array)
    ret_val = zeros(A)
    index = 1
    for i in A
        if i == value
            ret_val[index] = 1
        end
        index = index + 1
    end
    return ret_val
end

# and not working between two arrays
function andit(A::Array,B::Array)
    ret_val = zeros(A)
    for i = 1:length(A)
        if(A[i] == 1 || B[i] == 1)
            ret_val[i] = 1
        else
            ret_val[i] = 0
        end
    end
    return ret_val
end

# return value :

function draw_L_N0(N0,priors,EQUIV)
    Nd=7
    Nh=size(N0,1)
    # 1st: OVERALL AVERAGE RATE
    if (priors.MODE != 0)
        L0 = (sum(N0)+priors.aL)/(length(N0)+priors.bL)
    else
        L0 = rand(Gamma((sum(N0))+priors.aL,1/(length(N0)+priors.bL)))
    end
    L = zeros(size(N0)[1],size(N0)[2]).+L0
    # 2nd: DAY EFFECT
    D = zeros(1,Nd)
    for i=1:length(D)
        alpha = sum(N0[:,i:7:end])+priors.aD[i]
        if (priors.MODE != 0) 
            D[i] = (alpha-1)           # mode of Gamma(a,1) distribution
        else
            D[i] = rand(Gamma(alpha,1))
        end
    end 
    # 3rd: TIME OF DAY EFFECT
    A = zeros(Nh,Nd)
    for tau=1:size(A,2)
        for i=1:size(A,1),
            alpha = (sum(N0[i,tau:7:end]))+priors.aH[i]
            if (priors.MODE != 0)
                A[i,tau] = (alpha-1)          # mode of Gamma(a,1) distribution
            else
                A[i,tau] = rand(Gamma(alpha,1))
            end
        end
    end
    # ENFORCE PARAMETER SHARING
    @match EQUIV[1] begin # d(t)
        1 => D[1:7] = 1
        2 => D[[1,7]],D[2:6],D = mean(D[[1,7]]),mean(D[2:6]),D/mean(D)
        3 => D = D/mean(D)
    end
    @match EQUIV[2] begin # tau(t)
        1 => A[:,1:7] = repmat(mean(A,2),[1,size(A,2)])
        2 => A[:,[1,7]],A[:,2:6] = repmat(mean(A[:,[1,7]],2),[1,2]),repmat(mean(A[:,2:6],2),[1,5])
        3 => A=A
    end
    for tau=1:size(A,2)
        A[:,tau]=A[:,tau]/mean(A[:,tau])
    end
    # & COMPUTE L(t)
    for d=1:size(L,2)
        for t=1:size(L,1)
            dd=mod(d-1,7)+1
            L[t,d] = L0 * D[dd] * A[t,dd]
        end
    end
    return L
end

# --------------------
# End Drawing Functions
# --------------------
# Start Plotting Functions
# --------------------

# function plotMMPP(L,Z,N,TRUTH,FIG::Integer = 1,RANGE::Integer = -1)
# # plotMMPP(Rate,PEvent,Data,Events,Fig,Range)
# # plot data and parameters of the Markov modulated Poisson process
# #   Rate   = estimated rate function; 
# #   PEvent = estimated probability of event;
# #   Data   = observed data; 
# #   Events = known event times;
# #   Fig    = figure handle / number to use
# #   Range  = sub-range of the data to plot (default is full length)
# #
# # Copyright (C) 2006 Alexander Ihler; distributable under GPL -- see README.txt

#     if (RANGE != -1)
#         RANGE = 1:length(Z)
#     end
#     figure(FIG)
#     subplot(3,1,3,"replace") # ND
#     holdon()
#     S=stem(RANGE,Z[RANGE],"m")
#     set(S,"MarkerSize",0,"LineWidth",2) # ND
#     xlabel("Time") 
#     ylabel("P(event)")
#     if (~isempty(TRUTH))
#         holdon()
#         S=stem(RANGE,-.25*TRUTH[RANGE],"b")
#         set(S,"MarkerSize",0,"LineWidth",1) # ND
#     end
#     figure(FIG)
#     subplot(3,1,1:2,"replace") # ND
#     holdon()
#     H=plot(RANGE,N[RANGE],"b")
#     H=plot(RANGE,L[RANGE],"r")  
#     ylabel("Counts")
#     legend("Observed","Profile") # ND
# end

# function holdon()
#     if(hold() == false)
#         hold()
#     end
# end

# --------------------
# End Plotting Functions
# --------------------
# Start Function Calls
# --------------------

# delete all of this if you want only function definitions

time_postcomp = time()
# println("dirpdf = $(dirpdf([1,.3,.2,.1],.5))")
# make sure we are in the correct directory otherwise we won't be able to find
# data.mat
vars = matread("data.mat")
time_postdata = time()
# can look at Nin through vars["Nin"], vars is a dictionary containing all info in
# the file data.mat
event = vars["event_times"]
Ni = vars["Nin"]
No = vars["Nout"]
pri = prior(1,1,zeros(1,7)+5,zeros(48,7)+1,9900,100,2500,7500,5,1/3,0)
time_postparse = time()
results = sensorMCMC(Ni,pri,event)
time_posttest = time()

println("\n ------------------ \n Result = logpc = $(results.logpC) ; logpgd = $(results.logpGD) \n ------------------ \n")

# println("Results - ")
# println("Compilation Time : $time_precomp - $time_postcomp = $(-(time_precomp) + (time_postcomp))")
# println("Data Read Time   : $time_postcomp - $time_postdata = $(-(time_postcomp) + (time_postdata))")
# println("Parsing Time     : $time_postdata - $time_postparse = $(-(time_postdata) + (time_postparse))")
# println("Execution Time   : $time_postparse - $time_posttest = $(-(time_postparse) + (time_posttest))")