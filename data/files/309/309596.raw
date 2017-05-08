function card_dict{C<:NastranCard}(::Type{C},deck::NastranDeck)
    Dict{Int64,C}(map(filter(c -> typeof(c)<:C,deck)) do card
        (card.id,card)
    end)
end

# type Grid
#     id::Int64
#     csys_id::Int64
#     xyz::XYZ
# end

# type Coord
#     id::Int64
#     csys::CoordinateSystem
# end

# Grid(card::GRID) = Grid(card.id,card.csys_id,XYZ(card.x,card.y,card.z))
# Grid(card::SPOINT) = Grid(card.id,0,zero(XYZ))

# immutable CoordSet
#     coords::Vector{Coord}
#     local_xyzs::Vector{Grid}
#     global_xyzs::Vector{Grid}
# end

# sort_by_id(x::Int64) = x
# sort_by_id(x::Grid) = x.id
# sort_by_id(x::Coord) = x.id

# function get_coord(coordset::CoordSet,id)
#     i = searchsorted(coordset.coords,id,by=sort_by_id)
#     @assert length(i) == 1
#     coordset.coords[first(i)]
# end

# function get_global_xyz(coordset::CoordSet,id)
#     i = searchsorted(coordset.global_xyzs,id,by=sort_by_id)
#     @assert length(i) == 1
#     coordset.global_xyzs[first(i)]
# end

# function CoordinateSystem(global_xyzs::Vector{Grid},card::CORD1R)
#     iA = searchsorted(global_xyzs,card.gridA,by=sort_by_id)
#     @assert length(iA) == 1
#     gridA = global_xyzs[first(iA)]

#     iB = searchsortedfirst(global_xyzs,card.gridB,by=sort_by_id)
#     @assert length(iB) == 1
#     gridB = global_xyzs[first(iB)]

#     iC = searchsortedfirst(global_xyzs,card.gridC,by=sort_by_id)
#     @assert length(iC) == 1
#     gridC = global_xyzs[first(iC)]

#     if gridA.csys_id == 0 && gridB.csys_id == 0 && gridC.csys_id == 0
#         Coord(card.id,CoordinateSystem(gridA.xyz,gridB.xyz,gridC.xyz))
#     end
# end

# function CoordinateSystem(global_xyzs::Vector{Grid},card::CORD2R)
#     if card.csys_id == 0
#         pA = XYZ(card.gridAx,card.gridAy,card.gridAz)
#         pB = XYZ(card.gridBx,card.gridBy,card.gridBz)
#         pC = XYZ(card.gridCx,card.gridCy,card.gridCz)
#         Coord(card.id,CoordinateSystem(pA,pB,pC))
#     else
#         throw(MethodError("Not Implemented"))
#     end
# end

# function CoordSet(grid_cards::Dict{Int64,GridCard},csys_cards::Dict{Int64,CoordinateSystemCard})
#     grid_ids = sort(collect(keys(grid_cards)))
#     local_xyzs::Vector{Grid} = map(grid_ids) do id
#         Grid(grid_cards[id])
#     end
#     # global_xyzs starts the same as local_xyzs. As the coordinates are converted the csys_id is
#     # updated to be 0 and the global coordinate is changed
#     global_xyzs = copy(local_xyzs)
#     csys_ids = sort(collect(keys(csys_cards)))
#     converted = false
#     # coords is initiated as an empty vector that is filled in as coordinate systems are defined
#     coords = Vector{Coord}(length(csys_ids))
#     # Loop through all the coordinate systems and grids repeatedly until all the coordinate
#     # systems are defined and therefore the global locations of all the grids are found
#     while !converted
#         # Set converted to true at the top of every loop. converted gets set to false when
#         # it either fails to define a coordinate system or convert a grid to global coordinates
#         converted = true
#         for (i,id) in enumerate(csys_ids)
#             if isdefined(coords,i)
#                 continue
#             else
#                 csys = CoordinateSystem(global_xyzs,csys_cards[id])
#                 if csys != nothing
#                     coords[i] = csys
#                 else
#                     converted = false
#                 end
#             end
#         end
#         for grid in global_xyzs
#             if grid.csys_id == 0
#                 continue
#             else
#                 i_csys = searchsortedfirst(csys_ids,grid.csys_id)
#                 if isdefined(coords,i_csys)
#                     coord = coords[i_csys]
#                     grid.csys_id = 0
#                     grid.xyz = to_global(coord.csys,grid.xyz)
#                 else
#                     converted = false
#                 end
#             end
#         end
#     end
#     CoordSet(coords,local_xyzs,global_xyzs)
# end

type NastranModel
    grids::Dict{Int64,GridCard}
    elements::Dict{Int64,ElementCard}
    properties::Dict{Int64,PropertyCard}
    materials::Dict{Int64,MaterialCard}
    constraints::Dict{Int64,ConstraintCard}
    coordinate_systems::Dict{Int64,CoordinateSystemCard}
    sets::Dict{Int64,SetCard}
    # coordset::CoordSet
end

function show(io::IO,model::NastranModel)
    print(io,"NastranModel(")
    print(io,length(model.grids),",")
    print(io,length(model.elements),",")
    print(io,length(model.properties),",")
    print(io,length(model.materials),",")
    print(io,length(model.constraints),",")
    print(io,length(model.coordinate_systems),")")
    print(io,length(model.sets),",")
end

function CoordinateSystem(model::NastranModel,card::CORD1R)
    if card.gridA in keys(model.grids) && card.gridB in keys(model.grids) && card.gridC in keys(model.grids)
        xyzA = get_global_xyz(model,card.gridA)
        xyzB = get_global_xyz(model,card.gridB)
        xyzC = get_global_xyz(model,card.gridC)
        CoordinateSystem(xyzA,xyzB,xyzC)
    else
        throw(ExceptionError("Not all grids found"))
    end
end

function CoordinateSystem(model::NastranModel,card::CORD2R)
    if card.csys_id == 0
        pA = XYZ(card.gridAx,card.gridAy,card.gridAz)
        pB = XYZ(card.gridBx,card.gridBy,card.gridBz)
        pC = XYZ(card.gridCx,card.gridCy,card.gridCz)
        CoordinateSystem(pA,pB,pC)
    else
        throw(MethodError("Not Implemented"))
    end
end

function CoordinateSystem(model::NastranModel,id::Int64)
    card = model.coordinate_systems[id]
    CoordinateSystem(model,card)
end

function get_global_xyz(model::NastranModel,id::Int64)
    grid = model.grids[id]
    if grid.csys_id == 0
        XYZ(grid.x,grid.y,grid.z)
    else
        coord = CoordinateSystem(model,grid.csys_id)
        local_xyz = XYZ(grid.x,grid.y,grid.z)
        to_global(coord,local_xyz)
    end
end

function NastranModel(filename::AbstractString)
    deck = NastranDeck(filename)
    grid_cards = card_dict(GridCard,deck)
    element_cards = card_dict(ElementCard,deck)
    property_cards = card_dict(PropertyCard,deck)
    material_cards = card_dict(MaterialCard,deck)
    constraint_cards = card_dict(ConstraintCard,deck)
    set_cards = card_dict(SetCard,deck)
    coordinate_system_cards = card_dict(CoordinateSystemCard,deck)
    # coordset = CoordSet(grid_cards,coordinate_system_cards)
    NastranModel(grid_cards,
                 element_cards,
                 property_cards,
                 material_cards,
                 constraint_cards,
                 coordinate_system_cards,
                 set_cards)
end
