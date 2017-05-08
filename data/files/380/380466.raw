

###############################################################
# Gibbs sampler for probabilistic annotator model 
# using  parallel tempering 
# Includes fully observed data matrix Lnm
# Created by Salvador Ruiz Correa 01/30/15
# Revised version 02/12/15
# TODO: Use read/write instead of readcsv/writecsv
###############################################################

type gsModel	
	N				::Int64 			# number of subjects 
	M				::Int64   			# number of tasks
	K				::Int64   			# number of topics 
	R				::Int64  			# number of Likert scale points
	ALPHA 			::Float64 			# alpha Dirichlet concentration parameter
	GAMMA 			::Array{Float64,1} 	# gamma Dirichlet concentration parameter for each temperature value
	Zm  			::Array{Int64,2} 	# Zm tasks hidden values for each temperature value
	Beta            ::Array{Float64, 1} # Set of inverse temperatures

end

type gsParameters
	seed			::Int64     		# random generator seed  
	BURNIN			::Int64
	maxIter			::Int64
	shapeAlpha 		::Float64   		# prior hiperparameter
	scaleAlpha  	::Float64   		# prior hiperparameter
	shapeGamma		::Float64   		# prior hiperparameter
	scaleGamma		::Float64   		# prior hiperparameter  
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
function logPLZGamma( Snkr, Snk, GAMMA, NK, NKR, RGAMMA, Beta ) 

Ankr = lgamma( Snkr + GAMMA )
Bnk = sum( Ankr, 3 );
Cnk = lgamma( Snk + RGAMMA );
Dnk = Bnk - Cnk;
Dn = sum( Dnk, 2 );
tmp1 = sum( Dn );
tmp2 =  NK * lgamma( RGAMMA ) - NKR  * lgamma( GAMMA ) 
tmp3 = tmp1 + tmp2;

return  tmp3 * Beta;

end

# ------------------------------------------------------------------
# logPZAlpha() - log P(Z|Alpha)
# ------------------------------------------------------------------
function logPZAlpha( K ) 

return 1.0/K;

end

# -----------------------------------------------------------------------------------
# evalLogP()
# -----------------------------------------------------------------------------------
function evalLogP(  Lnm::Array{Int64,2}, 
				   	Model::gsModel, 
				   	Par::gsParameters,
				   	state,
				   	t ) 

N = Model.N;
M = Model.M;
K = Model.K;
R = Model.R;
GAMMA = Model.GAMMA[ t ];
ALPHA = Model.ALPHA;
Beta = Model.Beta[ t ];

MK = M * K;
NK = N * K;
NKR = NK * R;
KR = K * R;

Snkr  = zeros( Int64, N, K, R ); 
Snk   = zeros( Int64, N, K );

for n = 1 :  N
	for m = 1 : M
		Snkr[ n , Model.Zm[ m, state ] , Lnm[ n, m ] ] += 1;
		Snk[ n , Model.Zm[ m, state ] ] += 1;
	end
end	


return modelLikelihood( Snkr, Snk, GAMMA, NK, NKR, R * GAMMA, 
					    Model.Zm[ :, t  ], M, MK, K, ALPHA, shapeGamma, shapeAlpha, scaleGamma, scaleAlpha,
					    Beta );
end


# -----------------------------------------------------------------------------------
# modelLikelihood() - log P(L|Z,Gamma) + log P(Z|Alpha) + log p(Alpha) + log P(Gamma)
# -----------------------------------------------------------------------------------
function modelLikelihood( Snkr, Snk, GAMMA, NK, NKR, RGAMMA, Zm, M, MK, K, ALPHA, shapeGamma, shapeAlpha, scaleGamma, scaleAlpha, Beta ) 

	tmp1 = logPLZGamma( Snkr, Snk, GAMMA, NK, NKR, RGAMMA, Beta );
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
						L::Array{Int64,2},
						idL::Array{Int64,1},
						Model::gsModel, 
						Par::gsParameters,
						initState::Bool,
						betaIndex ) 


scaleGamma 		= Par.scaleGamma;
scaleAlpha 		= Par.scaleAlpha;
shapeGamma 		= Par.shapeGamma;
shapeAlpha 		= Par.shapeAlpha;
vFactorGamma 	= Par.vFactorGamma;

