module Nastran

import Base: show

using ImmutableArrays
using CoordinateSystems

export NastranDeck, GenericNastranDeck, NastranModel
export CBEAM, CONM2, CELAS1, CQUADR, CTRIAR, CELAS2, RBE2, RBE3, CBUSH, CROD
export CoordSet,get_coord,get_global_xyz

typealias GenericCard Vector{Any}
typealias GenericNastranDeck Vector{GenericCard}

abstract NastranCard{CardType}

immutable CardType{T} end

ElementCardType = CardType{:element}()
typealias ElementCard NastranCard{ElementCardType}

PropertyCardType = CardType{:property}()
typealias PropertyCard NastranCard{PropertyCardType}

MaterialCardType = CardType{:material}()
typealias MaterialCard NastranCard{MaterialCardType}

GridCardType = CardType{:grid}()
typealias GridCard NastranCard{GridCardType}

ConstraintCardType = CardType{:constraint}()
typealias ConstraintCard NastranCard{ConstraintCardType}

CoordinateSystemCardType = CardType{:coordinate_system}()
typealias CoordinateSystemCard NastranCard{CoordinateSystemCardType}

typealias NastranDeck Vector{NastranCard}

include("cards.jl")

@generated function NastranCard{U}(u::Type{Val{U}},card)
    return :(convert($U,card))
end
function convert(::Type{NastranCard},card::GenericCard)
    NastranCard(Val{symbol(card[1])},card)
end

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

function card_dict{C<:NastranCard}(::Type{C},deck::NastranDeck)
    Dict{Int64,C}(map(filter(c -> typeof(c)<:C,deck)) do card
        (card.id,card)
    end)
end

type Grid
    id::Int64
    csys_id::Int64
    xyz::Vector3{Float64}
end

type Coord
    id::Int64
    csys::CoordinateSystem
end

Grid(card::GRID) = Grid(card.id,card.csys_id,Vector3(card.x,card.y,card.z))
Grid(card::SPOINT) = Grid(card.id,0,Vector3(0.0,0.0,0.0))

immutable CoordSet
    coords::Vector{Coord}
    local_xyzs::Vector{Grid}
    global_xyzs::Vector{Grid}
end

sort_by_id(x::Int64) = x
sort_by_id(x::Grid) = x.id
sort_by_id(x::Coord) = x.id

function get_coord(coordset::CoordSet,id)
    i = searchsorted(coordset.coords,id,by=sort_by_id)
    @assert length(i) == 1
    coordset.coords[first(i)]
end

function get_global_xyz(coordset::CoordSet,id)
    i = searchsorted(coordset.global_xyzs,id,by=sort_by_id)
    @assert length(i) == 1
    coordset.global_xyzs[first(i)]
end

function CoordinateSystem(global_xyzs::Vector{Grid},card::CORD1R)
    iA = searchsorted(global_xyzs,card.gridA,by=sort_by_id)
    @assert length(iA) == 1
    gridA = global_xyzs[first(iA)]

    iB = searchsortedfirst(global_xyzs,card.gridB,by=sort_by_id)
    @assert length(iB) == 1
    gridB = global_xyzs[first(iB)]

    iC = searchsortedfirst(global_xyzs,card.gridC,by=sort_by_id)
    @assert length(iC) == 1
    gridC = global_xyzs[first(iC)]

    if gridA.csys_id == 0 && gridB.csys_id == 0 && gridC.csys_id == 0
        Coord(card.id,CoordinateSystem(gridA.xyz,gridB.xyz,gridC.xyz))
    end
end

function CoordinateSystem(global_xyzs::Vector{Grid},card::CORD2R)
    if card.csys_id == 0
        pA = Vector3(card.gridAx,card.gridAy,card.gridAz)
        pB = Vector3(card.gridBx,card.gridBy,card.gridBz)
        pC = Vector3(card.gridCx,card.gridCy,card.gridCz)
        Coord(card.id,CoordinateSystem(pA,pB,pC))
    else
        throw(MethodError("Not Implemented"))
    end
end

function CoordSet(grid_cards::Dict{Int64,GridCard},csys_cards::Dict{Int64,CoordinateSystemCard})
    grid_ids = sort(collect(keys(grid_cards)))
    local_xyzs = map(grid_ids) do id
        Grid(grid_cards[id])
    end
    # global_xyzs starts the same as local_xyzs. As the coordinates are converted the csys_id is
    # updated to be 0 and the global coordinate is changed
    global_xyzs = copy(local_xyzs)
    csys_ids = sort(collect(keys(csys_cards)))
    converted = false
    # coords is initiated as an empty vector that is filled in as coordinate systems are defined
    coords = Vector{Coord}(length(csys_ids))
    # Loop through all the coordinate systems and grids repeatedly until all the coordinate
    # systems are defined and therefore the global locations of all the grids are found
    while !converted
        # Set converted to true at the top of every loop. converted gets set to false when
        # it either fails to define a coordinate system or convert a grid to global coordinates
        converted = true
        for (i,id) in enumerate(csys_ids)
            if isdefined(coords,i)
                continue
            else
                csys = CoordinateSystem(global_xyzs,csys_cards[id])
                if csys != nothing
                    coords[i] = csys
                else
                    converted = false
                end
            end
        end
        for grid in global_xyzs
            if grid.csys_id == 0
                continue
            else
                i_csys = searchsortedfirst(csys_ids,grid.csys_id)
                if isdefined(coords,i_csys)
                    coord = coords[i_csys]
                    grid.csys_id = 0
                    grid.xyz = to_global(coord.csys,grid.xyz)
                else
                    converted = false
                end
            end
        end
    end
    CoordSet(coords,local_xyzs,global_xyzs)
end

type NastranModel
    grids::Dict{Int64,GridCard}
    elements::Dict{Int64,ElementCard}
    properties::Dict{Int64,PropertyCard}
    materials::Dict{Int64,MaterialCard}
    constraints::Dict{Int64,ConstraintCard}
    coordinate_systems::Dict{Int64,CoordinateSystemCard}
    coordset::CoordSet
end

function show(io::IO,model::NastranModel)
    print(io,"NastranModel(")
    print(io,length(model.grids),",")
    print(io,length(model.elements),",")
    print(io,length(model.properties),",")
    print(io,length(model.materials),",")
    print(io,length(model.constraints),",")
    print(io,length(model.coordinate_systems),")")
end

function NastranModel(filename::AbstractString)
    deck = NastranDeck(filename)
    grid_cards = card_dict(GridCard,deck)
    element_cards = card_dict(ElementCard,deck)
    property_cards = card_dict(PropertyCard,deck)
    material_cards = card_dict(MaterialCard,deck)
    constraint_cards = card_dict(ConstraintCard,deck)
    coordinate_system_cards = card_dict(CoordinateSystemCard,deck)
    coordset = CoordSet(grid_cards,coordinate_system_cards)
    NastranModel(grid_cards,
                 element_cards,
                 property_cards,
                 material_cards,
                 constraint_cards,
                 coordinate_system_cards,
                 coordset)
end


end # module
