typealias GenericNastranDeck Vector{GenericCard}
typealias NastranDeck Vector{NastranCard}

function next_token(line::IOBuffer,N::Int64)
    token = String(read(line,N))
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

function parse_line{T<:AbstractString}(line::T)
    buf = IOBuffer(line)
    card = T[]
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
function parse_number(field::String)
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

function parse_numbers(card::Vector{String})
    map(parse_number,card)
end

function read_cards(filename::AbstractString)
    map(eachline(open(filename))) do line
        line |> chomp |> remove_comments |> parse_line |> parse_numbers
    end
end

immutable NastranCardIterator
    cards
end

Base.start(I::NastranCardIterator) = (Dict{String,GenericCard}(),start(I.cards))

function Base.next(I::NastranCardIterator,state)
    cont_cards, cards_state = state
    while !done(I.cards,cards_state)
        card, cards_state = next(I.cards,cards_state)
        if all(f -> f == "",card)
            if haskey(cont_cards,"+") && haskey(cont_cards,"")
                c = pop!(cont_cards,"")
                cont_cards[""] = pop!(cont_cards,"+")
                return (c,(cont_cards,cards_state))
            elseif haskey(cont_cards,"+")
                cont_cards[""] = pop!(cont_cards,"+")
            end
        elseif card[1] == "+" || card[1] == ""
            if !haskey(cont_cards,"+")
                @show card
                @show cont_cards
                error()
            end
            append!(cont_cards["+"],card[2:end-1])
        else
            if haskey(cont_cards,"+") && haskey(cont_cards,"")
                c = pop!(cont_cards,"")
                cont_cards[""] = pop!(cont_cards,"+")
                cont_cards["+"] = card[1:end-1]
                return (c,(cont_cards,cards_state))
            elseif haskey(cont_cards,"+")
                cont_cards[""] = pop!(cont_cards,"+")
            end
            cont_cards["+"] = card[1:end-1]
        end
    end
    if haskey(cont_cards,"")
        c = pop!(cont_cards,"")
        return (c,(cont_cards,cards_state))
    end
    if haskey(cont_cards,"+")
        c = pop!(cont_cards,"+")
        return (c,(cont_cards,cards_state))
    end
end
Base.done(I::NastranCardIterator,state) = done(I.cards,state[2]) && length(state[1]) == 0

function GenericNastranDeck(filename::AbstractString)
    cards = read_cards(filename)
    GenericNastranDeck(collect(NastranCardIterator(cards)))
end

function NastranDeck(filename::AbstractString)
    cards = read_cards(filename)
    deck = []
    for card in NastranCardIterator(cards)
        push!(deck,card)
    end
    deck
end
