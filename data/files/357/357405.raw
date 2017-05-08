function DecrpytRSA(guess, C, N, r, ep)
    # construct modular polynomial
    # C is the ciphertext
    # N is the public modulus
    # r is the public exponent
    # ep is passed into Coppersmith solver
    P(x) = ((guess + x)^r - C) % N
    
    tic()
    result = CoppersmithSolve(P, N, ep) + guess
    toc()
    println("decrypted text: ", result)
    return result
end