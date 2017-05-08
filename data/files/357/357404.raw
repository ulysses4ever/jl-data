#####################################################
# Standardized environment for timing RSA attacks   #     
# against different plaintexts and public exponents #
#####################################################
function RSA_Attack_Timed(plaintext, public_exponent)

    # Standard RSA-100 primes
    p = 37975227936943673922808872755445627854565536638199
    q = 40094690950920881030683735292761468389214899724061
    
    # public modulus (~ 100 digits)
    N = p*q
    
    # encryption
    ciphertext = power_mod(plaintext, public_exponent, N)
    
    # ep parameter to use in Coppersmith method
    ep = 0.03;
    
    # offset the plaintext by a random amount
    # this will be our "guess" of M
    max_offset = ceil(0.5*N^(1/public_exponent-ep))
    guess = rand(-max_offset:max_offset) + plaintext
    
    # construct modular polynomial
    P(x) = (guess + x)^public_exponent - ciphertext
    
    tic()
    result = coppersmith(P, N, ep) + guess
    elapsed = toq();
    
    if (plaintext in result)
        return elapsed
    else
        print("RSA Attack FAILED")
        return 0.0
    end
    
end