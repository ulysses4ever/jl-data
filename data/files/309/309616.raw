using ImmutableArrays

immutable CoordinateSystem
    center::Vector3{Float64}
    rotation_matrix::Matrix3x3
end

normalize(a::Vector3{Float64}) = a/norm(a)

function CoordinateSystem(pc::Vector3{Float64},pz::Vector3{Float64},pxz::Vector3{Float64})
    vecz = normalize(pz - pc)
    vecy = normalize(cross(vecz,pxz-pc))
    vecx = normalize(cross(vecy,vecz))
    CoordinateSystem(pc,Matrix3x3(vecx,vecy,vecz))
end

from_global(csys::CoordinateSystem,p::Vector3{Float64}) = inv(csys.rotation_matrix) * (p - csys.center)
rotate_to_global(csys::CoordinateSystem,p::Vector3{Float64}) = csys.rotation_matrix * p
to_global(csys::CoordinateSystem,p::Vector3{Float64}) = rotate_to_global(csys,p) + csys.center
