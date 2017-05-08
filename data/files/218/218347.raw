# SFA by linear expansion



function linsfa(H::Matrix)
    Z = whiten(H)
    Zdiff = timediff(Z)
    A = Zdiff * Zdiff'
    B = Z * Z'

    # F = eigfact(A, B)
    F = eigfact(B, A)

    # return SlowSignals(F[:vectors])
    return F[:vectors]
end
