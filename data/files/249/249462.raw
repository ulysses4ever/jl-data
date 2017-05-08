# palindromic.jl

# Author: __MadHatter (alias used on https://www.reddit.com/r/dailyprogrammer)                        
# Challenge:
# http://www.reddit.com/r/dailyprogrammer/comments/38yy9s/20150608_challenge_218_easy_making_numbers/
#
# Optimizations/improvements by:
#   SingularInfinity
#
# Adjustments to while loop inspired by:
#   SerJothanChanes
#   Oops_TryAgain

function f()
  line = readline() |> chomp # read integer
  a = line
  b = reverse(line)
  x = BigInt(a)
  y = BigInt(b)
  steps = 0
  while a != b
    z = x + y
    a = string(z)
    b = reverse(a)
    x = BigInt(a)
    y = BigInt(b)
    steps = steps + 1
  end
  @printf "%s gets palindromic after %d steps: %d\n" line steps x
end

f()
