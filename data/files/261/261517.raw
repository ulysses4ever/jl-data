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

len = 2000000;
repeat = 1000;

b = Array(Float64,len)
c = Array(Float64,len)
d = Array(Float64,len)
b = rand(len)
d = rand(len)

#for i = 1:len
#        c[i] = i;   # c : all positive numbers
#end

#c = linspace(-100.,100.,len)    # c: half positive, half negative

#for i = 1:len
#        c[i] = -i;   # c : all negative numbers
#end
c = linspace(-10.,90.,len)    # c: half positive, half negative


{for i = 1 : repeat;triad(b,c,d);end}
{for i = 1 : repeat;triad_twist1(b, c,d);end}
{for i = 1 : repeat;triad_twist2(b, c,d);end}
{for i = 1 : repeat;triad_twist3(b, c,d);end}

Profile.clear();
#@profile {for i = 1 : repeat;triad(b, c,d);end}
#@profile {for i = 1 : repeat;triad_twist1(b, c,d);end}
#@profile {for i = 1 : repeat;triad_twist2(b, c,d);end}
@profile {for i = 1 : repeat;triad_twist3(b, c,d);end}

Profile.print();

t0 = @elapsed {for i = 1 : repeat;triad(b,c,d);end}
t1 = @elapsed {for i = 1 : repeat;triad_twist1(b, c,d);end}
t2 = @elapsed {for i = 1 : repeat;triad_twist2(b, c,d);end}
t3 = @elapsed {for i = 1 : repeat;triad_twist3(b, c,d);end}
println("triad takes ", t0);
println("triad_twist1 takes ", t1);
println("triad_twist2 takes ", t2);
println("triad_twist3 takes ", t3);

