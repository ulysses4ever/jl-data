function pretty_print(collection)
    for pair in collection
        @printf("%s: %d\n", pair[1], pair[2]);
    end
end

function get_frequency(str)
    alpha_freq = zeros(Int, 26)
    digram_freq = zeros(Int, (26, 26))
    trigram_freq = zeros(Int, (26, 26, 26))
    
    char_queue = Array(Int, 0);
    for c in str
        c = lowercase(c) - 'a' + 1;

        if 1 <= c <= 26
            push!(char_queue, c)
        else
            empty!(char_queue)
            continue
        end

        if length(char_queue) >= 1
            alpha_freq[char_queue[end]] += 1;
        else
            continue;
        end

        if length(char_queue) >= 2
            digram_freq[char_queue[end-1], char_queue[end]] += 1;
        else 
            continue;
        end

        if length(char_queue) >= 3
            trigram_freq[char_queue[end-2], char_queue[end-1], char_queue[end]] += 1;
            shift!(char_queue)
        else 
            continue;
        end
    end
    
    return (alpha_freq, digram_freq, trigram_freq)
end

function print_alpha_freq(freq)
    alphabet = [string(c) for c in 'a':'z'];
    alpha_freq = sort([item for item in zip(alphabet, freq)], by=x->x[2], rev=true);
    pretty_print(alpha_freq);
end

