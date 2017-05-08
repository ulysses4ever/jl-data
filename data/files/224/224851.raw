# slice sample (Neal 2003)
# copied from MATLAB

function slice_sample(log_f::Function, x0, width=10, max_iter=200)
	z = log_f(x0) + log(rand());
	xl = x0 - width * rand();
	xr = xl + width;
    for i = 1 : max_iter
        if log_f(xl) > z
            xl -= width
        else
            break
        end
    end
    for i = 1 : max_iter
        if log_f(xr) > z
            xr += width
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
        end
    end
    xp
end
