# Project Euler Problem 2
# 4-10-14, Ben Southgate

# Question:
# By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.


f = ( ()-> begin
    a = 1
    b = 1
    function x()
      produce(a+b)
      t = a
      a = b
      b = b+t
    end 
   end )()

s = 0
c = 0
while c <= 4e6
  c = f()
  s += c%2==0 ? c : 0
end

println(s)