#The learner-propagator component

## Translation table management.
function create_blank_table()
    return Array(Int, 1024)
end

function add_to_table(table, cipher_letter, translation)
    if (table[cipher_letter] != -1) && (table[cipher_letter] != translation)
        abort()
    end
    table[cipher_letter] = translation
    return table
end


## Dictionary handling
function read_dictionary()
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


## Scanner for permitted types
function scan_for_match(cipher, word, initial_position)
    #Depends on learning policy?
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
	    match_found = scan_for_match(cipher, word, position)
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