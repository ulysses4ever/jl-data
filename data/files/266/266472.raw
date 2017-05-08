using Distributions

function generate_conn_1D(N, J, ε, α)
        W=zeros(N, N)
        NC = int(ε*N)
        for i=1:N
                for j=sample([1:i-1,i+1:N],NC,replace=false)
                        W[j,i] = J/abs(i/N-j/N)^α
                end
        end
        return W'
end



function generate_conn_1D_2pop(N, f, g, J, ε, α)
	Ni = int(N - N*f)	
	Ne = N - Ni
	C = int(N*ε)
	Ce = int(f*C)
	Ci = int(C - C*f)
	LNe = [1:N]
	LNi = sort!(sample([1:N],Ni,replace=false))
	deleteat!(LNe,LNi)
	JMatrix = zeros(N,N)
	for n=1:N
		for m = sample(LNe,Ce,replace=false) # using Distributions
			if n!=m
				JMatrix[n,m] += J / abs(n/N-m/N)^α
			end
		end
		for m = sample(LNi,Ci,replace=false)
			if n!=m
				JMatrix[n,m] -= g*J / abs(n/N-m/N)^α
			end
		end
	end
	return JMatrix
end 
 

function F_θ(μ, σ, τ_m)
	# Use Benjamin Lindner formula at 3.3
	D = τ_m^2*σ
	β = τ_m*μ 
	iter_n = 10
	S = 0
	for n=0:iter_n
		S += (-1)^n * 2^((2n+1)/3)/factorial(n) * gamma((2n+1)/6) * (β*(3/D^2)^(1/3))^n
	end
	T = (1/3D)^(1/3.) * sqrt(π/D) * S
	return T
end

function μ_MFT(J, ν, K, τ_m, μ_ext)
	return   J*ν*K*τ_m + μ_ext
end

function σ2_MFT(J, ν, K, τ_m)
	return J^2*K*τ_m*ν
end


function simulate_network(T, W, μ_ext, dt , θ)
	τ_m = 0.010
	N = int(sqrt(length(W)))
	#srand(seed)
	#θ = rand(N) * 0.2
	θs = zeros(N,T)
	spikes = zeros(N, T)
	for i=1:T
        	spikes[:,i] = θ .>= π
		μ_tot = μ_ext + W*spikes[:,i]
        	θ[θ.>π] -= 2π
		θ[θ.<-π] = -π
		θ =  θ +  dt/τ_m*(1 .- cos(θ)+ (1 .+ cos(θ)).*μ_tot)
		θs[:,i] =  θ
	end
	return spikes, θs 
end

function empirical_var(S, m)
	N=size(S)[1]
	res = Float64[]
	for i=1:N
		 push!(res, varm(S[i,:], m))
	end
	return res
end


dt = 0.0001
srand(1234)
K = 100
T = 500
α = 0.0
J = -3.5 * sqrt(100/K)
#W = generate_conn_1D(N, J, ε, α) 
#W = generate_conn_1D_2pop(N, 0.8, 5.0,3.*sqrt(100)/sqrt(K), K/N, .900)
#μ_ext = rand(1000)*.01*sqrt(K)/sqrt(100)

#asym00 =  Float64[]#-0.6497536856298188
#asym90 =  Float64[]#-0.773806085834776

v00 = Float64[]
v90 = Float64[]


s = 100

for α in [ 0, 0.9]
#	if α == 0.0
        	#χ00 = Float64[]
        	#CV00 = Float64[]
        	#m00  = Float64[]
#v00 = Float64[]
#	else
        	#χ90 = Float64[]
        	#CV90 = Float64[]
        	#m90  = Float64[]
#v90 = Float64[]
#	end
for N=500:s:4000
	ε = K/N
	μ_ext = 0.025*sqrt(K)/sqrt(100)
	W = generate_conn_1D(N, J, ε, α)
	#W = generate_conn_1D_2pop(N, 0.8, 5.0,5.*sqrt(100)/sqrt(K), ε, α)
	for i=1:150
		srand(i*N*int(round(1+α) ))
		θ_int  = rand(N)#[θs[:,end], θs[:,end]][1:N] #[θs[:,end], θs[:,end], θs[:,end],  θs[:,end]][1:N] 
		spikes , θs = simulate_network(T, W, μ_ext, dt, θ_int)
		#CV = 0
		#n = 0
		#for i=1:N
		#	if length(findnz(spikes[i,:])[2])>3
		#		CV += sqrt(var(diff(findnz(spikes[i,:])[2])))/mean(diff(findnz(spikes[i,:])[2]) )
		#		n +=1
		#	end
		#end
		if α == 0
			#push!(χ00, sqrt( sqrt(var(mean(θs,1)) / mean(sqrt(var(θs,2)))  ) ))
			#push!(CV00, CV/n)
			#push!(m00, mean(sum(spikes,1)/dt))
			push!(v00, mean(θs[:,end]) )
			#push!(asym00, mean(θs[:,end]) )
		else
			#push!(χ90, sqrt( sqrt(var(mean(θs,1)) / mean(sqrt(var(θs,2)))  ) ))
			#push!(CV90, CV/n)
			#push!(m90, mean(sum(spikes,1)/dt) )
			push!(v90, mean(θs[:,end]) )
			#push!(asym90, mean(θs[:,end]) )

		end
	end
	println(N)
end
end


s00 = reshape(v00, length(500:100:4000), length(1:150))
s90 = reshape(v90, length(500:100:4000), length(1:150))

writedlm("est_meanTheta_alpha00.txt", empirical_var(s00, -0.6494352245159316))
writedlm("est_meanTheta_alpha90.txt", empirical_var(s90, -0.779307706950374))


#println(mean(asym00))
#println(mean(asym90))


# alpha = 0.9 then mean theta = -0.34289140170856797
# alpha = 0.0 then mean theta = -0.08672657380774774 



#rate=sum(spikes,1)/N
#println(var(rate[30000:end]))

#plot(findnz(spikes')[1],findnz(spikes')[2] ,".")
