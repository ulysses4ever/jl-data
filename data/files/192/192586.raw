module EMGMM

using Distributions
import Base.copy

export predict, emgmm, kmeans, GMM

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
  @printf io "Gaussian Mixture Model:\n"
  @printf io " * Type: %s\n" model.modeltype
  println(io, " * Prior probabilities: ", model.priors)
  println(io, " * Means: ", model.means)
  println(io, " * Covariances: ")
  for j=1:size(model.covariances,1)
    println(io, model.covariances[j,:,:])
  end
end

# hard assignment
function predict(X::Matrix, model::GMM)
  result = predict_proba(X,model)
  return result  # TODO: threshold and return hard assignment
end

# soft assignment
function predict_proba(X::Matrix, model::GMM)
  if model.covariancetype == "none" # kmeans, had assignment
  else # 
  end
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
               accuracy::Float64 = 1e-5)
  n = size(X,1) # num data pts
  d = size(X,2) # data dimension

  bestcompactness = typemax(Float64)
  bestmeans = zeros(Float64,(k,d))

  # main loop
  for repeat=1:repeats
    println("----------------")
    println("kmeans repeat: ",repeat)
    # initialize means using furthest-means:
    means = furthestmeans(X,k)
    count = zeros(Float64, k)
    compactness = typemax(Float64)
    lastmeans = copy(means)
    lastcompactness = copy(compactness)
    # iterate until max iters or compactness stops changing:
    for iter=1:maxiters
      lastmeans = copy(means)
      lastcompactness = copy(compactness)
      means = zeros(Float64, (k,d))
      count = zeros(Float64, k)
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
        compactness += mindist
      end
      println("iter: ", iter, " compactness: ", compactness)
      if abs(compactness-lastcompactness) < accuracy
        println("kmeans converged in ", iter, " iters")
        break
      end
      for j=1:k
        means[j,:] /= count[j]
      end
    end
    if compactness < bestcompactness
      bestcompactness = compactness
      bestmeans = copy(lastmeans)
    end
  end
  return bestmeans
end
 
# compute parameters of GMM using EM
function emgmm(X::Matrix,
               k::Integer,
               modeltype::String = "full",
               maxiters::Integer = 300,
               repeats::Integer = 6,
               accuracy::Float64 = 1e-5)
  n = size(X,1) # num data pts
  d = size(X,2) # data dimension
  priors = zeros(Float64,k)
  means = zeros(Float64,(k,d))
  covariance = zeros(Float64,(k,d,d))
  
  bestmodel = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
  bestloglike = typemin(Float64)
  model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
  loglike = 0

  # main loop
  for repeat=1:repeats
    println("=================")
    println("emgmm repeat: ",repeat)

    # initialize with kmeans and uniform prior:
    model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), ((1/k)*ones(Float64,k)),modeltype)
    model.means = kmeans(X,k,maxiters,1,accuracy)
    for j=1:k
      model.covariances[j,:,:] = reshape(eye(d,d),(1,d,d))
    end
    if modeltype == "none" # == kmeans
      return bestmodel
    end
    
    weights = zeros(Float64, (n,k))
    loglike = 0
    lastmodel = copy(model)
    lastloglike = copy(loglike)
    # iterate until max iters or loglike stops changing:
    for iter=1:maxiters
      lastmodel = copy(model)
      lastloglike = copy(loglike)
      model = GMM(zeros(Float64,(k,d)), zeros(Float64,(k,d,d)), zeros(Float64,k),modeltype)
      weights = zeros(Float64, (n,k))
      counts = zeros(Float64, (k,))
      loglike = 0
      for i=1:n
        for j=1:k
          NDist = MvNormal(reshape(lastmodel.means[j,:],(d,)),reshape(lastmodel.covariances[j,:,:],(d,d)))
          weights[i,j] = pdf(NDist,reshape(X[i,:],(d,)))*lastmodel.priors[j]
          #loglike += log(weights[i,j])
          loglike += logpdf(NDist,reshape(X[i,:],(d,))) + log(lastmodel.priors[j])
        end
        #weights /= sum(weights[i,:]) # x/y = exp(log(x)-log(y))
        denom = log(sum(weights[i,:]))
        for j=1:k
          weights[i,j] = exp(log(weights[i,j]) - denom)
        end
        # compute the next mean while we're at it.
        for j=1:k
          model.means[j,:] += X[i,:] * weights[i,j]
          counts[j] += weights[i,j]
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
          model.covariances[j,:,:] += reshape(dif' * dif * weights[i,j], (1,d,d))
        end
      end
      for j=1:k
        model.covariances[j,:,:] /= counts[j]
      end
    end
    if loglike > bestloglike
      bestloglike = loglike
      bestmodel = copy(lastmodel)
    end
  end
  
  return bestmodel
end

end # module
