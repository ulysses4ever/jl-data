typealias GenericNastranDeck Vector{GenericCard}
typealias NastranDeck Vector{NastranCard}

function next_token(line::IOBuffer,N::Int64)
    token = ascii(readbytes(line,N))
    n = length(token)
    i = searchindex(token,'\t')
    if i > 0
        skip(line,i-n)
        strip(token[1:i-1])
    else
        strip(token)
    end
end

function next_token_comma(line::IOBuffer)
    token = readuntil(line,',')
    if length(token) > 0 && token[end] == ','
        strip(token[1:end-1])
    else
        strip(token)
    end
end

function parse_line(line::AbstractString)
    buf = IOBuffer(line)
    card = Any[]
    if ',' in line
        tok = next_token_comma(buf)
        if length(tok) > 0 && tok[end] == '*'
            n = 5
            tok = tok[1:end-1]
        else
            n = 9
        end
        push!(card,tok)
        for i in 1:n
            push!(card,next_token_comma(buf))
        end
    else
        tok = next_token(buf,8)
        if length(tok) > 0 && tok[end] == '*'
            l = 16
            n = 4
            tok = tok[1:end-1]
        else
            l = 8
            n = 8
        end
        push!(card,tok)
        for _ in 1:n
            push!(card,next_token(buf,l))
        end
        push!(card,next_token(buf,8))
    end
    card
end

function remove_comments(line::AbstractString)
    i = searchindex(line,'$')
    if i == 0
        line
    else
        line[1:i-1]
    end
end

function parse_float(field::ASCIIString)
    field = replace(field,r"[dDE]","e")
    i = searchindex(field[2:end-1],'+')
    j = searchindex(field[2:end-1],'-')
    if i > 0 && !(field[i] == 'e')
        field = field[1:i] * "E" * field[i+1:end]
    elseif j > 0 && !(field[j] == 'e')
        field = field[1:j] * "E" * field[j+1:end]
    end
    parse(Float64,field)
end

function parse_number(field::ASCIIString)
    try
        if '.' in field
            parse_float(field::ASCIIString)
        elseif length(field) < 9
            parse(Int64,field)
        else
            field
        end
    catch
        field
    end
end

function parse_numbers{U <: GenericCard}(card::U)
    collect(map(parse_number,card))
end

function read_cards(filename::AbstractString)
    map(eachline(open(filename))) do line
        line |> chomp |> remove_comments |> parse_line |> parse_numbers
    end
end

function merge_continuations(cards)
    # active = Dict{ASCIIString,NastranGenericCard}()
    last_card = nothing
    for card in cards
        if all(f -> f == "",card)
            if last_card != nothing
                produce(last_card)
                last_card = nothing
            end
        elseif card[1] == "+" || card[1] == ""
            if last_card == nothing
                error()
            else
                append!(last_card,card[2:end-1])
            end
        else
            if last_card != nothing
                produce(last_card)
                last_card = nothing
            end
            last_card = card[1:end-1]
        end
    end
end

function GenericNastranDeck(filename::AbstractString)
    cards = read_cards(filename)
    t = @task merge_continuations(cards)
    GenericNastranDeck(collect(t))
end

function NastranDeck(filename::AbstractString)
    cards = read_cards(filename)
    t = @task merge_continuations(cards)
    m = map(t) do card
        convert(NastranCard,card)
    end
    NastranDeck(m)
end
