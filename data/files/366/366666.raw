immutable MassCG
    mass::Float64
    cg::Vector3{Float64}
end
MassCG() = MassCG(0.0,Vector3(0.0,0.0,0.0))

function +(a::MassCG,b::MassCG)
    mass = a.mass + b.mass
    if mass == 0
        cg = Vector3(0.0,0.0,0.0)
    else
        cg = (a.mass*a.cg + b.mass*b.cg)/mass
    end
    MassCG(mass,cg)
end

function -(a::MassCG,b::MassCG)
    mass = a.mass - b.mass
    if mass == 0
        cg = Vector3(0.0,0.0,0.0)
    else
        cg = (a.mass*a.cg - b.mass*b.cg)/mass
    end
    MassCG(mass,cg)
end

MassCG(card::CELAS1,model::NastranModel) = MassCG()
MassCG(card::CELAS2,model::NastranModel) = MassCG()
MassCG(card::CBUSH,model::NastranModel) = MassCG()
MassCG(card::RBE2,model::NastranModel) = MassCG()
MassCG(card::RBE3,model::NastranModel) = MassCG()

function MassCG(card::CBEAM,model::NastranModel)
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
function MassCG(card::CROD,model::NastranModel)
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
function MassCG(card::CTRIAR,model::NastranModel)
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

function MassCG(card::CQUADR,model::NastranModel)
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
function MassCG(card::CONM2,model::NastranModel)
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

MassCG(model::NastranModel) = mapreduce(card -> MassCG(card,model),
                                        +,
                                        values(model.elements))

MassCG(filename::AbstractString) = MassCG(NastranModel(filename))
MassCG(filenames::Vector{AbstractString}) =
    mapreduce(filename->MassCG(NastranModel(filename)),+,MassCG(),filenames)
