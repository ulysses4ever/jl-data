#The learner-propagator component

## Translation table management.
function create_blank_table()
    return Array(Int, 1024)
end

UNCOMMITTED = -1

function add_to_table(table, cipher_letter, translation)
    if (table[cipher_letter] != UNCOMMITTED) && (table[cipher_letter] != translation)
        abort()
    end
    table[cipher_letter] = translation
    return table
end


## Dictionary handling
function read_dictionary()
    #STUB
end

## Cipher read-in
function read_cipher()
    #STUB
end


## Inner functions for learning new symbols.
function learn_word(table, ciphertext, word, initial_position)
    end_position = initial_position + length(word)
    word_position = 1

    for position in initial_position:end_position
        table = add_to_table(table, ciphertext[position], word[word_position])
	word_position = word_position + 1
    end

    return table
end

GREEDY = 0
policy = GREEDY

## Scanner for permitted types
function scan_for_match(cipher, table, word, initial_position)
    if (policy == GREEDY)
        return any_matches(cipher, table, word, initial_position)
    end
end

##At least one letter matching.
##No misses.
function any_matches(cipher, table, word, initial_position)
    hits = 0
    misses = 0

    end_position = initial_position + length(word)

    in_word = 0
    for position in initial_position:end_position
        if table[cipher[position]] == word[in_word]
	    hits = hits + 1
	elseif table[cipher[position]] == UNCOMITTED
	    #Do nothing
	else
	    misses = misses + 1
	end
	in_word = in_word + 1
    end

    return hits > 0 && misses < 1
end
    

##The main loop which iteratively learns more and more symbols
function propagation_loop(cipher, word, initial_position)

    #Begin with an assumption that we have the word right at the current position
    table = learn_word(create_blank_table(), cipher, word, initial_position)

    iteration_limit = 5
    iteration_count = 0
    while iteration_count != iteration_limit
        words_found = 0

	end_position = length(ciphertext) - length(word)

	for position in 1:end_position
	    match_found = scan_for_match(cipher, table, word, position)
	    #if not full match
	        #if possible to learn such a match
		    #learn
		#else
		    #report, but don't learn
		#end
            #end
	end


       if (words_found == 0)
           break #Further learning is moot, we aren't learning anymore.
       end
       iteration_count = iteration_count + 1
    end
end
    


## March a single word across the entire ciphertext
function march_word(ciphertext, word)

    end_position = length(ciphertext) - length(word)

    result = make_blank_result()

    for position in 1:end_position
        result = propagation_loop(word, position)
    	accumulate_result(result_to_date, result)
    end

end

MAJORITY_VOTE = 0
combine_rule = MAJORITY_VOTE

function combine_many_march_results(results)
    if combine_rule == MAJORITY_VOTE
        return majority_combiner(results)
    end
end

## March many words across the ciphertext.
function main_loop()

    dictionary = read_dictionary(ARGS[1])
    ciphertext = read_cipher(ARGS[2])

    results = {}

    for word in dictionary
        push!(results, march_word(ciphertext, word))
    end

    digested_result = combine_many_march_results(results)

    #output to file the finished result

end