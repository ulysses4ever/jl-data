cols = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"] 
teens = ["ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"] 
rows = ["", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

function hundreds(i)
	i > 0 ? cols[i+1] * " hundred" : ""
end

function tens(j, k)
	if j == 1
		return teens[k+1]
	end
	rows[j+1] * (k == 1 && j > 1 ? "-" : "") * cols[k+1]
end

function num_string_array(i, j, k)
	hundreds(i), tens(j, k)
end

function num_string(i, j, k)
	a, b = num_string_array(i, j, k)
	if isempty(a) || isempty(b)
		"$a $b"
	else
		"$a and $b"
	end
end

num_strings = String[]

for num in 1:999
	k, j, i = digits(num, 10, 3)
	push!(num_strings, replace(num_string(i, j, k), r"[ -]", ""))
end
total_len = length("onethousand") + (num_strings |> join |> length)
println(total_len)
