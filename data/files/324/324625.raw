###############################################################
# Gibbs sampler for probabilistic annotator models. 
# Includes fully observed data matrix Lnm
# Created by Salvador Ruiz Correa 01/30/15
###############################################################

type gsModel	
	N				::Int64 			# number of subjects 
	M				::Int64   			# number of tasks
	K				::Int64   			# number of topics 
	R				::Int64  			# number of Likert scale points
	ALPHA 			::Float64 			# alpha Dirichlet concentration parameter
	GAMMA 			::Float64 			# gamma Dirichlet concentration parameter
	Zm  			::Array{Int64} 		# Zm tasks hidden values 
end

type gsParameters
	seed			::Int64     		# random generator seed  
	BURNIN			::Int64
	maxIter			::Int64
	shapeAlpha 		::Float64   		# prior hiperparameter
	scaleAlpha  	::Float64   		# prior hiperparameter
	shapeGamma		::Float64   		# prior hiperparameter
	scaleGamma		::Float64   		# prior hiperparameter
	vFactorAlpha	::Float64   		# Metropolis-Hasting kernel scale parameter for variance  
	vFactorGamma	::Float64   		# Metropolis-Hasting kernel scale parameter for variance  
end

global tmp = 1;
global tmp1 = 1;
global tmp2 = 1;
global tmp3 = 1;
global tmp4 = 1;
global tmp5 = 1;
global test = 1;

# ------------------------------------------------------------------
# Random number generators
# ------------------------------------------------------------------

## return a random sample from a normal (Gaussian) distribution
function rand_normal(mean, stdev)
    if stdev <= 0.0
        error("standard deviation must be positive")
    end
    u1 = rand()
    u2 = rand()
    r = sqrt( -2.0*log(u1) )
    theta = 2.0*pi*u2
    mean + stdev*r*sin(theta)
end


## return a random sample from a gamma distribution
function rand_gamma(shape, scale)
    if shape <= 0.0
        error("Shape parameter must be positive")
    end
    if scale <= 0.0
        error("Scale parameter must be positive")
    end
    
    ## Implementation based on "A Simple Method for Generating Gamma Variables"
    ## by George Marsaglia and Wai Wan Tsang.  
    ## ACM Transactions on Mathematical Software
    ## Vol 26, No 3, September 2000, pages 363-372.

    if shape >= 1.0
        d = shape - 1.0/3.0
        c = 1.0/sqrt(9.0*d)
        while true
            x = rand_normal(0, 1)
            v = 1.0 + c*x
            while v <= 0.0
                x = rand_normal(0, 1)
                v = 1.0 + c*x
            end
            v = v*v*v
            u = rand()
            xsq = x*x
            if u < 1.0 -.0331*xsq*xsq || log(u) < 0.5*xsq + d*(1.0 - v + log(v))
                return scale*d*v
            end
        end
    else
        g = rand_gamma(shape+1.0, 1.0)
        w = rand()
        #return scale*g*pow(w, 1.0/shape)
        return scale*g*w^(1.0/shape);
    end
end

# ------------------------------------------------------------------
# logNormal()
# ------------------------------------------------------------------
function logNormal( a, mu, sigma )

	tmp = -0.5 * log( pi * sigma ) - ( a - mu )^2 /2 / sigma;

	return tmp;

end

# ------------------------------------------------------------------
# logGamma()
# ------------------------------------------------------------------
function logGamma( x, shape, scale )

	tmp = -lgamma( shape ) - shape * log( scale ) + ( shape - 1 ) * x - x / scale;

	return tmp;

end

# ------------------------------------------------------------------
# logPLZGamma() - log P(L|Z,Gamma)
# ------------------------------------------------------------------
function logPLZGamma( Snkr, Snk, GAMMA, NK, NKR, RGAMMA ) 

