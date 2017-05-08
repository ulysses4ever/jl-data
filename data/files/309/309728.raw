function solver_irls(xref,XX,p,din,itMax,itTol,myeps,k)
  # function solver irls
  # implementes iterative reweighted least square optimization algorithm (batch)
  # inputs:
  #    xref   - reference microphone signal
  #    XX     - convolution matrix
  #    p      - parameter for updating weight/variances
  #    din    - initial estimation of clean speech
  #    itMax  - maximum number of iteration for the optimization algorithm
  #             [10]
  #    itTol  - error tolerance for the optimization algorithm
  #             [1e-4]
  #    myeps  - lower bound for estimation of variance,
  #             small positive constant to avoid zero division
  #             [1e-8]
  #    k      - current frequency bin
  # outputs:
  #    g      - prediction filter [vector, size = size(XX,2),1]
  #
  # Author: Zichao Wang
  # Date  : Aug 4, 2015

  # initial estimate
  d = din

  # initialize g vector
  g = zeros(size(XX,2),1) + im*zeros(size(XX,2),1)

  # iterative procedure
  for ii = 1:itMax

    d_old = d

    # update weights
    w = ( abs(d).^2 + myeps ).^(p/2-1);
    w = w[:]

    # estimate regression filters
    Q = XX' * diagm( w ) * XX
    b = XX' * diagm( w ) * xref

    #estimate prediction filter
    g = Q \ b # backsolve

    # estimate clean speech
    d = xref - XX*g

    # check convergence
    if ii>1 && vecnorm(d-d_old)/vecnorm(d_old) < itTol
      @printf "k=%d, ii=%d - d converged\n" k ii
      # keyboard
      break
    end

  end

  return g
end

