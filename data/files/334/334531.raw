
# to import MPIManager
using MPI
MPI.Init()

comm = MPI.COMM_WORLD


function main()
	N = 4028
	tag = 7
	rank = MPI.Comm_rank(comm)
	for i=1:10
		pingpong(rank,N,tag)
	end
end


function pingpong(rank,N,tag)
	other_rank = Bool(rank)?1:0
	println(other_rank)
	if (rank==0)
		send_mesg = Array(Float64, N)
	    println("[$(rank)] I am sending my message to $(other_rank).");
		MPI.send(send_mesg, other_rank, tag, comm)
		println("[$(rank)] Sent my message");

		# Wait for the pong
		src = 1
		recv_mesg = Array(Float64, N)
		println("[$(rank)] I am waiting for my message");
		rreq = MPI.recv(recv_mesg, other_rank,  rank, comm)
		println("[$(rank)] Got my message");
	elseif (rank==1)	
		src = 0
		recv_mesg = Array(Float64, N)
		println("[$(rank)] I am waiting for my message from $(other_rank).");
		rreq = MPI.Irecv!(recv_mesg, other_rank, rank, comm)
		stats = MPI.Waitall!([rreq])
		println("[$(rank)] Got my message");

		# Send a message back
		println("[$(rank)] Sending the message back");
		dst = 0
		send_mesg = Array(Float64, N)
		MPI.send(send_mesg, other_rank, tag, comm)
		println("[$(rank)] Sent the message back");
	end
end

println("[$(rank)] I am starting up");
@time main()
println("[$(rank)] Done");
