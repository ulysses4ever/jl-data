tic()

namesFile = open("F:\\programmering\\julia\\euler\\p022_names.txt")

namesStr = readall(namesFile)
names = ASCIIString[]

inName = 0
first = 2
tmp = 0
for i = 1:length(namesStr)
	if namesStr[i] == '\"' && inName == 0
		first = i+1
		tmp = 1
	elseif namesStr[i] == '\"' && inName == 1
		last = i-1
		tmp = 0
		append!(names,[namesStr[first:last]])
	end
	inName = tmp
end

sort!(names)

score = 0
i = 0
for name in names
	i += 1
	nameScore = 0
	for letter in name
		nameScore += int(letter) -64
	end
	score += nameScore*i
end

println("Score = $score")

toc()