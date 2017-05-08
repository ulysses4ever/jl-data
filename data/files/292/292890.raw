module SmithNormalForm
# Defines stuff around the Smith Normal Form

  export smith_normal_form
  
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

  function check_nonzero{T <: Int}(matrix::AbstractMatrix{T}, index::Int)
    #! True if there are two non-zero items in row and in column "index"
    nnz(matrix[:, index]) <= 1 && nnz(matrix[index, :]) <= 1
  end

  function check_same_magnitude{T <: Int}(matrix::AbstractMatrix{T}, mini::Int,
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

  function smith_col_impl{T <: Int}( left::AbstractMatrix{T}, 
                                     smith::AbstractMatrix{T}, 
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
      k::Int = 1
      for k in 1: size(smith, 1)
        smith[k, index] != 0 && break
      end
      if k != index 
        smith[k, :], smith[index, :] = smith[index, :], smith[k, :]
        left[k, :], left[index, :] = left[index, :], left[k, :]
      end
    end
    if smith[index, index] < 0
      smith[index, :] *= -1
      left[index, :]  *= -1
    end
  end

  function smith_row_impl{T <: Int}( smith::AbstractMatrix{T}, 
                                     right::AbstractMatrix{T},
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
      k::Int = 0
      for k in 1: size(smith, 2)
        smith[index, k] != 0 && break
      end
      if k != index 
        smith[:, k], smith[:, index] = smith[:, index], smith[:, k]
        right[:, k], right[:, index] = right[:, index], right[:, k]
      end
    end
    if smith[index, index] < 0
      smith[:, index] *= -1
      right[:, index] *= -1
    end
  end

  function smith_impl{T <: Int}( left::Array{T, 2}, 
                                 smith::Array{T, 2}, 
                                 right::Array{T, 2} )
    for index in 1:size(smith, 1)-1
      while !check_nonzero(smith, index)
        smith_col_impl(left, smith, index)
        smith_row_impl(smith, right, index)

        maxrow::Int = size(smith, 1)
        diag::Int = smith[index, index]
        maxmod::Int = 0
        for i in index+1:size(smith, 1)
          for j in index+1:size(smith, 2)
            modulus = abs(smith[i, j] % diag)
            if modulus != 0 && (maxmod == 0 || modulus > maxmod)
              maxrow = i
              maxmod = modulus
            end
          end # j loop
        end # i loop
        if maxmod != 0
          smith[index, :] += smith[maxrow, :]
          left[index, :]  += left[maxrow, :]
        end
      end # while loop
    end # index loop
    if smith[end, end] < 0
      smith[end, :] *= -1
      left[end, :] *= -1
    end
  end

  function smith_normal_form{T <: Int}(matrix::AbstractMatrix{T})
    left::AbstractMatrix{T} = eye(matrix)
    smith::AbstractMatrix{T} = deepcopy(matrix)
    right::AbstractMatrix{T} = eye(matrix)
    smith_impl(left, smith, right)
    @assert smith - diagm(diag(smith)) == zeros(eltype(smith), size(smith)...)
    diag(smith), left, right
  end
                              


 #function smith_normal_form{T}(M::Array{T, 2})
 #  if abs(det(M)) < 
 #  local S::Array{T, 2} = copy(M)
 #  local R::Array{T, 2} = eye(3)
 #  local L::Array{T, 2} = eye(3)
 #end
 

end
