# palindromic-bonus.jl

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

function lychrel(n,max)
  steps = 0
  a = string(n)
  b = reverse(a)
  while a != b
    x = BigInt(a)
    y = BigInt(b)
    z = x + y
    a = string(z)
    b = reverse(a)
    steps = steps + 1
    if steps >= max
      break
    end
  end
  if a == b
    @printf "%8d  %8d  %s\n" n steps a
  else
    @printf "%8d  %8s  %s\n" n "N/A" "LYCHREL_CANDIDATE"
  end
end

function start(i,last,steps)
  while i <= last
    lychrel(i,steps)
    i = i + 1
  end
end

function main()
  first = BigInt(readline() |> chomp)
  last  = BigInt(readline() |> chomp)
  steps = BigInt(readline() |> chomp)

  @printf "\nComputing numbers %d through %d with maximum number of steps set to %d.\n\n" first last steps
	@printf "%8s  %8s  %s\n" "NUMBER" "STEPS" "PALINDROME/LYCHREL"
	
  start(first,last,steps)
end

main()
