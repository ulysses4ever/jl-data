using NLopt
using Roots
#########################################
#computes predicted probabilities for multinomial regression, given X, beta, and number of categories
function multProb(X,beta,k)
  p=size(X)[2]
  n=size(X)[1]
  beta=reshape(beta,p,k)
  denominator=zeros(n)
  numerator=exp(X*beta)
  denominator=sum(numerator,2)
  prob=numerator./denominator
  beta=vec(beta)
  return(prob)
end

##################################
#computes predicted probabilities for multinomial regression, given X*beta
function multProbPrecompute(Xbeta)
  numerator=exp(Xbeta)
  denominator=sum(numerator,2)
  prob=numerator./denominator
  return(prob)
end

####################################
#computes gradient for multinomial regression
function multinomialGradient(X,beta,z)
  k=size(z)[2]
  grad=X'*(z-multProb(X,beta,k))
  grad=vec(grad)
  return(grad)
end

######################################
#computes multinomial log likelihood given X, beta, z
function loglikelihood(X,beta,z)
  p=size(X)[2]
  k=size(z)[2]
  beta=reshape(beta,p,k)
  probs=multProb(X,beta,k)
  val=0
  for i = 1:(size(X)[1])
    val=val+log(probs[i,find(z[i,:].==1)])
  end
  beta=vec(beta)
  return(val)
end

#######################################
#computes loglikelihood, given a precomputed X*beta and z
function loglikelihoodPrecompute(Xbeta,z)
  probs=multProbPrecompute(Xbeta)
  val=0
  for i = 1:(size(Xbeta)[1])
    val=val+log(probs[i,find(z[i,:].==1)])
  end
  return(val)
end

########################################
#not really used, does multinomial regression starting at beta, given model matrix X, response matrix z
function multinomialOptim(X,beta,z)
  function loglikeClosure(beta)
    return loglikelihood(X,beta,z)[1]
  end
  function gradientClosure(beta)
    return(multinomialGradient(X,beta,z))
  end
  opt = NLopt.Opt(:LD_LBFGS, length(beta))
  function f(beta,grad)
    grad[:]=-gradientClosure(beta)
    val=-loglikeClosure(beta)
    return(val)
  end
  NLopt.min_objective!(opt, f)
  (optf,optx,ret) = NLopt.optimize(opt,vec(beta))
  k=size(z)[2]
  p=size(X)[2]
  beta=reshape(optx,p,k)
  return(beta)
end

#######################################
#compute hessian for symmetric multinomial regression parameterization
function multinomialHessian(X,Xbeta)
  k=size(Xbeta)[2]
  p=size(X)[2]
  n=size(Xbeta)[1]

  mu=multProbPrecompute(Xbeta)
  hess=zeros(p*k,p*k)
  for i = 1:k
    start1=(i-1)*p+1
    end1=i*p

    for j = i:k
      start2=(j-1)*p+1
      end2=j*p
      temp=zeros(p)
      if i==j
        w1=mu[:,i]-mu[:,i].^2
        temp=X'*(scale(-w1,X))
      else
        w1=-mu[:,j].*mu[:,i]
        temp=X'*(scale(-w1,X))
      end
      hess[start1:end1,start2:end2]=temp
      hess[start2:end2,start1:end1]=temp
    end
  end
  return(hess)
end

#########################################
#main function, solve multinomial group lasso problem over a sequence of lambda using block coordinate descent
function multinomialBCD(X,z,groups,penaltyFactor)
  #convergence tolerance
  tol=10.0^-8
  #compute starting point for lambda
  #get number of groups
  categories=unique(groups)
  g=length(categories)
  k=size(z)[2]
  p=size(X)[2]
  n=size(z)[1]
  #get number of coefficients in each group
  groupLengths=zeros(g)
  for i = 1:g
    groupLengths[i]=sum(groups.==categories[i])
  end
#
#   #starting beta, get intercept term since this is unpenalized
  beta=zeros(p,k)
  factoredResponse=zeros(n)
  for i = 1:n
    factoredResponse[i]=find(z[i,:].==1)[1]
  end
#
#initialize Xbeta, update without doing full multiplications
  Xbeta=zeros(n,k)
#initialize penalty, rather than computing all the time
  groupPenalty=zeros(1)

#needed for gradient, can avoid computation
  z_mu=zeros(n,k)

