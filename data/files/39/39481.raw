module SplitWords

	export splitwords

	function isword(s)
		allwords = Set(["the", "quick", "brown", "fox", "jumped", "out", "window"])
		in(s,allwords)
	end

	function splitwordsinner{S<:String}(string::S, list::Vector{S})
		if isempty(string)
			return list
		end
		for i=1:endof(string)
			candidate = string[1:i]
			tail = string[i+1:end]
			if isword(candidate)
				splittail = splitwordsinner(tail, [list, candidate])
				if !isempty(splittail)
					return splittail
				end
			end
		end
		[]
	end

	function splitwords(string)
		splitwordsinner(string, ASCIIString[])
	end
end