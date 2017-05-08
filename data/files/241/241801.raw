x = rand(10, 1)

A = randn(3, 3)*2 + 5
B = randn(3, 4)*1 + 0
C = rand(4, 4)

[A B, B' C]

for i in x
    print(i, "\n")
end

function calc_mean(x)
    mean(x)
end

E = svd(B)

#####

# x = readdlm("mickey/files/julia/data/faculty.dat")
# x = readdlm("../data/oliver3b.txt")

x = readdlm("../data/faculty.dat")

require

srand(1)
n = 1000
nbeta = 10 # number of covariates
X = [ones(n) randn((n, nbeta-1))]
beta0 = randn((nbeta,))
Y = X * beta0 + randn((n,))

##########
#Pkg.status()
#Pkg.add("Distributions")
#Pkg.add("Stats")

using Distributions

rand(Normal(3, 2), 5)
pdf(Normal(3, 2), 0)
cdf(Normal(3, 2), 3)
kurtosis(Normal(3, 2))
skewness(Normal(3, 2))
entropy(Normal(3, 2))

skewness(Gamma(7, 0.3))
kurtosis(Gamma(7, 0.3))
entropy(Gamma(7, 0.3))

x = readdlm("../data/T3_7_BONE.DAT")
x = x[:, 2:end]

n = size(x, 1)
p = size(x, 2)
nu = n - 1
S = cov(x)

xbar = mean(x, 1)'
mu0 = [48.0, 49.0, 50.0, 51.0]

T2 = n * (xbar - mu0)' * inv(S) * (xbar - mu0)
F_stat = (nu - p + 1) / (nu * p) * T2

# p-value
1 - cdf(FDist(p, nu - p + 1), F_stat)

# discriminant function
a = inv(S) * (xbar - mu0)
a_star = diagm(sqrt(diag(S))) * a

# contrast
C = [[1 -1 0 0], [0 1 -1 0], [0 0 1 -1]]

T2 = n * (C * xbar)' * inv(C * S * C') * (C * xbar)
F_stat = (nu - p + 1) / (nu * p) * T2
1 - cdf(FDist(p, nu - p + 1), F_stat)
##########

##########
using Distributions

d = MvNormal([0.0, 0.0, 0.0], [[1.0 0.9 0.8], [0.9 1.0 0.9], [0.8 0.9 1.0]])
x = rand(d, 1000)'
eig(cov(x))
sum(1./eig(cov(x))[1])/3

x = randn(1000, 3)
sum(1./eig(cov(x))[1])/3
##########
