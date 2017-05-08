# TODO: Write sequential update for matrix
function updatemhseq!(obj::MetropolisVector)
  copy!(obj.can, obj.cur)  # reset the values of the candidate
  toggleupdating!(obj)     # turn on all updating flag for things impacted

  for i = 1:obj.length
    drawcandidate!(obj, i)  # get candidate value
    canimpacts!(obj)        # update everything this parameter impacts

    # log ratio for acceptance
    R = 0.0
    R += evalloglikelihood(obj)   # update acceptance ratio with the loglike
    R += evallogpriordiff(obj, i) # update acceptance ratio with the logprior

    # decide whether or not to accept or reject
    if (log(rand(1)[1]) < R)
      acceptcan!(obj, i)
    else
      # because we need the ith element of obj.can to be the only one that's
      # changed, we need to reset it back if it didn't get updated.
      obj.can[i] = obj.cur[i]
    end
  end
  toggleupdating!(obj)  # turn off all updating flags for things impacted
end

function updatemhseq!(obj::MetropolisMatrix)
  copy!(obj.can, obj.cur)  # reset the values of the candidate
  toggleupdating!(obj)  # turn on all updating flag for things impacted

  for j = 1:obj.nrows, i = 1:obj.ncols
    drawcandidate!(obj, i, j)  # get candidate value
    canimpacts!(obj)           # update everything this parameter impacts

    # log ratio for acceptance
    R = 0
    R += evallikelihood(obj)          # update acc ratio with the loglike
    R += evallogpriordiff(obj, i, j)  # update acc ratio with the logprior

    # decide whether or not to accept or reject
    if (log(rand(1)[1]) < R)
      acceptcan!(obj, i, j)
    else
      # because we need the ijth element of obj.can to be the only one that's
      # changed, we need to reset it back if it didn't get updated.
      obj.can[i, j] = obj.cur[i, j]
    end
  end
  toggleupdating!(obj)  # turn off all updating flags for things impacted
end
