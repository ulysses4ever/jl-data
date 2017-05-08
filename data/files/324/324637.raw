fileName = "../data/local/output_set_2_label_1.csv";
outFileName3 = "../data/local/output_set_2_label_1_recoded_Likert_3.csv";
outFileName7 = "../data/local/output_set_2_label_1_recoded_Likert_7.csv";

recode = false;

fid = open( fileName, "r");
P = readcsv( fid, Int64 );
close( fid );

P = P';

if recode  
	sz = size( P );
	L = zeros( Int64, size( P) );

	n = 1;
	for n = 1 : sz[ 1 ]
		for m = 1 : sz[ 2 ]

			if P[ n,  m ] > 4
       			L[ n, m ] = 3;
    		elseif P[ n, m ] == 4
       			L[ n, m ] = 2;
			elseif ( P[ n, m ] > 0 ) &&  ( P[ n, m ] < 4 )	
       			L[ n, m ] = 1;
			else
				L[ n, m ] = 0;
			end
		end
	end
	fid = open( outFileName3, "w");
	P = writecsv( fid, L );
	close( fid );
else

	L = P;
	fid = open( outFileName7, "w");
	P = writecsv( fid, L );
	close( fid );

end




