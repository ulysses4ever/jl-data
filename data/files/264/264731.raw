isdefined(Base, :__precompile__) && __precompile__()

module PeaksAndValleys

using Compat

export PEAK, VALLEY
export identify_initial_pivot, peak_valley_pivots, max_drawdown
export compute_segment_returns, pivots_to_modes

@compat const PEAK, VALLEY = Int8(1), Int8(-1)

"""Quickly identify the xs[1] as a peak or valley."""
function identify_initial_pivot(xs, up_thresh, down_thresh)
    x_1 = xs[1]
    max_x = x_1
    max_t = 1
    min_x = x_1
    min_t = 1
    up_thresh += 1
    down_thresh += 1

    for (t, x_t) in enumerate(xs[2:end])
        t += 1  # I wish Julia had an enumerate(*,from=X)

        if x_t / min_x >= up_thresh
            return min_t == 1 ? VALLEY : PEAK
        end

        if x_t / max_x <= down_thresh
            return max_t == 1 ? PEAK : VALLEY
        end

        if x_t > max_x
            max_x = x_t
            max_t = t
        end

        if x_t < min_x
            min_x = x_t
            min_t = t
        end
    end
    x_1 < xs[length(xs)] ? VALLEY : PEAK
end


"""
Finds the peaks and valleys of a series.

Parameters
---
- **xs** : This is your series.
- **up_thresh** : The minimum relative change necessary to define a peak.
- **down_thesh** : The minimum relative change necessary to define a valley.

Returns
---
an array with 0 indicating no pivot and -1 and 1 indicating valley and peak
respectively.


The First and Last Elements
---
The first and last elements are guaranteed to be annotated as peak or
valley even if the segments formed do not have the necessary relative
changes. This is a tradeoff between technical correctness and the
propensity to make mistakes in data analysis. The possible mistake is
ignoring data outside the fully realized segments, which may bias analysis.
"""
function peak_valley_pivots(xs, up_thresh, down_thresh)
    assert(down_thresh < 0) # "It must be negative.

    initial_pivot = identify_initial_pivot(xs, up_thresh, down_thresh)

    t_n = length(xs)
    pivots = zeros(Int8, t_n)
    pivots[1] = initial_pivot

    # Adding one to the relative change thresholds saves operations. Instead
    # of computing relative change at each point as x_j / x_i - 1, it is
    # computed as x_j / x_1. Then, this value is compared to the threshold + 1.
    # This saves (t_n - 1) subtractions.
    up_thresh += 1
    down_thresh += 1

    trend = -initial_pivot
    last_pivot_t = 1
    last_pivot_x = xs[1]
    for (t, x) in enumerate(xs[2:end])
        t += 1
        r = x / last_pivot_x

        if trend == -1
            if r >= up_thresh
                pivots[last_pivot_t] = trend
                trend = 1
                last_pivot_x = x
                last_pivot_t = t
            elseif x < last_pivot_x
                last_pivot_x = x
                last_pivot_t = t
            end
        else
            if r <= down_thresh
                pivots[last_pivot_t] = trend
                trend = -1
                last_pivot_x = x
                last_pivot_t = t
            elseif x > last_pivot_x
                last_pivot_x = x
                last_pivot_t = t
            end
        end
    end

    pivots[t_n] == 0 && (pivots[t_n] = trend)

    return pivots
end


"""
Return the absolute value of the maximum drawdown of sequence X.

Note
---
If the sequence is increasing, 0 is returned."""
function max_drawdown(xs)
    mdd = 0
    peak = xs[1]
    for x in xs
        if x > peak 
            peak = x
        end
        dd = (peak - x) / peak
        if dd > mdd
            mdd = dd
        end
    end
    return mdd
end


"""Return a numpy array of the pivot-to-pivot returns for each segment."""
function compute_segment_returns(xs, pivots)
    pivot_points = xs[pivots .!= 0]
    return pivot_points[2:end] ./ pivot_points[1:end-1] - 1.0
end


"""
Translate pivots into trend modes.

Parameters
---
pivots : the result of calling `peak_valley_pivots`

Returns
---
A vector of trend modes. That is, between (VALLEY, PEAK] it is 1 and
between (PEAK, VALLEY] it is -1.
"""
function pivots_to_modes(pivots)
    modes = zeros(Int8, length(pivots))
    modes[1] = pivots[1]
    mode = -modes[1]
    for (t, x) in enumerate(pivots[2:end])
        if x != 0
            modes[t+1] = mode
            mode = -x
        else
            modes[t+1] = mode
        end
    end
    modes
end

end
