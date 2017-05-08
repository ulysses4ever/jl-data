# These tests have been adapted from Criterim clojure library

macro fact_max_err(expected, actual, max_err)
    :(@fact abs(($expected) - ($actual)) < $max_err => true)
end

facts("bootstrap estimate") do
    C = Criterion 
    testdata = rand(10_000)
    est_mean  = C.bootstrap_bca(testdata, mean, 0.05, 1000)
    @fact (est_mean.point  - 0.5) < 1e-2 => true
    @fact_max_err 0.5 est_mean.lbound  0.02
    @fact_max_err 0.5 est_mean.ubound  0.02
    @fact C.scale_bootstrap_estimate((4.5, 5.5), 0.1) => (0.45, 0.55)
end

facts("bootstrap bca") do
    C = Criterion
    context("mean") do 
        test_data = ones(20)
        est_mean  = C.bootstrap_bca(test_data, mean, 0.05, 100)
        @fact est_mean.point  => roughly(1.0)
        @fact est_mean.lbound => roughly(1.0)
        @fact est_mean.ubound => roughly(1.0)
    end

    context("variance") do
        test_data = ones(20)
        est_var   = C.bootstrap_bca(test_data, std, 0.05, 100)
        @fact est_var.point  => roughly(0.0)
        @fact est_var.lbound => roughly(0.0)
        @fact est_var.ubound => roughly(0.0)
    end
end

facts("normal quantile") do
    nq = Criterion.normal_quantile

    @fact nq(0.5001) > 0 => true
    @fact nq(0.4999) < 0 => true
    @fact 2e-8 < (nq(0.999) - nq(0.001)) => true
    let max_error = 1e-7
        @fact_max_err  1.2815515655446   nq(0.9)  max_error
        @fact_max_err  0.674489750196082 nq(0.75) max_error
        @fact_max_err -1.03643338949379  nq(0.15) max_error
        @fact_max_err -2.32634787404084  nq(0.01) max_error
    end
end

facts("normal cdf test") do
    normal_cdf = Criterion.normal_cdf
    max_error = 1.5e-7
    @fact_max_err 0.99865010196837  normal_cdf(3.0) max_error
    @fact_max_err 0.977249868051821 normal_cdf(2.0) max_error
    @fact_max_err 0.841344746068543 normal_cdf(1.0) max_error
    @fact_max_err 0.691462461274013 normal_cdf(0.5) max_error
    @fact_max_err 0.5 normal_cdf(0.0) max_error
    @fact_max_err 0.158655253931457 normal_cdf(-1.0) max_error
    @fact_max_err 0.00134989803163009 normal_cdf(-3.0) max_error
end
