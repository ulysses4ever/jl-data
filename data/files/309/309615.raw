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

function inertia_from_tetra(points::Vector{XYZ})
    I11 = 0.0
    I22 = 0.0
    I33 = 0.0
    I21 = 0.0
    I31 = 0.0
    I32 = 0.0
    for i in 1:4
        for j in i:4
            I11 += points[i][2]*points[j][2] + points[i][3]*points[j][3]
            I22 += points[i][1]*points[j][1] + points[i][3]*points[j][3]
            I33 += points[i][1]*points[j][1] + points[i][2]*points[j][2]
        end
    end
    for i in 1:4
        for j in 1:4
            I21 -= points[i][1]*points[j][2]
            I31 -= points[i][1]*points[j][3]
            I32 -= points[i][2]*points[j][3]
        end
        I21 -= points[i][1]*points[i][2]
        I31 -= points[i][1]*points[i][3]
        I32 -= points[i][2]*points[i][3]
    end
    I21 /= 2.0
    I31 /= 2.0
    I32 /= 2.0
    Mat3x3([
         I11 I21 I31;
         I21 I22 I32;
         I31 I32 I33;
         ])/10.0
end

# http://docsdrive.com/pdfs/sciencepublications/jmssp/2005/8-11.pdf
function masscg_from_tetra(points::Vector{XYZ})
    cg = sum(points)/4
    vol = dot(cross(points[2] - points[1],points[3] - points[2]),points[4]-points[1])/6
    delta = map(p-> p-cg,points)
    I = inertia_from_tetra(delta)*vol
    return MassCG(vol,cg,I)
end

function masscg_from_pyramid(center::XYZ,points::XYZ...)
    face_center = sum(points)/length(points)
    mcg = MassCG()
    for i in 1:length(points)
        j = (i % length(points)) + 1
        mcg += masscg_from_tetra([points[i],points[j],face_center,center])
    end
    mcg
end

function MassCG(card::CHEXA,model::NastranModel)
    xyz1 = get_global_xyz(model,card.point1)
    xyz2 = get_global_xyz(model,card.point2)
    xyz3 = get_global_xyz(model,card.point3)
    xyz4 = get_global_xyz(model,card.point4)
    xyz5 = get_global_xyz(model,card.point5)
    xyz6 = get_global_xyz(model,card.point6)
    xyz7 = get_global_xyz(model,card.point7)
    xyz8 = get_global_xyz(model,card.point8)
    xyz9 = card.point9 == 0 ? (xyz1 + xyz2)/2 : get_global_xyz(model,card.point9)
    xyz10 = card.point10 == 0 ? (xyz2 + xyz3)/2 : get_global_xyz(model,card.point10)
    xyz11 = card.point11 == 0 ? (xyz3 + xyz4)/2 : get_global_xyz(model,card.point11)
    xyz12 = card.point12 == 0 ? (xyz4 + xyz1)/2 : get_global_xyz(model,card.point12)
    xyz13 = card.point13 == 0 ? (xyz1 + xyz5)/2 : get_global_xyz(model,card.point13)
    xyz14 = card.point14 == 0 ? (xyz2 + xyz6)/2 : get_global_xyz(model,card.point14)
    xyz15 = card.point15 == 0 ? (xyz3 + xyz7)/2 : get_global_xyz(model,card.point15)
    xyz16 = card.point16 == 0 ? (xyz4 + xyz8)/2 : get_global_xyz(model,card.point16)
    xyz17 = card.point17 == 0 ? (xyz5 + xyz6)/2 : get_global_xyz(model,card.point17)
    xyz18 = card.point18 == 0 ? (xyz6 + xyz7)/2 : get_global_xyz(model,card.point18)
    xyz19 = card.point19 == 0 ? (xyz7 + xyz8)/2 : get_global_xyz(model,card.point19)
    xyz20 = card.point20 == 0 ? (xyz8 + xyz5)/2 : get_global_xyz(model,card.point20)

    center = (xyz1 + xyz2 + xyz3 + xyz4 + xyz5 + xyz6 + xyz7 + xyz8)/8
    mcg = MassCG()
    mcg += masscg_from_pyramid(center,xyz1,xyz9,xyz2,xyz10,xyz3,xyz11,xyz4,xyz12)
    mcg += masscg_from_pyramid(center,xyz20,xyz8,xyz19,xyz7,xyz18,xyz6,xyz17,xyz5)
    mcg += masscg_from_pyramid(center,xyz1,xyz13,xyz5,xyz17,xyz6,xyz14,xyz2,xyz9)
    mcg += masscg_from_pyramid(center,xyz2,xyz14,xyz6,xyz18,xyz7,xyz15,xyz3,xyz10)
    mcg += masscg_from_pyramid(center,xyz3,xyz15,xyz7,xyz19,xyz8,xyz16,xyz4,xyz11)
    mcg += masscg_from_pyramid(center,xyz4,xyz16,xyz8,xyz20,xyz5,xyz13,xyz1,xyz12)
    mcg
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
MassCG(models::Vector{NastranModel}) = mapreduce(model -> MassCG(model), +, MassCG(), models)

MassCG(filename::AbstractString) = MassCG(NastranModel(filename))
MassCG(filenames::Vector{AbstractString}) =
    mapreduce(filename->MassCG(NastranModel(filename)),+,MassCG(),filenames)
