function convmtx(v,n)
  # function convmtx
  # computes a convolution matrix
  # input:  v - a vector
  #         n - number of columns for the convolution matrix
  # output: V - convolution matrix
  # NOTE: this function is only suitable for column vector as input,
  #       for the use of dereverberation algorithm. A generalized
  #       version of this algorithm needs to be developed.
  #
  # Author: Zichao Wang
  # Date  : Aug 4, 2015

  # get length of the vector
  len = length(v)


  if n > 1

    # zero padding
    temp_v = [v;zeros(n-1,1)]

    # initialize conv matrix
    V = zeros(length(temp_v),n) + im*zeros(length(temp_v),n)

    # fill in the conv matrix
    for col = 1:size(V,2)
      temp_v = [zeros(col-1,1);v;zeros(n-col,1)]
      V[:,col] = temp_v
    end

    return V

  # return the original vector if n is 1
  elseif n == 1
    return v
  end

  return V
end

# test cases
# h = [1+im;2;3;4]
# length(h)
# H = convmtx(h,2)
