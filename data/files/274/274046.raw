# Example usage of Cannon.jl
# Cannon.jl requires q^2 processors.
# This file should run correctly with any variation of q^2 processors

# Example usage:
# mpirun -n 4 julia cannon_examples.jl
# mpirun -n 9 julia cannon_examples.jl
# mpirun -n 16 julia cannon_examples.jl
include("cannon.jl")


function cannonMultiply2x2()
	# Example usage of Cannon Multiply
	# Each processor starts with a random 2x2 submatrix
	# Processors are arranged in a qxq grid
	
	m = 2;
	n = 2;

	A = rand(1:10, m, n)
	B = rand(1:10, n, m)
	C = cannonMultiply(A,B)
	
	Atotal = gather(A)
	Btotal = gather(B)
	Ctotal = gather(C)

	MPI.Barrier(comm)
	if rank==0	
		println("\n--- The A matrix (total) ---")
    	println(Atotal);

    	println("\n--- The B matrix (total) ---")
    	println(Btotal);

		println("\n---  The expected C matrix ---")
		println(Atotal*Btotal)

    	println("\n---  The calculated C matrix ---")
		println(Ctotal)

        assert(Atotal*Btotal==Ctotal)
        println("Test OK")
	end
	MPI.Barrier(comm)
end




function cannonMultiply3x4()
	# Example usage of Cannon Multiply
	# Each processor starts with a random 3x4 submatrix
	# Processors are arranged in a qxq grid
	
	m = 3;
	n = 4;

	A = rand(1:10, m, n)
	B = rand(1:10, n, m)
	C = cannonMultiply(A,B)
	
	Atotal = gather(A)
	Btotal = gather(B)
	Ctotal = gather(C)

	MPI.Barrier(comm)
	if rank==0	
		println("\n--- The A matrix (total) ---")
    	println(Atotal);

    	println("\n--- The B matrix (total) ---")
    	println(Btotal);

		println("\n---  The expected C matrix ---")
		println(Atotal*Btotal)

    	println("\n---  The calculated C matrix ---")
		println(Ctotal)

        assert(Atotal*Btotal==Ctotal)
        println("Test OK")
	end
	MPI.Barrier(comm)
end



cannonMultiply2x2()
cannonMultiply3x4()
MPI.Finalize()