Ankr = lgamma( Snkr + GAMMA )
Bnk = sum( Ankr, 3 );
Cnk = lgamma( Snk + RGAMMA );
Dnk = Bnk - Cnk;
Dn = sum( Dnk, 2 );
tmp1 = sum( Dn );
tmp2 =  NK * lgamma( RGAMMA ) - NKR  * lgamma( GAMMA ) 
tmp3 = tmp1 + tmp2;

return  tmp3;

end

# ------------------------------------------------------------------
# logPZAlpha() - log P(Z|Alpha)
# ------------------------------------------------------------------
function logPZAlpha( K ) 

return 1.0/K;

end

# -----------------------------------------------------------------------------------
# modelLikelihood() - log P(L|Z,Gamma) + log P(Z|Alpha) + log p(Alpha) + log P(Gamma)
# -----------------------------------------------------------------------------------
function modelLikelihood( Snkr, Snk, GAMMA, NK, NKR, RGAMMA, Zm, M, MK, K, ALPHA,shapeGamma, shapeAlpha, scaleGamma, scaleAlpha ) 

	tmp1 = logPLZGamma( Snkr, Snk, GAMMA, NK, NKR, RGAMMA );
	tmp2 = logPZAlpha( K );  
	tmp3 = logGamma( ALPHA, shapeAlpha, scaleAlpha );
	tmp4 = logGamma( GAMMA, shapeGamma, scaleGamma );

	tmp5 = tmp1 + tmp2 + tmp3 + tmp4;

	return tmp5;

end

# ------------------------------------------------------------------
# kernelMH() P(A|Ap)/P(Ap|A)
# ------------------------------------------------------------------
function kernelMH( a, ap, F ) 

	tmp1 = 0.5 * ( log( a ) - log( ap ) );
    tmp2 = 0.5 * F * ( a - ap )^3 / a / ap;

	return tmp1 - tmp2;

end

# ------------------------------------------------------------------
# logRatioGAMMAS() log P(Ap) - log P(A)
# ------------------------------------------------------------------
function logRatioGAMMAS( a, ap, shape, scale ) 

	tmp1 = ( shape - 1 ) * ( log( ap ) - log( a ) );
    tmp2 = ( a - ap ) / scale;

	return tmp1 + tmp2;

end

# ------------------------------------------------------------------
# gibbsSampler() - full Lnm data matrix
# ------------------------------------------------------------------

function gibbsSampler( 	Lnm::Array{Int64,2}, 
						Model::gsModel, 
						Par::gsParameters,
						initState::Bool,
						bwritecsv::Bool, 
						fileNamePrefix::ASCIIString ) 


scaleGamma 		= Par.scaleGamma;
scaleAlpha 		= Par.scaleAlpha;
shapeGamma 		= Par.shapeGamma;
shapeAlpha 		= Par.shapeAlpha;
vFactorAlpha 	= Par.vFactorAlpha;
vFactorGamma 	= Par.vFactorGamma;

if initState == true
	maxIter = Par.BURNIN;
else
	maxIter = Par.maxIter;
end

N 				= Model.N;
M 				= Model.M;
K 				= Model.K;
R 				= Model.R;
Zm 				= Model.Zm;
ALPHA 			= Model.ALPHA;
GAMMA 			= Model.GAMMA;

logP = zeros( Float64, 1, maxIter );


if bwritecsv
	fidZm 		= open( string(fileNamePrefix, "Zm.csv" ), "w" );
	fidALPHA	= open( string(fileNamePrefix, "ALPHA.csv" ), "w" );
	fidGAMMA 	= open( string(fileNamePrefix, "GAMMA.csv" ), "w" );
	fidLogP 	= open( string(fileNamePrefix, "LogP.csv" ), "w" );
end

alphaAccRate = 0.0;
gammaAccRate = 0.0;

if bwritecsv
	fid = open( string(fileName, "Header.csv" ), "w" );
	writecsv( fid, N );
	writecsv( fid, M );
	writecsv( fid, K );
	writecsv( fid, R );
	writecsv( fid, maxIter );
	close( fid );
end

# Initialize arrays

