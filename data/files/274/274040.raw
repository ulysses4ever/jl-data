# Cannon.jl
# Multiply matrices using the Cannon algorithm
# The usage algorthim is limited to the following conditions
# 1) The number of processors must be q^2
# 2) The processors will be arranged in a qxq grid
# 3) The A matrices on each processor must be the same size
# 4) The B matrices on each processor must be the same size
# 5) The A and B matrices must have dimensions such that Csub = Asub*Bsub is valid

using MPI
MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
csize = MPI.Comm_size(comm)

# Suppress some error messages that occur in Julia 4.0
# Julia 3.0 uses type int8 while Julia 4.0 uses Int8
# Julia will throw an error if Int8 is used in version 3.0
Int8 = int8


function cannonMultiply(A,B)
	# Multiply matrices using the Cannon algorithm
	# Return a matrix C - The resulting submatrix for this processor
	# @A the initial A submatrix on this processor
	# @B the initial B submatrix on this processor

	# Calculate the size of the processor grid
	ncols = nrows = Int8(floor(sqrt(csize)))
	if ncols != sqrt(csize)
		throw("The number of processors must be n^2")
	end

	setup=true
	C = 0
	A = cannonShift(A,true,false,setup,nrows,ncols)
	B = cannonShift(B,false,true,setup,nrows,ncols)
	setup=false
	for i=1:ncols
		C += A*B;
		A = cannonShift(A,true,false,setup,nrows,ncols)
		B = cannonShift(B,false,true,setup,nrows,ncols)
	end
	return C
end



function cannonShift(matrix,shiftLeft,shiftUp,isSetup,nrows,ncols)
	# Shift the submatrices so each processor can perform C=A*B
	# If isSetup is true we do the following:
	#   shiftLeft = True -> For the i-th row of processors, the matrix blocks are shifted (i-1) positions left
	#   shiftUp = True   -> For the j-th col of processors, the matrix blocks are shifted (j-1) positions upward
	# Otherwise we just shift by one 

	myRow = sendRow = recvRow = _getRow(rank,ncols)
	myCol = sendCol = recvCol = _getCol(rank,ncols)
	println("----- $myRow,$myCol --------")

	# Shift for matrix A
	if shiftLeft
		shift = isSetup ? myRow-1 : 1
		sendCol = mod(myCol-shift-1, ncols)+1
		recvCol = mod(myCol+shift-1, ncols)+1
	end
	if shiftUp
		shift = isSetup ? myCol-1 : 1
		sendRow = mod(myRow-shift-1, nrows)+1
		recvRow = mod(myRow+shift-1, nrows)+1
	end

	sendRank = _getProcessor(sendRow,sendCol,ncols)
	recvRank = _getProcessor(recvRow,recvCol,ncols)

	#wait(rand(1:1000,1,1)[1])
	println("[$shift -> $sendCol  $recvCol  $sendRow  $recvRow]:[$sendRank  $recvRank]")
	

	new_matrix = copy(matrix)
	rreq = MPI.Irecv!(new_matrix, recvRank,  MPI.ANY_TAG, comm)
    println("$rank: Sending ($myRow,$myCol) -> ($myRow,$sendCol)")
    
    sreq = MPI.Isend(matrix, sendRank, sendRank+32, comm)
    println("$rank: Receiving ($myRow,$recvCol) -> ($myRow,$myCol)")

    stats = MPI.Waitall!([rreq, sreq])
    MPI.Barrier(comm)

    return new_matrix
end



function _getRow(rank,ncols)
	# Return the row that this processor is in
	# The result is 1-based to be consistant with julia indexing
	return Int8(floor(rank/ncols+1))
end



function _getCol(rank,ncols)
	# Return the column that this processor is in
	# The result is 1-based to be consistant with julia indexing
	return Int8(mod(rank,ncols)+1)
end



function _getProcessor(row,col,ncols)
	# Return the rank of the processor at [row,col]
	# Assumes 1-based indexing to be consistant with julia indexing
	return (row-1)*ncols + col-1;
end



function gather(x)
    # Gather the matrices x from each processor to check validity
    # This function can be used to Gather A, B or C matrices
    # Ideally we would used MPI.Gather, but julia doesn't support this

    # Let m = sqrt(csize)
    # We assume that the processors are arranged in a mxm grid.
    # Processor 1 -> m are in row 1. ect.
    nrows = Int8(sqrt(csize))
    ncols = Int8(sqrt(csize))
    
    xrows = size(x, 1)
    xcols = size(x, 2)
    result = zeros(nrows*xrows,ncols*xcols)

    if rank!=0
        MPI.send(x,0,rank+32,comm)
    else
    	# Add my own matrix to the result
    	result[1:xrows,1:xcols] = x; 

    	# Add the other matrices to the result
        for i=1:csize-1	
		    row = Int8(floor(i/ncols+1))
		    col = Int8(mod(i,ncols)+1)
		    response = MPI.recv(i,i+32,comm)[1]
		    result[ (1:xrows)+(row-1)*xrows, (1:xcols)+(col-1)*xcols ] = response; 
        end
    end

    # Print the result from processor 0
    if rank==0
        return result
    end
end