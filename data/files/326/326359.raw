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

type jointDistWithMarginals
  pdist::Array{Float32,2}
  p_A::Array{Float32,1}
  p_B::Array{Float32,1}
end

function readData(aModel::model, filePath::String)
  aModel.dataArray = readdlm(filePath, ' ', Int);
  aModel.nodes=size(dataArray)[2]
  aModel.nval=ones(Int, nodes)
end

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
  TODO: Test that i,j are distinct and not in conditioning set
  that S is a dict of integers and that both are valid for the model
  """
  selectedPoints = reduce(&,[m.dataArray[:,condVar] .==SToVal[condVar] for condVar in keys(SToVal)])

end

dataArray
d=dataArray
reduce(&,Array[d[:,3] .==1, d[:,5] .==1])
reduce(&,[d[:,k] .==ad[k] for k in keys(ad)])
reduce(&,[dataArray[:,condVar] .==ad[condVar] for condVar in keys(SToVal)])
[x+5y for  x in 1:5, y in 0:1]

