function clean_corpus(text, regex; normalize = true, lower_case = true)
	if normalize
		# replace control characters with spaces
		text = normalize_string(text, stripmark = true, stripignore = true,
								stripcc = true)
	end

	if lower_case
		text = lowercase(text)
	end

	# remove unwanted characters
	text = replace(text, regex, "")

	# remove ""
	text = split(text)
	target_index = 1
	for i in 1:length(text)
		target_index = findnext(text, "", target_index)
		if target_index == 0
			break
		else
			splice!(text, target_index)
		end
	end
	text = join(text, " ")
end

function text_to_numeric(text, symbols)
	numeric_text = []
	for each in text
		push!(numeric_text, findfirst(symbols, each))
	end

	numeric_text
end

function numeric_to_text(numeric, symbols)
	text= []
	for num in numeric
		push!(text, symbols[num])
	end

	text
end

function get_phi(cleaned_corpus, ngram; groupby = "words")
	if groupby == "chars"
		cleaned_corpus_array = split(cleaned_corpus, "")
	else
		cleaned_corpus_array = split(cleaned_corpus)
	end
	starting_point = rand(1:length(cleaned_corpus_array)-ngram)
	ϕ = join(cleaned_corpus_array[starting_point:starting_point+ngram-1], " ")
end
