# Hermit polynomial related functions for mode coupling analysis	
# 2014 - murozturk@ku.edu.tr


# Returns values of hermite polynomials for x
# 0th hermite polynomial is always 1 so it is not passed around
# degree number of values are returned as an array

function hermit (x::Float64, degree::Int=32)  
	Hx = Array(Float64, degree+1)
	Hx[1:2] = [1. x]
	for i=3:degree+1
		Hx[i] = x*Hx[i-1] - (i-2)*Hx[i-2]
	end
	return Hx[2:end]
end
# vectorized version
function hermit (x::Vector{Float64} )
	degree = length(hermit(0.))
	Hx = Array(Float64, length(x), degree) 
	for i=1:length(x)
		Hx[i,:]=hermit(x[i])
	end
	return Hx
end


# Returns probabilites based on hermit polynomials 

function probHermit (x::Float64, coef::Vector{Float64})
	#exp(-(x*x)/2)/sqrt(2*pi)*(1+sum(hermit(x).*coef))
	# sum(a.*b)= a'*b
	# 1/sqrt(2pi)= 0.3989422804014327
	# hermit(x)[1:2] always zero
	exp(-(x*x)/2)*(1+ (hermit(x)[3:end]'*coef[3:end])[1] )*0.3989422804014327

end
# vectorized version
function probHermit (x::Vector{Float64}, coef::Vector{Float64})
	Float64[probHermit(r,coef) for r in x]
end

# Calculates hermit coefficients for a given distribution
# C_i = E[ H_i ] / i!

function coefHermit( r::Matrix{Float64} )
	
	println("Calculating Hermite coefficients..")
	
	nSamples, nModes = size(r)
	nBins=sqrt(nSamples)
	degree = length(hermit(0.))
	
	coef = Array(Float64, degree, nModes)
	
	for mode=1:nModes 
		rHat, rDist = dist(r[:,mode])
		rHermit = hermit(rHat) 
		for d=1:degree
			h = rHermit[:,d]
			# expectation of dth Hermite for this mode
			Ehr = sum(h.*rDist) 
			# divided by (d)!
			coef[d, mode] = divideByFactorial(Ehr, d)
		end
	end

	return  coef
end



# Returns samples from a Hermite distribution

function sampleHermit(nSamples::Int, coef::Vector{Float64})
	sample::Float64 = randn()
	#samples = randn(nSamples)


	samples = Array(Float64, nSamples)
	dice::Float64   = rand()
	for i=1:nSamples
		println(string(i,"/",nSamples))
		sample = randn()
		dice   = rand()
		while dice > probHermit(sample, coef)
			sample  = randn()
			dice    = rand()
		end
		samples[i]=sample
	end
	return samples
end

function sampleHermit(nSamples::Int, coef::Matrix{Float64})
	nModes = size(coef,2)
	
	sample::Float64 = randn()
	samples = Array(Float64, nSamples, nModes)
	
	println ("Sampling f1 distribution...")
	
	dice::Float64 = 1.

	for mode=1:nModes
		println(string(mode,"/",nModes));
		for i=1:nSamples
			dice   = 1.0
			while dice > probHermit(sample, coef[:,mode])
				#sample  = randn() #gaussian kernel
				sample = rand()*6-3 #uniform kernel
				dice   = rand()
			end
			samples[i,mode] = sample
		end
	end
	
	return samples
end


# Returns x/f!

function divideByFactorial (x::Float64, factorial::Int)
	factorial==0 && return x
	factorial==1 && return x 
	divideByFactorial(x/factorial, factorial-1)
end

# returns prob. distributions of a given sample

function dist (x::Vector{Float64})
	nSamples = length(x)
	nBins=int(sqrt(nSamples))

	bins= linspace(minimum(x), maximum(x), nBins+1)

	px= hist(x,bins)[2]/nSamples

	index = (bins[1:nBins] + bins[2:nBins+1] ) /2

	return index, px
end

# this results in a common bin for all modes
# but actual n nBins is not well defined
# only good for quick comparisons

function dist (X::Matrix{Float64})
	nSamples, nModes = size(X)
	nBins=int(sqrt(nSamples))
	
	bins=linspace(minimum(X),maximum(X),nBins+1)
	
	pX = hist(X,bins)[2] /nSamples
	
	rHat  = ( bins[1:nBins] + bins[2:nBins+1] ) / 2 

	return rHat , pX
end


# Calculates the expectation values for a given pair of modes

function f2_exp ( m1::Vector{Float64}, m2::Vector{Float64}, ind1::Int64 , ind2::Int64 , degree::Int = 32)


        bin_number=int(ceil(sqrt(length(m1))));

        combined = hcat(m1,m2);



        b1, b2, bins = hist2d(combined, linspace(minimum(m1),maximum(m1),bin_number), linspace(minimum(m2), maximum(m2),bin_number))

        # Normalization for a fixed bin base area

        base_area = (b1[2]-b1[1]) * (b2[2]-b2[1]);

        area = 0;

        for i=1:size(bins,1);
                for j=1:size(bins,2)
                        area += bins[i,j];
                end
        end

        bins /= (area);


        HxHy=zeros(495,5);

	# To keep track of the mode indices

        HxHy[:,3] = max(ind1,ind2);

        HxHy[:,4] = min(ind1,ind2);
        
        # Main loop

        for s1=1:bin_number-1

                for s2=1:bin_number-1

                        vec1 = modeCouplingAnalysis.hermit(b1[s1]);
                        vec2 = modeCouplingAnalysis.hermit(b2[s2]);

                        n = 1;

                        for v=3:degree

                                for p=1:(v-1)

                                        HxHy[n,5] += bins[s1,s2] * vec1[v-p] * vec2[p]
                                        HxHy[n,1] = p;

                                        HxHy[n,2] = v-p;

                                        n += 1;
                                end

                        end

                end

        end

        return HxHy

end

function combination (x1::Int64, x2::Int64)
	
	# Calculates and returns (x1,x2)
	if x1 >= x2
	return factorial(x1)/factorial(x2)/factorial(x1-x2)
	end
end

function coef_f2( f2_exp :: Array )
        
        # Calculates the f2 coefficients as in Eq. 8

        coef_f2 = f2_exp;

        for i=1:length(f2_exp)

                coef_f2[n,5] = combination(f2_exp[n,2] + f2_exp[n,1], f2_exp[n.1]) * f2_exp[n,5] ;
                
        end     
        
        return coef_f2;
        
end 

