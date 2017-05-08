import Base.show
using MPI
MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)
    
println("$rank: Starting up")


function bitonic_sort(up,x)
    if length(x) <= 1
        return x
    else
        dist = round(Int,length(x) / 2)
        first = bitonic_sort(true, x[1:dist])
        second = bitonic_sort(false, x[dist+1:end])
        return bitonic_merge(up, vcat(first,second))
    end
end



function bitonic_merge(up,x)
    # assume input x is bitonic, and sorted list is returned 
    if length(x) == 1
        return x
    else
        bitonic_compare(up, x)
        dist = round(Int,length(x) / 2)
        first = bitonic_merge(up,x[1:dist])
        second = bitonic_merge(up,x[dist+1:end])
        return vcat(first,second)
    end 
end

 

#function bitonic_compare(up,x)
#    dist = round(Int,length(x) / 2)
#    #print(dist)
#    for i in 1:dist
#        if (x[i] > x[i + dist])==up
##            x[i], x[i + dist] = x[i + dist], x[i] #swap
#        end
#    end
#end







function bitonic_swap(x,up,ranka,rankb)
    # Compare the values on this processor against another processor
    # The values on ranka always end smaller than the values on rankb

    up2order = rank<size/2
    x = sort(x, rev=~up);
 
    # Send the data over to processor rank+1
    if (rank==ranka)
        println("swap $ranka to $rankb :: up = $up")
    
        #println("$rank: Sending $rank -> $rankb = $x ")
        MPI.send(x, rankb, rank+32, comm)
        #println("$rank: Waiting for message from $rankb")
        x = MPI.recv(rankb, MPI.ANY_TAG, comm)[1]
        #println("$rank: Receiving $ranka -> $rank = $x ")

    elseif (rank==rankb)   
        x_src = MPI.recv(ranka,  ranka+32, comm)[1]
        x_merged = vcat(x_src,x)
        x_merged = sort(x_merged, rev=~up);
        # Split the array in half, and send back the smaller one
        dist = round(Int,length(x_merged) / 2)
        x = x_merged[dist+1:end]
        s = x_merged[1:dist]
        MPI.send(s, ranka, rank+128, comm)
        #println("$rank: Bouncing $rank -> $ranka = $x ") 
    end

    x = sort(x, rev=~up);
    return x
end












function bitonic_compare(x,min,max)
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



function main(x)
    x = bitonic_compare(x,0,8)
    return x
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
            #println("Failure!!!")
        end
    end
end



#array = [1,2,9,4,5,6,7,8,9,10,11,12,13,14,15,16]
#array = [9,1,3,4,5,6,14,7,8,16,10,11,12,2,13,15,68]
#bitonic_compare(true,array)
#sorted = bitonic_sort(true,array)
#println(sorted)

N = 2
#x = vec(rand(1:100,1,N))
#x = 2*(size-rank-1)*vec([1,1]) + vec([0,1])
x=vec([size-rank])
println(x)
x = main(x)
    
println("[$rank] done")
MPI.Barrier(comm)

gather(x)

MPI.Barrier(comm)







