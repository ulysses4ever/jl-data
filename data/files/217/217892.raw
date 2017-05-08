# These tests have been adapted from Criterim clojure library

facts("outlier effect") do
    C = Criterion
    @fact C.outlier_effect(0.009) => C.Unaffected()
    @fact C.outlier_effect(0.09)  => C.Slight()
    @fact C.outlier_effect(0.45)  => C.Moderate()
    @fact C.outlier_effect(0.51)  => C.Severe()
end

facts("outliers") do
    C = Criterion
    @fact C.classify_outliers([1,2,5,7,8])        => C.Outliers(5, 0, 0, 0, 0)
    @fact C.classify_outliers([1,2,3,5,7,8])      => C.Outliers(6, 0, 0, 0, 0)
    @fact C.classify_outliers([-100,1,2,5,7,8,9]) => C.Outliers(7, 1, 0, 0, 0)
    @fact C.classify_outliers([-10,1,2,5,7,8,9])  => C.Outliers(7, 0, 1, 0, 0)
    @fact C.classify_outliers([1,2,3,5,7,8,22])   => C.Outliers(7, 0, 0, 1, 0)
    @fact C.classify_outliers([1,1,2,5,7,8,100])  => C.Outliers(7, 0, 0, 0, 1)
end

facts("outlier significance") do 
    # http://www.ellipticgroup.com/misc/article_supplement.pdf, p22  
    mean_est = 1.395522860870968
    std_est  = sqrt(0.0013859776344426547 * 0.0013859776344426547)
    niter    = 67108864
    o_var = Criterion.outlier_variance(mean_est, std_est, niter)
    @fact o_var.frac => 0.9960022873987793
end
