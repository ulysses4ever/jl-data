module SmithNormalForm
# Defines stuff around the Smith Normal Form

  export smith_normal_form

  function solve_gcd_equation(a0::Int, a1::Int)
    # Finds sigma, tau, beta
    #
    # Solves the equation :math:`\sigma a_0 + \tau a_1 = \beta` with
    # :math:`\beta = \mathop{gcd}(a_0, a_1)`.
    #
    # Parameters:
    #  a0: First integer.
    #  a1: Second integer
    # Returns: :math:`\sigma, \tau, \beta`
      
    # Makes the search a bit faster
    if a0 == 0 && a1 == 0
      return 0, 0, 0
    elseif a0 == 0
      return 0, sign(a1), abs(a1)
    elseif a1 == 0
      return 1, 0, a0
    elseif abs(a0) < abs(a1)
      tau, sigma, beta = solve_gcd_equation(a1, a0)
      return sign(a0) == sign(a1) ? (sigma, tau, beta): (-sigma, -tau, -beta)
    end
    beta = gcd(a0, a1)
    iscorrect(s) = (u = beta - s*a0; abs(u) < abs(a1) || (beta - s*a0) % a1 != 0)
    sigma::Int = 1
    while iscorrect(sigma)
      sigma += 1
    end
    return sigma, div(beta - sigma * a0, a1), beta
  end 

  function choose_pivot{T <: Int}( t::Int, jt::Int, 
                                   smith::Matrix{T}, 
                                   left::Matrix{T} )
    @assert t <= jt
    @assert jt <= size(smith, 2)
    while jt <= size(smith, 2) && nnz(smith[:, jt]) < 1
      jt += 1
    end
    if jt > size(smith, 2); return -1; end
    if nnz(smith[:, jt]) < 1; return jt; end
    if smith[t, jt] == 0
      k = findfirst(smith[:, jt])
      smith[jt, :], smith[k, :] = smith[k, :], smith[jt, :]
      left[jt, :], left[k, :] = left[k, :], left[jt, :]
    end
    return jt
  end

  function improve_pivot_col{T <: Int}( t::Int, jt::Int,
                                        smith::Matrix{T}, 
                                        left::Matrix{T} )
    # Transform matrix such that matrix[:, jt] is zero except for alement t.
    @assert t <= size(smith, 1)
    @assert jt <= size(smith, 2)
    @assert smith[t, jt] != 0
    for k in 1:size(smith, 1)
      # If same row or already zero, then continue
      (k == t || smith[k, jt] == 0) && continue
      # If not divisible, make divisible
      if smith[k, jt] % smith[t, jt] != 0 
        # Get parameters of gcd equation
        sigma, tau, beta = solve_gcd_equation(smith[t, jt], smith[k, jt])
        # Put beta on smith[t, jt]
        smith[t, :] = sigma * smith[t, :] + tau * smith[k, :]
        left[t, :] = sigma * left[t, :] + tau * left[k, :]
      end
      # Put 0 on smith[k, jt]
      alpha = div(smith[k, jt], smith[t, jt])
      smith[k, :] -= alpha * smith[t, :]  
      left[k, :]  -= alpha * left[t, :]
    end
    # if negative, make positive
    if smith[t, jt] < 0
      smith[t, :] *= -1
      left[t, :] *= -1
    end
  end

  function improve_pivot_row{T <: Int}( t::Int, jt::Int,
                                        smith::Matrix{T}, 
                                        right::Matrix{T} )
    # Transform matrix such that matrix[:, jt] is zero except for alement t.
    @assert t <= size(smith, 1)
    @assert jt <= size(smith, 2)
    @assert smith[t, jt] != 0
    for k in 1:size(smith, 2)
      # If same col or already zero, then continue
      (k == jt || smith[t, k] == 0) && continue
      # If not divisible, make divisible
      if smith[t, k] % smith[t, jt] != 0 
        # Get parameters of gcd equation
        sigma, tau, beta = solve_gcd_equation(smith[t, jt], smith[t, k])
        # Put beta on smith[t, jt]
        smith[:, jt] = sigma * smith[:, jt] + tau * smith[:, k]
        right[:, jt] = sigma * right[:, jt] + tau * right[:, k]
      end
      # Put 0 on smith[k, jt]
      alpha = div(smith[t, k], smith[t, jt])
      smith[:, k] -= alpha * smith[:, jt]  
      right[:, k] -= alpha * right[:, jt]  
    end
    # if negative, make positive
    if smith[t, jt] < 0
      smith[:, t] *= -1
      right[:, t] *= -1
    end
  end

  function make_divisible{T <: Int}( i::Int,
                                     smith::Matrix{T}, 
                                     left::Matrix{T},
                                     right::Matrix{T} )

    # Add right column to left
    smith[:, i-1] += smith[:, i]
    right[:, i-1]  += right[:, i-1]
    # Put gcd in smith[i-1, i-1]
    sigma, tau, beta = solve_gcd_equation(smith[i-1, i-1], smith[i, i])
    alpha = div(smith[i-1, i-1], beta)
    gamma = div(smith[i, i], beta)
    # Make smith[i-1, i-1] = beta
    smith[i-1, :] = sigma * smith[i-1, :] + tau * smith[i, :]
    left[i-1, :] = sigma * left[i-1, :] + tau * left[i, :]
    # Make smith[i, i-1] = 0 again by adding row i-1 to i with factor -gamma
    smith[i, :] -= gamma  * smith[i-1, :]
    left[i, :]  -= gamma  * left[i-1, :]
    # Make smith[i-1, i] = 0 by acting on columns
    smith[:, i] -= tau * gamma * smith[:, i-1]
    right[:, i] -= tau * gamma * right[:, i-1]
  end

  function rescale_lower_matrix{T <: Int}( t::Int, jt::Int, 
                                           smith::Matrix{T},
                                           left::Matrix{T} )
    # Rescale lower matrices so they don't get too big
    maxrow::Int = size(smith, 1)
    diagelem::Int = smith[t, jt]
    maxmod::Int = 0;
    for i in (t+1):size(smith, 1)
      for j in (jt+1):size(smith, 2)
        smith[i, j] % diagelem == 0 && continue
        if maxmod == 0 || abs(smith[i, j] % diagelem) > maxmod
          maxrow = i
          maxmod = abs(smith[i, j] % diagelem)
        end
      end
    end
    if maxmod != 0
      smith[t, :] += smith[maxrow, :]
      left[t, :] += left[maxrow, :]
    end
  end

