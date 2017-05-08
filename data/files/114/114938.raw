#Implementation of the port stemmer algorithm in Julia


# Type Word for containing the relevant indicess for the algorithm
type Word
    b::String
    k0::Int
    k::Int
    j::Int
end

function stem(s::String)
    if length(s)>2
        return stem(Word(s, 1, length(s),0))
    else
        return s
    end
end

function cons(word::Word, i::Int)
    # cons(word, i) is TRUE <=> b[i] is a consonant.

    if word.b[i]=='a' || word.b[i]=='e' || word.b[i]=='i' ||
        word.b[i]=='o' || word.b[i]=='u'
        return false
    end
    if word.b[i] == 'y'
        if i == word.k0
            return true
        else
            return (!cons(word, i-1))
        end
    end
    return true
end

function m (word::Word)

    # m() measures the number of consonant sequences between k0 and j.
    # if c is a consonant sequence and v a vowel sequence, and <..>
    # indicates arbitrary presence,
    # <c><v>       gives 0
    # <c>vc<v>     gives 1
    # <c>vcvc<v>   gives 2
    # <c>vcvcvc<v> gives 3
    # ....

    n = 0
    i = word.k0
    while true
        if i > word.j
            return n
        end
        if ! cons(word, i)
            break
        end
        i +=1
    end
    i +=1

    while true
        while true
            if i > word.j
                return n
            end
            if cons(word, i)
                break
            end
            i +=1
        end
        i +=1
        n +=1

        while true
            if i > word.j
                return n
            end
            if ! cons(word, i)
                break
            end
            i +=1
        end
        i +=1
    end
    return i
end

function vowelinstem(word::Word)
    # vowelinstem() is TRUE <==> k0...j contains a vowel
    for i in word.k0:word.j
        if ! cons(word, i)
            return true
        end
    end
    return false
end

function doublec(word::Word, j::Int)
    # doublec(j) is TRUE <==> j, (j-1) contain a double consonant.

    if j < (word.k0 + 1)
        return false
    end

    if (word.b[j]!=word.b[j-1])
        return false
    end
    return cons(word, j)
end

function cvc (word::Word, i::Int)
    # cvc(i) is TRUE <==> i-2,i-1,i has the form consonant - vowel - consonant
    # and also if the second c is not w,x or y. This is used when trying to
    # restore and e at the end of a short word e.g. cav(e), lov(e) but
    # snow, box, tray.

    if i < (word.k0 + 2) || ! cons(word, i) || cons(word, i-1) || !cons(word, i-2)
        return false
    end
    ch = word.b[i]
    if ch =='w' || ch =='x' || ch =='y'
        return false
    end
    return true
end

function ends(word::Word, s::String)
    # ends(s) is TRUE <==> k0...k ends with the string s.

    len = length(s)
    if s[len] != word.b[word.k]

        return false
    end

    if len > (word.k - word.k0 +1)

        return false
    end

    if word.b[word.k-len+1:word.k]!=s

        return false
    end

    word.j =word.k-len

    return true#, word
end

function setto(word::Word, s::String)
    # setto(word, s) sets (j+1),...k to the characters in the string s, readjusting k.
    len = length(s)
    word.b=string(word.b[1:word.j],s,word.b[word.j+len:end])
    word.k = word.j+len
    return word
end

function r(word::Word, s::String)
    # r(word, s) is used further down
    if m(word) > 0
        setto(word,s)
    end
    return word
end

function step1ab(word::Word)
    # step1ab(word) gets rid of plurals and -ed or -ing.

    if word.b[word.k]=='s'
        if ends(word, "sses")
            word.k -= 2
        elseif ends(word, "ies")
            setto(word, "i")
        elseif word.b[word.k-1]!='s'
            word.k -=1
        end
    end
    if ends(word, "eed")
        if m(word)>0
            word.k -=1
        end
    elseif ((ends(word, "ed") || ends(word, "ing")) && vowelinstem(word))
        # ("sí!")
        word.k = word.j
        if ends(word, "at")
            setto(word, "ate")
        elseif ends(word, "bl")
            setto(word, "ble")
        elseif ends(word,"iz")
            setto(word, "ize")
        elseif (doublec(word, word.k))
            word.k -=1
            ch = word.b[word.k]
            if (ch =='l' || ch =='s' || ch =='z')
                word.k +=1
            end
        elseif (m(word)==1 && cvc(word, word.k))
            setto(word, "e")
        end

    end
    return word
end

function step1c(word)
    # step1c(word) turns terminal y to i when there is another vowel in the stem.
    if (ends(word, "y") && vowelinstem(word))
        word.b = string(word.b[1:word.k-1],'i', word.b[word.k+1:end])
    end

    return word
end

