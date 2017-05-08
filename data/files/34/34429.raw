using Digits

function pe206()

  smallest = int(floor(sqrt(1020304050607080900)))
  biggest = int(ceil(sqrt(1929394959697989990)))

  r = [smallest:10:biggest]

  res = 0
  for n in reverse!(r)
    tmp = n*n;
    if digits(tmp)[1:2:end] == [0,9:-1:1]
      res = n
      break
    end
  end

  return res
end

@time pe206()

1389019170^2

function pe()

  smallest = int(floor(sqrt(1020304050607080900)))
  biggest = int(ceil(sqrt(1929394959697989990)))

  n = smallest+20
  res = 0

  while res == 0
    tmp = n*n
    if digits(tmp)[1:2:end] == [0,9:-1:1]
      res = n
    end
    if n%100 == 30
      n += 40
    else
      n += 60
    end
  end

  return res
end

@time pe()

