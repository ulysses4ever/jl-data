
# to import MPIManager
using MPI
MPI.Init()

# specify, number of mpi workers, launch cmd, etc.
manager=MPIManager(np=4)
comm = MPI.COMM_WORLD


# start mpi workers and add them as julia workers too.
addprocs(manager)



function counter(n)
	total = 0
	for i = 1:n
    	total = total += 1.001;
    end

    println("[$(MPI.Comm_rank(comm))] I am finished counting to $(n)");
end


counter(10^1)
counter(10^2)
counter(10^3)
counter(10^4)
counter(10^5)
counter(10^6)
counter(10^7)
counter(10^8)
counter(10^9)
counter(10^10)
counter(10^11)
counter(10^12)
