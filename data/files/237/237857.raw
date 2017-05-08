
# greedy spectral embedding

# packages
using PyPlot
using Debug

# local
using KPCA

# simple data set:
dim = 2
grouped = 10
n = 4*grouped
n2 = floor(n/2)

#regenerate = false
regenerate = true
if regenerate
	# square with 2 pts on each corner - dictionary should be approximately one from each corner
	X = randn(n,dim) .* 1
	L = zeros(n,1)

	i = 1+0*grouped
	X[i:i+grouped-1,:] += 20
	L[i:i+grouped-1] = 1

	i = 1+1*grouped
	X[i:i+grouped-1,:] -= 20
	L[i:i+grouped-1] = 2

	i = 1+2*grouped
	X[i:i+grouped-1,1] += 5
	X[i:i+grouped-1,2] -= 10
	L[i:i+grouped-1] = 3

	i = 1+3*grouped
	X[i:i+grouped-1,1] -= 5
	X[i:i+grouped-1,2] += 10
	L[i:i+grouped-1] = 4
end

if false #regenerate

	# two gaussian groups of pts similar to figure in paper
	X = randn(n,dim)
	X[1:n2,:] .*= 10
	X[n2:n,1] .+= 20
	X[n2:n,1] .*= 10

	L = ones(n,1)
	L[n2:n] = 2

	figure()
	maxv = maximum(X)
	minv = minimum(X)
	p_i = 1
	for r=1:dim
			for c=1:dim
					subplot(dim,dim,p_i)
					scatter(X[:,c],X[:,r])
					xlim(minv,maxv)
					ylim(minv,maxv)

					p_i += 1
			end
	end

end


for i=1:5 # mix up well
	newind = shuffle([1:n])
	X = X[newind,:]
	L = L[newind]
end

println(mean(X,1))


K = LinearKernel(X)

# test definitions - separated into function to make code isolation easier..

function test_kpca(K)
	# run KPCA to compare:
	Kc, P_kpca, Y_kpca = KernelPCA(K, 0, 2, "none")

	kpca_proj_err = 0
	for i=1:size(K,1)
		# kpca
		ki = K[:,i]
		kpca_proj_err += K[i,i] - (ki' * (K \ ki) )

	end
	# avg proj err
	kpca_proj_err /= size(K,1)
	println("kpca proj err: ", kpca_proj_err)
end



# run the tests:
test_kpca(K)



