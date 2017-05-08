# slice sample (Neal 2003)
# copied from MATLAB

function slice_sample(log_f::Function, x0; width=10, max_iter=200, ub=Inf, lb=-Inf)
    z = log_f(x0) + log(rand());
    xl = x0 - width * rand();
    xr = xl + width;
    for i = 1 : max_iter
        if log_f(xl) > z
            xl -= width
            if xl < lb
                xl = lb
                break
            end
        else
            break
        end
    end
    for i = 1 : max_iter
        if log_f(xr) > z
            xr += width
            if xr > ub
                xr = ub
                break
            end
        else
            break
        end
    end
    xp = rand()*(xr - xl) + xl
    for i = 1 : max_iter
        if log_f(xp) > z
            break
        else
            if xp > x0
                xr = xp
            else
                xl = xp
            end
            xp = rand()*(xr - xl) + xl
            if xp < lb
                xp = lb
            elseif xp > ub
                xp = ub
            end
        end
    end
    xp
end
