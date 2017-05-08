include("bitonic.jl")


function test_bitonic_swap()
    # Check that the MPI part of the swapping algorithm is 
    # working correctly
    if rank==0
        u = [1,2,14]
        d = [1,2,15]
    elseif rank==1
        u = [0,2,6]
        d = [0,2,5]
    else 
        return
    end
    bitonic_swap!(u,true,0,1)
    bitonic_swap!(d,false,0,1)
    
    # Check that the values are correctly sorted
    if rank==0
        assert(u == [0,1,2])
        assert(d == [15,5,2])
    elseif rank==1
        assert(u == [2,6,14])
        assert(d == [2,1,0])
    end
end
    
test_bitonic_swap()
