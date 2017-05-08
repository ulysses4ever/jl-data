
immutable CoordinateSystem
    center::XYZ
    rotation_matrix::Mat3x3
end

function CoordinateSystem(pc::XYZ,pz::XYZ,pxz::XYZ)
    vecz = normalize(pz - pc)
    vecy = normalize(cross(vecz,pxz-pc))
    vecx = normalize(cross(vecy,vecz))
    CoordinateSystem(pc,Mat3x3([Array(vecx) Array(vecy) Array(vecz)]))
end

from_global(csys::CoordinateSystem,p::XYZ) = inv(csys.rotation_matrix) * (p - csys.center)
rotate_to_global(csys::CoordinateSystem,p::XYZ) = csys.rotation_matrix * p
to_global(csys::CoordinateSystem,p::XYZ) = rotate_to_global(csys,p) + csys.center
