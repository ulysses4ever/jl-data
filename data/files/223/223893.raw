

boxcar{T<:FloatingPoint}(n, ::Type{T}) = ones(T, n)
boxcar(n) = boxcar(n, Float64)

function bartlett{T<:FloatingPoint}(n, ::Type{T})

    nn = convert(T, n-1)
    o = one(T)
    w = zeros(T, n)

    for i=1:n
        w[i] = o - abs(2*(i-1)/nn - o)
    end
    return w
    
end
bartlett(n) = bartlett(n, Float64)


function welch{T<:FloatingPoint}(n, ::Type{T})

    nn = convert(T, n)
    o = one(T)
    w = zeros(T, n)

    for i = 1:n
        w[i] = o - (2*((i-o) - (nn-o)/2)/(nn+o) )^2
    end
    return w
end
welch(n) = welch(n, Float64)

function hanning{T<:FloatingPoint}(n, ::Type{T})

    nn = convert(T, n)
    o = one(T)
    w = zeros(T,n)

    for i = 1:n
        w[i] = o/2 * (o - cos(2*pi*(i-o)/(nn-o)))
    end

    return w
end
hanning(n) = hanning(n, Float64)


function hamming{T<:FloatingPoint}(n, ::Type{T})

    nn = convert(T, n)
    o = one(T)
    a = (25*o)/46
    b = o-a

    w = zeros(T,n)

    for i = 1:n
        w[i] = a - b*cos(2*pi*(i-o)/(nn-o))
    end

    return w
end
hamming(n) = hamming(n, Float64)

function blackman{T<:FloatingPoint}(n, ::Type{T})

    nn = convert(T, n-1)
    o = one(T)
    a0 = (7938*o)/18608
    a1 = (9240*o)/18608
    a2 = (1430*o)/18608

    w = zeros(T, n)

    for i = 1:n
        x = 2*pi*(i-o) / nn
        w[i] = a0 - a1*cos(x) + a2*cos(2*x)
    end

    return w
end
blackman(n) = blackman(n, Float64)



