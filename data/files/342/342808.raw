function testi(x)
	return (x-2)^2 - 4
end

# golden section search
function lineSearch(f, L, a, b)
	C = (sqrt(5) - 1)/2
	a_h = a
	b_h = b

	x_h = b - C*(b-a)
	y_h = a + C*(b-a)

	while true
		# step 2
		if abs(b_h - a_h) < L
			@printf("minimi on: \[%f, %f\]\n", a_h, b_h)
			break
		end

		# step 4
		if f(x_h) <= f(y_h)
			b_h = y_h

			y_h = x_h
			x_h = b_h - C*(b_h - a_h)
		# step 3
		else
			a_h = x_h

			x_h = y_h
			y_h = a_h + C*(b_h - a_h)
		end
	end
end

lineSearch(testi, 0.000001, -25, 25)