#initialize gradient
  fullGradient=zeros(p*k)
  #get intercept
  intercept=reshape(ones(n),n,1)
  beta[1,:]=multinomialOptim(intercept,beta[1,:],z)
  beta[1,:]=beta[1,:]-mean(beta[1,:])
  Xbeta=Xbeta+intercept*beta[1,:]

  #update z_mu
  z_mu=z-multProbPrecompute(Xbeta)

  #majorized hessian
  fullHess=kron(1/2*eye(k),X'*X)/n

  #get eigenvalues for step from zero
  eigList=getEigs(X,categories,groups)
  invList=getInvs(X,categories,groups,k,n)
  #update gradient
  fullGradient=X'*z_mu
  #get first lambda and lambda sequence
  norms=zeros(sum(penaltyFactor.>0))
  count=0
  for i = 1:g
    if (penaltyFactor[i]>0)
      count=count+1
      cat=categories[i]
      inds=(groups.==cat)
      gradient=fullGradient[inds,:]/n
      norms[count]=(sum(gradient.^2)^0.5)
    end
  end
  lambdas=norms./((groupLengths[penaltyFactor.>0]*k).^0.5)
  lambdaStart=maximum(lambdas)
  num=100
  lambdaVec=lambdaStart*(collect(num:-1:(num-95))/num)
  #lambdaVec=userLambda
  betaList=zeros(p,k,length(lambdaVec))
  #the first set of coefficients only has the intercept
  betaList[:,:,1]=beta

  count=1
  if (length(lambdaVec)==1)
    return(betaList)
  end
  #lambdaVec=lambdaVec[1:30]

  #initialize active set
  activeCats=zeros(length(categories)).>1
  activeInds=zeros(size(X)[2]).>1

  for lambda = lambdaVec[2:length(lambdaVec)]
    count=count+1
    diff=tol+1

    #objective at start
    #adjust the group penalty for the new lambda
    groupPenalty=groupPenalty*lambda/lambdaVec[round(Int,(find(lambdaVec.==lambda))-1)][1]
    objEnd=0

#####related to active set
    #get active set
    lambda1=lambda
    lambda0=lambdaVec[round(Int,(find(lambdaVec.==lambda))-1)][1]
    activeCats=zeros(length(categories)).>1
    activeInds=zeros(size(X)[2]).>1
    getActiveCategories!(activeCats,activeInds,beta,Xbeta,categories,groups,X,z_mu,lambda,lambda0)

    #while kkt condition not satisfied
    converged=false
    while !converged
      while (diff>tol)
        betaStart=copy(beta)
        #update beta based on penalized quadratic approximation
        #modifies Xbeta, z_mu, and groupPenalty
        indsRep=repmat(activeInds,k)
        changedFlag=false
        beta[activeInds,:]=coordDescentQuadratic!(beta[activeInds,:],Xbeta,z_mu,groupPenalty,X[:,activeInds],z,groups[activeInds],categories[activeCats],lambda,penaltyFactor[activeCats],fullHess[indsRep,indsRep],eigList[activeCats],invList[activeCats])
        diff=maximum(diag(fullHess).*(vec(beta-betaStart).^2))
        #println(diff)
      end
      #objective=-loglikelihoodPrecompute(Xbeta,z)/n+groupPenalty
      #println(objective)
      #check kkt conditions
      converged=checkKKT(activeCats,activeInds,X,z_mu,groups,categories,lambda)
    end
    betaList[:,:,count]=beta
  end
  print(lambdaVec)
  return(betaList)
end

####################################
#optimize penalized quadratic group lasso problem
function coordDescentQuadratic!(beta,Xbeta,z_mu,groupPenalty,X,z,groups,categories,lambda,penaltyFactor,H,eigList,invList)
  tolMiddle=10.0^-8
  diffMiddle=tolMiddle+1
  quadraticObj=0
  totalObj=groupPenalty
  k=size(z_mu)[2]
  n=size(X)[1]
  fullGradient=-X'*z_mu/n
  betaDiffMiddle=zeros(size(beta))
  betaDiffTotal=zeros(size(beta))
  beta0=copy(beta)
  beta0_1=copy(beta)


  #H=-multinomialHessian(X,Xbeta)/n
  currentGrad=copy(fullGradient)
  #keep track of nonzero indices of beta, only use these for X*beta
  nonZeroInds=zeros(size(X)[2]).>1
  innerCount=1
  while diffMiddle>tolMiddle
    totalObj0=totalObj
    beta0_1[:]=copy(beta)
    nonZeroCats=zeros(length(categories))
    for i = 1:length(categories)
      cat=categories[i]

      inds=(groups.==cat)

      #starter quantities
      inds2=repmat(inds,k)
      #gradient=vec(fullGradient)[inds2]+H[inds2,:]*vec(betaDiffTotal)-H[inds2,inds2]*vec(beta)[inds2]
      gradient=vec(currentGrad[inds,:])-H[inds2,inds2]*vec(beta[inds,:])
      innerCount=innerCount+1
      hess=H[inds2,inds2]
      norm=sum(gradient.^2)^0.5

      #optimize group
      #get group related quantities so each group and penalty
      #can be updated one at a time
      penaltyStart=penalty(beta[inds,:],lambda*penaltyFactor[i])
      penaltyEnd=0
      betaStart=beta[inds,:]
      if norm>lambda*penaltyFactor[i]*sqrt(length(betaStart))
        nonZeroCats[i]=1
        #beta[inds,:]=innerOptimize(betaStart,lambda*penaltyFactor[i]*sqrt(length(betaStart)),gradient,hess,eigList[i])
        #beta[inds,:]=innerCyclicMM(betaStart,lambda*penaltyFactor[i]*sqrt(length(betaStart)),gradient,hess,eigList[i])
        #beta[inds,:]=innerFullMM(betaStart,lambda*penaltyFactor[i]*sqrt(length(betaStart)),gradient,hess,eigList[i],invList[i],k)
        beta[inds,:]=innerSoftThresholdMM(betaStart,lambda*penaltyFactor[i]*sqrt(length(betaStart)),gradient,hess,eigList[i])
        betaDiffMiddle[inds,:]=beta[inds,:]-beta0_1[inds,:]
        penaltyEnd=penalty(beta[inds,:],lambda*penaltyFactor[i])
        nonZeroInds[inds]=true
      end
      startEndZero=false
      if norm<=lambda*penaltyFactor[i]*sqrt(length(betaStart))
        if (all(beta[inds,:].==0))
          startEndZero=true
          betaDiffMiddle[inds,:]=0
        else
          beta[inds,:]=0
          nonZeroInds[inds]=false
          betaDiffMiddle[inds,:]=-beta0_1[inds,:]
          nonZeroCats[i]=0
        end
      end

      if (!startEndZero)
        currentGrad=currentGrad+reshape(H[:,inds2]*vec(betaDiffMiddle[inds,:]),size(currentGrad))
      end
      penaltyDiff=penaltyEnd-penaltyStart

      #update penalty
      groupPenalty[:]=groupPenalty+penaltyDiff
    end
    #@show sum(nonZeroCats)/length(categories)
    #@show sum(size(beta)[1])
    totalObj=quadraticObj+groupPenalty
    diffMiddle=maximum(diag(H).*(vec(betaDiffMiddle).^2))
  end
  Xbeta[:]=X[:,nonZeroInds]*beta[nonZeroInds,:]
  z_mu[:]=z-multProbPrecompute(Xbeta)
  return(beta)
end

##########################################
#group update function as implemented in another paper
function innerOptimize(betaK,lambda,gradient,hess,maxEig)
   tolInner=10.0^-8
   diffInner=tolInner+1
   if (all(betaK.==0))
     betaK=max(0,(1-lambda/(sum(gradient.^2)^0.5)))*(-1/maxEig*gradient)
   end

   while diffInner>tolInner
     startBetaK=copy(betaK)
     tempInds=zeros(length(betaK)).>1
     for i = 1:length(betaK)
       tempInds[i]=true
       #sum of other betas
       cons=sum(betaK[!tempInds].^2)
       grad=gradient[i]+hess[tempInds,!tempInds]*betaK[!tempInds]
       subHess=hess[tempInds,tempInds]

       grad=grad[1]
       rootSign=-abs(grad)/grad
       grad=-abs(grad)
       subHess=abs(subHess[1])
       cons=cons[1]
       function innerGradClosure(x)
         return grad+subHess*x+lambda*x/(sqrt(x^2+cons))
       end
       val=fzero(innerGradClosure,0,-grad/subHess)
       betaK[i]=rootSign*val
       tempInds[i]=false
     end
     endBetaK=betaK
     diffInner=maximum(abs(startBetaK-endBetaK))
   end
   return(betaK)
end

##########################################
#cyclic MM update within a group, using majorized loss
function innerCyclicMM(betaK,lambda,gradient,hess,maxEig)
  #avoid evaluation at zero
  if all(betaK.==0)
    betaK=max(0,(1-lambda/(sum(gradient.^2)^0.5)))*(-1/maxEig*gradient)
  end
  #vector of false's
  tempInds=zeros(length(betaK)).>1

  #precompute constant for penalty term
  consTot=sum(betaK.^2)
  for i = 1:length(betaK)
    tempInds[i]=true
    #sum of other beta
    grad=gradient[i]+hess[tempInds,!tempInds]*betaK[!tempInds]
    subHess=hess[tempInds,tempInds]
    grad=grad[1]
    subHess=subHess[1]
    val=betaK[i]
    val=val-(grad+subHess*val+lambda*val/sqrt(consTot))*(subHess+lambda*(consTot)^-0.5)^(-1)
    consTot=consTot-betaK[i]^2+val^2
    betaK[i]=val
    tempInds[i]=false
  end
  return(betaK)
end

##########################################
#MM whole-group update, using majorized penalty
function innerFullMM(betaK,lambda,gradient,hess,maxEig,eig_xx,k)
  #avoid evaluation at zero
  betaK=max(0,(1-lambda/(sum(gradient.^2)^0.5)))*(-1/maxEig*gradient)
  betaK=vec(betaK)
  consTot=sum(betaK.^2)
  gradTot=vec(gradient)+hess*betaK+lambda*vec(betaK)./consTot^0.5
  hessTot=hess+lambda*(1/consTot^0.5)*eye(size(hess)[1])
  test=kron(eye(k),eig_xx.vectors')'*inv(lambda/consTot^(0.5)*eye(size(hess)[1])+kron(1/2*eye(k),diagm(eig_xx.values)))*kron(eye(k),eig_xx.vectors')
  #betaK=betaK-hessTot\gradTot
  betaK=betaK-test*gradTot
  #@show maximum(abs(betaK betaK2))
  return(betaK)
end

############################################
#MM whole-group update using soft thresholding, using majorized loss
function innerSoftThresholdMM(betaK,lambda,gradient,hess,maxEig)
  if all(betaK.==0)
  end
  betaK=vec(betaK)
  betaR=-1/maxEig*(gradient+hess*betaK)+betaK
  betaK=max(0,(1-lambda/(maxEig*sum(betaR.^2)^0.5)))*(betaR)
  return(betaK)
end

#############################################
#helper function, computes l2 norm of a group and multiplies by lambda and sqrt(group length)
function penalty(beta,lambda)
  val=lambda*((length(beta))^0.5)*sum(beta.^2)^0.5
  return(val)
end

#############################################
#see which groups have a high chance of being non-zero, then we can do coordinate descent over these groups first
function getActiveCategories!(activeCats,activeInds,beta,Xbeta,categories,groups,X,z_mu,lambda1,lambda0)
  g=length(groups)
  fullGradient=-X'*z_mu/size(X)[1]
  for i=1:length(categories)
     cat=categories[i]
     inds=(groups.==cat)
     gradient=fullGradient[inds,:]
     norm=sum(gradient.^2)^0.5

     #for strong rule
     lambdaDiff=(2*lambda1-lambda0)*penaltyFactor[i]
     if (norm>(length(gradient))^(0.5)*lambdaDiff) | (penaltyFactor[i]==0)
       activeCats[i]=true
       activeInds[inds]=true
     else
       activeCats[i]=false
       activeInds[inds]=false
       if sum(beta[inds,:].!=0)>0
         Xbeta[:]=Xbeta-X[:,inds]*beta[inds,:]
         beta[inds,:]=0
       end
     end
   end
   z_mu[:]=z-multProbPrecompute(Xbeta)
end

######################################
#cycle through all inactive groups to see if any should be included in the model
function checkKKT(activeCats,activeInds,X,z_mu,groups,categories,lambda)
  fullGradient=-X'*z_mu/size(X)[1]
  converged=true
  for i = 1:length(categories)
    if (!activeCats[i])
      cat=categories[i]
      inds=(groups.==cat)
      gradient=fullGradient[inds,:]
      norm=sum(gradient.^2)^0.5
      if norm>length(gradient)^0.5*penaltyFactor[i]*lambda
        converged=false
        activeCats[i]=true
        activeInds[inds]=true
      end
    end
  end
  return(converged)
end


#################################
#get maximum eigenvalue of the hessian for each group for majorization step
function getEigs(X,categories,groups)
  eigs=zeros(length(categories))
  for i=1:length(categories)
    cat=categories[i]
    inds=(groups.==cat)
    eigs[i]=0.5*maximum(eigvals(X[:,inds]'*X[:,inds]))/size(X)[1]
  end
  return(eigs)
end

#################################
#precompute majorized hessian inverses
function getInvs(X,categories,groups,k,n)
  invList=Array(Any,0)
  for i=1:length(categories)
    cat=categories[i]
    inds=(groups.==cat)
    xx=X[:,inds]'*X[:,inds]/n
    push!(invList,eigfact(xx))
  end
  return(invList)
end