count1 = M
count2 = count1 + 1;
count3 = count2 + 1;

Snkr  = zeros( Int64, N, K, R ); 
Snk   = zeros( Int64, N, K );
ind = zeros( 1, count3 ); 

# Set random seed
srand( Par.seed );

# Set markov chain state

if initState == true
	Zm = rand( int64( 1 : K ), M );
	GAMMA = rand_gamma( shapeGamma, scaleGamma);
end

MK = M * K;
NK = N * K;
NKR = NK * R;
KR = K * R;
RGAMMA = R * GAMMA;
KALPHA = K * ALPHA;

# Update arrays

for n = 1 :  N
	for m = 1 : M
		Snkr[ n , Zm[ m ] , Lnm[ n, m ] ] += 1;
		Snk[ n , Zm[ m ] ] += 1;
	end
end	


# Main loop 

id = 1;
temp = 1.0;
maxval = 1.0;
termZ = 1.0;
totProb = 1.0;
probS = Array( Float64, R );
probZ = Array( Float64, K );

for iter = 1 : maxIter

	
	rand!( 1 : count3, ind );  

    for vars = 1 : count3  # random scan loop

	if ind[ vars ] <= count1  # update Zm

	   		m = ind[ vars ];
	   		
	   		for n = 1 : N	
	   	    	Snkr[ n, Zm[ m ], Lnm[ n, m] ] -= 1;
				Snk[ n, Zm[ m ] ] -= 1;
			end

			totProb = 0.;
			for k = 1 : K
				termZ = 1.;
				for n = 1 : N
					termZ *= ( float64( Snkr[ n, k, Lnm[ n, m ] ] ) + GAMMA ) / ( float64( Snk[ n, k ] ) + RGAMMA );
				end

				probZ[ k ] =  termZ;
				totProb += probZ[ k ];
			end

 			temp = rand() * totProb;
            maxval = probZ[ 1 ];
            id = 1;

            while ( temp  > maxval )             	
	            id += 1;
                maxval += probZ[ id ];
            end

			Zm[ m ] = id;
			for n = 1 : N
		    	Snkr[ n, Zm[ m ], Lnm[ n, m ] ] += 1;
				Snk[ n, Zm[ m ] ] += 1;
	   		end

	   	elseif 	ind[ vars ]  > count1  &&  ind[ vars ]  <= count2 # update gamma
	   														 # Metropolis within Gibbs
            
            gam = rand_gamma( shapeGamma, scaleGamma )       # proposal
            tmp1 = logPLZGamma( Snkr, Snk, gam, NK, NKR, R * gam ) - logPLZGamma( Snkr, Snk, GAMMA, NK, NKR, RGAMMA );
	   		tmp2 = logGamma( gam, shapeGamma,scaleGamma ) - logGamma( GAMMA, shapeGamma, scaleGamma );

	   		tmp3 = kernelMH( GAMMA, gam, vFactorGamma );   
	   		 
	   		test  = tmp1 + tmp2 + tmp3;	

			if  log( rand() ) <= test  
				GAMMA = gam;
				RGAMMA = R * GAMMA;	 
				gammaAccRate += 1;  
			end

    	else 											  	 
			ALPHA;
    	end
    end
    logP[ iter ]  =  modelLikelihood( Snkr, Snk, GAMMA, NK, NKR, RGAMMA, Zm, M, MK, K, ALPHA,shapeGamma, shapeAlpha, scaleGamma, scaleAlpha ) 
    tmp1 = logP[ iter ];

    if bwritecsv				    # save data
    	writecsv( fidLogP, tmp1 );
		writecsv( fidALPHA, ALPHA );
		writecsv( fidGAMMA, GAMMA );
		writecsv( fidZm, Zm);		
	end
end

if bwritecsv
	close( fidZm );
	close( fidALPHA );
	close( fidGAMMA );
	close( fidLogP );
end


Model.Zm 	= Zm;
Model.GAMMA = GAMMA;


