using EMGMM
using Stats

# generate a sample of known mean and variance:
n = 1000
m1 = 50
sd1 = 10
X1 = sd1 * randn((convert(Int,floor(n/2)),2)) + m1

#m2 = -30
m2 = 30
sd2 = 10
X2 = sd2 * randn((convert(Int,floor(n/2)),2)) + m2

X = [X1 ; X2]
println("size X: ",size(X))

println("known parameters:")
println("means = ",m1,", ",m2)
println("stdevs = ",sd1,", ",sd2)

# fit the GMM to the data:
#(model,membersip) = emgmm(X,2,"full",300,6,1e-5)

#println("best model:")
#println(model)


# use learn, predict interface:

println("kmeans example: ")
model = learn(X,2,"none") # kmeans
result = predict(X,model)
t = modes(result[1:n])
c1 = t[1]
t = mode(result[n+1:n+n]
c2 = t[1]
println("error: ", sum(result[1:n]==c1)+sum(result[n+1:n+n]==c2))
