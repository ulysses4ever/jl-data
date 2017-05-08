function plot_densitymatrix(densityMat)
  pygui(false)
  n = size(densityMat,1)
  x = zeros(n,n) # x represents the rows
  for i=1:n-1
    x[i+1,:] = i*ones(1,n)
  end

  realpart = real(vec(densityMat))
  imagpart = imag(vec(densityMat))

  subplot(111, projection="3d")
  bar3D(vec(x),vec(x'),vec(zeros(n,n)),1,1,realpart)
  subplot(111, projection="3d")
  bar3D(vec(x),vec(x'),vec(zeros(n,n)),1,1,abs(vec(densityMat)))
end
