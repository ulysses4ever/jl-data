module Problem02

fibonaccis = [n=>n for n in 1:2]

function fibonacci(n)
	# get!(fibonaccis, n, fibonacci(n-1) + fibonacci(n-2)) results in stack overflow.
	if haskey(fibonaccis,n)
		fibonaccis[n]
	else
		f = fibonacci(n-1) + fibonacci(n-2)
		fibonaccis[n] = f
		f
	end
end

f=1
n=1
while f<4_000_000
	f = fibonacci(n)
	n+=1
end

evenFibs = filter(iseven, values(fibonaccis))

problem02 = sum(evenFibs)

end
