#Pkg.add("Winston")

# for plotting
using Winston

# ~ didn't work for home directory
y = readdlm("/home/mickey/files/data/637/aids.txt")

y = y[2:end,2:end]'
y = float(y[:])

X = [ones(20) log(1:20)]

# part a
plot(exp(X[:,2]), y, "d")
index = 4.5:4:16.5
for i in index
    oplot(i*ones(160), [1:160], "--")
end
oplot()

# part b
plot(X[:,2], log(y), "d")
for i in log(index)
    oplot(i*ones(160), [0:log(160)], "--")
end
oplot()

# part c
betahat = [1, 1]    # similarly betahat = [1 0]', but this is technically different
                    # as this will get a 2x1 Array instead of a 2-element Array
epsilon = 1e-6
diff = 1
iter = 0

while diff > epsilon
    iter += 1
    xbeta = (X * betahat)
    W = diagm(exp(xbeta))
    z = xbeta + y .* exp(-xbeta) - 1
    diff = norm((inv(X' * W * X) * X' * W * z) - betahat, 2)
    betahat = inv(X' * W * X) * X' * W * z
end
