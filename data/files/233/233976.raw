function bisection(f, a, b, tol, iter)

fa = f(a)

for i = 1:iter
	p = a + (b-a)/2
	fp = f(p)
	
	if fp < tol
		return p
	end

	if fa*fp > 0
		a = p
	else
		b = p
	end
end

return p

end


