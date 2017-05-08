module EMGMM

using Distributions
import Base.copy

export predict,predict_proba,learn, emgmm,kmeans,GMM

type GMM
  means::Array{Float64}
  covariances::Array{Float64}
  priors::Array{Float64}# prior probs of each distribution.
  modeltype::String # full, diag, uniform_diag, none (kmeans)
end
function copy(A::GMM)
  c = GMM(A.means,A.covariances,A.priors,A.modeltype)
  c
end

function Base.show(io::IO, model::GMM)
  println(io, "Gaussian Mixture Model:")
  println(io, " * Type: ", model.modeltype)
  println(io, " * Prior probabilities: ", model.priors)
  println(io, " * Means: ", model.means)
  println(io, " * Covariances: ")
  for j=1:size(model.covariances,1)
    println(io, model.covariances[j,:,:])
  end
end

# learn a gmm
function learn(X::Matrix,k,modeltype="full")
  (model,_tmp) = emgmm(X,k,modeltype)
  model
end

# hard assignment
function predict(X::Matrix, model::GMM)
  membership = predict_proba(X,model)
  k = size(membership,2)
  if k > 1
    n = size(membership,1)
    result = zeros(Float64, (n,))
    for i=1:n
      maxj = 0.
      maxv = 0.
      for j=1:k
        if membership[i,j] > maxv
          maxv = membership[i,j]
          maxj = j
        end
        result[i] = maxj
      end
    end
  else
    result = membership # already membership index
  end
  result  
end

# soft assignment
function predict_proba(X::Matrix, model::GMM)
  local membership
  if model.covariancetype == "none" # kmeans, hard assignment
    (_means,membership,_compactness) = kmeans(X,size(model.priors),1,1,typemax(Float64),model.means)
  else # 
    (_model,membership,_loglike) = emgmm(X,size(model.priors),model.modeltype,1,1,typemax(Float64),model)
  end
  membership
end


# find initial means that are furthest from each other:
function furthestmeans(X::Matrix, k::Integer)
  n = size(X,1) # num data pts
  d = size(X,2) # data dimension
  means = zeros(Float64, (k,d))

  # start with a random data point
  randi = ceil(rand()*n)
  means[1,:] = X[randi,:] 

  for iter=2:k
    maxdist = 0
    maxdisti = 0 
    for i=1:n
      mindist = typemax(Float64)
      for j=1:iter-1
        mindist = min(mindist, norm(X[i,:]-means[j,:])) # find which cluster this datum belongs to
      end
      # keep track of the furthest point from all clusters
      if mindist > maxdist
        maxdisti = i
        maxdist = mindist 
      end
    end
    means[iter,:] = X[maxdisti,:]
  end

  return means
end
 
# compute centroids using kmeans
function kmeans(X::Matrix,
               k::Integer,
               maxiters::Integer = 300,
               repeats::Integer = 6,
               accuracy::Float64 = 1e-5,
               initialmeans = None)
  n = size(X,1) # num data pts
  d = size(X,2) # data dimension
  println("maxiters: ",maxiters," repeats: ",repeats)

  bestcompactness = typemax(Float64)
  bestmeans = zeros(Float64,(k,d))
  bestmembership = zeros(Float64,(n,))

  if initialmeans == None
    # no point to multiple runs
    maxiters = 1
  end

  # main loop
  for repeat=1:repeats
    println("----------------")
    println("kmeans repeat: ",repeat)
    # initialize means using furthest-means:
    if initialmeans == None
      means = furthestmeans(X,k)
    else
      means = copy(initialmeans)
    end
    count = zeros(Float64, k)
    compactness = typemax(Float64)
    lastmeans = copy(means)
    lastcompactness = copy(compactness)
    # iterate until max iters or compactness stops changing:
    for iter=1:maxiters
      println("km iter: ",iter)
      lastmeans = copy(means)
      lastcompactness = copy(compactness)
      means = zeros(Float64, (k,d))
      count = zeros(Float64, k)
      membership = zeros(Float64, (n,))
      compactness = 0
      for i=1:n
        mindist = typemax(Float64)
        mindisti = 0
        for j=1:k
          dist = norm(X[i,:]-lastmeans[j,:])
          if dist < mindist
            mindisti = j
            mindist = dist
          end
        end
        means[mindisti,:] += X[i,:]
        count[mindisti] += 1
        membership[i] = mindisti
        compactness += mindist
      end
      println("iter: ", iter, " compactness: ", compactness)
      println("lastc: ",lastcompactness)
      println("acc: ", accuracy)
      if abs(compactness-lastcompactness) < accuracy
        println("kmeans converged in ", iter, " iters")
        break
      end
      for j=1:k
        means[j,:] /= count[j]
      end
    end
    if compactness < bestcompactness || maxiters == 1
      bestcompactness = compactness
      bestmeans = copy(lastmeans)
      bestmembership = copy(bestmembership)
    end
  end
  return bestmeans,bestmembership,bestcompactness
