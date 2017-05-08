## 18.336 PS 1
#This applies an operation to everything except you, assuming the group
## define a state variable s = sum of everything until you
## define a second state variable t = sum of everything after you
N = 40;
y = rand(0:10,N);

## this function works for any general symmetric binary operator, \oplus
function exclusive_prefix_suffix!(y,⊕)
  N = length(y);
  s = zeros(N);
  t = zeros(N);
  for i=2:N
  s[i] = s[i-1]⊕y[i-1]
  t[N-i+1] = t[N-i+2]⊕y[N-i+2]
  end
  for i=1:N
  y[i] = t[i]⊕s[i];
  end
  y
end

exclusive_prefix_suffix!([1:8],+)
#NB: redefine s0,t0 to ones() so as to ensure the identiy
exclusive_prefix_suffix!([1:15],*)
#That's it!
