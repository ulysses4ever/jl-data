function subsampleChain( fileNamePrefix::String, divide::Int64 )


	@printf( "\n------------------------------------------");
	@printf( "\nSampling ...");


	fid = open( string(fileNamePrefix, "_GAMMA.csv" ), "r" );
	GAMMA = readcsv( fid );
	close( fid );

	fid = open( string(fileNamePrefix, "_Zm.csv" ), "r" );
	Zm = readcsv( fid );
	close( fid );

	rowsGAMMA, colsGAMMA = size( GAMMA );
	rowsZm, colsZm = size( Zm );

	nSamples = int( floor( rowsGAMMA / divide ) );
	ind = [ 1 : divide : rowsGAMMA ];

	if nSamples > 0 
		newGAMMA = zeros( Float64, nSamples, colsGAMMA )
		newZm = zeros( Int64, nSamples, colsZm )
		newGAMMA = GAMMA[ ind, : ];
		newZm = Zm[ ind, : ];
	else
		error("subsampleChain(): the resulting number of samples must be greater than zero.")
	end	

	fid = open( string(fileNamePrefix, "_subsampled_GAMMA.csv" ), "w" );
	writecsv( fid, newGAMMA );
	close( fid );

	fid = open( string(fileNamePrefix, "_subsampled_Zm.csv" ), "w" );
	writecsv( fid, newZm );
	close( fid );


	return size( newGAMMA ), size( newZm );

end