# Tests for cannon.jl
# Tests are designed to be run with 9 processors, although some
# of the tests can be run with more/less processors.
# Example usage:
# mpirun -n 9 julia cannon_tests.jl
include("cannon.jl")

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
csize = MPI.Comm_size(comm)


function test_gather()
	# Test that gather correctly gathers the matrices from 
	# a mxm grid of processors. This should only be run with
	# nprocessors=m^2
	
	# Create the matrix we expect to see
	nrows = Int8(sqrt(csize))
    ncols = Int8(sqrt(csize))
	expected = zeros(nrows,ncols)
	
	for row=1:nrows
		for col=1:ncols
			expected[row,col] = _getProcessor(row,col,ncols)
		end
	end

	# Test against the expected matrix on proccessor 1
	A = rank#ones(1,1)
	result = gather(A)
	
	MPI.Barrier(comm)
	if rank==0	
    	println("The matrix across all processors:")
        println(result)
		println("The matrix that was expected:")
        println(expected)
        assert(result==expected)
	end
	MPI.Barrier(comm)
end



function test_cannonSetupLeft()
	# Test that cannonShift correctly moves data between the processors
	# Assumes a 3x3 matrix. Must be run with -np 9
	ncols = 3
	nrows = 3
	setup = true;
	A = rank*ones(1,1)
	A = cannonShift(A,true,false,setup,nrows,ncols)
	
	expected = [0.0 1 2; 4 5 3; 8 6 7]
	result = gather(A)
	
	MPI.Barrier(comm)
	if rank==0	
		println("\n---  test_cannonSetupLeft  ---")
    	println("The matrix across all processors:")
        println(result)
		println("The matrix that was expected:")
        println(expected)
        assert(result==expected)
	end
	MPI.Barrier(comm)
end



function test_cannonSetupUp()
	# Test that cannonShift correctly moves data between the processors
	# Assumes a 3x3 matrix. Must be run with -np 9
	ncols = 3
	nrows = 3
	setup = true;
	A = rank*ones(1,1)
	A = cannonShift(A,false,true,setup,nrows,ncols)
	
	expected = [0.0 4 8; 3 7 2; 6 1 5]
	result = gather(A)
	
	MPI.Barrier(comm)
	if rank==0	
		println("\n---  test_cannonSetupUp  ---")
    	println("The matrix across all processors:")
        println(result)
		println("The matrix that was expected:")
        println(expected)
        assert(result==expected)
	end
	MPI.Barrier(comm)
end



function test_cannonShiftLeft()
	# Test that cannonShift correctly moves data between the processors
	# Assumes a 3x3 matrix. Must be run with -np 9
	ncols = 3
	nrows = 3
	setup = false;
	A = rank*ones(1,1)
	A = cannonShift(A,true,false,setup,nrows,ncols)
	
	expected = [1.0 2 0; 4 5 3; 7 8 6]
	result = gather(A)
	
	MPI.Barrier(comm)
	if rank==0	
		println("\n---  test_cannonShiftLeft ---")
    	println("The matrix across all processors:")
        println(result)
		println("The matrix that was expected:")
        println(expected)
        assert(result==expected)
	end
	MPI.Barrier(comm)
end



function test_cannonShiftUp()
	# Test that cannonShift correctly moves data between the processors
	# Assumes a 3x3 matrix. Must be run with -np 9
	ncols = 3
	nrows = 3
	setup = false;
	A = rank*ones(1,1)
	A = cannonShift(A,false,true,setup,nrows,ncols)
	
	expected = [3.0 4 5; 6 7 8; 0 1 2]
	result = gather(A)
	
	MPI.Barrier(comm)
	if rank==0	
		println("\n---  test_cannonShiftUp ---")
    	println("The matrix across all processors:")
        println(result)
		println("The matrix that was expected:")
        println(expected)
        assert(result==expected)
	end
	MPI.Barrier(comm)
end




function test_cannonMultiply()
	# Test that cannonMultiply correctly computes the matrix multiplication
	# Each processor contains a 1x1 matrix with a single floating point value
	# Assumes a mxm grid of proccessors matrix. Must be run with -nprocessors m^2
	A = rank*ones(1,1)
	B = 10*rank*ones(1,1)
	C = cannonMultiply(A,B)
	
	Atotal = gather(A)
	Btotal = gather(B)
	Ctotal = gather(C)

	MPI.Barrier(comm)
	if rank==0	
		println("\n---  test_cannonMultiply---")
    	println("The matrix across all processors:")
        println(Ctotal)
		println("The matrix that was expected:")
        println(Atotal*Btotal)
        assert(Atotal*Btotal==Ctotal)
	end
	MPI.Barrier(comm)
end



function test_cannonMultiplyWithSubmatrices()
	# Test that cannonMultiply correctly computes the matrix multiplication
	# Each processor contains a mxn matrix, of floating point numbers
	# Assumes a qxq grid of proccessors matrix. Must be run with -nprocessors q^2
	
	m = 2;
	n = 3;

	A = rand(1:10, m, n)
	B = rand(1:10, n, m)
	C = cannonMultiply(A,B)
	
	Atotal = gather(A)
	Btotal = gather(B)
	Ctotal = gather(C)

	MPI.Barrier(comm)
	if rank==0	
		println("\n---  test_cannonMultiply---")
    	println("The matrix across all processors:")
        println(Ctotal)
		println("The matrix that was expected:")
        println(Atotal*Btotal)
        assert(Atotal*Btotal==Ctotal)
        println("Test OK")
	end
	MPI.Barrier(comm)
end



test_gather()
test_cannonSetupLeft()
test_cannonSetupUp()
test_cannonShiftLeft()
test_cannonShiftUp()
test_cannonMultiply()
test_cannonMultiplyWithSubmatrices()
