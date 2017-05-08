module MMA

export std, var, dist, rms, angle

function std(x)
  return vecnorm(x - mean(x))/sqrt(length(x))
end

function var(x)
  return sum((x - mean(x)).^2)/length(x)
end

function dist(x, y)
  return vecnorm(x - y)
end

function rms(x)
  return vecnorm(x)/sqrt(length(x))
end

function angle(x, y)
  return acos(dot(x, y)/(vecnorm(x) * vecnorm(y)))
end

end # module
