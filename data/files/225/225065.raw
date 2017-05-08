module BasePi

export basepi

function nextdigit(d::BigFloat, _pi::BigFloat)
    d *= _pi
    digit = floor(Int, d)
    (digit, d - digit)
end

function basepi{T}(n::T, prec=20)
    with_bigfloat_precision(ceil(Int, log2(10) * (prec + 2))) do
        d = BigFloat(n)
        _pi = BigFloat(pi)
        magnitude = ceil(Int, log(_pi, d))
        d /= _pi^magnitude

        s = ""

        for i in 1:magnitude+prec
            (digit, d) = nextdigit(d, _pi)
            s *= string(digit)
        end

        s[1:magnitude] * "." * s[magnitude+1:end]
    end
end

end  # module BasePi
