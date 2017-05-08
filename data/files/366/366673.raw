immutable MassCG
    mass::Float64
    cg::XYZ
    inertia::Mat3x3
end
zero(::Type{MassCG}) = MassCG(0.0,zero(XYZ),zero(Mat3x3))
MassCG() = zero(MassCG)

function parallel_axis_inertia(mcg::MassCG,new_cg::XYZ)
    vec = new_cg - mcg.cg
    return mcg.inertia + mcg.mass*(sumabs2(vec)*eye(Mat3x3) - vec*vec')
end

function +(a::MassCG,b::MassCG)
    mass = a.mass + b.mass
    if mass == 0
        cg = zero(XYZ)
    else
        cg = (a.mass*a.cg + b.mass*b.cg)/mass
    end
    inertia = parallel_axis_inertia(a,cg) + parallel_axis_inertia(b,cg)
    MassCG(mass,cg,inertia)
end

function -(a::MassCG,b::MassCG)
    mass = a.mass - b.mass
    if mass == 0
        cg = zero(XYZ)
    else
        cg = (a.mass*a.cg - b.mass*b.cg)/mass
    end
    inertia = parallel_axis_inertia(a,cg) - parallel_axis_inertia(b,cg)
    MassCG(mass,cg,inertia)
end

MassCG(card::CAERO1,model::NastranModel) = MassCG()
MassCG(card::SPLINE1,model::NastranModel) = MassCG()
MassCG(card::SPLINE2,model::NastranModel) = MassCG()
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
    inertia = Mat3x3([
                        card.I11 card.I21 card.I31;
                        card.I21 card.I22 card.I32;
                        card.I31 card.I32 card.I33;
                        ])
    if card.csys_id == -1
        MassCG(card.mass,XYZ(card.x,card.y,card.z),inertia)
    else
        vec = XYZ(card.x,card.y,card.z)
        grid = get_global_xyz(model,card.grid_id)
        if card.csys_id == 0
            loc = grid + vec
        else
            csys = CoordinateSystem(model,card.csys_id)
            loc = grid + rotate_to_global(csys,vec)
            inertia = rotate_to_global(csys,inertia)
        end
        MassCG(card.mass,loc,inertia)
    end
end

MassCG(model::NastranModel) = mapreduce(card -> MassCG(card,model), +, values(model.elements))

MassCG(filename::AbstractString) = MassCG(NastranModel(filename))
MassCG(filenames::Vector{AbstractString}) =
    mapreduce(filename->MassCG(NastranModel(filename)),+,MassCG(),filenames)
