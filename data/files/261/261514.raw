function triad(b::Vector, c::Vector, d::Vector)
  assert(length(b)==length(c)==length(d))
  a = similar(b)
  for i in 1:length(a)
     a[i] = b[i] + c[i] * d[i]
  end
  return a
end

function triad_twist1(b::Vector, c::Vector, d::Vector)
  assert(length(b)==length(c)==length(d))
  a = similar(b)
  for i in 1:length(a)
     if c[i]<0.
       a[i] = b[i] - c[i] * d[i]
     else
       a[i] = b[i] + c[i] * d[i]
     end
  end
  return a
end

function triad_twist2(b::Vector, c::Vector, d::Vector)
  assert(length(b)==length(c)==length(d))
  a = similar(b)
  for i in 1:length(a)
     if c[i]<0.
       a[i] = b[i] - c[i] * d[i]
     end
  end
  for i in 1:length(a)
     if c[i]>0.
       a[i] = b[i] + c[i] * d[i]
     end
  end
  return a
end

function triad_twist3(b::Vector, c::Vector, d::Vector)
  assert(length(b)==length(c)==length(d))
  a = similar(b)
  for i in 1:length(a)
     cc = abs(c[i])
     a[i] = b[i] + cc * d[i]
  end
  return a
end

#b = [1,3,5]
#c = [2,4,6]
#d = [3,5,7]
b = rand(100)
c = rand(100)
d = rand(100)

triad(b,c,d)
#triad_twist1(b,c,d)
#triad_twist2(b,c,d)
#triad_twist3(b,c,d)
