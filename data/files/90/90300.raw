immutable CanonicalCorrelation{T} <: RegressionModel
    X::Matrix{T}        # (centered) input X
    Y::Matrix{T}        # (centered) input Y
    coefX::Matrix{T}    # canonical coefficients of X
    coefY::Matrix{T}    # canonical coefficients of Y
    r::Vector{T}        # canonical correlations
end

coef(cc::CanonicalCorrelation) = (cc.coefX, cc.coefY)
Base.cor(cc::CanonicalCorrelation) = cc.r
scores(cc::CanonicalCorrelation) = (cc.X*cc.coefX, cc.Y*cc.coefY)

function canoncor(X::AbstractMatrix, Y::AbstractMatrix; center::Bool=true)
    if center
        X = X .- mean(X, 1)
        Y = Y .- mean(Y, 1)
    end
    qr1 = qrfact(X)
    qr2 = qrfact(Y)
    usv = svdfact(full(qr1[:Q])'*full(qr2[:Q]))
    A = qr1[:R]\usv[:U]
    B = qr2[:R]\usv[:Vt]'

    s = sqrt(size(X, 1) - 1)
    scale!(A, s)
    scale!(B, s)

    CanonicalCorrelation(X, Y, A, B, usv[:S])
end
