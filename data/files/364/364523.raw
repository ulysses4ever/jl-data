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
y = [0 1 1 0]

#Seeding random generator
srand(1)

#Randomly initialize the weights
syn0 = 2*rand(3,4)-1
syn1 = 2*rand(4,1)-1

l1 = []
l2 = []

display("Starting training: ")
display("----------------------------------------")
for i=0:10-1
  #forward propogation
  l0 = float(X)
  l1 = transpose(nonlin(l0*syn0))
  l2 = transpose(nonlin(l1*syn1))

  #calculate error
  display(y)
  display(l2)
  l2_error = y - l2

  if(i%10000 == 0)
    display(mean(abs(l2_error)))
  end

  δ2 = l2_error .* nonlin(l2,true)

  l1_error = δ2 * syn1

  δ1 = l1_error .* nonlin(l1,true)

  #update weights
  syn1 += transpose(l1) * transpose(δ2)
  syn0 += transpose(l0) * transpose(δ1)
end

display("Output after training:")
display(l1)
display(l2)