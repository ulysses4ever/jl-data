using Distributions
include("bcd.jl")
using ProfileView
##################
#basically plumbing to generate a multinomial problem with the setup given below
#predictor matrix, p>n
num=200
n=100
X=zeros(n,num)
X[:]=rand(n*num)

#intercept
X[:,1]=1

#true beta values, first 10 rows are nonzero
#four different response categories
beta=zeros(num,4)
beta[1:10,:]=(rand(4*10)-1/2)*3
Xbeta=X*beta
probs=multProbPrecompute(Xbeta)

#simulate response
z=zeros(n,4)
for i=1:n
  t1=Multinomial(1,vec(probs[i,:]))
  z[i,:]=rand(t1,1)
end

#define grouping: columns with same group number/label are considered grouped
groups=zeros(num)
for i=1:(div(num,2)-1)
  groups[2*i+1]=i
  groups[2*i+2]=i
end

groups[1]=-1
groups[2]=0

#the intercept is unpenalized, every other group is penalized equally
penaltyFactor=ones(length(unique(groups)))
penaltyFactor[1]=0
#####################


@time multinomialBCD(X,z,groups,penaltyFactor);
