export ppsimple

function ppsimple(pold::PolynomialProbability)
    pnew = PolynomialProbability()

    for pi = 1:length(pold)
        piece = pold[pi]
        if (!isempty(piece.polys))
            order = sortperm(piece.exp, rev=true)
            allexp = piece.exp[order]
            allpoly = piece.polys[order, :]

            # Combine like exponents
            npoly = allpoly[1, :]
            nexp = [allexp[1]]
            for ii = 2:length(allexp)
                if allexp[ii] == nexp[end]
                    npoly[end, :] = npoly[end, :] + allpoly[ii, :]
                else
                    push!(nexp, allexp[ii])
                    npoly = vcat(npoly, allpoly[ii, :])
                end
            end

            # Eliminate zero rows and columns
            nonzero = npoly .== 0 # just initialize
            nonzero[:, end:-1:1] = cumsum(float(npoly[:, end:-1:1] .!= 0), 2) .!= 0
            colskept = sum(nonzero, 1) .!= 0
            rowskept = sum(nonzero, 2) .!= 0
            npoly = npoly[rowskept, colskept]
            nexp = nexp[collect(rowskept)]
        else
            npoly = zeros(1, 1)
            nexp = [0.]
        end

        append!(pnew, piece.t0, piece.t1, npoly, nexp)
    end

    pnew
end
