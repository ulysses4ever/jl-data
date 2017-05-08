function fastFFT(x)
  # function fastFFT
  # perform fast fourier transform
  # using the simplest radix-2, decimation-in-time algorithm
  # Input:
  #   x - input vector
  #output:
  #   X - fourier coefficients

  # get length of input vector
  N = length(x)
  # initialize output fourier coefficients
  X = zeros(1,N) + zeros(1,N)*im
  # twiddle factor
  W = exp(-im*2*pi/N)

  if N == 2
    # base case
    X[1] = x[1] + x[2]
    X[2] = x[1] - x[2]
  else
    # recursive procedure
    for k = 1:N/2
      E = fastFFT(x[1:2:end])
      O = fastFFT(x[2:2:end])
      X[k] = E[k] + W^(k-1)*O[k]
      X[k+N/2] = E[k] + W^(k-1+N/2)*O[k]
    end
  end

  return X'
end

# test cases
x = [1,2,3,4]  # test input vector
fft(x)         # julia implementation of FFT
fastFFT(x)     # my implementation of FFT
