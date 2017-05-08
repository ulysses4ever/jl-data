calc_masscg(card::CELAS1,model::NastranModel) = MassCG()
calc_masscg(card::CELAS2,model::NastranModel) = MassCG()
calc_masscg(card::CBUSH,model::NastranModel) = MassCG()
calc_masscg(card::RBE2,model::NastranModel) = MassCG()
calc_masscg(card::RBE3,model::NastranModel) = MassCG()

function calc_masscg(card::CBEAM,model::NastranModel)
    prop = model.properties[card.prop_id]
    mat = model.materials[prop.mat_id]
    if prop.nonstructural_mass != 0
        throw(ExceptionError("Nonstructural Mass not supported on CBEAM"))
    end
    if mat.rho != 0
        throw(ExceptionError("Structural Mass not supported on CBEAM"))
    end
    MassCG()
end
function calc_masscg(card::CROD,model::NastranModel)
    prop = model.properties[card.prop_id]
    mat = model.materials[prop.mat_id]
    if prop.nonstructural_mass != 0
        throw(ExceptionError("Nonstructural Mass not supported on CROD"))
    end
    if mat.rho != 0
        throw(ExceptionError("Structural Mass not supported on CROD"))
    end
    MassCG()
end
function calc_masscg(card::CTRIAR,model::NastranModel)
    prop = model.properties[card.prop_id]
    mat = model.materials[prop.mat1_id]
    if prop.nonstructural_mass != 0
        throw(ExceptionError("Nonstructural Mass not supported on CTRIAR"))
    end
    if mat.rho != 0
        throw(ExceptionError("Structural Mass not supported on CTRIAR"))
    end
    MassCG()
end

function calc_masscg(card::CQUADR,model::NastranModel)
    prop = model.properties[card.prop_id]
    mat = model.materials[prop.mat1_id]
    if prop.nonstructural_mass != 0
        throw(ExceptionError("Nonstructural Mass not supported on CQUADR"))
    end
    if mat.rho != 0
        throw(ExceptionError("Structural Mass not supported on CQUADR"))
    end
    MassCG()
end
function calc_masscg(card::CONM2,model::NastranModel)
    if card.csys_id == -1
        MassCG(card.mass,Vector3(card.x,card.y,card.z))
    else
        vec = Vector3(card.x,card.y,card.z)
        grid = get_global_xyz(model.coordset,card.grid_id)
        if card.csys_id == 0
            loc = grid.xyz + vec
        else
            coord = get_coord(model.coordset,card.csys_id)
            loc = grid.xyz + rotate_to_global(coord.csys,vec)
        end
        MassCG(card.mass,loc)
    end
end

function calc_masscg(model::NastranModel)
    masscg = MassCG(0.0,Vector3(0.0,0.0,0.0))
    for card in values(model.elements)
        masscg += calc_masscg(card,model)
    end
    masscg
end

calc_masscg(filename::AbstractString) = calc_masscg(NastranModel(filename))
calc_masscg(filenames::Vector{AbstractString}) =
    mapreduce(filename->calc_masscg(NastranModel(filename)),+,MassCG(),filenames)
