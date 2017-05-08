function labelSwitching( fileNamePrefix::String, K::Int64 )

	@printf( "\n------------------------------------------");
	@printf( "\nChecking for label switching ...");


	fid = open( string(fileNamePrefix, "_Zm.csv" ), "r" );
	Zm = readcsv( fid );
	close( fid );

	fid = open( string(fileNamePrefix, "_logP.csv" ), "r" );
	logP = readcsv( fid );
	close( fid );

	fid = open( string(fileNamePrefix, "_subsampled_Zm.csv" ), "r" );
	subZm = readcsv( fid );
	close( fid );

	ind = indmax( logP );
	logP = 0;
	Z0 = Zm[ ind, : ] # reference

	rowsSubZm, colsSubZm = size( subZm );

	ZmNew = zeros( size( subZm ) );

	nPermK = factorial( K  ); # K = 3 for our model
	P = zeros( Int64, nPermK, K )
	for per = 1 : nPermK
		P[ per, : ] = nthperm( [ 1 : K ], per )
	end

	dist = zeros( 1, nPermK );
	p = 0;
	Q = zeros( Int64, 1, nPermK );
	S = zeros( Int64, 1, colsSubZm );
	for row = 1 : rowsSubZm
		S = subZm[ row, : ];
    	if true          		# use brute force matchinh for K = 3 ;
    							# could use simulated annealing otherwise (larger K)
			for p = 1 : nPermK
		    	Q = P[ p, : ]
				dist[ p ] = sum( int( Z0 .!= Q[ S ] ) );
				# @printf "\n %d %d " p dist[ p ] 
			end
			id = indmin( dist );
			Q = P[ id, : ]
			ZmNew[ row, : ] = Q[ S ]; 
		end
	end

	fid = open( string(fileNamePrefix, "_subsampled_ZmNew.csv" ), "w" );
	writecsv( fid, ZmNew );
	close( fid );

	end