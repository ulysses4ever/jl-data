module DirectionalRegression
using Distributions
import Base.Test

type VonMisesModel
	β::Array{Float64,1}
	μ::Float64
	κ::Float64
end

type VonMisesResult
	model::VonMisesModel
	θ::Array{Float64,1}
	ll::Float64
end

#Code based on 
#Fisher, N. I., & Lee, A. J. (1992). Regression Models for an Angular Response. Biometrics, 48(3), 665. http://doi.org/10.2307/2532334
#

#TODO: Provide a reasonable goodness of fit measure (perhaps aic?)
#		   Also try cross-validation
g(μ) = 2*atan(μ)
#derivate of g wrt its argument
#gd(η) = (tt = tan(0.5*η); t2 = tt.*tt; 0.5*(1+t2))
gd(μ) = 2.0./(1+μ.*μ)

I0(x) = besseli(0,x)
I1(x) = besseli(1,x)

"""
Get κ from Aκ by running a few iterations of Newton's method
"""
function get_κ(Aκ::Real,maxiter=10)
	κ = 1.0
	A(κ) = I1(κ)/I0(κ)
	i = 0 
	#use newtons method to get κ
	while  i < maxiter
		Aκ1 = A(κ)
		κ = κ - (Aκ1 - Aκ)./(1-Aκ1*Aκ1 - Aκ1/κ)
		i+=1
	end
	κ
end

"""
Get the MLE for κ, assuming θ are IID from a Von Mises distribution
"""
function get_κ(θ::Array{Float64,1}, args...)
	N = length(θ)
	z = mean(exp(θ*im))
	R2 = z*conj(z)
	get_κ(sqrt(real(N/(N-1)*(R2 - 1/N))),args...)
end

function loglikehood(θ::Array{Float64,1}, κ::Real, μ::Real, β::Array{Float64,1},X::Array{Float64,2})
  ncells,ntrials = size(X)
  LL = -2*pi*ntrials*log(I0(κ))
  l = 0.0
	η = X'*β
	gη = g(η)
  for i in 1:ntrials
    l += cos(θ[i] - μ - gη[i])
  end
  l *= κ
  LL + l
end

"""
The objective functino to be minimised
"""
function func1(β::Array{Float64,1},X::Array{Float64,2},Θ::Array{Float64,1},μ::Real)
  ncells,ntrials = size(X)
  Y = zeros(ncells)
  η = X'*β
  gη = g(η)
  gdη = gd(η)
  for k in 1:ncells
    for i in 1:ntrials
      #η = dot(X[:,i],β)
      u = sin(Θ[i] - μ - gη[i])
      qq = u*gdη[i]
      for j in 1:ntrials
        Y[k] += qq*X[k,j]
      end
    end
  end
  Y
end

"""
Generate a new estimate of β by running a single step of Newton's method
"""
function func2(β::Array{Float64,1},X::Array{Float64,2},θ::Array{Float64,1},μ::Real,Aκ::Real)
  η = X'*β
  gη = g(η)
  gdη = gd(η)
	u = sin(θ -μ - gη)
	y = u./(Aκ*gdη) 
	G2 = diagm(gdη.*gdη)
	D = X*G2*X'
	V = X*G2*y
	dβ = inv(D)*V
	dβ
end

function func3(β::Array{Float64,1},X::Array{Float64,2},θ::Array{Float64,1},μ::Real,Aκ::Real)
  η = X'*β
  gη = g(η)
  gdη = gd(η)
	y = sin(θ -μ - gη)./(Aκ*gdη)
	G2 = diagm(gdη.*gdη)
	D = X*G2*X'
	V = X*G2*y
	dβ = D\V 
	dβ
end

"""
Same as func3, but avoid allocating a large diagonal matrix
"""
function func4(β::Array{Float64,1},X::Array{Float64,2},θ::Array{Float64,1},μ::Real,Aκ::Real)
  η = X*β
  gη = g(η)
  gdη = gd(η)
	y = sin(θ -μ - gη)./(Aκ*gdη)
	D = zeros(length(β),length(β))
	V = zeros(length(β))
	for i in 1:length(β)
		for j in 1:length(β)
			for k in 1:length(y)
				D[i,j] += X[k,i]*gdη[k]*gdη[k]*X[k,j]
			end
		end
	end
	for i in 1:length(β)
		for k in 1:length(y)
			gk = gdη[k]
			yk = y[k]
			V[i] += X[k,i]*gk*gk*yk
		end
	end

	dβ = D\V 
	dβ
