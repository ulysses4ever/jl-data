# Written in Julia by André Ferrari
# April 2015
#
# Translation in julia of algorithm in section 2.2:
# "Generating Stationary Processes via Circulant embedding"

# Kroese, D.P. and Botev, Z.I. (2013).
# "Spatial Process Generation."
# Lectures on Stochastic Geometry, Spatial Statistics and Random Fields,
# Volume II: Analysis, Modeling and Simulation of Complex Structures,
# V. Schmidt (Ed.).  Springer-Verlag, Berlin.
#
# http://arxiv.org/abs/1308.0399
#

module GHF

export genghf

function genghf(tx::Vector, ty::Vector, rho::Function)
    m = length(tx)
    n = length(ty)
    rows = zeros(m,n)
    cols = zeros(m,n)

    for i = 1:n, j = 1:m
        rows[j,i] = rho(tx[i]-tx[1],ty[j]-ty[1])
        cols[j,i] = rho(tx[1]-tx[i],ty[j]-ty[1])
    end

    blkcirc_row = [[rows cols[:,end:-1:2]] ,
        [cols[end:-1:2,:] rows[end:-1:2,end:-1:2]]]

    lam = real(fft(blkcirc_row))/(2*m-1)/(2*n-1)

    ind0 = lam .< 0.0
    if (isempty(ind0)) && (abs(minimum(lam[ind0])) > 1e-15)
        error("Could not find positive definite embedding!")
    else
        lam[ind0] = 0.0
        lam = sqrt(lam)
    end

    z = complex(randn(2*m-1, 2*n-1), randn(2*m-1, 2*n-1))
    f = fft(lam .* z)
    f = f[1:m,1:n]
    field1 = real(f)
#   field2 = imag(f)  # if needed

end
end
