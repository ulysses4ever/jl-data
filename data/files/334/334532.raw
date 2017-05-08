
# to import MPIManager
using MPI
MPI.Init()

comm = MPI.COMM_WORLD


function pingpong(roundtrips,msg_size)
	# Ping another processor and wait for the response
	# Rountrips is the number of rountrips to complete before returning
	# msg_size is the size of the message. bytes = 8 * msg_size
    
    comm = MPI.COMM_WORLD
    rank = MPI.Comm_rank(comm)
    size = MPI.Comm_size(comm)

    dst = mod(rank+1, size)
    src = mod(rank-1, size)
 
    send_msg = Array(Float64, msg_size)
    fill!(send_msg, Float64(rank))
    
    size = sizeof(send_msg)
    #println("Message is $size bytes")

    for i=1:roundtrips
	    if (mod(rank,2)==0)
	    	#println("$rank: Sending $src -> $rank = $send_mesg ")
	    	MPI.send(send_msg, dst, rank+32, comm)
	    	response = MPI.recv(dst, src+32, comm)
	    	#println("$rank: Receiving $src -> $rank = $response ")
	   	else 	
	    	response = MPI.recv(src,  src+32, comm)
	    	MPI.send(response[1], dst, rank+32, comm)
	    	#println("$rank: Bouncing $src -> $rank = $response ")
	    end
	end

    MPI.Barrier(comm)
end


function main()
	# Call pingpong with an increasing data size
	roundtrips = 500
	
	for i=1:20
		msg_size = 2^i
		byte_size = 8*msg_size;
		time = @elapsed pingpong(roundtrips, msg_size)
		average = 1000*time/roundtrips #ms
		println("[size(bytes) : time(ms)] = $byte_size $average")
	end
end

main()
