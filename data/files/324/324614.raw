fileNamePrefix = "../data/nonlocal/non_local_output_set_2_label_1_recoded_Likert_3pt_iterations"


fid = open( string(fileNamePrefix, "Header.csv" ), "r" );
H = readcsv( fid )
close( fid ) 

N = int( H[ 1 ] );
M = int( H[ 2 ] );
K = int( H[ 3 ] );
R = int( H[ 4 ] );
BURNIN = int( H[ 5 ] );  # not used
MAXITER = int( H[ 6 ] ); # not used


fid = open( string(fileNamePrefix, "logP.csv" ), "r" );
logP = readcsv( fid );
close( fid )



fid = open( string(fileNamePrefix, "Zm.csv" ), "r" );
Z = readcsv( fid );
close( fid );

fid = open( string(fileNamePrefix, "GAMMA.csv" ), "r" );
G = readcsv( fid );
close( fid );

fid = open( string(fileNamePrefix, "newLnm.csv" ), "r");
Lnm = readcsv( fid, Int64 );
close( fid );

BURNIN = 2000;


# discard BURNIN samples

nR, nC = size( logP )

@printf "\nDiscarding %d burn-in samples out of %d ... " BURNIN nR;


logP2 = logP[ BURNIN : end ];
Z2 = Z[ BURNIN : end, : ];
G2 = G[ BURNIN : end ];
Znew = Z2;

# check for sampler's label switching 

@printf "\nChecking for sampler's label switching ... "

ind = indmax( logP2 );
Z0 = Z2[ ind, : ]

rowsZ2, colsZ2 = size( Z2 );

nPermK = factorial( K  ); # K = 3 for our model
P = zeros( nPermK, K )
for per = 1 : nPermK
	P[ per, : ] = nthperm( [ 1 : K ], per )
end

dist = zeros( 1, nPermK );
p = 0;
Q = zeros( 1, nPermK );
S = zeros( 1, colsZ2 );
for row = 1 : rowsZ2
	S = Z2[ row, : ];
    if row != ind           # use brute force matchinh as K = 3 is small;
    						# could use simulated annealing otherwise (larger K)
		for p = 1 : nPermK
		    Q = P[ p, : ]
			dist[ p ] = sum( int( Z0 .!= Q[ S ] ) );
			# @printf "\n %d %d " p dist[ p ] 
		end
		id = indmin( dist );
		Q = P[ id, : ]
		Znew[ row, : ] = Q[ S ]; 
	end
end

fid = open( string(fileNamePrefix, "Znew.csv" ), "w" );
writecsv( fid, Znew );
close( fid );

@printf "\nComputing mean distributions over %d samples ... " rowsZ2


# compute distributions for Zm and Gamma


meanGAMMA = mean( G2 );

Phi = zeros( Float64, rowsZ2, N, K, R );
PZmk = zeros( Float64, rowsZ2, M, K );
Snkr  = zeros( Int64,  N, K, R ); 
Snk   = zeros( Int64,  N, K );
probZ = zeros( Float64, K )
termZ  = 1.0;
totProb = 0.0;

for row = 1 : rowsZ2

	Snkr  = zeros( Int64,  N, K, R ); 
	Snk   = zeros( Int64,  N, K );


	for n = 1 :  N
		for m = 1 : M
			Snkr[ n , Znew[ row, m ] , Lnm[ n, m ] ] += 1;
			Snk[ n , Znew[ row, m ] ] += 1;
		end
	end	

    for n = 1 : N
    	for k = 1 : K
    		for r = 1 : R
    			Phi[ row, n, k, r ] = ( Snkr[ n, k, r ] + meanGAMMA ) / ( Snk[ n, k ] + R * meanGAMMA );
    		end
    	end
    end

    for m = 1 : M

    	

		totProb = 0.0;
    	for k = 1 : K

    		termZ = 1.0;
		
			for n = 1 : N

		   	   	Snkr[ n, Znew[ row, m ], Lnm[ n, m ] ] -= 1;
				Snk[ n, Znew[ row, m ] ] -= 1;

				termZ *= ( float64( Snkr[ n, k, Lnm[ n, m ] ] ) + meanGAMMA ) / ( float64( Snk[ n, k ] ) + R * meanGAMMA );

				Snkr[ n, Znew[ row, m ], Lnm[ n, m ] ] += 1;
				Snk[ n, Znew[ row, m ] ] += 1;

			end
			probZ[ k ] =  termZ;
			if termZ < 0.0
				@printf "\n%e " probZ[ k ] 
			end
			totProb += probZ[ k ];
		end

		probZ /= totProb; 
		PZmk[ row, m, : ] = probZ;
				


    end
end

meanPhi = squeeze( mean( Phi, 1 ), 1 );
meanPZmk = squeeze( mean( PZmk, 1 ), 1 );


@printf "\nSaving results ... "

fid = open( string("../data/nonlocal/non_local_output_set_2_label_1_recoded_Likert_3_pt_iterations", "meanPhi1.csv" ), "w" );
writecsv( fid, squeeze( meanPhi[ : ,1, :], 2) );
close( fid );

fid = open( string("../data/nonlocal/non_local_output_set_2_label_1_recoded_Likert_3_pt_iterations", "meanPhi2.csv" ), "w" );
writecsv( fid, squeeze( meanPhi[ : ,2, :], 2) );

close( fid );fid = open( string("../data/nonlocal/non_local_output_set_1_label_2_recoded_Likert_3_pt_iterations", "meanPhi3.csv" ), "w" );
writecsv( fid, squeeze( meanPhi[ : ,3, :], 2) );
close( fid );

fid = open( string("../data/nonlocal/non_local_output_set_2_label_1_recoded_Likert_3_pt_iterations", "meanPZmk.csv" ), "w" );
writecsv( fid, meanPZmk );
close( fid );