N 				= Model.N;
M 				= Model.M;
K 				= Model.K;
R 				= Model.R;
Zm 				= Model.Zm;
ALPHA 			= Model.ALPHA;
GAMMA 			= Model.GAMMA[ betaIndex ];
Beta 			= Model.Beta[ betaIndex ];
Zm              = Model.Zm[ :, betaIndex ]

logP = 1.0;


# Initialize arrays

count0 = M * N;
count1 = count0 + M
count2 = count1 + 1;
count3 = count2 + 1;

Snkr  = zeros( Int64, N, K, R ); 
Snk   = zeros( Int64, N, K );
ind = zeros( 1, count3 ); 

# Set markov chain state

if initState == true
	Zm = rand( int64( 1 : K ), M );
	GAMMA = rand_gamma( shapeGamma, scaleGamma);
	for i = 1 : length( idL )
		Lnm[ idL[ i ] ] = rand( int64( 1 : R ) );
	end
end

MK = M * K;
NK = N * K;
NKR = NK * R;
KR = K * R;
RGAMMA = R * GAMMA;

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
ind = zeros( Int64, 1, count3 );


for iter = 1 : 1

	rand!( 1 : count3, ind );  

    for vars = 1 : count3  # random scan loop


		if ind[ vars ] <= count0  # update Lnm

   		n, m = ind2sub( size( Lnm ), ind[ vars ] );

    	if L[ n, m ] == 1

    	    Snkr[ n, Zm[ m ], Lnm[ n, m ] ] -= 1;
    	    Snk[ n, Zm[ m ] ] -= 1;

			totProb = 0.;
    	    for r = 1 : R
    	    	termS = ( Snkr[ n, Zm[ m ], r ] + GAMMA ) / ( Snk[ n, Zm[ m ] ] + RGAMMA );
    	    	probS[ r ] = termS;
    	    	totProb += probS[ r ];
    	    end

    	    temp = rand() * totProb;
            maxval = probS[ 1 ];
            id = 1;

            while ( temp  > maxval )             	
	            id += 1;
                maxval += probS[ id ];
            end

			Lnm[ n, m ] = id;

      	    Snkr[ n, Zm[ m ], Lnm[ n, m ] ] += 1;
    	    Snk[ n, Zm[ m ] ] += 1;
  	    
    	end

	elseif (ind[ vars ] > count0 ) && (ind[ vars ] <= count1)  # update Zm

	   		m = ind[ vars ] - count0;
	   		
	   		for n = 1 : N	
	   	    	Snkr[ n, Zm[ m ], Lnm[ n, m ] ] -= 1;
				Snk[ n, Zm[ m ] ] -= 1;
			end

			totProb = 0.;
			for k = 1 : K
				termZ = 1.;
				for n = 1 : N
					termZ *= ( float64( Snkr[ n, k, Lnm[ n, m ] ] ) + GAMMA ) / ( float64( Snk[ n, k ] ) + RGAMMA );
				end

				probZ[ k ] =  termZ ^ Beta;
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
            tmp1 = logPLZGamma( Snkr, Snk, gam, NK, NKR, R * gam, Beta ) - logPLZGamma( Snkr, Snk, GAMMA, NK, NKR, RGAMMA, Beta );
	   		tmp2 = logGamma( gam, shapeGamma,scaleGamma ) - logGamma( GAMMA, shapeGamma, scaleGamma );

	   		tmp3 = kernelMH( GAMMA, gam, vFactorGamma );   
	   		 
	   		test  = tmp1 + tmp2 + tmp3;	

			if  log( rand() ) <= test  
			#if rand() < min( 1, exp( test ) )
				GAMMA = gam;
				RGAMMA = R * GAMMA;	  
			end

    	else 											  	 
			ALPHA;
    	end
    end
    logP =  modelLikelihood( Snkr, Snk, GAMMA, NK, NKR, RGAMMA, Zm, M, MK, K, ALPHA,shapeGamma, shapeAlpha, scaleGamma, scaleAlpha, Beta ) 

end


Model.Zm[ :, betaIndex ] = Zm;
Model.GAMMA[ betaIndex ]  = GAMMA;


return logP;

end



