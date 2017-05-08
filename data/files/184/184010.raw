# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Qualification Round Africa 2010
# Problem C: T9 Spelling

# Converts a character into a string representing a keypad instruction.
function charseq(c)
	if c == ' '; return "0"; end
	q, r = divrem(int(c)-int('a'), 3)
	# Account for keys with 4 letters.
	if q > 5
		r -= 1
		if r == -1
			q -= 1
			r = (q == 5) ? 3 : 2
		elseif q == 8
			q = 7; r = 3
		end
	end
	# ABC begins at the second key.
	string(q+2)^(r+1)
end

# Inserts spaces to represent pauses between keypad instructions whenever the
# last character of one is identical to the first character of the next. Returns
# the modified instruction list.
function addpauses!(list)
	i = 2
	while i <= length(list)
		if list[i-1][end] == list[i][1]
			insert!(list, i, " ")
			i += 1
		end
		i += 1
	end
	list
end

# Convert a string of alphabetic characters and spaces into a sequence that can
# be entered using an old-fashioned cellphone keypad.
keypad(str) = join(addpauses!(map(charseq, collect(str))))

function main()
	n = int(readline())
	for i = 1:n
		str = keypad(chomp(readline()))
		println("Case #$i: ", str)
	end
end

main()
