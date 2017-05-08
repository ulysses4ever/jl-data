#!/usr/bin/julia
## A palindromic number reads the same both ways.
## The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
## Find the largest palindrome made from the product of two 3-digit numbers.

function ispalindrome(n)
    s = string(n)
    return s == reverse(s)
end

maxP = 0 
for i in range(100, 999)
    for j in range(i, 999)
        p = i * j
        if ispalindrome(p)
            if p > maxP
                maxP = p
            end
        end
    end 
end

println(maxP)