return gammaAccRate/maxIter*100, logP;

end


# ------------------------------------------------------------------
# computeGa()
# ------------------------------------------------------------------

function computeGa( X, lX, t )

  lT = lX - t;
  sum = 0;
  mu = mean( X );

  for i = 1 : lT
  	sum += ( X[ i ] - mu )  * ( X[ i  + t ] - mu );
  end

  return  sum / lX;

end

# ------------------------------------------------------------------
# computeEstimator()
# ------------------------------------------------------------------

function computeEstimator( Ga, ga, mf )

    sum = 0.0;  
    for i = 1 : mf 
    	sum += Ga[ i ];
    end
	sum  *= 2;
    sum -= ga[ 1 ];

    return sum;   
end

# ------------------------------------------------------------------
# estimateVariance()
# ------------------------------------------------------------------

function estimateVariance( X )

    ga = zeros( size( X ) );
    Ga = zeros( size( X ) );
    GaM = zeros( size( X ) );
    
	mf = 0;
    lX = length( X );
	for t = 1 : lX
		ga[ t ] = computeGa( X, lX, t );
	end

	for m = 1 : lX
		Ga[ m ] = ga[ 2 * m ] + ga[ 2 * m + 1 ];
		if Ga[ m ] < 0
	    	mf = m - 1; # m must be > 1!
	    	break;
		end
	end

   ipse = computeEstimator( Ga, ga, mf );  # IPSE


   GaM[ 1 ] = Ga[ 1 ];

   for m = 2 :  lX
   		if( m < mf )
			if ( GaM[ m - 1 ] < Ga[ m ] )
                GaM[ m ] = GaM[ m - 1 ];
            else 
                GaM[ m ] = Ga[ m ];
            end
        else
          GaM[ m ] = 0;  
        end
   end
 
   imse = computeEstimator( GaM, ga, mf ); # IPSE

    return ipse, imse;

end


# ------------------------------------------------------------------
# Function calls
# ------------------------------------------------------------------

fileName = "output_set_2_label_5_recoded_Likert_3.csv";
fid = open( fileName, "r");
Lnm = readcsv( fid, Int64 );
close( fid );

seed 			= int64(time_ns());
BURNIN 			= 50000;
maxIter 		= 50000;
EXAlpha 		= 1;					# prior mean alpha
VXAlpha 		= .1;					# prior variance alpha	
EXGamma 		= 1;					# prior mean gamma
VXGamma 		= 1;					# prior variance gamma
scaleGamma 		= VXGamma/EXGamma;
shapeGamma 		= EXGamma/scaleGamma; 
scaleAlpha 		= VXAlpha/EXAlpha;
shapeAlpha 		= EXAlpha/scaleGamma;
vFactorAlpha 	= 3;
vFactorGamma 	= 2;

N = 76;
M = 51;
K = 3;
R = 3;
ALPHA = 1.0;
GAMMA = 1.0;

Par = gsParameters( seed, BURNIN, maxIter, shapeAlpha, scaleAlpha, shapeGamma, scaleGamma, vFactorAlpha, vFactorGamma );
Model = gsModel( N, M, K, R, ALPHA, GAMMA, rand( int64( 1 : K ), M ) );



gammaAccRate, logP = gibbsSampler( Lnm, Model, Par, true, false, "" ); 


fileName = "logP.csv";
fid = open( fileName, "w");
writecsv( fid, logP' );
close( fid );

Par.seed += 1;
gammaAccRate, logP = gibbsSampler( Lnm, Model, Par, false, true, "iterations" ); 

ipse, imse = estimateVariance( logP )

fileName = "logP2.csv";
fid = open( fileName, "w");
writecsv( fid, logP' );
close( fid );


x = zeros(Float64, 1, 10000);
fid = open( "test_gammarnd.csv", "w")
for i = 1 : 10000
x[ i ] = rand_gamma(shapeGamma, scaleGamma)
end
writecsv( fid, x' );
close( fid )