# function smith_normal_form{T <: Int}(matrix::Matrix{T})

#   smith::Matrix{T} = deepcopy(matrix)
#   left ::Matrix{T} = eye(T, size(smith, 1), size(smith, 1))
#   right::Matrix{T} = eye(T, size(smith, 2), size(smith, 2))

#   t::Int, jt::Int = 0, 0
#   for t in 1:size(smith, 2)
#     # First, find pivot
#     jt = choose_pivot(t, jt+1, smith, left)

#     # Then, make all elements but one zero in row and column
#     while nnz(smith[:, jt]) > 1 || nnz(smith[t, :]) > 1
#       improve_pivot_col(t, jt, smith, left)
#       print("col: $smith\n")
#       improve_pivot_row(t, jt, smith, right)
#       print("row: $smith\n")
#     end
#     print("Row $jt\n")
#   end

#   # Figure out non-zero columns and make them first
#   isNotZero = find([nnz(smith[:, i]) for i in 1:size(smith, 2)])
#   if length(isNotZero) != size(smith, 2)
#     isZero    = find([nnz(smith[:, i]) == 0 for i in 1:size(smith, 2)])
#     smith[:, 1:length(isNotZero)] = smith[:, isNotZero]
#     smith[:, length(isNotZero)+1:end] = 0
#     right[:, 1:length(isNotZero)], right[:, length(isZero)+1:end] = 
#        right[:, isNotZero], right[:, isZero]
#   end

#   # Finally, make sure things are divisible
#   for t in 2:size(smith, 2)
#     smith[t, t] % smith[t-1, t-1] != 0 &&
#       make_divisible(t, smith, left, right)
#   end

