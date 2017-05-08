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
z = 0  # final palindrome
steps = 0
@printf "%d gets palindromic after " x
while ((x + y) / 2) != x
  z = x + y
  a = string(z)
  b = reverse(a)
  x = BigInt(a)
  y = BigInt(b)
  steps = steps + 1
end
@printf "%d steps: %d\n" steps z
