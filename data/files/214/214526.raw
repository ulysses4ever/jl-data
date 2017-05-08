function var_onepass(y::Array)
    #PURPOSE:
    # - A function that calculates the variance of an array
    #   in a single pass
    #
    #RETURNS:
    # - A floating point value of the sample variance
    #
    #NOTES:
    # - This has its downsites - can lead to precision errors
    #   if the numbers in the array are large
    #

    n = length(y);
    sum = zero(y[1]);
    sum2 = zero(y[1]);
    #Throw an error if we have NaNs, or Infs
    @assert n== length(y[isfinite(y)])

    #One pass
    for i in 1:n
        sum = sum + y[i];
        sum2 = sum2 + y[i]*y[i];
    end
    mean = sum/n;
    return (1/(n-1))*(sum2-n*mean^2);
end

function var_twopass(y::Array)
    #PURPOSE:
    # - A function that calculates the variance of an array
    #   going through the data twice
    #
    #RETURNS:
    # - A floating point value of the sample variance
    #
    #NOTES:
    # - Going through the data twice makes the calculation slower,
    #   but the end result is less prone to rounding errors.
    #

    n = length(y);
    sum = zero(y[1]);
    diffsum2 = zero(y[1]);
    #Throw an error if we have NaNs, or Infs
    @assert n == length(y[isfinite(y)])

    #First pass
    for i in 1:n
        sum = sum + y[i];
    end
    mean = sum/n;
    #Second pass
    for i in 1:n
        diffsum2 = diffsum2 + (y[i]-mean)*(y[i]-mean);
    end
    result = (1/(n-1))*diffsum2;
    return result
end


function var_dynamic(y::Array)
    #PURPOSE:
    # - A function that calculates the variance of an array
    #   going through the data once for large arrays (#elements > 10000)
    #   or twice for smaller arrays. Moreover, it also strips
    #   the array of any bad values: NaNs and +-Inf
    #
    #RETURNS:
    # - A floating point value of the sample variance
    #
    #NOTES:
    # - Going through the data twice makes the calculation slower,
    #   but the end result is less prone to rounding errors.
    # - The funtion throws away all +-Inf, and NaNs
    #
    n = length(y);
    #Strip the array y from all +-Inf, and NaNs
    if n!= length(y[isfinite(y)])
        println("Warning! Some Inf/NaNs exist in dataset!");
        y = y[isfinite(y)]
    end

    #We speed up the calculation if we have a very large array
    if n > 10000
        println("Variance calculated using one pass")
        return var_onepass(y::Array)
    else
        println("Variance calculated using two passes")
        return var_twopass(y::Array)
    end
end
