# TODO: Write sequential update for matrix
function updatemhseq!(obj::MetropolisVector)
  copy!(obj.can, obj.cur)     # reset the values of the candidate
  toggleupdating!(obj)  # turn on all updating flag for things impacted

  for i = 1:obj.length
    drawcandidate!(obj, i)  # get candidate value
    canimpacts!(obj)        # loop through and update everything this parameter impacts

    # log ratio for acceptance
    R = 0.0
    R += evalloglikelihood(obj)   # update the acceptance ratio with the diff in loglike
    R += evallogpriordiff(obj, i) # update the acceptance ratio with the logprior values

    # decide whether or not to accept or reject
    if (log(rand(1)[1]) < R)
      acceptcan!(obj, i)
      copycan2cur!(obj)
    end
  end
  toggleupdating!(obj)  # turn off all updating flags for things impacted
end

function updatemhseq!(obj::MetropolisMatrix)
  copy!(obj.can, obj.cur)  # reset the values of the candidate
  toggleupdating!(obj)  # turn on all updating flag for things impacted

  for j = 1:obj.nrows, i = 1:obj.ncols
    drawcandidate!(obj, i, j)  # get candidate value
    canimpacts!(obj)           # loop through and update everything this parameter impacts

    # log ratio for acceptance
    R = 0
    R += evallikelihood(obj)          # update the acceptance ratio with the diff in loglike
    R += evallogpriordiff(obj, i, j)  # update the acceptance ratio with the logprior values

    # decide whether or not to accept or reject
    if (log(rand(1)[1]) < R)
      acceptcan!(obj, i, j)
      copycan2cur!(obj)
    end
  end
  toggleupdating!(obj)  # turn off all updating flags for things impacted
end
