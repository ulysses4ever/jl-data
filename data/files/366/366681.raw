
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

rotate_from_global(csys::CoordinateSystem,p::XYZ) = csys.rotation_matrix' * p
rotate_to_global(csys::CoordinateSystem,p::XYZ) = csys.rotation_matrix * p

rotate_from_global(csys::CoordinateSystem,p::Mat3x3) = csys.rotation_matrix' * p * csys.rotation_matrix
rotate_to_global(csys::CoordinateSystem,p::Mat3x3) = csys.rotation_matrix * p * csys.rotation_matrix'

from_global(csys::CoordinateSystem,p::XYZ) = rotate_from_global(csys,p-csys.center)
to_global(csys::CoordinateSystem,p::XYZ) = rotate_to_global(csys,p) + csys.center