# ------------------------------------------------------------------
# kernelPT() 
# ------------------------------------------------------------------
function kernelPT( 	logP::Array{Float64,2},
					Lnm::Array{Int64,2}, 
				   	Model::gsModel, 
				   	Par::gsParameters,
				   	iter,
				   	t ) 



tt 		= evalLogP( Lnm, Model, Par, t, t ); 		# state model t evaluated at  model t
tptp 	= evalLogP( Lnm, Model, Par, t + 1, t + 1); # state model t + 1 evaluated at  model t
ttp 	= evalLogP( Lnm, Model, Par, t, t + 1);     # state model t evaluated at  model t + 1
tpt 	= evalLogP( Lnm, Model, Par, t + 1, t );    # state model t + 1  evaluated at  model t


return  rand()  <  min( 1, exp( ttp + tpt - tptp - tt ) );

@printf "%f %f %f %f\n " ttp tpt  tptp  tt 


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
# gsPTPar
# ------------------------------------------------------------------

type gsPTPar

seed 			::Int64
BURNIN 			::Int64
maxIter 		::Int64

end

# ------------------------------------------------------------------
# gsPTModelPar
# ------------------------------------------------------------------

type gsPTModelPar

EXAlpha 		::Float64		# prior mean alpha
VXAlpha 		::Float64		# prior variance alpha	
EXGamma 		::Float64		# prior mean gamma
VXGamma 		::Float64		# prior variance gamma
scaleGamma		::Float64		
shapeGamma		::Float64		 
scaleAlpha		::Float64 		
shapeAlpha 		::Float64		
vFactorGamma	::Float64 	

end

# ------------------------------------------------------------------
# gsPTModel
# ------------------------------------------------------------------

type gsPTModel

N 				::Int64
M 				::Int64
K 				::Int64
R 				::Int64
T 				::Int64
r 				::Float64
ALPHA 			::Float64
GAMMA 			::Array{Float64,1}
Zm              ::Array{Int64} 
Lnm 			::Array{Int64}

end

# ------------------------------------------------------------------
# printVer()
# ------------------------------------------------------------------

function printVer( outStream, bBurnIn  )

@printf( outStream, "\n-- Annotator modeling v 1.0 --" );
@printf( outStream, "\n" );
@printf( outStream, "\nFull Lnm data matrix." );
@printf( outStream, "\nUsing parallel tempering." );
if bBurnIn
	@printf( outStream, "\nBurnin mode." );
else
	@printf( outStream, "\nSampling mode." );
end

end

# ------------------------------------------------------------------
# printgsPTPar()
# ------------------------------------------------------------------

function printgsPTPar( outStream , Par::gsPTPar  )

@printf( "\n------------------------------------------");
@printf( "\n-gsPTPar-");
@printf( "\nSEED: %d", Par.seed );
@printf( "\nBURNIN: %d", Par.BURNIN );
@printf( "\nMAXITER: %d", Par.maxIter );

end

# ------------------------------------------------------------------
# writegsPTPar()
# ------------------------------------------------------------------

function writegsPTPar( Par::gsPTPar , fileName::String  )

    try 
		fid = open( fileName, "w" );
	catch e
		println( e )
	end	

	write( fid, Par.seed );
	write( fid, Par.BURNIN );
	write( fid, Par.maxIter );

	close( fid );
end

# ------------------------------------------------------------------
# readgsPTPar()
# ------------------------------------------------------------------

function readgsPTPar( Par::gsPTPar , fileName::String  )

    try 
		fid = open( fileName, "r" );
	catch e
		println( e )
	end	

	close( fid );

	Par.seed = read( fid, Int64, 1 );
	Par.BURNIN = read( fid, Int64, 1 );
	Par.maxIter = read( fid, Int64, 1 );

end


function printgsPTModelPar( outStream, modelPar::gsPTModelPar   )

