using MPI
MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
csize = MPI.Comm_size(comm)
    

function bitonic_sort!(x,up,ranks)
    # Sort the vector x accross proccessors specified in @ranks
    # The first processor in @ranks will recieve the smallest values and so on
    # The boolean variable @up specifies the order (up or down)
    # The vector x is modified in place
    if length(ranks) <= 1
        return ranks
    else
        dist = iround(length(ranks) / 2)
        first = bitonic_sort!(x, true, ranks[1:dist])
        second = bitonic_sort!(x, false, ranks[dist+1:end])
        return bitonic_merge!(x, up, vcat(first,second))
    end
end



function bitonic_merge!(x,up,ranks)
    # Assuming the data on @ranks is bitonic, the data will become sorted 
    # x is modified in place
    if length(ranks) == 1
        return ranks
    else
        bitonic_compare!(x, up, ranks)
        dist = iround(length(ranks) / 2)
        first = bitonic_merge!(x, up, ranks[1:dist])
        second = bitonic_merge!(x, up, ranks[dist+1:end])
        return vcat(first,second)
    end 
end

 

function bitonic_compare!(x,up,ranks)
    # Perform a bitonic compare between the processors in @ranks
    # x is modified in place
    dist = iround(length(ranks) / 2)
    for i in 1:dist
        bitonic_swap!(x,up,ranks[i],ranks[i + dist])
    end
end



function bitonic_swap!(x,up,ranka,rankb)
    # Compare the values on this processor against another processor
    # The values on ranka always end smaller than the values on rankb
    # x is modified in place

    if (rank==ranka)
        # Send the data over to processor rank+1
        MPI.send(x, rankb, rank+32, comm)
        x[1:end] = MPI.recv(rankb, MPI.ANY_TAG, comm)[1]

    elseif (rank==rankb)   
        x_src = MPI.recv(ranka,  ranka+32, comm)[1]
        x_merged = sort(vcat(x_src,x), rev=~up)
        
        # Split the array in half, and send back the smaller values
        # Modification: Send back the same sized array to allow for different sizes
        dist = length(x_src)
        x[1:end] = x_merged[dist+1:end]
        send = x_merged[1:dist]
        MPI.send(send, ranka, rank+128, comm)
    end
end





function gather(x)
    # Gather the sequences and check their validity
    # Ideally we would used MPI.Gather, julia doesn't support this
    # x is the vector of data on this processor 
    if rank!=0
        MPI.send(x,0,rank+32,comm)
    else
        gathered = x;

        for i=1:csize-1
            response = MPI.recv(i,i+32,comm)
            gathered = vcat(gathered,response[1])
        end

        sorted = sort(gathered)
        println(sorted)
        println(gathered)
        if all(sorted==gathered)
            println("Bitonic sort successful!")
        else
            println("Bitonic sort failed!")
        end
    end
end






####### EXAMPLE USAGE #######
function main()
    N = 4 # The number of values on each processor
    x = vec(rand(1:100,1,N)) # The vector of values on this processor
    ranks = 0:csize-1
    bitonic_sort!(x,true,ranks)

    MPI.Barrier(comm)
    gather(x)
    MPI.Barrier(comm)
    MPI.Finalize()
end
main()

# Restrictions
# - N must be the same on all processors
# - The number of processors must be 2^n
# - x must be a vector








