# Finds is the 10 001st prime number
# uses the default isprime function

## alternative basic isprime function
#function isPrime(x)
#	for i in 2:sqrt(x)
#		if(x%i==0)
#			return false
#		end
#	end
#	return true
#end

count = 1 # include 2 to count
testForPrime = 2
while(count<10001)
	testForPrime+=1
	if(isprime(testForPrime))
		count+=1
	end
end
println("10001st prime number is: ",testForPrime)