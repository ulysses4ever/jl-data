function computePStatistics( fileName::String, fileNamePrefix::String, K::Int64, R::Int64 )


	@printf( "\n------------------------------------------");
	@printf( "\nComputing statistics ...");

	fid = open( string(fileNameTestPrefix, "_lastLnm.csv" ), "r" );
	Lnm = readcsv( fid,  Int64 ); 
	close( fid );

	N, M = size( Lnm );
	
	fid = open( string(fileNamePrefix, "_subsampled_ZmNew.csv" ), "r" );
	Zm = readcsv( fid );
	close( fid );

	rowsZm, colsZm = size( Zm );

	fid = open( string(fileNamePrefix, "_subsampled_GAMMA.csv" ), "r" );
	GAMMA = readcsv( fid );
	close( fid );

	@printf( " %d samples", rowsZm);

	meanGAMMA = mean( GAMMA );

	Phi = zeros( Float64, rowsZm, N, K, R );
	PZmk = zeros( Float64, rowsZm, M, K );
	Snkr  = zeros( Int64,  N, K, R ); 
	Snk   = zeros( Int64,  N, K );
	probZ = zeros( Float64, K )
	termZ  = 1.0;
	totProb = 0.0;

	for row = 1 : rowsZm

		Snkr  = zeros( Int64,  N, K, R ); 
		Snk   = zeros( Int64,  N, K );


		for n = 1 :  N
			for m = 1 : M
				Snkr[ n , Zm[ row, m ] , Lnm[ n, m ] ] += 1;
				Snk[ n , Zm[ row, m ] ] += 1;
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

			   	   	Snkr[ n, Zm[ row, m ], Lnm[ n, m ] ] -= 1;
					Snk[ n, Zm[ row, m ] ] -= 1;

					termZ *= ( float64( Snkr[ n, k, Lnm[ n, m ] ] ) + meanGAMMA ) / ( float64( Snk[ n, k ] ) + R * meanGAMMA );

					Snkr[ n, Zm[ row, m ], Lnm[ n, m ] ] += 1;
					Snk[ n, Zm[ row, m ] ] += 1;

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

	fid = open( string( fileNamePrefix, "_meanPhi1.csv" ), "w" );
	writecsv( fid, squeeze( meanPhi[ : ,1, :], 2) );
	close( fid );

	fid = open( string( fileNamePrefix, "_meanPhi2.csv" ), "w" );
	writecsv( fid, squeeze( meanPhi[ : ,2, :], 2) );

	close( fid );fid = open( string( fileNamePrefix, "_meanPhi3.csv" ), "w" );
	writecsv( fid, squeeze( meanPhi[ : ,3, :], 2) );
	close( fid );

	fid = open( string( fileNamePrefix, "_meanPZmk.csv" ), "w" );
	writecsv( fid, meanPZmk );
	close( fid );

	fid = open( string( fileNamePrefix, "_allPZmk.csv" ), "w" );
	write( fid, PZmk );
	close( fid );



end