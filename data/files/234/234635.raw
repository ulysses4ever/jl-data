# TODO: Write block updates for vectors and matrices
function updatemhblock!(obj::MetropolisParameter)
  copy!(obj.can, obj.cur)  # reset the values of the candidate
  toggleupdating!(obj)     # turn on all updating flag for things impacted

  drawcandidate!(obj)  # get candidate value
  canimpacts!(obj)        # update everything this parameter impacts

  # log ratio for acceptance
  R = 0.0
  R += evalloglikelihood(obj)   # update acceptance ratio with the loglike
  R += evallogpriordiff(obj) # update acceptance ratio with the logprior

  # decide whether or not to accept or reject
  if (log(rand(1)[1]) < R)
    acceptcan!(obj)
  else
    # because we need the ith element of obj.can to be the only one that's
    # changed, we need to reset it back if it didn't get updated.
    copy!(obj.can. obj.cur)
  end

  toggleupdating!(obj)  # turn off all updating flags for things impacted
end