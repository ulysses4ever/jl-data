module Vec

export Vec3,+,-,*,/,⋅,x

immutable Vec3{T}
  x::T
  y::T
  z::T
end

@inline function +(a::Vec3, b::Vec3)
  return Vec3(a.x + b.x,
              a.y + b.y,
              a.z + b.z)
end

@inline function -(a::Vec3, b::Vec3)
  return Vec3(a.x - b.x,
              a.y - b.y,
              a.z - b.z)
end

@inline function *(a::Vec3, b::Vec3)
  return Vec3(a.x * b.x,
              a.y * b.y,
              a.z * b.z)
end

@inline function /(a::Vec3, b::Vec3)
  return Vec3(a.x / b.x,
              a.y / b.y,
              a.z / b.z)
end

@inline function ⋅(a::Vec3, b::Vec3)
  return a.x*b.x +
         a.y*b.y +
         a.z*b.z
end

@inline function x (a::Vec3, b::Vec3)
  return Vec3(a.y*b.z - a.z*b.y,
              a.z*b.x - a.x*b.z,
              a.x*b.y - a.y*b.x)
end

end
