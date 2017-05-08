module Soundex
    export soundex!, soundex

    function ispseudovowel(chr::Char)
        return contains(['a', 'e', 'i', 'o', 'u', 'y', 'h', 'w'], chr)
    end

    isvowel(chr::Char) = contains(['a', 'e', 'i', 'o', 'u', 'y'], chr)

    function encode(chr::Char)
        if contains(['b', 'f', 'p', 'v'], chr)
            return '1'
        elseif contains(['c', 'g', 'j', 'k', 'q', 's', 'x', 'z'], chr)
            return '2'
        elseif contains(['d', 't'], chr)
            return '3'
        elseif 'l' == chr
            return '4'
        elseif contains(['m', 'n'], chr)
            return '5'
        elseif 'r' == chr
            return '6'
        elseif ispseudovowel(chr)
            return '9'
        else
            msg = @sprintf "Unknown character encountered %s" chr
            throw(ArgumentError(msg))
        end
    end

    function soundex!(output::Array{Char}, s::String)
        index = 0
        previous_chr, previous_encoding = char(0), '9'
        for chr in s
            chr = lowercase(chr)
            encoding = encode(chr)
            if index == 0
                index += 1
                output[index] = uppercase(chr)
            elseif index <= 3
                # Vowels along with 'h' and 'w' are not encoded
                if !ispseudovowel(chr)
                    # If two or more letters with the same number are adjacent in
                    #  the original name, only retain the first
                    if encoding != previous_encoding
                        if encoding == output[index]
                            # Two letters with the same number separated by a
                            # vowel are coded as two numbers
                            #
                            # Two letters with the same number separated by
                            # 'h' or 'w' are coded as a single number
                            if isvowel(previous_chr)
                                index += 1
                                output[index] = encoding
                            end
                        else
                            index += 1
                            output[index] = encoding
                        end
                    end
                end
            else
                # Only retain the first four encoded letters
                break
            end
            previous_chr, previous_encoding = chr, encoding
        end
        # Append with zeros if needed
        if index < 4
            for i in (index + 1):4
                output[i] = '0'
            end
        end
    end

    function soundex(s::String)
        output = Array(Char, 4)
        soundex!(output, s)
        return CharString(output)
    end
end # module
