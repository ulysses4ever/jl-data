

function linsfa(signal::Array{Float64})
    w_signal = whiten!(signal)
    w_sig_diff = timediff(w_signal)
    A = w_sig_diff * w_sig_diff'
    B = w_signal * w_signal'

    # F = eigfact(A, B)
    F = eigfact(B, A)

    return F[:vectors]
end

# ensure signal is zero mean and unit variance
function whiten!(signal::Array{Float64})
    # zero mean
    signal = signal.-mean(signal,1)

    # unit variance
    signal = signal./std(signal,1)
    return signal
end

function timediff(signal::Array{Float64})
    # xdiff = diff(signal, 1)
    xdiff = [signal[1, :] ; diff(signal, 1)]
    return xdiff
end


function timediff!(signal::Array{Float64})
    signal =  [signal[1, :] ; diff(signal, 1)]
end
