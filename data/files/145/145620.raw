default_f(x) = x
function diff_from_function(x::Array, f=default_f)
  out = zeros(Float64, length(x));
  n = length(x);
  for i = 1:n
    out[i] = sum(f(x[1:i]))/i;
  end
  out
end

function fast_means(x::Array, f=default_f)
  out = zeros(Float64, length(x));
  n = length(x);
  out[1] = f(x[1]);
  for i = 2:n
    out[i] = (i-1)/i*out[i-1] + f(x[i])/i;
  end
  out
end

function stabalise(x::Array, target::Float64, range=0.01)
  n = length(x);
  first = 0;
  for i = n:-1:1
    if abs(x[i] - target)/target > range
      first = i;
      break;
    end
  end
  return(first)
end


