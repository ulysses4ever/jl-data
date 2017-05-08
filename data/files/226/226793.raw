function heun(f, tspan, y0; h = 1, iter = false, AbsTol = 0.00001)
t = floor((tspan[end] - tspan[1])/h)
	y = zeros(int64(t) + 1,1)
	y[1,1] = y0
	j = 1

	for i=tspan[1]:h:(tspan[end]-h)
		s1 = f(i,y[j,1])
		y1 = y[j,1] + s1 * h
		s2 = f(i+h,y1)
		y2 = y[j,1] + ((s1 + s2)/2) * h

		err = 100
		while err >= AbsTol
			y3 = y[j,1] + ((f(i,y[j,1]) + f(i+h,y2)) / 2) * h
			err = abs((y3 - y2)/y3) * 100
			y2 = y3
			y[j+1,1] = y3
		end

		if iter == true
			if j == 1
				println("Iter\t\t X\t\t\t Y")
				@printf("%i\t\t %f\t\t %f\n",0,i,y[1,1])
				@printf("%i\t\t %f\t\t %f\n",j,i+h,y[j+1,1])
			else
				@printf("%i\t\t %2f\t\t %f\n",j,i+h,y[j+1,1])
			end
		end
		j += 1
	end
	return y, tspan[1]:h:tspan[end]
end