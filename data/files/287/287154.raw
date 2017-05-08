#   Project Euler
#   Problem:    4
#   Author:     Ben Hobbs
#   Date:       28/5/2015
#   Desc:       A palindromic number reads the same both ways. The largest
#               palindrome made from the product of two 2-digit numbers is
#               9009 = 91 × 99.
#
#               Find the largest palindrome made from the product of two
#               3-digit numbers.

function isPalindrome(num)
    if num[1:(floor(length(num)/2))] == reverse(num[(ceil(length(num)/2)+1):end])
        return true
    end
    return false
end

lower, upper = 100,999

a = Int64[]

for i in lower:upper
    for j in lower:upper
        if isPalindrome(string(i*j))
            palindrome = i * j
            #@printf "%d * %d = %d\n" i j palindrome
            push!(a,palindrome)
        end
    end
end

sort!(a, rev=true)
println(a[1:1])