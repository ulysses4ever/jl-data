# Test the gaussian pre-image code
# Danny Perry (dperry@cs.utah.edu)
# May 2015

using Debug
using PyPlot
using Kernel

@debug function main()

	n = 100
	rad = 10
	thetas = 2*pi*rand(n)
	X = rad*[cos(thetas) sin(thetas)]
	Xtest = mean(X,1)

	figure()
	plot(X[:,1],X[:,2],"ro")
	hold(:on)
	plot(Xtest[1],Xtest[2],"bo")

	iters = 1
	neibsize = 2
	sigma = 10.0
	#result,neibs = GaussianKernelDenoise(X, Xtest, iters, neibsize, sigma)
	K = GaussianKernel(X,sigma)
	Ktest = GaussianKernel(X,Xtest,sigma)
	result,neibs = GaussianKernelPreImage(X, K, Ktest, neibsize, sigma)
	println("==================")
	println("neibsize: ", neibsize)
	println("input: ", Xtest)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))
	println("==================")

	figure()
	plot(X[:,1],X[:,2],"ro")
	hold(:on)
	plot([Xtest[1],result[1]],[Xtest[2],result[2]],"bx--")
	plot(result[1],result[2],"gs")
	plot(X[vec(neibs[1,:]),1],X[vec(neibs[1,:]),2],"y^")
	title(@sprintf("%d",neibsize))


	neibsize = 4
	result,neibs = GaussianKernelDenoise(X, Xtest, iters, neibsize, sigma)
	println("==================")
	println("neibsize: ", neibsize)
	println("input: ", Xtest)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))
	println("==================")


	figure()
	plot(X[:,1],X[:,2],"ro")
	hold(:on)
	plot([Xtest[1],result[1]],[Xtest[2],result[2]],"bx--")
	plot(result[1],result[2],"gs")
	plot(X[vec(neibs[1,:]),1],X[vec(neibs[1,:]),2],"y^")
	title(@sprintf("%d",neibsize))



	neibsize = 10
	result,neibs = GaussianKernelDenoise(X, Xtest, iters, neibsize, sigma)
	println("==================")
	println("neibsize: ", neibsize)
	println("input: ", Xtest)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))
	println("==================")

	figure()
	plot(X[:,1],X[:,2],"ro")
	hold(:on)
	plot([Xtest[1],result[1]],[Xtest[2],result[2]],"bx--")
	plot(result[1],result[2],"gs")
	plot(X[vec(neibs[1,:]),1],X[vec(neibs[1,:]),2],"y^")
	title(@sprintf("%d",neibsize))




	theta = rand()*2*pi
	Xtest = rad*[cos(theta) sin(theta)]
	neibsize = 2
	result,neibs = GaussianKernelDenoise(X, Xtest, iters, neibsize, sigma)
	println("neibsize: ", neibsize)
	println("input: ", Xtest)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))

	figure()
	plot(X[:,1],X[:,2],"ro")
	hold(:on)
	plot([Xtest[1],result[1]],[Xtest[2],result[2]],"bx--")
	plot(result[1],result[2],"gs")
	plot(X[vec(neibs[1,:]),1],X[vec(neibs[1,:]),2],"y^")
	title(@sprintf("%d",neibsize))



	neibsize = 4
	result,neibs = GaussianKernelDenoise(X, Xtest, iters, neibsize, sigma)
	println("neibsize: ", neibsize)
	println("input: ", Xtest)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))

	figure()
	plot(X[:,1],X[:,2],"ro")
	hold(:on)
	plot([Xtest[1],result[1]],[Xtest[2],result[2]],"bx--")
	plot(result[1],result[2],"gs")
	plot(X[vec(neibs[1,:]),1],X[vec(neibs[1,:]),2],"y^")
	title(@sprintf("%d",neibsize))



	neibsize = 10
	result,neibs = GaussianKernelDenoise(X, Xtest, iters, neibsize, sigma)
	println("neibsize: ", neibsize)
	println("exact: ", Xtest)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))

	figure()
	plot(X[:,1],X[:,2],"ro")
	hold(:on)
	plot([Xtest[1],result[1]],[Xtest[2],result[2]],"bx--")
	plot(result[1],result[2],"gs")
	plot(X[vec(neibs[1,:]),1],X[vec(neibs[1,:]),2],"y^")
	title(@sprintf("%d",neibsize))


	PyPlot.plt.show()
	@bp

end

function testdata()
	X = reshape([1:33],11,3)
	Xtest = X[5,:]
	X = X[[1:4,6:end],:]

	println("Xtest: ", Xtest)
	println("X:\n", X)

	return X,Xtest
end


@debug function simple(neibsize = 2)
	println("~~~~~~~~~~~~~~~~~~~")
	println(" neighbors approach")
	println("~~~~~~~~~~~~~~~~~~~")

	X,Xtest = testdata()

	sigma = 1.0
	K = GaussianKernel(X,sigma)
	Ktest = GaussianKernel(X,Xtest,sigma)
	result,neibs = GaussianKernelPreImage(X, K, Ktest, neibsize, sigma)

	println("neibs: ", neibs)

	println("===================")
	println("neibsize: ", neibsize)
	println("exact: ", Xtest)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))
	println("===================")

	return result
end

@debug function simple2()
	println("~~~~~~~~~~~~~~~~~~~")
	println(" fixed point approach")
	println("~~~~~~~~~~~~~~~~~~~")

	X,Xtest = testdata()

	sigma = 1.0
	K = GaussianKernel(X,sigma)
	U,S,V = svd(K)
	Ktest = GaussianKernel(X,Xtest,sigma)
	y = vec(Ktest' * V)
	z_init = mean(X,1)
	result,iters = GaussianKernelPreImage(y,V, X,z_init, sigma, 1e-3,100)
	
	println("===================")
	println("exact: ", Xtest)
	println("iters: ", iters)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))
	println("===================")
end

@debug function simple3()
	println("~~~~~~~~~~~~~~~~~~~")
	println(" both approach")
	println("~~~~~~~~~~~~~~~~~~~")
	
	X,Xtest = testdata()

	neibsize = 3
	sigma = 1.0
	K = GaussianKernel(X,sigma)
	U,S,V = svd(K)
	Ktest = GaussianKernel(X,Xtest,sigma)
	y = vec(Ktest' * V)
	z_init = simple(neibsize)
	println("zinit: ", z_init)
	println("diff: ", norm(Xtest-z_init))
	result,iters = GaussianKernelPreImage(y,V, X,z_init, sigma, 1e-20,10000)

	println("===================")
	println("neibsize: ", neibsize)
	println("exact: ", Xtest)
	println("iters: ", iters)
	println("result: ", result)
	println("diff: ", norm(Xtest-result))
	println("===================")
end



simple() # method 1
simple2() # method 2
simple3() # method 1 and 2
#main()
