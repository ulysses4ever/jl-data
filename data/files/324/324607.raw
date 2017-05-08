# ------------------------------------------------------------------
# Funcion calls
# ------------------------------------------------------------------

include("createDirTree.jl")
include("gsPT.jl");
include("subsampleChain.jl");
include("labelSwitching.jl");
include("computeStatistics.jl")



fileNameBase = 			"../data/local/output_set_2_label_1_recoded_Likert_7"
fileName = 				"../data/local/output_set_2_label_1_recoded_Likert_7.csv"; # Lnm data
fileNameTestPrefix = 	"../data/local/output_set_2_label_1_recoded_Likert_7/output/output_set_2_label_1_recoded_Likert_7_burnin"; # BURNIN data file
fileNamePrefix = 		"../data/local/output_set_2_label_1_recoded_Likert_7/output/output_set_2_label_1_recoded_Likert_7_pt_iterations"; # output files prefix 


bCreate = false;
bBurnIn = false;
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
MAXITER 		= 100000;
BURNIN 			= 2500;
maxIter 		= 15000;
pTPar 			= gsPTPar( seed, BURNIN, maxIter );

EXAlpha 		= 1;					# prior mean alpha
VXAlpha 		= 10;					# prior variance alpha	
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
R = 7;  	# number of Likert points
T = 4;		# number of PT chains
r = 1.5 	#1.001;  # Beta = 1/r^t, t = 1,2,...,T
pTM = gsPTModel(N, M, K, R, T, r, 1.0, rand( Float64, T ), zeros( Float64, M) , Lnm );


# MCMC sampler call
gsmain( pTPar , pTMPar , pTM , MAXITER, bBurnIn, fileNameTestPrefix, fileNamePrefix, bVerbose );

if ~bBurnIn

	if bComputeVariance

		fid = open( string(fileNamePrefix, "_logP.csv" ), "r" );
		logP = readcsv( fid );
		close( fid );

		# compute and save variance estimates: IPSE, IMSE

		@printf( "\n------------------------------------------");
		@printf( "\n-Variance estimates-");

		ipse, imse = estimateVariance( logP );
		@printf "\nIPSE(logP): %f; IMSE(logP): %f" ipse imse;

		fid = open( string(fileNamePrefix, "_GAMMA.csv" ), "r" );
		Gamma = readcsv( fid );
		close( fid );

		ipseGamma, imseGamma = estimateVariance( Gamma );
		@printf "\nIPSE (GAMMA) : %f; IMSE (GAMMA) : %f" ipseGamma imseGamma;


	end

	subsampleChain( fileNamePrefix, 4 );
	labelSwitching( fileNamePrefix, K );
	computeStatistics( fileName, fileNamePrefix, K, R );

end

