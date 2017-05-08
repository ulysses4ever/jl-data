# If all the numbers from 1 to 1000 (one thousand) 
# inclusive were written out in words, how many letters would be used?

# print answer
len = 0
for i = 1:1000
	len += length(toWord(i))
end
println("Letters used: ",len)

# converts an int in range 1:1000 to word
function toWord(x)
	if x == 1000
		return thousand(x)
	end
	if x >= 100
		return hundreds(x)
	end
	if x >= 20
		return overTwenty(x)
	end
	return belowTwenty(x)
end

# integers < 20
function belowTwenty(x)
	strings = ["","one","two","three","four",
	"five","six","seven","eight","nine","ten",
	"eleven","twelve","thirteen","fourteen",
	"fifteen","sixteen","seventeen","eighteen","nineteen"]
	return strings[x+1]
end

# integers > 20
function overTwenty(x)
	strings = ["twenty","thirty","forty",
	"fifty","sixty","seventy","eighty","ninety"]
	return "$(strings[digits(x)[2]-1])$(belowTwenty(x % 10))"
end

# integers > 99
function hundreds(x)
	if x % 100 == 0
		return "$(belowTwenty(digits(x)[3]))hundred"
	end
	if digits(x)[2] >= 2
		return "$(belowTwenty(digits(x)[3]))hundredand$(overTwenty(x % 100))"
	end
	return "$(belowTwenty(digits(x)[3]))hundredand$(belowTwenty(x % 100))"
end

# integer 1000
function thousand(x)
	return "onethousand"
end