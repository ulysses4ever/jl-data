export count_inv

count_inv{T<:Number}(a::AbstractArray{T,1}) = count_inv!(copy(a))

count_inv!{T<:Number}(a::AbstractArray{T,1}) = count_inv!(a, 1, length(a))

function count_inv!{T<:Number}(
    a::AbstractArray{T,1}, lo::Integer, hi::Integer, t=similar(a, T, div(length(a), 2)))
  if lo < hi
    mid = (hi+lo) >>> 1
    lcount = count_inv!(a, lo, mid, t)
    rcount = count_inv!(a, mid+1, hi, t)
    scount = count_splits!(a, lo, mid, hi, t)
    lcount + rcount + scount
  else
    0
  end
end

function count_splits!(a, lo, mid, hi, t)
  count = 0

  i, j = 1, lo
  while j <= mid
    t[i] = a[j]
    i += 1
    j += 1
  end

  i, k = 1, lo
  while k < j <= hi
    if a[j] < t[i]
      a[k] = a[j]
      j += 1
      count += mid-i+1
    else
      a[k] = t[i]
      i += 1
    end
    k += 1
  end

  count
end
