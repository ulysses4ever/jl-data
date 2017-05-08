#  The MIT License (MIT)
#
#   Copyright 2014 Peter Schulam
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy of
#   this software and associated documentation files (the "Software"), to deal in
#   the Software without restriction, including without limitation the rights to
#   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
#   the Software, and to permit persons to whom the Software is furnished to do so,
#   subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in all
#   copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
#   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
#   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
#   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
#   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

type GaussianProcess
    noise::Float64
    kernel::CovarianceKernel
end

type GaussianProcessPrediction
    mean::Vector{Float64}
    sd::Vector{Float64}
end

function gppredict(gp::GaussianProcess,
                 x_in::Vector{Float64},
                 y_in::Vector{Float64},
                 x_out::Vector{Float64})

    n_in = size(x_in, 1)
    n_out = size(x_out, 1)

    mu_in = zeros(n_in)
    mu_out = zeros(n_out)

    sigma_in = gpcov(gp.kernel, x_in, x_in)
    sigma_in += gp.noise ^ 2 * eye(n_in)
    
    sigma_out = gpcov(gp.kernel, x_out, x_out)

    sigma_in_out = gpcov(gp.kernel, x_in, x_out)
    sigma_out_in = sigma_in_out'

    pred_mean = mu_out
    pred_mean += sigma_out_in * inv(sigma_in) * y_in

    pred_var = sigma_out
    pred_var -= sigma_out_in * inv(sigma_in) * sigma_in_out

    pred_sd = sqrt(diag(pred_var))

    GaussianProcessPrediction(pred_mean, pred_sd)
end