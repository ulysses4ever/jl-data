function numberOfDivisors(x)
	sum(map((i) -> mod(x, i) == 0, [1:x]))
end

function triangularNumber(x)
	sum([1:x])
end

function euler12(divs)
	divisors = 0
	triIndex = 1
	triNum = 0
	while divisors <= divs
		triNum = triNum + triIndex
		triIndex = triIndex + 1
		divisors = numberOfDivisors(triNum)
	end
	triNum
end