#   return smith, left, right
# end

  function get_min_max{T <: Int}(array::AbstractArray{T})
    #! Finds indices of maximum and minimum of elements
    #! 
    #! Maximum is found starting on the left, whereas minimum is found from the
    #! right. Minimum ignores null elements.
    #!
    #! returns: indices of min and max
    array = abs(array)
    maxi::(Int, T) = (1, array[1])
    i::Int = 2
    for i in 2:length(array)
      array[i] > maxi[2] && (maxi = (i, array[i]))
    end
    mini::(Int, T) = (i, array[i])
    for i in i-1:-1:1
      array[i] != 0                           &&
        (mini[2] == 0  || array[i] < mini[2]) &&
        (mini = (i, array[i]))
    end
    (mini[1], maxi[1])
  end 

  function check_nonzero{T <: Int}(matrix::Matrix{T}, index::Int)
    #! True if there are two non-zero items in row and in column "index"
    nnz(matrix[:, index]) <= 1 && nnz(matrix[index, :]) <= 1
  end

  function check_same_magnitude{T <: Int}(matrix::Matrix{T}, mini::Int,
                                          maxi::Int, index::Int,
                                          dotranspose::Bool=false)
    dotranspose ? (vi(x, y) = matrix[y, x]): (vi(x, y) = matrix[x, y]) 
    if abs(vi(mini, index)) == abs(vi(maxi, index))
      n0::Int, n1::Int = 0, 0
      for i in 1:size(matrix, dotranspose ? 2: 1)
        vi(maxi, i) != 0&& (n0 += 1)
        vi(mini, i) != 0&& (n1 += 1)
      end 
      return n0 < n1 ? (maxi, mini): (mini, maxi)
    end
    mini, maxi
  end

  function smith_col_impl{T <: Int}( left::Matrix{T}, 
                                     smith::Matrix{T}, 
                                     index::Int )
    while nnz(smith[:, index]) > 1
      # find min/max elements.
      mini::Int, maxi::Int = get_min_max(smith[:, index])
      mini, maxi = check_same_magnitude(smith, mini, maxi, index)
      # Remove multiple from column.
      multiple::Int = div(smith[maxi, index], smith[mini, index]);
      smith[maxi, :] -= multiple * smith[mini, :];
      left[maxi, :]  -= multiple * left[mini, :];
    end
    if smith[index, index] == 0
      k::Int = findfirst(smith[:, index])
      if k != index && k != 0
        smith[k, :], smith[index, :] = smith[index, :], smith[k, :]
        left[k, :], left[index, :] = left[index, :], left[k, :]
      end
    end
    if smith[index, index] < 0
      smith[index, :] *= -1
      left[index, :]  *= -1
    end
  end

  function smith_row_impl{T <: Int}( smith::Matrix{T}, 
                                     right::Matrix{T},
                                     index::Int )
    while nnz(smith[index, :]) > 1
      # find min/max elements.
      mini::Int, maxi::Int = get_min_max(smith[index, :])
      mini, maxi = check_same_magnitude(smith, mini, maxi, index, true)
      # Remove multiple from column.
      multiple::T = div(smith[index, maxi], smith[index, mini]);
      smith[:, maxi] -= multiple * smith[:, mini];
      right[:, maxi] -= multiple * right[:, mini];
    end
    if smith[index, index] == 0
      k::Int = findfirst(smith[index, :])
      if k != index && k != 0
        smith[:, k], smith[:, index] = smith[:, index], smith[:, k]
        right[:, k], right[:, index] = right[:, index], right[:, k]
      end
    end
    if smith[index, index] < 0
      smith[:, index] *= -1
      right[:, index] *= -1
    end
  end


  function smith_normal_form{T <: Int}(matrix::Matrix{T})

    @assert size(matrix, 1) == size(matrix, 2)
    @assert det(matrix) != 0
    smith::Matrix{T} = deepcopy(matrix)
    left::Matrix{T} = eye(T, size(matrix, 1), size(matrix, 1))
    right::Matrix{T} = eye(T, size(matrix, 2), size(matrix, 2))

    for index in 1:size(smith, 1)
      while !check_nonzero(smith, index)
        smith_col_impl(left, smith, index)
        smith_row_impl(smith, right, index)

        rescale_lower_matrix(index, index, smith, left)
      end
    end
        
    if smith[1, 1] < 0
      smith[1, :] *= -1
      left[1, :] *= -1
    end
    for i in 2:min(size(smith))
      # If divisible, nothing to do.
      if smith[i, i] % smith[i-1, i-1] != 0
        make_divisible(i, smith, left, right)
      end
      if smith[i, i] < 0
        smith[i, :] *= -1
        left[i, :] *= -1
      end
    end

#   @assert smith - diagm(diag(smith)) == zeros(eltype(smith), size(smith)...)
    smith, left, right
  end
                                


 #function smith_normal_form{T}(M::Array{T, 2})
 #  if abs(det(M)) < 
 #  local S::Array{T, 2} = copy(M)
 #  local R::Array{T, 2} = eye(3)
 #  local L::Array{T, 2} = eye(3)
 #end
 

end
