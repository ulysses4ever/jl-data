function nonlin(x,deriv=false)
  if(deriv==true)
    return x.*(1-x)
  end
  return 1.0./(1.0+exp(-x))
end

#Input dataset
X = [0 0 1;
     0 1 1;
     1 0 1;
     1 1 1]
y = transpose([0,0,1,1])

#Seeding random generator
srand(1)

#Randomly initialize the weights
syn0 = 2*randn(3,1)-1

l1 = []

for i in 0:10000-1
  #forward propogation
  l0 = float(X)
  l1 = transpose(nonlin(l0*syn0))

  #calculate error
  l1_error = y-l1

  #compute delta
  δ = l1_error .* nonlin(l1,true)

  #update weights
  syn0 += transpose(l0) * transpose(δ)
end

display("Output after training:")
display(l1)