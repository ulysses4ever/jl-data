cd(string(dirname(@__FILE__)))

file = open("p082_matrix.txt")
numbers = readall(file)
close(file)
numbers

N = int(split(strip(numbers),[',','\n']))
M = reshape(N,80,80)'

function pe82(M)
  r,c = size(M)
  res = M[:,1]
  for i = 2:c # colums
    d = M[:,i]
    tmp = res+d # step right
    down = tmp
    up = tmp
    for j = 1:r # step up or down (several times)

    end
    res = minimum([tmp [Inf; tmp[1:end-1]+d[2:end]] [tmp[2:end] + d[1:end-1]; Inf]],2)
  end
  res
  return minimum(res)
end


@time pe82(M)

A = [131 673 234 103 18;
     201 96 342 965 150;
     630 803 746 422 111;
     537 699 497 121 956;
     805 732 534 37 331]

@time pe82(A)

