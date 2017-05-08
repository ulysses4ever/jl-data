dataArray = readdlm("/Users/eliotpbrenner/PycharmProjects/SparsityBoost/data/synthetic_examples/experiments/0/alarm1000.dat", ' ', Int);
size(dataArray)
# reproducing functionality of model::read_data
nodes=size(dataArray)[2]
nval=ones(Int, nodes)
typeof(dataArray)
typeof(nodes)
typeof(nval)


workspace() #use this to clear definitions
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
  assert(maximum(transpose(sumA)-aJointDistributionWithMarginals.p_A) < 1e-20)
  assert(maximum(sumB-aJointDistributionWithMarginals.p_B) < 1e-20)
  assert(sum(sumA)-1.0 < 1e-20)
end

using Base.Test
@test 1 == 1
@test 1==0
goodDist=jointDistWithMarginals([[0.25 0.25], [ 0.25 0.25]], [0.5, 0.5], [0.5, 0.5])
verify(goodDist)

goodDist.pdist
sum(goodDist.pdist, 1)
goodDist.p_A

