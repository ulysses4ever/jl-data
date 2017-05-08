module Solvers
using DataArrays

    function cg(A, b, x, maxiter, eps)
    # Conjugate Gradients method
    # INPUT: A, b, starting value x, max numer of iterations maxiter, error tolerance eps<1

        i           = 0;
        r           = b - A*x;
        d           = r;
        delta_new   = dot(r,r); #r'*r;
        delta_0     = delta_new;
        while i <= maxiter && delta_new[1] > (eps^2)*delta_0
            q       = A*d;
            alpha   = delta_new/dot(d,q) #(d'*q);
            x       = x + alpha*d;

            # Error
            if mod(i,50)==0    # if stucked somewhere
                r = b - A*x;
            else
                r = r - alpha*q;
            end

            # Update
            delta_old = delta_new;
            delta_new = dot(r,r) #r'*r;
            beta      = delta_new/delta_old;
            d         = r + beta*d;
            i         = i+1;

        end #while
        return x
    end #function

end