end


function func_s(β::Array{Float64,1}, X::Array{Float64,2}, θ::Array{Float64,1})
  s = 0.0
  ncells,ntrials = size(X)
  for i in 1:ntrials
    η = dot(X[:,i],β)
    s += sin(θ[i] - g(η))
  end
  s/ntrials
end

function func_c(β::Array{Float64,1}, X::Array{Float64,2}, θ::Array{Float64,1})
  c = 0.0
  ncells,ntrials = size(X)
  for i in 1:ntrials
    η = dot(X[:,i],β)
    c += cos(θ[i] - g(η))
  end
  c/ntrials
end

function get_params(β::Array{Float64,1}, X::Array{Float64,2}, θ::Array{Float64,1})
	s = func_s(β, X', θ)
	c = func_c(β, X', θ)
	r = sqrt(s*s + c*c)
	μ = atan(s/c)
	Aκ = r
	μ, Aκ
end

"""
Fit a Von Mises model which predicts the  angles `θ` from `X`.  

	function fitmodel(X::Array{Float64,2}, θ::Array{Float64,1}, μ=0.0, κ = 1.0;tol=1e-6,maxiter=1000,verbose=0,max_auto_restarts=0)
"""
function fitmodel(X::Array{Float64,2}, θ::Array{Float64,1}, μ=0.0, κ = 1.0;tol=1e-6,maxiter=1000,verbose=0,max_auto_restarts=0)
	i = 0
	Aκ = I1(κ)/I0(κ)
	fitted = false
	restarts = 0
	β = 2*rand(size(X,2))-1
	βp = zeros(β)
	_isnan = false
	while !fitted && restarts <= max_auto_restarts
		β = 0.5*(rand(size(X,2))-0.5)
		βp = zeros(β)
		LL_old = loglikehood(θ,κ, μ, β, X')
		_isnan = false
		try
			while true
				i += 1
				s = func_s(β, X', θ)
				c = func_c(β, X', θ)
				r = sqrt(s*s + c*c)
				μp = atan(s/c)
				Aκp = r
				j = 0
				while true
					j += 1
					#println(β)
					βp[:] = β + func4(β, X, θ, μp, Aκp)
					verbose > 1 && println("βp = $(βp)")
					if (sumabs2(βp - β) < tol) || j > maxiter || isnan(βp[1])
						break
					end
					β = copy(βp)
				end
				κp = get_κ(Aκp)
				LL = loglikehood(θ,κp, μp, βp, X')
				if isnan(LL)
					if verbose > 0 
						println("NaN detected")
						println("\tβp = $(βp)")
						println("\tβ = $(β)")
						println("\tμp = $(μp)")
						println("\tκp = $(κp)")
					end
					_isnan = true
					break
				end
				verbose > 1 && println(LL)
				if  abs(LL-LL_old) < tol || i > maxiter 
					break
				end
				LL_old = LL
				μ = μp
				Aκ = Aκp
			end
			if i > maxiter && verbose > 0
				println("Max number of iterations reached")
			elseif _isnan
				fitted = false
			else
				fitted = true
			end
			restarts += 1
		catch ee
			if !isa(ee, Base.LinAlg.SingularException)
				rethrow(ee)
			end
		end

	end
	βp
	μp,Aκp = get_params(βp, X, θ)
	κp = get_κ(Aκp)
	LL = loglikehood(θ,κp, μp, βp, X')
	VonMisesResult(VonMisesModel(βp, μp, κp), θ, LL)
end

function test(μ=0, κ=1.0)
	X = 2*rand(1000,3)-1
	β = [0.181689,0.533594,0.132475]
	μ0 = g(X*β);
	θ = zeros(size(X,1))
	for i in 1:length(θ)
		 θ[i] = rand(sampler(VonMises(μ + μ0[i], κ)))
	end
	βp = fitmodel(X, θ, 2*pi*rand()-pi, 0.1+3*rand(); tol=1e-3, maxiter=100)
	μp, Aκp = get_params(βp, X, θ)
	κp = get_κ(Aκp)
	LL = loglikehood(θ, κp, μp, βp, X')
	β, βp, μp, κp, LL
end
end #module
