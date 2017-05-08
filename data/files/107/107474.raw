import Base.getindex

type DelayedBuffer
    data::Array{Float64,1}
    w_len::Int
    w_inc::Int
    delay::Int
    z::Array{Float64,1}

    function DelayedBuffer(data::Array{Float64,1},w_len::Int,w_inc::Int)
        delay = w_len-w_inc
        z = zeros(delay)
        new(data,w_len,w_inc,delay,z)
    end
end

function getindex(x::DelayedBuffer, i::Integer)
    ll = 1+(i-1)*x.w_inc-x.delay
    rr = (i-1)*x.w_inc+x.w_len-x.delay
    if ll < 1 # accessing delay indexes
        return vcat(x.z[1:abs(ll)+1], x.data[1:rr])
    elseif ll > length(x.data)-x.delay
        error("BoundsError")
    elseif rr > length(x.data)
        return vcat(x.data[ll:end], x.z[1:(rr-length(x.data))])
    else
        return x.data[ll:rr]
    end
end
