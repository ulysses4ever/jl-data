import Base.show
using MPI
MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)
    
println("$rank: Starting up")


function bitonic_sort(x,up,ranks)
    println("$x")
    if length(ranks) <= 1
        return x
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
        if (ranks[i] > ranks[i + dist])==up
            ranks[i], ranks[i + dist] = ranks[i + dist], ranks[i] #swap
        end
        #bitonic_swap(x,up,ranks[i],ranks[i + dist])
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
        println("swap $ranka to $rankb :: up = $up")
    
        #println("$rank: Sending $rank -> $rankb = $x ")
        MPI.send(x, rankb, rank+32, comm)
        #println("$rank: Waiting for message from $rankb")
        newx = MPI.recv(rankb, MPI.ANY_TAG, comm)[1]
        println("$rank: Receiving $ranka -> $rank = $newx ")

    elseif (rank==rankb)   
        x_src = MPI.recv(ranka,  ranka+32, comm)[1]
        x_merged = vcat(x_src,x)
        x_merged = sort(x_merged, rev=~up);
        # Split the array in half, and send back the smaller one
        dist = round(Int,length(x_merged) / 2)
        newx = x_merged[dist+1:end]
        s = x_merged[1:dist]
        MPI.send(s, ranka, rank+128, comm)
        println("$rank: Bouncing $rank -> $ranka = $x ") 
    end

    # Modify x in place with newx
    for i in 1:length(newx)
        x[i] = newx[i]
    end

    sort!(x, rev=~up);
end

















function bitonic_compare_old(x,min,max)
    # Form a bitonic vector that stretches from min->max
    # @min and @max are processor ranks
    # Min is included in the bitonic vector but max is not
    midpoint = round(Int, abs(min-max)/2)
    shift = round(Int, abs(min-max)/2)

    if shift<1
        return x
    end 

    x = bitonic_compare(x,min,midpoint)
    #x = bitonic_compare(x,midpoint+1,max)
    println("We should now have bitonic $min->$midpoint + $midpoint->$max")
    gather(x)

    # Make our bigger bitonic sequence
    for processor in min:midpoint-1
        println("Swapping $processor -> $processor+$shift")
        x = bitonic_swap(x,true,processor,processor+shift)
        gather(x)

    end 
    return x
    #for processor in midpoint:max-shift
    #    x = bitonic_compare(x,processor,max-shift)
    #    println("bitonic $min to $max :: shift = $shift, mid=$midpoint")
    #    #x=bitonic_swap(x,false,processor,processor+shift)
    #    #x = bitonic_compare(x,processor,processor+shift)
    #end
    #return x
        #println(x)
        #x=bitonic_swap(x,true,1,1+shift)
        #println("$x")

        #x=bitonic_swap(x,true,2,2+shift)
        #println(x)
        #x=bitonic_swap(x,false,3,3+shift)
        #println(x)
        #x=bitonic_swap(x,false,3,4+shift) 
        #println(x)    
        # x=bitonic_swap(x,false,3,5+shift)
        #println(x)
        #end
    #end


    #x=bitonic_swap(x,true,0,3)
    #x=bitonic_swap(x,true,1,3)
    #x=bitonic_swap(x,true,2,3)
    #up = rank<size/2
    #x = sort(x,rev=~up)
    
    # Now perform bitonic merge
    #x=bitonic_swap(x,true,0,2)
    #x=bitonic_swap(x,true,1,3)

    #x=bitonic_swap(x,true,0,1)
    #x=bitonic_swap(x,true,2,3)

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
#x = vec(rand(1:100,1,N))


x = vec([18-rank]);
x=bitonic_sort(x,true,[0,1,2,3,4,5,6,7])
println("xxx=$x")





println("[$rank] done")
MPI.Barrier(comm)

gather(x)

MPI.Barrier(comm)



