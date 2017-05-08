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

isnastranfloat = r"^([+-]?[0-9]*(?:[0-9]\.|\.[0-9])[0-9]*)[dD]?([+-][0-9]+)$"
isfloat = r"^([+-]?[0-9]*(?:[0-9]\.|\.[0-9])[0-9]*)(?:[eE]([+-][0-9]+))?$"
isint = r"^(?:[+-][0-9]{1,7}|[0-9]{1,8})$"
function parse_number(field::ASCIIString)
    m = match(isnastranfloat,field)
    if m != nothing
        parse(Float64,join(m.captures,"e"))
    elseif ismatch(isfloat,field)
        parse(Float64,field)
    elseif ismatch(isint,field)
        parse(Int64,field)
    else
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

immutable NastranCardIterator
    cards
end

Base.start(I::NastranCardIterator) = (nothing,start(I.cards))

function Base.next(I::NastranCardIterator,state)
    last_card, cards_state = state
    while !done(I.cards,cards_state)
        card, cards_state = next(I.cards,cards_state)
        if all(f -> f == "",card)
            if last_card != nothing
                return (last_card,(nothing,cards_state))
            end
        elseif card[1] == "+" || card[1] == ""
            if last_card == nothing
                error()
            end
            append!(last_card,card[2:end-1])
        else
            if last_card == nothing
                last_card = card[1:end-1]
            else
                return (last_card,(card[1:end-1],cards_state))
            end
        end
    end
    return (last_card,(nothing,cards_state))
end
Base.done(I::NastranCardIterator,state) = done(I.cards,state[2]) && state[1] == nothing

function GenericNastranDeck(filename::AbstractString)
    cards = read_cards(filename)
    GenericNastranDeck(collect(NastranCardIterator(cards)))
end

function NastranDeck(filename::AbstractString)
    cards = read_cards(filename)
    # for card in NastranCardIterator(cards)
    #     @show card
    # end
    NastranDeck(collect(NastranCardIterator(cards)))
    # m = map(NastranCardIterator(cards)) do card
    #             card
    #     # convert(NastranCard,card)
    # end
    # m
end
