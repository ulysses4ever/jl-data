# SFA by linear expansion



function linsfa(H::Matrix)
    Z = whiten(H)
    Zdiff = diff(Z, 1)
    A = Zdiff * Zdiff'
    B = Z * Z'

    evecs = eigfact(A, B)

    return SlowSignals(evecs[:vectors])
end
