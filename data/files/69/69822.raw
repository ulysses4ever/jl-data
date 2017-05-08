module Stemmer

export stem

function stem(word, lang)
    word = lowercase(word)
    chars = length(word)

    if chars < 4
        return word
    end

    if chars > 5
        local stem = replace(word, r"ища$", "")
        if stem != word
            return stem
        end
    end

    word = remove_article(word)
    word = remove_plural(word)
    chars = length(word)

    if chars > 3
        word = replace(word, r"я $"x, "")  # masculine

        # normalization (e.g., -а could be a definite article or plural form)
        word = replace(word, r"[аео] $"x, "")

        chars = length(word)
    end

    if chars > 4
        word = replace(word, r"е (?= н $)"x, "")  # -ен → -н

        chars = length(word)
    end

    if chars > 5
        word = replace(word, r"ъ (?= \p{Cyrillic} $)"x, "")  # -ъ� → -�
    end

    return word
end

function remove_article(word)
    chars = length(word)

    if chars > 6
        # definite article with adjectives and masculine
        stem = replace(word, r"ият $"x, "")
        if stem != word
            return stem
        end
    end

    if chars > 5
        stem = replace(word, r"(?:
              ия  # definite articles for nouns:
            | ът  # ∙ masculine
            | та  # ∙ feminine
            | то  # ∙ neutral
            | те  # ∙ plural
        ) $"x, "")
        if stem != word
            return stem
        end
    end

    if chars > 4
        # article for masculine
        stem = replace(word, r"ят $"x, "")
        if stem != word
            return stem
        end
    end

    return word
end

function remove_plural(word)
    chars = length(word)

    if chars > 6
        # specific plural rules for some words (masculine)
        stem = replace(word, r"ове $"x, "")
        if stem != word
            return stem
        end
        stem = replace(word, r"еве $"x, "й")
        if stem != word
            return stem
        end
        stem = replace(word, r"овци $"x, "о")
        if stem != word
            return stem
        end
    end

    if chars > 5
        stem = replace(word, r"зи $"x, "г")
        if stem != word
            return stem
        end
        # -е�и → -я�
        m = match(r"е ( \p{Cyrillic} ) и $"x, word)
        if m != nothing
            return replace(word, Regex("$(m.match)\$"), "я$(m.captures[1])")
        end
        stem = replace(word, r"ци $"x, "к")
        if stem != word
            return stem
        end
        stem = replace(word, r"(?: та | ища ) $"x, "")
        if stem != word
            return stem
        end
    end

    if chars > 4
        stem = replace(word, r"си $"x, "х")
        if stem != word
            return stem
        end
        # plural for various nouns and adjectives
        stem = replace(word, r"и $"x, "")
        if stem != word
            return stem
        end
    end

    return word
end

end
