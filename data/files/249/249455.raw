# palindromic.jl

# Author: __MadHatter (alias used on https://www.reddit.com/r/dailyprogrammer)                        
# Challenge:
# http://www.reddit.com/r/dailyprogrammer/comments/38yy9s/20150608_challenge_218_easy_making_numbers/

line = readline() # read integer
line = line[1:length(line)-1] # remove next line character
a = line
b = reverse(line)
x = BigInt(a)
y = BigInt(b)
z = 0
steps = 0
while ((z = x + y) / 2) != x
  a = string(z)
  b = reverse(a)
  x = BigInt(a)
  y = BigInt(b)
  steps = steps + 1
end
@printf "%s gets palindromic after %d steps: %d\n" line steps x
