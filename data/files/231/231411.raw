function is_valid_iban(iban::String)
    @assert is_valid_ascii(iban)
    ## convert to common format
    iban = unify_iban(iban)
    m = match(iban_global_re, iban)
    if m == nothing
        error("IBAN '$(iban)' not according to format")
    end
    country, check_digits, bban = m.captures
    ## supported country
    @assert haskey(iban_country_length, country)
    ## check total length
    @assert length(iban) == iban_country_length[country]
    ## reformat iban
    is_valid_base97 = is_iban_base97(iban)
    @assert is_valid_base97
    return true
end


function split_iban(iban::String)
    iban = unify_iban(iban)
    m = match(iban_global_re, iban)
    if m == nothing
        error("IBAN '$(iban)' not according to format")
    end
    return m.captures
end


## iban validation utils ##

function unify_iban(iban::String)
    iban = replace(iban, " ", "")
    iban = replace(iban, ",", "")
    iban = uppercase(iban)
    return iban
end


function is_iban_base97(iban::String)
    ## reformat
    rban = *(iban[5:end], iban[1:4]) ## preallocate and fill instead
    ## base97 check
    digit_ban = [string(pos2number(x)) for x in rban]
    digit_int = parseint(BigInt, join(digit_ban))
    d, rest = divrem(digit_int, 97)
    return rest == 1
end


function pos2number(char::Char)
    if isdigit(char)
        ind = convert(Int, char) - 48
    elseif isalpha(char)
        ind = convert(Int, char) - 55
    else
        error("Not a valid IBAN entry: '$(char)'")
    end
    return ind
end


function construct_bban_re(pattern)
    re = join([*(re_format[f], "{", string(n), "}") for (n, f) in pattern])
    re = Regex(re)
    return re
end


bban_length(pattern) = sum([n for (n, f) in pattern])
iban_length(pattern) = bban_length(pattern) + 4
