cd(string(dirname(@__FILE__)))

file = open("p081_matrix.txt")
numbers = readall(file)
close(file)
numbers

N = int(split(strip(numbers),[',','\n']))
M = reshape(N,80,80)'

function pe81(M)
  s = size(M,1)
  res = [M[1]]
  for i = 2:s # upper left triangle
    d = M[i:s-1:i*s-1]
    res = minimum([[res[1], res]+d  [res, res[end]]+d],2)
  end
  for i = 2:s # lower right triangle
    d = M[i*s:s-1:s*s]
    res = minimum([res[2:end]+d  res[1:end-1]+d],2)
  end
  return res[1]
end


@time pe81(M)

A = [131 673 234 103 18;
     201 96 342 965 150;
     630 803 746 422 111;
     537 699 497 121 956;
     805 732 534 37 331]

@time pe81(A)


