function updatemh!(obj::MetropolisParameter)
  # generic call function used to update a metropolis parameter
  if obj.seq
    updatemhseq!(obj)
  else
    updatemhblock!(obj)
  end
end

function activevalue(obj::MetropolisParameter)
  # get either the current or candidate values from a metropolis parameter
  # used in the update functions
  if obj.updating
    return obj.can
  else
    return obj.cur
  end
end

function toggleupdating!(obj::MetropolisParameter)
  # set update flag to false whether currently updating
  obj.updating = obj.updating ? false : true
  for i = 1:length(obj.impacts)
    obj.impacts[i].updating = obj.impacts[i].updating ? false : true
  end
end

function canimpacts!(obj::MetropolisParameter)
  # updater(requires...) requires... unpacks the array named requires
  # loop over everything that this metropolis object impacts
  # allows the updatemh! function to accommodate any number of
  # possible updates
  for i = 1:length(obj.impacts)
    this_impact = obj.impacts[i]  # get the name of the object impacted
    this_impact.updater(this_impact, this_impact.requires...)  # candidate
  end

  # get candidate ll
  # generally speaking this array will have length 1, but sometimes a parameter
  # also impacts a random effect and we also need to evaluate the likelihood
  # for that too.
  for i = 1:length(obj.ll)
    this_ll = obj.ll[i]
    this_ll.updating = true
    this_ll.updater(this_ll, this_ll.requires...)
    this_ll.updating = false
  end
end

function evalloglikelihood(obj::MetropolisParameter)
  R = 0.0
  # evaluate the likelihood
  for i = 1:length(obj.ll)
    R += sum(obj.ll[i].can) - sum(obj.ll[i].cur)
  end

  return R
end

# draw from the candidate distribution
function drawcandidate!(obj::MetropolisVector, i::Integer)
  obj.att[i] += 1

  if obj.transform == transident
    obj.curstar[i] = obj.cur[i]
  else # transform candidate
    obj.curstar[i] = obj.transform(obj.cur[i], obj.support, false)
  end

  obj.canstar[i] = obj.curstar[i] + obj.mh[i] * rand(obj.canddist, 1)[1]

  if obj.transform == transident
    obj.can[i] = obj.canstar[i]
  else  # transform candidate
    obj.can[i] = obj.transform(obj.canstar[i], obj.support, true)
  end
end

function drawcandidate!(obj::MetropolisVector)
  for i = 1:obj.length
    drawcandidate!(obj, i)
  end
end

function drawcandidate!(obj::MetropolisMatrix, i::Integer, j::Integer)
  obj.att[i, j] += 1

  if obj.transform == transident
    obj.curstar[i, j] = obj.cur[i, j]
  else  # transform candidate
    obj.curstar[i, j] = obj.transform(obj.cur[i, j], obj.support, false)
  end

  obj.canstar[i, j] = obj.curstar[i, j] + obj.mh[i, j] * rand(obj.canddist, 1)[1]

  if obj.transform == transident
    obj.can[i, j] = obj.canstar[i, j]
  else  # transform candidate
    obj.can[i, j] = obj.transform(obj.canstar, obj.support, true)
  end
end

function drawcandidate!(obj::MetropolisMatrix)
  for j = 1:obj.ncols, i = 1:obj.nrows
    drawcandidate!(obj, i, j)
  end
end


function evallogpriordiff(obj::MetropolisVector, i::Integer)
  # when we transform a parmaeter, sometimes we want the prior to be on the
  # transformed space. Mostly used when working with a candidate that has a
  # uniform prior
  if !obj.usestar
    return logpdf(obj.prior, obj.can[i]) -
           logpdf(obj.prior, obj.cur[i])
  else
    return logpdf(obj.prior, obj.canstar[i]) -
           logpdf(obj.prior, obj.curstar[i])
  end
end

function evallogpriordiff(obj::MetropolisVector)
  R = 0.0
  for i = 1:obj.length
    R += evallogpriordiff(obj, i)
  end
  return R
end

function evallogpriordiff(obj::MetropolisMatrix, i::Integer, j::Integer)
  if !obj.usestar
    return logpdf(obj.prior, obj.can[i, j]) -
           logpdf(obj.prior, obj.can[i, j])
  else
    return logpdf(obj.prior, obj.canstar[i, j]) -
           logpdf(obj.prior, obj.canstar[i, j])
  end
end

function evallogpriordiff(obj::MetropolisMatrix)
  R = 0.0
  for j = 1:obj.ncols, i = 1:obj.nrows
    R += evallogpriordiff(obj, i, j)
  end
  return R
end

function copycan2cur!(obj::MetropolisParameter)
  # update the likelihood storage
  for i = 1:length(obj.ll)
    copy!(obj.ll[i].cur, obj.ll[i].can)
  end

  # update the elements that the parameter impacts
  for i = 1:length(obj.impacts)
    copy!(obj.impacts[i].cur, obj.impacts[i].can)
  end
end

#### methods used when accepting to copy
function acceptcan!(obj::MetropolisVector, i::Integer)
  obj.acc[i] += 1
  obj.cur[i] = obj.can[i]

  copycan2cur!(obj)
end

function acceptcan!(obj::MetropolisVector)
  obj.acc[:] += 1
  copy!(obj.cur, obj.can)

  copycan2cur!(obj)
end

function acceptcan!(obj::MetropolisVector, i::Integer, j::Integer)
  obj.acc[i, j] += 1
  obj.cur[i, j] = obj.can[i, j]

  copycan2cur!(obj)
end

function acceptcan!(obj::MetropolisMatrix)
  obj.acc[:, :] += 1
  copy!(obj.cur, obj.can)

  copycan2cur!(obj)
end

# update the candidate standard deviation
function updatestepsize!(obj::MetropolisVector, nattempts=50,
                         lower=0.8, higher=1.2)
  for i = 1:obj.length
    if obj.att[i] > nattempts
      acc_rate = obj.acc[i] / obj.att[i]
      if acc_rate < 0.25
        obj.mh[i] *= lower
      elseif acc_rate > 0.50
        obj.mh[i] *= higher
      end
      obj.acc[i] = 0
      obj.att[i] = 0
    end
  end
end

function updatestepsize!(obj::MetropolisMatrix, nattempts=50,
                         lower=0.8, higher=1.2)
  for j = 1:obj.ncols, i = 1:obj.nrows
    if obj.att[i, j] > nattempts  # avoid divide by 0
      acc_rate = obj.acc[i, j] / obj.att[i, j]
      if acc_rate < 0.25
        obj.mh[i, j] *= lower
      elseif acc_rate > 0.50
        obj.mh[i, j] *= higher
      end
      obj.acc[i, j] = 0
      obj.att[i, j] = 0
    end
  end
end