using MultivariateStats
using PyPlot

close("all")
# suppose Xtr and Xte are training and testing data matrix,
# with each observation in a column

#Xtr = [collect(1:10) collect(1:10)*5+rand(10,1)]
Xtr = 
b = rand(1,10)
Xte = [b, 5*b]

# train a PCA model
M = fit(PCA, Xtr; maxoutdim=100)
print(projection(M))

#figure()
#plot(Xtr[:,1], Xtr[:,2], "x")
#plot(b, projection(M).*(b), "r.")
# apply PCA model to testing set
#Yte = transform(M, Xte)

## reconstruct testing observations (approximately)
#Xr = reconstruct(M, Yte)
