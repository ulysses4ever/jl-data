dataArray = readdlm("/Users/eliotpbrenner/PycharmProjects/SparsityBoost/data/synthetic_examples/experiments/0/alarm1000.dat", ' ', Int);
size(dataArray)
# reproducing functionality of model::read_data
nodes=size(dataArray)[2]
nval=ones(Int, nodes)
typeof(dataArray)
typeof(nodes)
typeof(nval)


#workspace() use this to clear definitions
type model
  nodes::Int64
  nval::Array{Int64,1}
  dataArray::Array{Int64,2}
end

function readData(aModel::model, filePath::String)
  aModel::dataArray = readdlm(filePath, ' ', Int);
  nodes=size(dataArray)[2]
  nval=ones(Int, nodes)
end

