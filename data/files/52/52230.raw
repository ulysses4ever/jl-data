module SharedWords
using Levenshtein
"A measurement of string distance that checks to see how many words are shared between two different strings"

function get_words(string)
	"Simple regexp match to get the word characters from a string"
	"""Returns the words in a string as an array"""
	words_matches = collect(eachmatch(r"\w+",string))
	word_array = map(x->x.match,words_matches)
	return unique(word_array)
end

function is_words_in_string(word_array,string,levthresh)
	"Checks to see if the words in word_array are in string"
	"""If a levthresh is supplied, words that are a Levenshtein distance
	of levthresh or less are considered to be the same word"""
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

function lev_contains(string,word,levthresh)
	"Checks to see if a word within a certain levenshtein distance is in another array of words"
	"""If string contains any word that is within a certain levenshtein distance of word, 
	return true, else, return false"""
	any(x->levenshtein(x,word) <= levthresh,string)
end

function ordered_shared_words(larger,smaller,levthresh)
	"Returns the number of shared words between length-ordered strings"
	"""Helper function"""
	smallwords = get_words(smaller)
	words_shared = is_words_in_string(smallwords,larger,levthresh)
	return words_shared
end

function sharedwords(string1,string2,levthresh=0)
	"Returns the number of shared words between two strings"
	(longer,shorter) = order_strings_by_length(string1,string2)
	#Small words is an array of all the words in shorter
	shortwords = get_words(shorter)
	#words_shared is the number of words shared between the two strings
	words_shared = is_words_in_string(shortwords,longer,levthresh)
	return words_shared
end
export sharedwords

function order_strings_by_length(string1,string2)
	"Returns a tuple where the first element is the longer
	and the second element is the shorter of the two strings"
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


function jarowinkler(string1,string2,levthresh=0)
	"A an implementation of a metric for determining the distance of two strings that share words"
	"""Returns the number of shared words divided by the length of the smallest string. 
	If the smallest string is a substring of the largest string, this will return 0, 
	if not, it returns the ratio of shared words to the length of the shorter string"""
	(longer,shorter) = order_strings_by_length(string1,string2)
	length_of_shortest = length(get_words(shorter))
	shared = ordered_shared_words(longer,shorter,levthresh)
	sharemetric = shared/length_of_shortest
	return 1-sharemetric
end
export similarwords


end # module
