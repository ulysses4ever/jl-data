using TimeIt
using AperturePhotometry

data = ones(10, 10)

error = 0.1 * ones(10, 10)
mask = falses(10, 10)

@timeit sum_circle(data, nothing, 0.1, 5.0, 5.0, 3.0; maskthresh=1)
@timeit sum_circle(data, mask, error, 5.0, 5.0, 3.0)
@timeit sum_circle(data, 5.0, 5.0, 3.0)
