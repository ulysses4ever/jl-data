function generate_text(ϕ, num_steps, unique_symbols, ngram, M, groupby)
	if groupby == "chars"
		ϕ = split(ϕ, "")
	else
		ϕ = split(ϕ)
	end

	# create empty array to store result of Markov jumping from state to state
	markov_chain_text = []
	append!(markov_chain_text, ϕ)

	current_state = text_to_numeric(ϕ, unique_symbols)

	# "trickle-down" transition matrices
	for step in 1:num_steps
		next_word_idx = trickle_down(current_state, M)
		next_word = numeric_to_text([next_word_idx], unique_symbols)[1]
		push!(markov_chain_text, next_word)
		current_state = text_to_numeric(markov_chain_text[end-ngram+1:end], unique_symbols)
	end

	markov_chain_text
end
