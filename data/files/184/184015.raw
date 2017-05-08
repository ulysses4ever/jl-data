# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Qualification Round 2014
# Problem D: Deceitful War

# Returns the points Naomi can score if she plays War optimally.
function points_war(msn, msk)
	points = 0
	mskc = copy(msk)
	for mn in msn
		i = findfirst(mk -> mk > mn, mskc)
		if i == 0
			shift!(mskc)
			points += 1
		else
			deleteat!(mskc, i)
		end
	end
	points
end

# Returns the points Naomi can score if she plays Deceitful War optimally.
# Assumes that msn and msk are sorted.
# Empties both msn and msk.
function points_deceitfulwar!(msn, msk)
	points = 0
	while !isempty(msn)
		i = findfirst(mn -> mn > msk[end], msn)
		if i == 0
			shift!(msn)
			pop!(msk)
		else
			deleteat!(msn, i)
			pop!(msk)
			points += 1
		end
	end
	points
end

function main()
	n = int(readline())
	for i = 1:n
		int(readline()) # number of masses
		msn = sort(float(split(readline())))
		msk = sort(float(split(readline())))
		pw = points_war(msn, msk)
		pdw = points_deceitfulwar!(msn, msk)
		println("Case #$i: $pdw $pw")
	end
end

main()
