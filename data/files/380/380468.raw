fileName = "../data/abcd/abcd12.csv";
outFileName = "../data/abcd/abcd12_Likert_3.csv";


fid = open( fileName, "r");
P = readcsv( fid, Int64 );
close( fid );

 
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


fid = open( outFileName, "w");
P = writecsv( fid, L );
close( fid );