@printf( "\n------------------------------------------");
@printf( "\n-gsPTModelPar-");
@printf( outStream,"\nE(alpha): %f", modelPar.EXAlpha );
@printf( outStream,"\nVar(alpha) %f", modelPar.VXAlpha );
@printf( outStream,"\nE(gamma): %f", modelPar.VXGamma );
@printf( outStream,"\nVar(gamma): %f", modelPar.VXGamma );
@printf( outStream,"\nFactor(gamma): %f", modelPar.vFactorGamma );
@printf( outStream,"\nscaleAlpha: %f", modelPar.scaleAlpha );
@printf( outStream,"\nshapeAlpha %f", modelPar.shapeAlpha );
@printf( outStream,"\nscaleGamma: %f", modelPar.scaleGamma );
@printf( outStream,"\nshapeGamma %f", modelPar.shapeGamma );

end

# ------------------------------------------------------------------
# writegsPTPar()
# ------------------------------------------------------------------

function writegsPTPar( modelPar::gsPTModelPar , fileName::String  )

    try 
		fid = open( fileName, "w" );
	catch e
		println( e )
	end	

	write( fid, modelPar.EXAlpha );
	write( fid, modelPar.VXAlpha );	
	write( fid, modelPar.EXGamma );
	write( fid, modelPar.VXGamma );	
	write( fid, modelPar.vFactorGamma );
	write( fid, modelPar.scaleAlpha );	
	write( fid, modelPar.shapeAlpha );
	write( fid, modelPar.scaleGamma );	
	write( fid, modelPar.shapeGamma  );

	close( fid );
end

# ------------------------------------------------------------------
# eadgsPTPar()
# ------------------------------------------------------------------

function readgsPTPar( modelPar::gsPTModelPar , fileName::String  )

    try 
		fid = open( fileName, "r" );
	catch e
		println( e )
	end	

	modelPar.EXAlpha = read( fid, Float64, 1 );
	modelPar.VXAlpha = read( fid, Float64, 1 );
	modelPar.EXGamma = read( fid, Float64, 1 );
	modelPar.VXGamma = read( fid, Float64, 1 );
	modelPar.VFactorGamma = read( fid, Float64, 1 );
	modelPar.shapeAlpha = read( fid, Float64, 1 );
	modelPar.scaleGamma = read( fid, Float64, 1 );
	modelPar.shapeGamma  = read( fid, Float64, 1 );

	close( fid );

end

# ------------------------------------------------------------------
# printgsPTModel()
# ------------------------------------------------------------------

function printgsPTModel( outStream , Model::gsPTModel   )

@printf( "\n------------------------------------------");
@printf( "\n-gsPTModel-");
@printf( outStream, "\nN: %d", Model.N );
@printf( outStream, "\nM: %d", Model.M );
@printf( outStream, "\nK: %d", Model.K );
@printf( outStream, "\nR: %d", Model.R );
@printf( outStream, "\nT: %d", Model.T );
@printf( outStream, "\nr: %f", Model.r );
@printf( outStream, "\nALPHA: %f", Model.ALPHA );

@printf( outStream, "\nLnm, GAMMA and Zmk arrays are not being printed out." );

end

# ------------------------------------------------------------------
# writegsPTPar()
# ------------------------------------------------------------------

function writegsPTPar( Model::gsPTModel , fileName::String  )

    try 
		fid = open( fileName, "w" );
	catch e
		println( e )
	end	

	write( fid, Model.N );
	write( fid, Model.M );	
	write( fid, Model.K );
	write( fid, Model.R );	
	write( fid, Model.T );
	write( fid, Model.r );	
	write( fid, Model.ALPHA  );	
	write( fid, Model.GAMMA );
	write( fid, Model.Lnm, length( Model.Lmn ) );	
	write( fid, Model.Zm, length( Model.Zm )  );

	close( fid );
end

# ------------------------------------------------------------------
# readgsPTPar()
# ------------------------------------------------------------------

function readgsPTPar( Model::gsPTModel , fileName::String  )

    try 
		fid = open( fileName, "r" );
	catch e
		println( e )
	end	

	Model.N = read( fid, Int64, 1 );
	Model.M = read( fid, Int64, 1 );
	Model.K = read( fid, Int64, 1 );
	Model.R = read( fid, Int64, 1 );
	Model.T = read( fid, Int64, 1 );
	Model.r = read( fid, Float64, 1 );
	Model.ALPHA = read( fid, Float64, 1 );
	Model.GAMMA = read( fid, Float64, 1 );
	Model.Lnm = read( fid, Float64, Model.N * Model.M );
	Model.Zm = read( fid, Float64, Model.M );	

	close( fid );


