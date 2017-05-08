module SharedWords
using Levenshtein
"A measurement of string distance that checks to see how many words are shared between two different strings"

function get_words(string)
	words_matches = collect(eachmatch(r"\w+",string))
	word_array = map(x->x.match,words_matches)
	return word_array
end

function is_words_in_string(word_array,string,levthresh)
	if levthresh == 0
		bool_array = map(x->contains(string,x),word_array)
		summn = sum(map(int,bool_array))
		return summn
	else
		stringwords = get_words(string)
		bool_array = map(x->lev_contains(stringwords,x,levthresh),word_array)
		summn = sum(map(int,bool_array))
	end
end

function lev_contains(stringwords,word,levthresh)
	"Checks to see if a word within a certain levenshtein distance is in another array of words"
	"""If stringwords contains a word that is within a certain levenshtein distance of word, return true, else, return false"""
	any(x->levenshtein(x,word) <= levthresh,stringwords)
end

	


function orderedsharedwords(larger,smaller,levthresh)
	"Returns the number of shared words between two strings, where the first argument is shorter than the second"
	smallwords = get_words(smaller)
	words_shared = is_words_in_string(smallwords,larger)
	return words_shared
end

function sharedwords(string1,string2,levthresh=0)
	"Returns the number of shared words between two strings"
	"""This version askes for an index: that index is if you 
	already know that one string is shorter or longer than the other.
	If that's the case, pass it either one or two and it will know that string1 is larger than string 2 (this is to optimize against sharedwordsmetric which wants this information as well)"""
	(longer,shorter) = return_strings_in_length_order_descending(string1,string2)
	#Small words is an array of all the words in shorter
	shortwords = get_words(shorter)
	#words_shared is the number of words shared between the two strings
	words_shared = is_words_in_string(shortwords,longer,levthresh)
	return words_shared
end
export sharedwords
function return_strings_in_length_order_descending(string1,string2)
	"Returns a tuple where the first element is the longer and the second element is the shorter of the two strings"
	l1 = length(string1)
	l2 = length(string2)
	if l1 > l2
		larger = string1
		smaller = string2
	else
		larger = string2
		smaller = string1
	end
	return (larger,smaller)
end
function return_strings_in_length_order_descending_with_length_of_shortest(string1,string2)
	"Returns a tuple where the first element is the longer, the second element is the shorter of the two strings, and the third element is the length of the shortest string"
	l1 = length(string1)
	l2 = length(string2)
	if l1 > l2
		larger = string1
		smaller = string2
		return (larger,smaller,l2)

	else
		larger = string2
		smaller = string1
		return (larger,smaller,l1)
	end
end



function similarwords(string1,string2,levthresh=0)
	"Returns the number of shared words divided by the length of the smallest string. If the smallest string is a substring of the largest string, this will return 0. Otherwise, it returns 1 - percentage_difference"
	(longer,shorter,length_of_shortest) = return_strings_in_length_order_descending_with_length_of_shortest(string1,string2)
	shared = orderedsharedwords(longer,shorter,levthresh)
	sharemetric = shared/length_of_shortest
	return 1-sharemetric
end
export similarwords


end # module