end
 
# compute parameters of GMM using EM
function emgmm(X::Matrix,
               k::Integer,
               modeltype::String = "full",
               maxiters::Integer = 300,
               repeats::Integer = 6,
               accuracy::Float64 = 1e-5,
               initialmodel = None)
  n = size(X,1) # num data pts
  d = size(X,2) # data dimension
  priors = zeros(Float64,k)
  means = zeros(Float64,(k,d))
  covariance = zeros(Float64,(k,d,d))
  
  bestmodel = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
  bestloglike = typemin(Float64)
  bestmembership = zeros(Float64,(n,k))
  model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
  loglike = 0
  membership = zeros(Float64,(n,k))

  if initialmodel == None
    # no point to multiple runs
    repeats = 1
  end

  # main loop
  for repeat=1:repeats
    println("=================")
    println("emgmm repeat: ",repeat)

    # initialize with kmeans and uniform prior:
    model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), ((1/k)*ones(Float64,k)),modeltype)
    if initialmodel == None
      (model.means,_tmp1,_tmp2) = kmeans(X,k,maxiters,1,accuracy)
    else
      model = copy(initialmodel)
    end
    for j=1:k
      model.covariances[j,:,:] = reshape(eye(d,d),(1,d,d))
    end
    if modeltype == "none" # == kmeans
      return bestmodel
    end
    
    lastmodel = copy(model) # so var is in scope below..
    lastmembership = copy(membership)
    lastloglike = loglike
    # iterate until max iters or loglike stops changing:
    for iter=1:maxiters
      lastmodel = copy(model)
      lastloglike = copy(loglike)
      model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
      membership = zeros(Float64, (n,k))
      counts = zeros(Float64, (k,))
      loglike = 0
      for i=1:n
        for j=1:k
          NDist = MvNormal(reshape(lastmodel.means[j,:],(d,)),reshape(lastmodel.covariances[j,:,:],(d,d)))
          membership[i,j] = pdf(NDist,reshape(X[i,:],(d,)))*lastmodel.priors[j]
          #loglike += log(membership[i,j])
          loglike += logpdf(NDist,reshape(X[i,:],(d,))) + log(lastmodel.priors[j])
        end
        #membership /= sum(membership[i,:]) # x/y = exp(log(x)-log(y))
        denom = log(sum(membership[i,:]))
        for j=1:k
          membership[i,j] = exp(log(membership[i,j]) - denom)
        end
        # compute the next mean while we're at it.
        for j=1:k
          model.means[j,:] += X[i,:] * membership[i,j]
          counts[j] += membership[i,j]
        end
      end
      println("iter: ", iter, ", log like: ", loglike)
      if abs(loglike-lastloglike) < accuracy
        println("emgmm converged in ", iter, " iters")
        break
      end
      for j=1:k
        model.means[j,:] /= counts[j]
        model.priors[j] = counts[j]/n
      end
      for i=1:n
        for j=1:k
          dif = X[i,:] - model.means[j,:]
          model.covariances[j,:,:] += reshape(dif' * dif * membership[i,j], (1,d,d))
        end
      end
      for j=1:k
        model.covariances[j,:,:] /= counts[j]
      end
    end
    if loglike > bestloglike || maxiters == 1
      bestloglike = loglike
      bestmodel = copy(lastmodel)
      bestmembership = copy(lastmembership)
    end
  end
  
  return bestmodel,bestmembership,bestloglike
end

# compute parameters of GMM using iterative EM
# See paper by Neal,Hinton in 1999 on EM.
function emgmm_iterative(X::Matrix,
                         k::Integer,
                         modeltype::String = "full",
                         maxiters::Integer = 300,
                         repeats::Integer = 6,
                         accuracy::Float64 = 1e-5,
                         initialmodel = None)
  n = size(X,1) # num data pts
  d = size(X,2) # data dimension
  priors = zeros(Float64,k)
  means = zeros(Float64,(k,d))
  covariance = zeros(Float64,(k,d,d))
  
  bestmodel = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
  bestloglike = typemin(Float64)
  bestmembership = zeros(Float64,(n,k))
  model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
  loglike = 0
  membership = zeros(Float64,(n,k))

  if initialmodel == None
    # no point to multiple runs
    repeats = 1
  end

  # main loop
  for repeat=1:repeats
    println("=================")
    println("emgmm repeat: ",repeat)

    # initialize with kmeans and uniform prior:
    model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), ((1/k)*ones(Float64,k)),modeltype)
    local _tmp1
    local _tmp2
    if initialmodel == None
      (model.means,_tmp1,_tmp2) = kmeans(X,k,maxiters,1,accuracy)
    else
      model = copy(initialmodel)
    end
    for j=1:k
      model.covariances[j,:,:] = reshape(eye(d,d),(1,d,d))
    end
    if modeltype == "none" # => kmeans
      return model,_tmp1,1/_tmp2
    end

    # run normal EM once to get initial state.
    model,membership,loglike = emgmm(X,k,modeltype,1,1,accuracy,initialmodel)

    # setup the sufficent statistics
    sufstat_mem = zeros(Float64, (k,))
    sufstat_mean = zeros(Float64, (k,d))
    sufstat_cov = zeros(Float64, (k,d,d))
    for i=1:n
      for j=1:k
        sufstat_mem[j] += membership[i,j]
        sufstat_mean[j,:] += membership[i,j]*X[i,:]
        sufstat_cov[j,:,:] = reshape(sufstat_cov[j,:,:], (a,a)) + membership[i,j]*(X[i,:]'*X[i,:])
      end
    end
    
    lastmodel = copy(model) # so var is in scope below..
    lastmembership = copy(membership)
    lastloglike = loglike
    # iterate until max iters or loglike stops changing:
    for iter=1:maxiters
      lastmodel = copy(model)
      lastloglike = copy(loglike)
      #model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
      #membership = zeros(Float64, (n,k))
      #counts = zeros(Float64, (k,))
      loglike = 0
      roundsize = 10
      for i=1:n
        memb = zeros(Float64, (k,))
        for j=1:k
          NDist = MvNormal(reshape(lastmodel.means[j,:],(d,)),reshape(lastmodel.covariances[j,:,:],(d,d)))
          memb[j] = pdf(NDist,reshape(X[i,:],(d,)))*lastmodel.priors[j]
          #loglike += log(membership[i,j])
          loglike += logpdf(NDist,reshape(X[i,:],(d,))) + log(lastmodel.priors[j])
        end
        #membership /= sum(membership[i,:]) # x/y = exp(log(x)-log(y))
        denom = log(sum(memb))
        for j=1:k
          memb[j] = exp(log(memb[j]) - denom)
        end
        # update sufficient stats:
        for j=1:k
          sufstat_mem[j] -= membership[i,j]
          sufstat_mean[j,:] -= membership[i,j]*X[i,:]
          sufstat_cov[j,:,:] = reshape(sufstat_cov[j,:,:], (a,a)) - membership[i,j]*(X[i,:]'*X[i,:])
          membership[i,:] = memb
          sufstat_mem[j] += membership[i,j]
          sufstat_mean[j,:] += membership[i,j]*X[i,:]
          sufstat_cov[j,:,:] = reshape(sufstat_cov[j,:,:], (a,a)) + membership[i,j]*(X[i,:]'*X[i,:])
        end
        if i > 1 && (i-1)%roundsize == 0
          # update the model parameters
          for j=1:k
            model.priors[j] = sufstat_mem[j]/sum(sufstat_mem)
            model.means[j,:] = sufstat_mean[j]/sufstat_mem[j]
            model.covariances[j,:,:] = (sufstat_cov[j]/sufstat_mem[j]) - model.means[j,:]'*model.means[j,:]
          end
        end
      end
      if n/roundsize != floor(n/roundsize)
        # if our mod operator doesn't get all the points, recompute model again here:
        for j=1:k
          model.priors[j] = sufstat_mem[j]/sum(sufstat_mem)
          model.means[j,:] = sufstat_mean[j]/sufstat_mem[j]
          model.covariances[j,:,:] = (sufstat_cov[j]/sufstat_mem[j]) - model.means[j,:]'*model.means[j,:]
        end
      end
      println("iter: ", iter, ", log like: ", loglike)
      if abs(loglike-lastloglike) < accuracy
        println("emgmm converged in ", iter, " iters")
        break
      end
    end
    if loglike > bestloglike || maxiters == 1
      bestloglike = loglike
      bestmodel = copy(lastmodel)
      bestmembership = copy(lastmembership)
    end
  end
  return bestmodel,bestmembership,bestloglike
end


end # module