end

# ------------------------------------------------------------------
# gsParallelTempering()
# ------------------------------------------------------------------

function gsParallelTempering( L::Array{Int64,2}, idL::Array{Int64,1}, pTM::gsPTModel, pTMPar::gsPTModelPar, pTPar::gsPTPar, bInit::Bool, bWrite::Bool, fileNamePrefix::String, bVerbose::Bool )


exchangeRate = 0;   # PT chain exchange rate

# Set random seed
srand( pTPar.seed );

# Set data matrix
Lnm = pTM.Lnm;

# open output data streams
if bWrite

		fidZm 		= open( string(fileNamePrefix, "_Zm.csv" ), "w" );
		fidGAMMA 	= open( string(fileNamePrefix, "_GAMMA.csv" ), "w" );
end


Par = gsParameters( pTPar.seed, 
					pTPar.BURNIN, 
					pTPar.maxIter, 
					pTMPar.shapeAlpha, 
					pTMPar.scaleAlpha, 
					pTMPar.shapeGamma, 
					pTMPar.scaleGamma, 
					pTMPar.vFactorGamma );


# Initialize inverse temperature parameters 
Beta = zeros( Float64, pTM.T );
for t = 0 : pTM.T - 1
	Beta[ t + 1 ] = 1.0 / pTM.r^t;
end



if bInit							# random state initialization					
	Model = gsModel(	pTM.N, 
						pTM.M, 
						pTM.K, 
						pTM.R, 
						1.0, 
						rand( Float64, T ),
						rand( int64( 1 : K ), M, T ),
						Beta );
for t = 1 : T 
	gibbsSampler( Lnm, L, idL, Model, Par, true, t )
end

else
	Model = gsModel(	pTM.N, 
						pTM.M, 
						pTM.K, 
						pTM.R, 
						1.0, 
						pTM.GAMMA,
						pTM.Zm,
						Beta );
end


# Sample using parallel tempering
SWAP_PROB = 0.5;

logP = zeros( Float64, pTPar.maxIter, T );
auxZm = zeros( Int64, M );
swap = false;
auxGAMMA = 0.0;
iter = 1;
count = 0;
it = 0;

