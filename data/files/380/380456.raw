# ------------------------------------------------------------------
# Funcion calls
# ------------------------------------------------------------------

include("createDirTree.jl")
include("gspPT.jl");
include("subsampleChain.jl");
include("labelSwitching.jl");
include("computepStatistics.jl")


fileNameBase = 			"../data/abcd/abcd12_Likert_3/" #  directory where data is located
fileName = 				"../data/abcd/abcd12_Likert_3.csv"; # Lnm data
fileNameTestPrefix = 	"../data/abcd/abcd12_Likert_3/output/abcd12_Likert_3_burnin";
# BURNIN data file
fileNamePrefix = 		"../data/abcd/abcd12_Likert_3/output/abcd12_Likert_3_pt_iterations"; 
# output files prefix 


bCreate = false;
bBurnIn = true;
bComputeVariance = false;
bWrite = true;  	# save data
bVerbose = false;	# show some intermediate calculaions

if bCreate
	createDirTree( fileNameBase );
end	


# input data matrix
fid = open( fileName, "r");
Lnm = readcsv( fid, Int64 );
close( fid );

# set algorithm parameters
seed 			= int64(time_ns());
MAXITER 		= 20000;
BURNIN 			= 5000;
maxIter 		= 20000;
pTPar 			= gsPTPar( seed, BURNIN, maxIter );

EXAlpha 		= 1;					# prior mean alpha
VXAlpha 		= 1;					# prior variance alpha	
EXGamma 		= 1;					# prior mean gamma
VXGamma 		= 1;					# prior variance gamma
scaleGamma 		= VXGamma/EXGamma;
shapeGamma 		= EXGamma/scaleGamma; 
scaleAlpha 		= VXAlpha/EXAlpha;
shapeAlpha 		= EXAlpha/scaleGamma;
vFactorGamma 	= 2;
pTMPar = gsPTModelPar( EXAlpha, VXAlpha, EXGamma, VXGamma, scaleGamma, shapeGamma, scaleAlpha, shapeAlpha, vFactorGamma) 

N,M = size(Lnm);
K = 3;  	# number of topics
R = 3;  	# number of Likert points
T = 8;		# number of PT chains
r = 1.05; #1.2; 	    #1.001;  # Beta = 1/r^t, t = 1,2,...,T
pTM = gsPTModel(N, M, K, R, T, r, 1.0, rand( Float64, T ), zeros( Float64, M) , Lnm );


# MCMC sampler call
gsmain( pTPar , pTMPar , pTM , MAXITER, bBurnIn, fileNameTestPrefix, fileNamePrefix, bVerbose );

if ~bBurnIn

	if bComputeVariance

		# compute and save variance estimates: IPSE, IMSE

		@printf( "\n------------------------------------------");
		@printf( "\n-Variance estimates-");

		ipse, imse = estimateVariance( logP );
		tmp = float64(exchangeRate)*100.0/float64(MAXITER);
		@printf "\nIPSE(logP): %f; IMSE(logP): %f; Exchenge rate: %f" ipse imse tmp;

		fid = open( string(fileNamePrefix, "_GAMMA.csv" ), "r" );
		Gamma = readcsv( fid );
		close( fid );

		ipseGamma, imseGamma = estimateVariance( Gamma );
		@printf "\nIPSE (GAMMA) : %f; IMSE (GAMMA) : %f" ipseGamma imseGamma;
		@printf( "\n..........................................");

	end


	subsampleChain( fileNamePrefix, 4 );
	labelSwitching( fileNamePrefix, K );
	computePStatistics( fileName, fileNamePrefix, K, R );

end

