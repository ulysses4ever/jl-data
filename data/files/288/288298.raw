   function MetodoNewton (f,fd,x0)

        e = 0                       #e = 0 -> função converge
    i = 0
    xk = x0
    xk1 = x0                    
    while f(xk)!= 0

            if fd(xk)==0
                e = - 1             #e = -1 ->Derivada horizontal
                break
            end

    xk1 = xk - (f(xk)/fd(xk))

    if i>10000                       
        if xka == xk1
        e = -2                      #e = - 2 -> função alterna, sem convergir            
        else
        e = 1                       #e = 1 -> sem raiz ou divergente
        end
    break
    end 

    xka = xk
    xk = xk1
    i = i + 1                         

    end

        x = xk1
        f = f(xk1)
        k = i

    return(x,f,k,e)
    end

    f(x) = x^3 - x
    fd(x) = 3x^2 - 1


x,g,k,e = MetodoNewton (f,fd,sqrt(3)/3)
