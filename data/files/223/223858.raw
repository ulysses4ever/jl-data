function reversa(n::Integer)
	alReves = 0
	while n > 0
		alReves = 10*alReves + mod(n,10)
		n = div(n,10)
	end
	return alReves
end

function esPalindromo(n::Integer)
	return n == reversa(n)
end

palindromoBuscado = 0
a = 999
while a >= 100
	b = 999
	while b >= a 
		if a*b <= palindromoBuscado
			break
		end
		if esPalindromo(a*b)
			palindromoBuscado = a*b
		end
		b = b - 1
	end
	a = a -1 
end 

println("El palindromo buscado es $(palindromoBuscado)")
