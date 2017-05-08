


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
	if chk == false
		outfile = open("Prime List.txt","a+")
		write(outfile,"\n")
		write(outfile,string(p))
		close(outfile)
	end
end

for i = 2:53
	x = pascalRow(int(i)+1)
	println(x)
	p = int(i)
	p_row = x
	y = chk_prime(p, p_row)
	println(y)
end














