function resample(x::Array,num::Int)
  # resample signal in Fourier domain

  axis = 1 # default
  X = fft(x)
  Nx = size(x)[axis]

  # ** apply window function **

  newshape = int([x_ for x_ in size(x)])
  newshape[axis] = num
  N = int(min(num,Nx))
  Y = zeros(Complex128,tuple(newshape...))
  nrm = (num / Nx)
  for sl = 1:fld(N+1,2)
    Y[sl] = nrm*X[sl]
  end
  for sl = 0:-1:fld(-(N-1),2)+1
    Y[num+sl] =  nrm*X[Nx+sl]
  end

  return ifft(Y)

end
