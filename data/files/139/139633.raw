function normalize!{T}(s::Array{T, 2})
# Normalize s so that the squared L2 vector norm of each row is at most 1

  dictSize = size(s, 1);
  for k=1:dictSize;
    norm_s = norm(s[k, :]);
    if norm_s*norm_s>1;
      s[k, :] /= norm_s;
    end
  end
end
