#===============================================================================
# Row/Column Swapping Functions
function swap_slice!(arr::AbstractMatrix, i::Int, j::Int, dim::Int, dim_size::Int)
    if dim == 1
        swap_row!(arr, i, j, dim_size)
    else
        swap_column!(arr, i, j, dim_size)
    end
end

#-------------------------------------------------------------------------------
function swap_row!(arr::AbstractMatrix, i::Int, j::Int, n::Int)
  for col = 1:n
    arr[i, col], arr[j, col] = arr[j, col], arr[i, col]
  end
end

#-------------------------------------------------------------------------------
function swap_column!(arr::AbstractMatrix, i::Int, j::Int, m::Int)
  for row = 1:m
    arr[row, i], arr[row, j] = arr[row, j], arr[row, i]
  end
end

#-------------------------------------------------------------------------------
function replace_slice!{T}(arr::AbstractMatrix{T}, r::AbstractMatrix{T},
                           i::Int, dim::Int, dim_size::Int)
  if dim == 1
    return replace_row!(arr, r, i, dim_size)
  else
    return replace_column!(arr, r, i, dim_size)
  end
end

#-------------------------------------------------------------------------------
function replace_row!{T}(arr::AbstractMatrix{T}, r::AbstractMatrix{T},
                         i::Int, n::Int)
    for col = 1:n
      arr[i, col] = r[col]
    end
end

#-------------------------------------------------------------------------------
function replace_column!{T}(arr::AbstractMatrix{T}, r::AbstractMatrix{T},
                            i::Int, m::Int)
    for row = 1:m
        arr[row, i] = r[row]
    end
end

#===============================================================================
# Sorting Algorithms
function sort!(arr::AbstractMatrix, lo::Int, hi::Int, ::InsertionSortAlg,
               o::Ordering, keys::Vector{Int}, dim::Int)

    if dim > 2 || dim < 1
        error("Only 2 dimensional arrays are supported")
    end

    dim_size = dim == 1 ? size(arr, 2) : size(arr, 1)

    @inbounds for i = lo+1:hi
        j = i
        while j > lo
            if mc_lt(o, arr, j, j - 1, keys, dim)
                swap_slice!(arr, j, j - 1, dim, dim_size)
                j -= 1
                continue
            end
            break
        end
    end
    return arr
end

#--------------------------------------------------------------------------------
function sort!(arr::AbstractMatrix, lo::Int, hi::Int, a::QuickSortAlg,
               o::Ordering, keys::Vector{Int}, dim::Int)

  if dim > 2 || dim < 1
    error("Only 2 dimensional arrays are supported")
  end

  dim_size = dim == 1 ? size(arr, 2) : size(arr, 1)

  @inbounds while lo < hi
    hi-lo <= SMALL_THRESHOLD && return sort!(arr, lo, hi, SMALL_ALGORITHM,
                                             o, keys, dim)
    mi = (lo+hi)>>>1
    if mc_lt(o, arr, mi, lo, keys, dim)
      swap_slice!(arr, mi, lo, dim, dim_size)
    end
    if mc_lt(o, arr, hi, mi, keys, dim)
      swap_slice!(arr, hi, mi, dim, dim_size)
    end
    if mc_lt(o, arr, mi, lo, keys, dim)
      swap_slice!(arr, mi, lo, dim, dim_size)
    end
    swap_slice!(arr, mi, lo, dim, dim_size)
    i, j = lo, hi
    while true
      i += 1; j -= 1;
      while mc_lt(o, arr, i, lo, keys, dim); i += 1; end;
      while mc_lt(o, arr, lo, j, keys, dim); j -= 1; end;
      i >= j && break
      swap_slice!(arr, i, j, dim, dim_size)
    end
    swap_slice!(arr, j, lo, dim, dim_size)
    lo < (j-1) && sort!(arr, lo, j-1, a, o, keys, dim)
    lo = j+1
  end
  return arr
end

#-------------------------------------------------------------------------------
function sort!(arr::AbstractMatrix, lo::Int, hi::Int, a::MergeSortAlg,
               o::Ordering, keys::Vector{Int}, dim::Int, t=similar(arr))

    if dim > 2 || dim < 1
        error("Only 2 dimensional arrays are supported")
    end

    dim_size = dim == 1 ? size(arr, 2) : size(arr, 1)

    @inbounds if lo < hi
        hi-lo <= SMALL_THRESHOLD && return sort!(arr, lo, hi, SMALL_ALGORITHM,
                                             o, keys, dim)

        m = (lo+hi)>>>1
        sort!(arr, lo,  m,  a, o, keys, dim, t)
        sort!(arr, m + 1, hi,  a, o, keys, dim, t)

        i, j = 1, lo
        while j <= m
            replace_slice!(t, slicedim(arr, dim, j), i, dim, dim_size)
            i += 1
            j += 1
        end

        i, k = 1, lo
        while k < j <= hi
            if mc_lt(o, arr, i, lo, keys, dim)
                swap_slice!(arr, k, j, dim, dim_size)
                j += 1
            else
                replace_slice!(arr, slicedim(t, dim, i), k, dim, dim_size)
                i += 1
            end
            k += 1
        end
        while k < j
            replace_slice!(arr, slicedim(t, dim, i), k, dim, dim_size)
            k += 1
            i += 1
        end
    end

    return arr
end
#-------------------------------------------------------------------------------
defalg(m::AbstractMatrix) = DEFAULT_STABLE
defalg{T<:Number}(m::AbstractMatrix{T}) = DEFAULT_UNSTABLE

#-------------------------------------------------------------------------------
sort!(m::AbstractMatrix, alg::Algorithm, order::Ordering, keys::Vector{Int},
      dim::Int = 1) =  sort!(m, 1, size(m, dim), alg,
                          order, keys, dim)
sort!(m::AbstractMatrix, keys::Vector{Int}; alg::Algorithm=defalg(m),
      lt::Function=isless, by::Function=identity, rev::Bool=false,
      order::Ordering=Forward, dim::Int = 1) =
      sort!(m, alg, ord(lt,by,rev,order), keys, dim)

sort(m::AbstractMatrix, keys::Vector{Int}; kws...) = sort!(copy(m), keys; kws...)

#-------------------------------------------------------------------------------
sortperm(m::AbstractMatrix, keys::Vector{Int}; alg::Algorithm=defalg(m),
         lt::Function=isless, by::Function=identity, rev::Bool=false,
         order::Ordering=Forward, dim::Int = 1) =
         sort!([1:size(m, dim)], 1, size(m, dim), alg,
                MCPerm(ord(lt, by, rev, order), m, keys,  dim))
