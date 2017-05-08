


function pascalRow(n::Int64)
	baseVector = [1] #the first row is equal to 1. 
	kernel = [1,1]   #This is the second row and a kernel. 
	row = zeros(n)
	for i = 1 : n
		row = baseVector 
		baseVector = conv(baseVector, kernel) #convoltion with kernel
	end
	return row::Array{Int64,1}
end

function chk_prime(p, p_row)
	chk = false
	for i = p_row
		if i == 1
			continue
		end
		if i % p != 0
			chk = true
			break
		end
	end
	if chk == true
		return "Composite Number"
	else
		return "Prime Number"
	end
end

z = ARGS[1]
x = pascalRow(int(z)+1)
println(x)
p = int(z)
p_row = x
y = chk_prime(p, p_row)
println(y)







