

x = 25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784406918290641249515082189298559149176184502808489120072844992687392807287776735971418347270261896375014971824691165077613379859095700097330459748808428401797429100642458691817195118746121515172654632282216869987549182422433637259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133844143603833904414952634432190114657544454178424020924616515723350778707749817125772467962926386356373289912154831438167899885040445364023527381951378636564391212010397122822120720357
readfile = open(readall,"RSA_2048_Last_Number.txt")
limitindex = searchindex(readfile,"|")
if limitindex < 9
	num = 1000000
else 
	num = parse(BigInt,readfile[1:limitindex-2])
end
upperLimit = BigInt(round(BigInt(x)/BigInt(num)))

q = "Factors of " * string(x) * ": "
j = 0
b = 0
c = 0

println("I'm working here!...")

while j == 0
	z = rand(10:length(digits(upperLimit)))
	a = rand(1:9)
	for b = 2:z
		a = parse(BigInt,join((a,rand(0:9))))
	end
	if digits(BigInt(a))[1] in [2, 4, 5, 6, 8, 0]
		continue
	else
		if BigInt(x)%BigInt(a)==0
			q = join((q,a),",")
			j = 1
			break
		end
		# println(a,", ",length(digits(a))," digits")
	end
	c += 1
	if c == 1000000 then
		c = 0
		readfile = open(readall,"RSA_2048_Last_Number.txt")
		limitindex = searchindex(readfile,"|")
		if limitindex < 9
			num = 1000000
		else 
			num = parse(BigInt,readfile[1:limitindex-2])
		end
		upperLimit = BigInt(round(BigInt(x)/BigInt(num)))
		println("I was born a random-man.....", " - ", now())
	end
end

println("Found the numer, lemme save it")

outfile = open("RSA_Gambler_Number.txt","w")
if j == 1 then 
	write(outfile,string(q))
else
	write(outfile,string(a) * " was the last number checked")
end	
close(outfile)

println("Jobs Done")


