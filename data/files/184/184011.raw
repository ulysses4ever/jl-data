# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Qualification Round 2014
# Problem A: Magic Trick

# Attempts to determine the volunteer's card given two card arrangements ca and
# cb, and the row that the card was on for each arrangement, a and b. Returns a
# vector of the cards that the volunteer could have chosen.
function magic(a, b, ca, cb)
	ra = ca[a,:]
	rb = cb[b,:]
	intersect(ra, rb)
end

# Given the possible cards, returns the appropriate message to print.
function message(cards)
	len = length(cards)
	if len == 1
		cards[1]
	elseif len == 0
		"Volunteer cheated!"
	else
		"Bad magician!"
	end
end

# Parses the volunteer's answer and the cards.
function parse()
	a = int(readline())
	cards = Array(Int, 4, 4)
	for i = 1:4
		cards[i,:] = int(split(readline()))
	end
	(a, cards)
end

function main()
	n = int(readline())
	for i = 1:n
		a, ca = parse()
		b, cb = parse()
		cards = magic(a, b, ca, cb)
		str = message(cards)
		println("Case #$i: ", str)
	end
end

main()
