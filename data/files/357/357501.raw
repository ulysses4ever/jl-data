using TimeIt
using AperturePhotometry

data = ones(10, 10)

error = 0.1 * ones(10, 10)
mask = falses(10, 10)

@timeit sum_circle(data, 5.0, 5.0, 4.0)
@timeit sum_circle(data, 5.0, 5.0, 4.0; mask=error, error=error, maskthresh=0.2)

@timeit sum_circann(data, 5.0, 5.0, 2.0, 4.0)
@timeit sum_circann(data, 5.0, 5.0, 2.0, 4.0; mask=error, error=error, maskthresh=0.2)


@timeit sum_ellipse(data, 5.0, 5.0, 3.0, 2.0, pi/4.)
@timeit sum_ellipse(data, 5.0, 5.0, 3.0, 2.0, pi/4.; mask=error, error=error, maskthresh=0.2)
