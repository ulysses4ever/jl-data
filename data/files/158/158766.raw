# Heavy tailed proposal
function randh()
  return 10.^(1.5 - 6.*rand())*randn()
end

function logsumexp(x)
  top = maximum(x)
  y = exp(x - top)
  return log(sum(y)) + top
end

function logdiffexp(a, b)
  return b + log(exp(a - b) - 1.)
end

