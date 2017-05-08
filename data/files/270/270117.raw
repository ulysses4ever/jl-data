using DataFrames
using Graphs
using Distributions

# dropnarows
df = DataFrame(A=@data([NA, 1, 1, 1]), B=@data([NA, 1, 1, 1]), C=@data([NA, 1, NA, 1]))
@test size(Link.dropnarows(df, 0.4)) == (3,3)
@test size(Link.dropnarows(df, 0.1)) == (2,3)

# imputerandom!
df = DataFrame(A=@data([NA, 1, 1, 1]), B=@data([NA, 3, 3, 3]), C=@data([NA, 4, NA, 4]))
imputerandom!(df)
@test df[1,1] == 1
@test df[1,2] == 3
@test df[3,3] == 4

# blocksample!
arr1 = [1 1; 2 2; 3 3; 4 4; 5 5]
arr2 = zeros(5,2)
blocksample!(arr1, arr2)
@test arr2[1,1] in [1,2,3,4,5]
@test arr2[5,2] in [1,2,3,4,5]

arr2 = zeros(5,2)
blocksample!(arr1, arr2, 2)
@test arr2[1,1]+1 == arr2[2,1]
@test arr2[3,2]+1 == arr2[4,2]
@test arr2[5,2] in [1,2,3,4,5]

# blocksamplecov
srand(1)
data = [array(Link.sim_trivial(1000)) randn(1000)]
data .-= mean(data, 1)
data ./= std(data, 1)
c = cov(data)
bc = blocksamplecov(data)
for i in 1:size(data)[2], j in 1:size(data)[2]
	@test abs(c[i,j] - bc[i,j]) < 0.1
end

# estimatesparsity 
srand(1)
d = estimatesparsity(x->inv(cov(x)), array(Link.sim_trivial(100)), 1000)
@test size(d) == (3, 3)
@test maximum(d) <= 0
@test d[1,3] > log(0.002)

d = estimatesparsity(x->inv(cov(x)), array(Link.sim_trivial(10)), 100, blockSize=4)
@test size(d) == (3, 3)
@test maximum(d) <= 0

d = estimatesparsity(x->cov(x), array(Link.sim_trivial(100)), 1000)
@test size(d) == (3, 3)
@test maximum(d) <= 0
@test d[1,3] < log(0.002)

# estimatecovsparsity
srand(1)
data = array(Link.sim_trivial(100))
data .-= mean(data,1)
data ./= std(data, 1)
d = estimatecovsparsity(data, 1000, transform=x->inv(x))
@test size(d) == (3, 3)
@test maximum(d) <= 0
@test d[1,3] > log(0.002)

d = estimatecovsparsity(data, 1000)
@test size(d) == (3, 3)
@test maximum(d) <= 0
@test d[1,3] < log(0.002)

data = array(Link.sim_trivial(10))
data .-= mean(data,1)
data ./= std(data, 1)
d = estimatecovsparsity(data, 100, blockSize=4, transform=x->inv(x))
@test size(d) == (3, 3)
@test maximum(d) <= 0


# metadata = [["label" => "test1", "value" => "test", "a" => ["x", "y"]], ["label" => "test2", "a" => ["y"]], ["label" => "test3", "a" => ["x", "y"]]]
# P = [1 0.5 0.01; 0.5 1 0.02; 0.01 0.02 1]
# g1 = pvalgraph(metadata, P, 0.015)
# @test num_edges(g1) == 1
# @test source(edges(g1)[1]).attributes["value"] == "test"
# @test source(edges(g1)[1]).label == "test1"
# @test target(edges(g1)[1]).label == "test3"

# g2 = pvalgraph(metadata, P, 0.02)
# @test num_edges(g2) == 2

# @test edgematches(g1, g2, "label") == 1
# @test edgematches(g2, g2, "label") == 2
# @test edgematches(g1, g2, "a") == 1
# @test edgematches(g2, g2, "a") == 2

# # make sure the directionality of the undirected edge specification does not effect things
# g3 = pvalgraph(metadata, P, 0.9)
# g4 = deepcopy(g3)
# permutevertices!(vertices(g4))
# @test edgematches(g4, g3, "label") == 3

srand(1)
C = randomcov(2, 0)
@test C[1,1] != 0
@test_approx_eq C[1,2] 0
@test size(C) == (2,2)

# updatemoments
data = randn(1000)
currMean = 0
currVarSum = 0
for i in 1:1000
    currMean,currVarSum = updatemoments(currMean, currVarSum, data[i], i)
end
@test_approx_eq(currMean, mean(data))
@test_approx_eq(currVarSum/999, var(data))

# ZeroTailDensity
srand(1)
d = ZeroTailDensity()
for i in 1:1000
	addsample!(d, randn())
end
@test 0.45 < pvalue(d) < 0.55

d = ZeroTailDensity()
for i in 1:10
	addsample!(d, randn()+10)
end
@test pvalue(d) < 0.00001

d = ZeroTailDensity()
for i in 1:100
	addsample!(d, randn()*2 + 10)
end
@test pvalue(d) < 0.0001
@test logpvalue(d) < -4

srand(1)
d = ZeroTailDensity()
data = 4 + randn(1000)
for i in 1:1000
    addsample!(d, data[i])
end
@test abs(logpvalue(d) - (log(2)+logcdf(Normal(mean(data),std(data)), 0))) < 3 # stay within 3 orders of magnitude (since we don't guess the middle perfectly)

d = ZeroTailDensity()
for i in 1:100
	addsample!(d, randn().*2 .+ 10)
end
@test pvalue(d) < 0.0001

d = zerotaildensities(10)
for i in 1:1000
	addsample!(d, randn(10))
end
pvals = pvalue(d)
for i in 1:10
	@test 0.45 < pvals[i] < 0.55
end

d = zerotaildensities(10, 10)
data = randn(1000, 10, 10) - 4
for i in 1:1000
	addsample!(d, reshape(data[i,:,:], 10, 10))
end
lpvals = logpvalue(d)
@test std(pvals) > 0.0000001 # make sure we don't have all the same value
diffs = Float64[]
for i in 1:10, j in 1:10
	push!(diffs, abs(lpvals[i,j] - (log(2)+logccdf(Normal(mean(data[:,i,j]),std(data[:,i,j])), 0))))
end
@test mean(diffs) < 2


d = zerotaildensities(10, 10)
for i in 1:1000
	addsample!(d, 7 + randn(10,10))
end
pvals = pvalue(d)
for i in 1:10, j in 1:10
	@test pvals[i,j] < 0.001
end
