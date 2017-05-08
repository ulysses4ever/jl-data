module Diff
    
    #TODO : Create a LCS_Matrix type
    
    # compute the LCS matrix paded with 0 on
    # first row and first column,
    # the LCS matric is then of size
    # (len(s1)+1) X (len(s2)+1)
    #
    # This is not the more efficient way (memory speeking)
    # of computing a LCS edit distance, but can bu used to back track the
    # changes to get the lcs sequences afterward.
    function lcs_matrix{T}(s1::Vector{T},s2::Vector{T})
        m::Int = length(s1)
        n::Int = length(s2)
            
        lcs_lengths = Array(Int,(m+1,n+1))
        lcs_lengths[1,:] = 0
        lcs_lengths[:,1] = 0
        
        # Check which index is faster to iterate over.
        # wether we are fortran or c-like
        for i2 in 1:n
            for i1 in 1:m
                if s1[i1] == s2[i2]
                    lcs_lengths[i1+1,i2+1] = lcs_lengths[i1,i2]+1
                else
                    lcs_lengths[i1+1,i2+1] = max(lcs_lengths[i1,i2+1], lcs_lengths[i1+1,i2])
                end
            end
        end
        return lcs_lengths
    end
    
    # Compute the Edit Distance of 2 sequeces s1 and s2
    # (which is the last elemet of the lcs matrix)
    # but can be a more eficient algorythme using O(min(len(s1), len(s2)))
    # in memory if one is not interested in knowign the sequnce, but just its
    # length
    function lcs_length(s1,s2)
        return lcs_matrix(s1,s2)[end,end]
    end
    
    ## private, backtrack the LCS matrix to find **one**
    ## of the LCS.
    function _backtrack{T}(C :: Array{Int, 2},
			   X :: Vector{T},
			   Y :: Vector{T},
			   i :: Int, j :: Int)
        if (i == 1) || (j == 1)
            ## Ugly typing, sure we can be smarter in function definition by typing X and Y
            return T[]
        elseif  ( X[i-1] == Y[j-1] )
            return append!(_backtrack(C, X, Y, i-1, j-1), [X[i-1]])
        else
            if C[i,j-1] > C[i-1,j]
                return _backtrack(C, X, Y, i, j-1)
            else
                return _backtrack(C, X, Y, i-1, j)
            end
        end
    end
    
    ## backtrack **ONE** LCS of X and Y if one already know its LCS_matrix (C)
    function backtrack(C, X, Y)
        return _backtrack(C, X, Y, length(X)+1, length(Y)+1)
    end
    
    function one_of_the_lcs{T}(s1::Vector{T},s2::Vector{T})
        C = lcs_matrix(s1,s2)
        return backtrack(C,s1,s2)
    end
    
    function one_of_the_lcs(s1::String, s2::String)
        s1 = [s for s=s1]
        s2 = [s for s=s2]
        C = lcs_matrix(s1, s2)
        return join(backtrack(C,s1,s2))
    end
    
    # return a lcs edit distance between
    # the 2 sequences by using as low memeory as possible.
    # mainly by storing only previous row of current lcs matrice + 1 element
    # but for whichever reason this is much slower than
    # edit_distance. but have a O(m+n) memory footprint, where
    # edit_distance have a O(m*n) footprint.
    function lcs_distance_low_m(s1,s2)
        m::Int = length(s1)
        n::Int = length(s2)
        if n < m
            m, n =  n, m
            s1, s2 = s2, s1
        end
        ## c = current , p = previous
        lcs_lengthsc = Array(Int,(m))
        lcs_lengthsp = Array(Int,(m))
        lcs_lengthsc[:] = 0
        lcs_lengthsp[:] = 0

        cc = ' '
        for i2 in 1:n
            cc = s2[i2]
            lcs_lengthsc , lcs_lengthsp = lcs_lengthsp, lcs_lengthsc
            for i1 in 1:m
                if s1[i1] == cc
                    if(i1==1)
                        lcs_lengthsc[1] = 1
                    else
                        lcs_lengthsc[i1] = lcs_lengthsp[i1-1]+1
                    end
                else
                    if (i1 != 1)
                        a = lcs_lengthsp[i1]
                        b = lcs_lengthsc[i1-1]
                        lcs_lengthsc[i1] = max(a,b)
                    else
                        lcs_lengthsc[1] = lcs_lengthsp[1]
                    end
                end
            end
        end
        return lcs_lengthsc[end]
    end
end
