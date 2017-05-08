sigmoid(z) = 1./(1+exp(-z))

function sigprime(z)
        s = sigmoid(z)
        return s .* (1-s)
end

addBias(matr) = [-ones(size(matr,1),1) matr]

function costFunction(Theta1, Theta2, X, y)
        m=size(X,1)
        a1 = addBias(X)
        z2 = a1 * Theta1'
        a2 = sigmoid(z2)
        a2 = addBias(a2)
        z3 = a2 * Theta2'
        a3 = sigmoid(z3)
        J = (1/m) * sum(sum(-y.*log(a3) - (1-y).*log(1-a3)))

        Delta1=zeros(size(Theta1))
        Delta2=zeros(size(Theta2))
        for i=1:m
                d3 = a3[i,:]- y[i,:] #row
                Delta2 += d3' * a2[i,:]
                d2 = Theta2'[2:end,:] * d3' .* sigprime(z2[i,:]')
                Delta1 += d2 * a1[i,:]
        end
        Delta1 ./= m
        Delta2 ./= m
        return J, Delta1, Delta2
end

function gradientDescent(costFunc, Theta1, Theta2, X, y, alpha)
        (J, Delta1, Delta2) = costFunc(Theta1, Theta2, X, y)
        println(J)
        Theta1 -= alpha * Delta1
        Theta2 -= alpha * Delta2
        return Theta1, Theta2
end