# Parallel tempering loop
for iter =  1 : pTPar.maxIter
	if rand() < SWAP_PROB || iter == 1  	# Update all states
		it +=1
		for t = 1 : T
			logP[ it, t ] = gibbsSampler( Lnm, L, idL, Model, Par, false, t );	
		end

		if bWrite				    # save data
			writecsv( fidGAMMA, Model.GAMMA[ 1 ] );
			writecsv( fidZm, Model.Zm[ :, 1]');		
		end

	else # Propose# to exchange two states
        
		t = rand( 1 : T - 1 )
		swap = kernelPT( logP, Lnm, Model, Par, iter, t );
		

		if swap == true
			if bVerbose 
			    if t == 1
					count += 1;
				end
				@printf "%d %d<->%d %d\n" iter t t+1 count
			end	
			auxZm 	 = Model.Zm[ :, t ];
			auxGAMMA = Model.GAMMA[ t ];
			Model.Zm[ :, t ] = Model.Zm[ :, t + 1 ];
			Model.GAMMA[ t ] = Model.GAMMA[ t + 1 ];
			Model.Zm[ :, t + 1 ] = auxZm;
			Model.GAMMA[ t + 1 ] = auxGAMMA;
			exchangeRate += 1;
		end
	end
end

if bWrite
	close( fidZm );
	close( fidGAMMA );
end

fid = open( string(fileNamePrefix, "_logP.csv" ), "w" );
writecsv( fid, logP[ 1 : it, 1] );
close( fid );

return exchangeRate, Model.GAMMA, Model.Zm, Lnm;

end

# ------------------------------------------------------------------
# gsmain()
# ------------------------------------------------------------------

function gsmain( pTPar::gsPTPar , pTMPar::gsPTModelPar , pTM::gsPTModel, MAXITER::Int64, bBurnIn::Bool, fileNameTestPrefix::String, fileNamePrefix::String, bVerbose::Bool )


idL = find( pTM.Lnm .== 0 );
L = zeros( Int, size( pTM.Lnm ) );
L[ idL ] = 1;


printVer( STDOUT, bBurnIn );
printgsPTPar( STDOUT , pTPar );
printgsPTModelPar( STDOUT, pTMPar  );
printgsPTModel( STDOUT, pTM  );

if bBurnIn # compute BURNINN samples
	
	@printf( "\n------------------------------------------");
	@printf( STDOUT, "\nBurnin ..." );
	exchangeRate, GAMMA, Zm, Lnm = gsParallelTempering( L, idL, pTM, pTMPar, pTPar, true, true, fileNameTestPrefix, bVerbose );

	fid = open( string(fileNameTestPrefix, "_logP.csv" ), "r" );
	logP = readcsv( fid );
	close( fid );

	#show(size(logP))

	# compute and save variance estimates: IPSE, IMSE

	@printf( "\n------------------------------------------");
	@printf( "\n-Variance estimates-");
	

	ipse, imse = estimateVariance( logP[ pTPar.BURNIN : end ] );
	tmp = float64(exchangeRate)*100.0/float64(pTPar.maxIter);
	@printf "\nIPSE(logP): %f; IMSE(logP): %f; Exchenge rate: %f" ipse imse tmp;

	fid = open( string(fileNameTestPrefix, "_GAMMA.csv" ), "r" );
	Gamma = readcsv( fid );
	close( fid );

	ipseGamma, imseGamma = estimateVariance( Gamma[ pTPar.BURNIN : end ] );
	@printf "\nIPSE (GAMMA) : %f; IMSE (GAMMA) : %f" ipseGamma imseGamma;


	# save chain state

	fid = open( string(fileNameTestPrefix, "_lastZm.csv" ), "w" );
	writecsv( fid, Zm );
	close( fid );

	fid = open( string(fileNameTestPrefix, "_lastGAMMA.csv" ), "w" );
	writecsv( fid, GAMMA );
	close( fid );

	fid = open( string(fileNameTestPrefix, "_lastLnm.csv" ), "w" );
	writecsv( fid, Lnm );
	close( fid );

else

	@printf( "\n------------------------------------------");
	@printf( STDOUT, "\nComputing samples ..." );
	# read previous chain state

	fid = open( string(fileNameTestPrefix, "_lastGAMMA.csv" ), "r" );
	GAMMA = readcsv( fid, Float64 ); # Here GAMMA is Array{Float64, 2} due to readcsv
	close( fid );

	fid = open( string(fileNameTestPrefix, "_lastZm.csv" ), "r" );
	Zm = readcsv( fid,  Int64 ); 
	close( fid );

	fid = open( string(fileNameTestPrefix, "_lastLnm.csv" ), "r" );
	Lnm = readcsv( fid,  Int64 ); 
	close( fid );
	pTM.Lnm = Lnm;


	pTM.Zm = Zm;	
	for g = 1 : length( GAMMA )
		pTM.GAMMA[ g ] = GAMMA[ g ];# Here GAMMA is Array{Float64, 2} this is why we need a for loop
	end

	pTPar.maxIter = MAXITER;	
	exchangeRate, GAMMA, Zm, LL = gsParallelTempering( L, idL, pTM, pTMPar, pTPar, false, true, fileNamePrefix, bVerbose );

	#fid = open( string(fileNamePrefix, "_logP.csv" ), "r" );
	#logP = readcsv( fid );
	#close( fid );

	# compute and save variance estimates: IPSE, IMSE

	#@printf( "\n------------------------------------------");
	#@printf( "\n-Variance estimates-");

	#ipse, imse = estimateVariance( logP );
	#tmp = float64(exchangeRate)*100.0/float64(MAXITER);
	#@printf "\nIPSE(logP): %f; IMSE(logP): %f; Exchenge rate: %f" ipse imse tmp;

	#fid = open( string(fileNamePrefix, "_GAMMA.csv" ), "r" );
	#Gamma = readcsv( fid );
	#close( fid );

	#ipseGamma, imseGamma = estimateVariance( Gamma );
	#@printf "\nIPSE (GAMMA) : %f; IMSE (GAMMA) : %f" ipseGamma imseGamma;
	#@printf( "\n..........................................");
 
end

return;

end





