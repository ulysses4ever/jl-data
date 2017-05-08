#!/usr/bin/env julia

# A palindromic number reads the same both ways.
# The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
# Find the largest palindrome made from the product of two 3-digit numbers.

function is_palindrome(str)
    len = endof(str)
    res = true
    i = 1
    while res && i <= floor(int(len/2))
        res = (str[i] == str[len+1-i])
        i += 1
    end
    return res
end

function find_palimdrome(max, min)
    pal = 0
    max_palin = 0
    n1 = max
    while n1 > min
        n2 = max
        while n2 >= n1
            prod = n1 * n2
            if prod > max_palin
                prod_str = string(prod)
                if is_palindrome(prod_str)
                    max_palin = prod
                end
            end
            n2 -= 1
        end
        n1 -= 1
    end
    return max_palin
end

foo = find_palimdrome(999, 100)

println(foo)