function step2(word)
    # step2(word) maps double sufficies to single ones.
    # so -ization (= -ize plus -ation) maps to -ize etc. note that
    # the string before the suffix must give m(word)>0

    if word.k==1
        word.k+=1
    end

    if word.b[word.k-1]=='a'
        if ends(word, "ational")
            word = r(word, "ate")
        elseif ends(word, "tional")
            word = r(word, "tion")
        end
    elseif word.b[word.k-1]=='c'
        if ends(word, "enci")
            word = r(word, "ence")
        elseif ends(word, "anci")
            word = r(word, "ance")
        end
    elseif word.b[word.k-1]=='e'
        if ends(word, "izer")
            word = r(word, "ize")
        end
    elseif word.b[word.k-1]=='l'
        if ends(word, "bli") # departure
            # To match the published algorith replace
            # if ends(word, "albi")
            #   r(word, "able")
            word = r(word, "ble")
        elseif ends(word, "alli")
            word = r(word,"al")
        elseif ends(word, "entli")
            word = r(word, "ent")
        elseif ends(word, "eli")
            word = r(word, "e")
        elseif ends(word, "ousli")
            word = r(word, "ous")
        end
    elseif word.b[word.k-1]=='o'
        if ends(word,"ization")
            word = r(word, "ize")
        elseif ends(word, "ation")
            word = r(word, "ate")
        elseif ends(word, "ator")
            word = r(word, "ate")
        end
    elseif word.b[word.k-1]=='s'
        if ends(word, "alism")
            word = r(word, "al")
        elseif ends(word,"iveness")
            word = r(word, "ive")
        elseif ends(word, "fulness")
            word = r(word, "ful")
        elseif ends(word, "ousness")
            word = r(word, "ous")
        end
    elseif word.b[word.k-1]=='t'
        if ends(word, "aliti")
            word = r(word, "al")
        elseif ends(word, "iviti")
            word = r(word, "ive")
        elseif ends(word, "biliti")
            word = r(word, "ble")
        end
    elseif word.b[word.k-1]=='g' # departure, delete to match original
        if ends(word, "logi")
            word = r(word, "log")
        end
    end
    return word
end

function step3(word)
    #step3(word) deals with -ic-, -full, -ness etc. in a similar strategy to step2(word)

    if word.b[word.k]=='e'
        if ends(word, "icate")
            word = r(word, "ic")
        elseif ends(word,"ative")
            word = r(word, "")
        elseif ends(word, "alize")
            word = r(word, "al")
        end
    elseif word.b[word.k]=='i'
        if ends(word, "iciti")
            word = r(word, "ic")
        end
    elseif word.b[word.k]=='l'
        if ends(word, "ical")
            word = r(word, "ic")
        elseif ends(word, "ful")
            word = r(word, "")
        end
    elseif word.b[word.k]=='s'
        if ends(word, "ness")
            word = r(word, "")
        end
    end
    return word
end

function step4(word)
    # step4(word) takes off -ant, -ence etc., in context <c>vcvc<v>.

    if word.b[word.k-1]=='a'
        if ends(word, "al")

        else
            return word
        end
    elseif word.b[word.k-1]=='c'
        if ends(word, "ance")

        elseif ends(word, "ence")

        else
            return word
        end
    elseif word.b[word.k-1]=='e'
        if ends(word, "er")

        else
            return word
        end
    elseif word.b[word.k-1]=='i'
        if ends(word, "ic")

        else
            return word
        end
    elseif word.b[word.k-1]=='l'
        if ends(word, "able")

        elseif ends(word,"ible")

        else
            return word
        end
    elseif word.b[word.k-1]=='n'
        if ends(word, "ant")

        elseif ends(word, "ement")

        elseif ends(word, "ment")

        elseif ends(word, "ent")

        else
            return word
        end
    elseif word.b[word.k-1]=='o'
        if ends(word, "ion") && (word.b[word.j]=='s' || word.b[word.j]=='t')

        elseif ends(word, "ou")

        else
            return word
        end
    elseif word.b[word.k-1]=='s'
        if ends(word, "ism")

        else
            return word
        end
    elseif word.b[word.k-1]=='t'
        if ends(word, "ate")

        elseif ends(word, "iti")

        else
            return word
        end
    elseif word.b[word.k-1]=='u'
        if ends(word, "ous")

        else
            return word
        end
    elseif word.b[word.k-1]=='v'
        if ends(word, "ive")

        else
            return word
        end
    elseif word.b[word.k-1]=='z'
        if ends(word, "ize")

        else
            return word
        end
    else
        return word
    end

    if m(word)>1
        word.k = word.j
    end
    return word
end

function step5(word)
    #step5(word) removes a final -e if m(word) > 1, and changes -ll to -l if m(word > 1)
    word.j = word.k
    if word.b[word.k]=='e'
        a = m(word)
        if a > 1 || (a==1 && !cvc(word,word.k-1))
            word.k -=1
        end
    end
    if word.b[word.k]=='l' && doublec(word, word.k) && m(word)>1
        word.k-=1
    end
    return word
end

function stem(word)
    # In stem(word, p, i, j), p is a char pointer, and the string to be steemed
    # is from p[i] to p[j] inclusive. Typically i is zero and j is the offset
    # to the last character of a string, (p[j+1]=='\0'). The stemmer adjusts
    # the characters p[i] ... p[j] and returns the new end-point of the string,
    # k. Stemming never increases word length, so i <= k <= j.

    word = step1ab(word)
    word = step1c(word)
    word = step2(word)
    word = step3(word)
    word = step4(word)
    word = step5(word)

    return word.b[1:word.k]
end
