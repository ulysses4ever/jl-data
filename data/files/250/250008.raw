

x = 25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784406918290641249515082189298559149176184502808489120072844992687392807287776735971418347270261896375014971824691165077613379859095700097330459748808428401797429100642458691817195118746121515172654632282216869987549182422433637259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133844143603833904414952634432190114657544454178424020924616515723350778707749817125772467962926386356373289912154831438167899885040445364023527381951378636564391212010397122822120720357
readfile = open(readall,"RSA_2048_Last_Number.txt")
limitindex = searchindex(readfile,"|")
if limitindex < 9
	num = 1000001
else 
	num = BigInt(readfile[1:limitindex-2])
end
z = BigInt(round(x/num))
q = "Factors of " * string(x) * ": "
j = 0
k = 0

while BigInt(num)%6 != 0 
	num = BigInt(num - 1)
end

for a = num:6:BigInt(z)
	if BigInt(x)%BigInt(a-1)==0
		j = 1
		q = join((q,a-1),",")
		break
	end
	if BigInt(x)%BigInt(a+1)==0
		j = 1
		q = join((q,a+1),",")
		break
	end
	if digits(BigInt(a))[8] != k
		outfile = open("RSA_2048_Last_Number.txt","w")
		write(outfile,string(a) * " | " * "last number checked")
		close(outfile)
		k = digits(BigInt(a))[8]
		println(a-1)
		println(a+1)
	end
end

outfile = open("RSA_Last_Number.txt","w")

if j == 1 then 
	write(outfile,string(q))
else
	write(outfile,string(x) * " is a prime number")
end	
close(outfile)