function print_frequency(freq)
    alpha_freq, digram_freq, trigram_freq = freq;

    # Initialize frequency dictionary
    
    # Initialize digram/trigram dictionaries
    alphabet = [string(c) for c in 'a':'z'];
    digrams = reshape(alphabet.*alphabet', length(alphabet)*length(alphabet));
    trigrams = reshape(digrams.*alphabet', length(digrams)*length(alphabet));

    alpha_freq = sort([item for item in zip(alphabet, alpha_freq)], by=x->x[2], rev=true);
    digram_freq = sort([item for item in zip(digrams, digram_freq)], by=x->x[2], rev=true);
    trigram_freq = sort([item for item in zip(trigrams, trigram_freq)], by=x->x[2], rev=true);

    println("-------------------------------------------------");
    println("singles");
    println("-------------------------------------------------");
    pretty_print(alpha_freq);
    println("");
    
    println("-------------------------------------------------");
    println("digrams");
    println("-------------------------------------------------");
    pretty_print(digram_freq[1:40]);
    println("");
    
    println("-------------------------------------------------");
    println("trigrams");
    println("-------------------------------------------------");
    pretty_print(trigram_freq[1:40]);
end

function build_monoalphabet_matrix(plain_freq, cipher_freq)
    rtrn = zeros(Float64, 26, 26);

    increment_element(idx, p, c) = rtrn[p,c] += 1.0/idx;
    flatten(m) = reshape(m, length(m));
    map(increment_element,
        1:length(plain_freq[1]),
        sortperm(plain_freq[1], rev=true),
        sortperm(cipher_freq[1], rev=true));
    
    increment_element_digram(idx, p, c) = map((x, y)->increment_element(idx, x, y),
                                              ind2sub(size(plain_freq[2]), p),
                                              ind2sub(size(cipher_freq[2]), c));
    map(increment_element_digram, 
        1:length(plain_freq[2]),
        sortperm(flatten(plain_freq[2]), rev=true),
        sortperm(flatten(cipher_freq[2]), rev=true));
    
    increment_element_trigram(idx, p, c) = map((x, y)->increment_element(idx, x, y),
                                          ind2sub(size(plain_freq[3]), p),
                                          ind2sub(size(cipher_freq[3]), c));
    map(increment_element_trigram, 
        1:length(plain_freq[3]),
        sortperm(flatten(plain_freq[3]),  rev=true),
        sortperm(flatten(cipher_freq[3]), rev=true));

    return rtrn;
end

function key_from_matrix(mat)
    rtrn = Dict();
    for idx in 1:26
        # find maximum
        cipher_idx,  plain_idx = ind2sub(size(mat), indmax(mat));
        
        # Remember this key
        #@printf("%c => %c: %f\n", 'a' + cipher_idx - 1, 'a' + plain_idx - 1, mat[cipher_idx, plain_idx]);
        rtrn['a' + plain_idx - 1] = 'a' + cipher_idx - 1;

        # Zero out this row and column so we dont find it again
        mat[cipher_idx, :] = zeros(1, 26);
        mat[:, plain_idx] = zeros(26, 1);
    end
    return rtrn
end

function distance(str1, str2)
    if length(str1) != length(str2)
        return Inf
    end
    return sum(map((x,y)->x != y, str1, str2));
end

# TODO: Only load dictionary once
dict_words = filter(x->!contains(x, "\'"),
               [chomp(lowercase(word)) for word in readlines(open("words"))]);

function guess_word(garbled)
    dist, ind = findmin([distance(word, garbled) for word in dict_words]);
    return (dict_words[ind], dist);
end

function print_key(key)
    map((k,v)->@printf("%s -> %s\n", k, v), keys(key), values(key));
end


if length(ARGS) == 1
    f = open(ARGS[1], "r");
    str = readall(f);
    
    freq = get_frequency(str);

    print_frequency(freq);
elseif length(ARGS) == 2
    plain_f = open(ARGS[1], "r");
    plaintext = readall(plain_f);

    cipher_f = open(ARGS[2], "r");
    ciphertext = readall(cipher_f);

    @printf("Analyzing '%s' letter frequency... ", ARGS[1]);
    plain_freq = get_frequency(plaintext);
    println("Done.");

    @printf("Analyzing '%s' letter frequency... ", ARGS[2]);
    cipher_freq = get_frequency(ciphertext);
    println("Done.");

    @printf("Comparing letter frequencies to estimate monoalphabetic cipher key... ");
    ma_matrix = build_monoalphabet_matrix(plain_freq, cipher_freq);

    # populate monoalphabetic key
    ma_key = key_from_matrix(ma_matrix)
    println("Done.");

    println("")

    # First round decryption
    decrypt = join([get!(ma_key, c, c) for c in ciphertext]);
    decrypt_words = [rstrip(word, [',', '.', ';']) for word in split(decrypt)];

    println("");
    println("=====================");
    println("Initial Decrypt Guess");
    println("=====================");
    println(decrypt);

    println("Comparing decrypt to dictionary words to correct mistakes")

    find_in_dict(d, element) = collect(keys(d))[findfirst(collect(values(d)), element)]
    fix_key(good_char, bad_char) = begin
        if good_char == bad_char
            return;
        end
        good_key = find_in_dict(ma_key, good_char);
        bad_key = find_in_dict(ma_key, bad_char);
        ma_key[good_key] = bad_char;
        ma_key[bad_key] = good_char;
    end

    # Iterate through and guess words to correct key
    length_order = sortperm([length(word) for word in decrypt_words], rev=true);
    match_counter = 0
    for word_idx in length_order
        if contains(decrypt_words[word_idx], "\'")
            continue
        end
        @printf("Correcting \'%s\'... ", decrypt_words[word_idx]);

        # guess a word
        corrected_word, dist = guess_word(decrypt_words[word_idx]);
        println(corrected_word);
        if dist > length(corrected_word)/3
            println("Corrected word is not close enough! Skipping")
            continue
        end

        # use differences to correct ma_key
        map(fix_key, corrected_word, decrypt_words[word_idx]);

        # re-decrypt
        decrypt = join([get!(ma_key, c, c) for c in ciphertext]);
        decrypt_words = [rstrip(word, [',', '.', ';']) for word in split(decrypt)];

        if dist == 0
            match_counter += 1;
            if match_counter > 30
                break;
            end
        else
            match_counter = 0;
        end
    end

    println("");
    println("=============");
    println("Final Decrypt");
    println("=============");
    println(decrypt);

    println("");
    println("Final Key:");
    println("----------");
    [pop!(ma_key, c) for c in " ;.,'\n"];
    @printf("Plaintext:\t");
    println(join('a':'z', " "));
    @printf("Ciphertext:\t");
    println(join([ma_key[c] for c in 'a':'z'], " "));
end
