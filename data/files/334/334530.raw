import Base.show
using MPI
MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)
    
println("$rank: Starting up")


function bitonic_sort(x,up,ranks)
    if length(ranks) <= 1
        return ranks
    else
        dist = round(Int,length(ranks) / 2)
        first = bitonic_sort(x, true, ranks[1:dist])
        second = bitonic_sort(x, false, ranks[dist+1:end])
        return bitonic_merge(x, up, vcat(first,second))
    end
end



function bitonic_merge(x,up,ranks)
    # Assuming the data on @ranks is bitonic, the data will become sorted 
    if length(ranks) == 1
        return ranks
    else
        bitonic_compare(x, up, ranks)
        dist = round(Int,length(ranks) / 2)
        first = bitonic_merge(x, up, ranks[1:dist])
        second = bitonic_merge(x, up, ranks[dist+1:end])
        return vcat(first,second)
    end 
end

 


function bitonic_compare(x,up,ranks)
    # Perform a bitonic compare between the processors in @ranks
    dist = round(Int,length(ranks) / 2)
    for i in 1:dist
        if rank==ranks[i]
            next = rank + dist;
            println("Comparing rank=$rank -> rank=$next")
            #if (ranks[i] > ranks[i + dist])==up
            #    ranks[i], ranks[i + dist] = ranks[i + dist], ranks[i] #swap
            #end
        end
        bitonic_swap(x,up,ranks[i],ranks[i + dist])
        if rank==ranks[i]
            #MPI.Barrier(comm)
            #gather(x)
        end
    end
end



function bitonic_swap(x,up,ranka,rankb)
    # Compare the values on this processor against another processor
    # The values on ranka always end smaller than the values on rankb

    newx = x
    up2order = rank<size/2
    sort!(x, rev=~up);
 
    # Send the data over to processor rank+1
    if (rank==ranka)
        #println("swap $ranka to $rankb :: up = $up")
    
        #println("$rank: Sending $rank -> $rankb = $x ")
        MPI.send(x, rankb, rank+32, comm)
        #println("$rank: Waiting for message from $rankb")
        newx = MPI.recv(rankb, MPI.ANY_TAG, comm)[1]
        #println("$rank: Receiving $ranka -> $rank = $newx ")

    elseif (rank==rankb)   
        x_src = MPI.recv(ranka,  ranka+32, comm)[1]
        x_merged = vcat(x_src,x)
        x_merged = sort(x_merged, rev=~up);
        # Split the array in half, and send back the smaller one
        dist = round(Int,length(x_merged) / 2)
        newx = x_merged[dist+1:end]
        s = x_merged[1:dist]
        MPI.send(s, ranka, rank+128, comm)
        #println("$rank: Bouncing $rank -> $ranka = $x ") 
    end

    # Modify x in place with newx
    #for i in 1:length(newx)-1
    x[1] = newx[1]
    #end

    sort!(x, rev=~up);
end





function gather(x)
    # Gather the sequences and check their validity
    # x is the sorted array on this processor
    #println("$rank: gathering")

    
    if rank!=0
        #println("$rank: sending my results")
        MPI.send(x,0,rank+32,comm)
    else
        gathered = x;

        for i=1:size-1
            #println("$rank: collecting data from rank=$i")
            response = MPI.recv(i,i+32,comm)
            gathered = vcat(gathered,response[1])
        end

        # Check for validity
        sorted = sort(gathered)
        println(sorted)
        println(gathered)
        if all(sorted==gathered)
            println("Success!!!")
        else
            println("Failure!!!")
        end
    end
end




N = 2
x = vec(rand(1:100,1,1))
ranks = bitonic_sort(x,true,[0,1,2,3,4,5,6,7])
println("RANKS=$ranks")

println("[$rank] done")
gather(x)
MPI.Barrier(comm)









