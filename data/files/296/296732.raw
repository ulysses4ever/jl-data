function LLL_reduce(Lambda, c=2)
    
    # dimension of lattice matrix
    n = size(Lambda, 2)
 
    # compute projection coeffcients of v
    function mu(v, i, Q)
        sum([dot(v, Q[:,j])/dot(Q[:,j], Q[:,j]) for j=i:n])
    end
 
    while true
        # size reduction step
        finished = true
        for i = 1:n
            for j = (i-1):-1:1
                z = int(dot(Lambda[:,i], Lambda[:,j])
                Lambda[:,i]-=Lambda[:,j]*z
                /norm(Lambda[:,j])^2
            end
        end
        
        # Grant-Schmidt orthogonalization
        Q, R = qr(Lambda)
        
        # check c-reduced condition
        for i = 1:(n-1)
            if norm(mu(Lambda[:,i], i, Q))^2 > 
              (4*c/(4+c))*norm(mu(Lambda[:,i+1], i, Q))^2
                # Swap consecutive vectors
                Lambda[:,i], Lambda[:,i+1] = 
                Lambda[:,i+1], Lambda[:,i]
                finished = false
            end
        end
        if finished
            return Lambda
        end
    end
end