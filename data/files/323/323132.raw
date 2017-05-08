module Problem04

isPalindrome(s) = s == reverse(s)

# I couldn't get this to work.
# products = [(p,q) for (p,q) in ([100:999], [100:999])]
# So, instead:
products = []
for p in 100:999, q in 100:999
	push!(products, "$(p*q)")
end

palindromes = filter(isPalindrome, products)

problem04 = maximum(map(s -> parse(Int,s), palindromes))

end
