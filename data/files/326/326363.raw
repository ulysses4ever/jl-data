using Base.Test

dataArray = readdlm("/Users/eliotpbrenner/PycharmProjects/SparsityBoost/data/synthetic_examples/experiments/0/alarm1000.dat", ' ', Int);
size(dataArray)
# reproducing functionality of model::read_data
nodes=size(dataArray)[2]
nval=ones(Int, nodes)
typeof(dataArray)
typeof(nodes)
typeof(nval)

tol=1e-20
type model
  nodes::Int64
  nval::Array{Int64,1}
  dataArray::Array{Int64,2}
end

m=model(nodes,nval,dataArray)

type jointDistWithMarginals
  pdist::Array{Float32,2}
  p_A::Array{Float32,1}
  p_B::Array{Float32,1}
end

function joinDistWithMarginals(pdist::Array{Float32,2})
  sumA=sum(pDist,1)
  sumB=sum(pDist,2)
  jointDistWithMarginals(pdist, sumA, sumB)
end

function readData(aModel::model, filePath::String)
  aModel.dataArray = readdlm(filePath, ' ', Int);
  aModel.nodes=size(dataArray)[2]
  #TODO: correct the way the number of values is set
  aModel.nval=2*ones(Int, nodes)
end

function readData(filePath::String)
  dataArray = readdlm(filePath, ' ', Int);
  nodes=size(dataArray)[2];
  nval=2*ones(Int, nodes)
  theModel = model(nodes,nval,dataArray);
end

aModel = readData("/Users/eliotpbrenner/PycharmProjects/SparsityBoost/data/synthetic_examples/experiments/0/alarm1000.dat")
aModel.nval

function verify(aJointDistributionWithMarginals::jointDistWithMarginals)
  sumA=sum(aJointDistributionWithMarginals.pdist,1)
  sumB=sum(aJointDistributionWithMarginals.pdist,2)
  println(sumB);
  println(aJointDistributionWithMarginals.p_A)
  @test_approx_eq(transpose(sumA),aJointDistributionWithMarginals.p_A)
  @test_approx_eq(sumB,aJointDistributionWithMarginals.p_B)
  @test_approx_eq(sum(sumA),1.0)
  return true
end

@test 1 == 1
@test 1==0
goodDist=jointDistWithMarginals([[0.25 0.25], [ 0.25 0.25]], [0.5, 0.5], [0.5, 0.5])
goodDist=jointDistWithMarginals([[0.25 0.25], [ 0.25 0.25]])
@test verify(goodDist) == true
badDist = jointDistWithMarginals([[0.25 0.25], [ 0.25 0.25]], [0.6, 0.4], [0.5, 0.5])
@test_throws ErrorException verify(badDist)
goodDist.pdist[1,2]

function MI_term(i::Int, j::Int, dist::jointDistWithMarginals)
  return -dist.pdist[i,j]*log(dist.pdist[i,j]/(dist.p_A[i]*dist.p_B[j])  )
end

function MI(dist::jointDistWithMarginals)
  (a,b)=size(dist.pdist)
  return sum([(MI_term(i,j,dist)) for i=1:a, j=1:b])
end

MI_term(1,1,goodDist)
@test_approx_eq(MI(goodDist),0)


verify(badDist)

goodDist.pdist
sum(goodDist.pdist, 1)
goodDist.p_A

function conditionalDist(m::model,i::Int,j::Int,SToVal::Dict)
  """
  TODO: that S is a dict of integers and that both are valid for the model
  TODO: vectorize the computation of the pDist
  """
  @test i!=j
  @test testNotInDict(i, SToVal)
  @test testNotInDict(j, SToVal)
  selectedPoints = m.dataArray[reduce(&,[m.dataArray[:,condVar] .==SToVal[condVar] for condVar in keys(SToVal)]),:]
  numSelectedPoints = size(selectedPoints)[1]
  pDist = zeros(m.nval[i], m.nval[j])
  for k = 1:m.nval[i]
      for l = 1:m.nval[j]
          pDist[k,l] = size(selectedPoints[(selectedPoints[:,i] .==k-1)&(selectedPoints[:,j] .==l-1), :])[1]/numSelectedPoints
    end
  end
  #sumA=sum(pDist,1)
  #sumB=sum(pDist,2)
  #return (pDist, sumA, sumB)
  jointDistWithMarginals(pDist)
end

function MI(m::model,i::Int,j::Int,SToVal::Dict)
  """
  TODO: test
  """
  MI(conditionalDist(m::model,i::Int,j::Int,SToVal::Dict))
end

MI(aModel, 1, 2, SToVal)
SToVal
SList=[3,4]
Iteraotors.product({1:4, 1:3})
Iterators.product({1:i for i in range(1,5)})
Iterators.product([1:aModel.nval[i] for i in SList]...)
Dict(zip([1,2], [3,4]))

function MI(m::model, i::Int, j::Int, S::Array)
  """
  TODO: test
  """
  min=Inf
  for p in Iterators.product([1:m.nval[i] for i in S]...)
    candidate=MI(m,i,j, Dict(zip(S,p)))
    if candidate < min
      min=candidate
    end
  end
  return min
end

MI(aModel, 1,2,[3,4])
for i in combinations(1:5,3)
    print(i')
end



# & (selectedPoints[:,j] .== l)]oO

SToVal = [3=>0, 4=>1]
aModel.dataArray
cd = conditionalDist(aModel, 1, 2, SToVal)
vec(cd[3])
d=[0.5, 0.5]
size(cd)[1]
cd[cd[:,1].==2,:]
cd.shape()
aModel.dataArray[cd,:]

[x+5y for  x in 1:5, y in 0:1]
Pkg.add("Iterators")
using Iterators
x=(Int64,Int64)[]
for p in Iterators.product(1:4,1:3)
  push!(x, p)
end
x


  S=[1=>2, 3=>4]
f(x) = try
      return S[x]
    catch y
      if isa(y, KeyError)
        return 5
      end
    end
f(5)

  #warn("$x is in $SToVal")

testNotInDict(elt::Int, SToVal::Dict) = try
    """TODO: figure out how to propagate y up the call stack if it's not a KeyError"""
    x=SToVal[elt]
    warn("$elt is in $SToVal with value $x")
    throw(DomainError())
  catch y
    if isa(y, KeyError)
      return true
    else
      return y
    end
  end

S
testNotInDict(1,S)
conditionalDist(m, 4, 5, S)
@test_throws(DomainError(), )

