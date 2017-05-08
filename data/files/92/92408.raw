## function ptmvnorm(lowerx, upperx, μ, Σ, lower, upper, maxpts = 25000, abseps = 0.001, releps = 0)


##    lower = pmax(lowerx, -Inf)
##    upper = pmin(upperx, +Inf)
    
##  #Psi(b)-Psi(a)/

##   f <- pmvnorm(, upper=pmin(upperx, upper), mean=mean, sigma=sigma, maxpts = maxpts, abseps = abseps, releps = releps) /
##            pmvnorm(lower=lower, upper=upper, mean=mean, sigma=sigma, maxpts = maxpts, abseps = abseps, releps = releps)
##   return(f)



function mvt(lower, upper, df, corr, delta, algorithm = GenzBretz(),
    ...)
{
    addargs <- list(...)
    if (length(addargs) > 0)
        algorithm <- GenzBretz(...)
    if (is.function(algorithm) || is.character(algorithm))
        algorithm <- do.call(algorithm, list())
    if (any(abs(lower - upper) < sqrt(.Machine$double.eps)) ||
        any(is.na(lower - upper))) {
        RET <- list(value = 0, error = 0, msg = "lower == upper")
        return(RET)
    }
    n <- ncol(corr)
    if (is.null(n) || n < 2)
        stop("dimension less then n = 2")
    if (length(lower) != n)
        stop("wrong dimensions")
    if (length(upper) != n)
        stop("wrong dimensions")
    if (n > 1000)
        stop("only dimensions 1 <= n <= 1000 allowed")
    infin <- rep(2, n)
    infin[isInf(upper)] <- 1
    infin[isNInf(lower)] <- 0
    infin[isNInf(lower) & isInf(upper)] <- -1
    if (class(algorithm) == "Miwa") {
        if (any(infin == -1) & n >= 3) {
            WhereBothInfIs <- which(infin == -1)
            n <- n - length(WhereBothInfIs)
            corr <- corr[-WhereBothInfIs, -WhereBothInfIs]
            upper <- upper[-WhereBothInfIs]
            lower <- lower[-WhereBothInfIs]
        }
        if (any(infin == 0) & n >= 2) {
            WhereNegativInfIs <- which(infin == 0)
            inversecorr <- rep(1, n)
            inversecorr[WhereNegativInfIs] <- -1
            corr <- diag(inversecorr) %*% corr %*% diag(inversecorr)
            infin[WhereNegativInfIs] <- 1
            tempsaveupper <- upper[WhereNegativInfIs]
            upper[WhereNegativInfIs] <- -lower[WhereNegativInfIs]
            lower[WhereNegativInfIs] <- -tempsaveupper
        }
    }
    if (all(infin < 0))
        return(list(value = 1, error = 0, msg = "Normal Completion"))
    if (n > 1) {
        corrF <- matrix(as.vector(corr), ncol = n, byrow = TRUE)
        corrF <- corrF[upper.tri(corrF)]
    }
    else corrF <- corr
    ret <- probval(algorithm, n, df, lower, upper, infin, corr,
        corrF, delta)
    error <- ret$error
    value <- ret$value
    inform <- ret$inform
    msg <- NULL
    if (inform == 0)
        msg <- "Normal Completion"
    if (inform == 1)
        msg <- "Completion with error > abseps"
    if (inform == 2)
        msg <- "N greater 1000 or N < 1"
    if (inform == 3)
        msg <- "Covariance matrix not positive semidefinite"
    if (is.null(msg))
        msg <- inform
    RET <- list(value = value, error = error, msg = msg)
    return(RET)
}
