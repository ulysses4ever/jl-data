#! /usr/bin/julia

# Rosetta Code, Playing cards

type DeckDesign{T<:Integer,U<:String}
    rlen::T
    slen::T
    ranks::Array{U,1}
    suits::Array{U,1}
    hlen::T
end

type Deck{T<:Integer}
    cards::Array{T,1}
    design::DeckDesign
end

Deck(n::Integer, des::DeckDesign) = Deck([n], des)

function pokerlayout()
    r = [map(string, 2:10), "J", "Q", "K", "A"]
    r = map(utf8, r)
    s = ["\u2663", "\u2666", "\u2665", "\u2660"]
    DeckDesign(13, 4, r, s, 5)
end

function fresh(des::DeckDesign)
    Deck(collect(1:des.rlen*des.slen), des)
end

Base.isempty(d::Deck) = isempty(d.cards)
Base.empty!(d::Deck) = empty!(d.cards)
Base.length(d::Deck) = length(d.cards)
Base.endof(d::Deck) = endof(d.cards)
Base.shuffle!(d::Deck) = shuffle!(d.cards)
Base.sort!(d::Deck) = sort!(d.cards)
Base.getindex(d::Deck, r) = Deck(getindex(d.cards, r), d.design)
Base.size(d::Deck) = (d.design.rlen, d.design.slen)
function Base.print(d::Deck)
    sz = size(d)
    r = map(x->d.design.ranks[ind2sub(sz, x)[1]], d.cards)
    s = map(x->d.design.suits[ind2sub(sz, x)[2]], d.cards)
    join(r.*s, " ")
end

function deal!{T<:Integer}(d::Deck, hlen::T)
    if hlen < length(d)
        hand = Deck(d.cards[1:hlen], d.design)
        d.cards = d.cards[hlen+1:end]
    else
        hand = d
        empty!(d)
    end
    return hand
end

function deal!(d::Deck)
    deal!(d, d.design.hlen)
end

function pretty(d::Deck)
    s = ""
    llen = d.design.rlen
    dlen = length(d)
    for i in 1:llen:dlen
        j = min(i+llen-1, dlen)
        s *= print(d[i:j])*"\n"
    end
    chop(s)
end

d = fresh(pokerlayout())
println("A new poker deck:")
println(pretty(d))

shuffle!(d)
println()
println("The deck shuffled:")
println(pretty(d))

n = 4
println()
println("Deal ", n, " hands:")
for i in 1:n
    h = deal!(d)
    println(pretty(h))
end

println()
println("And now the deck contains:")
println(pretty(d))
