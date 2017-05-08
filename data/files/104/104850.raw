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
    function lcs_matrix(s1,s2)
    
        m::Int = length(s1)
        n::Int = length(s2)
            
        edit_distances = Array(Int,(m+1,n+1))
        edit_distances[1,:] = 0
        edit_distances[:,1] = 0
        
        # Check which index is faster to iterate over.
        # wether we are fortran or c-like
        for i2 in 1:n
            for i1 in 1:m
                if s1[i1] == s2[i2]
                    edit_distances[i1+1,i2+1] = edit_distances[i1,i2]+1
                else
                    edit_distances[i1+1,i2+1] = max(edit_distances[i1,i2+1], edit_distances[i1+1,i2])
                end
            end
        end
        return edit_distances
    end
    
    # Compute the Edit Distance of 2 sequeces s1 and s2
    # (which is the last elemet of the lcs matrix)
    # but can be a more eficient algorythme using O(min(len(s1), len(s2)))
    # in memory if one is not interested in knowign the sequnce, but just its
    # length
    function edit_distance(s1,s2)
        return lcs_matrix(s1,s2)[end,end]
    end
    
    ## private, backtrack the LCS matrix to find **one**
    ## of the LCS.
    function _backtrack(C, X, Y, i::Int, j::Int)
        if (i == 1) || (j == 1)
            ## Ugly typing, sure we can be smarter in function definition by typing X and Y
            return typeof(X[1])[]
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
    
    function one_of_the_lcs(s1::Any,s2::Any)
        C = lcs_matrix(s1,s2)
        return backtrack(C,s1,s2)
    end
    
    ## special case dispatch on string to re-join them
    function one_of_the_lcs(s1::String, s2::String)
        C = lcs_matrix(s1,s2)
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
        edit_distances = Array(Int,(n+1))
        edit_distances[:] = 0
        ci = 0
        for i2 in 1:n
            for i1 in 1:m
                ci +=1
                if s1[i1] == s2[i2]
                    if(i1==1)
                        edit_distances[mod(ci,n+1)+1] = 1
                    else
                        edit_distances[mod(ci,n+1)+1] += 1
                    end
                else
                    if (i1==1)
                        edit_distances[mod(ci,n+1)+1] = edit_distances[mod(ci,n+1)+1]
                    else
                        edit_distances[mod(ci,n+1)+1] = max(edit_distances[mod(ci-1,n+1)+1], edit_distances[mod(ci,n)+1])
                    end
                end
            end
        end
        return edit_distances[end]
    end
end
