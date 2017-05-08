module Vec

export Vec3,+,-,*,/,⋅,x,mag

immutable Vec3
  x::Float64
  y::Float64
  z::Float64
end
function Vec3(val::Float64)
  return Vec3(val, val, val)
end
function Vec3()
  return Vec3(0.0, 0.0, 0.0)
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

# component multiplication
@inline function *(a::Vec3, b::Vec3)
  return Vec3(a.x * b.x,
              a.y * b.y,
              a.z * b.z)
end

# Scalar multiplication
@inline function *(a::Vec3, b::Float64)
  return Vec3(a.x*b, a.y*b, a.z*b)
end
@inline function *(a::Float64, b::Vec3)
  return Vec3(a*b.x, a*b.y, a*b.z)
end

@inline function /(a::Vec3, b::Vec3)
  return Vec3(a.x / b.x,
              a.y / b.y,
              a.z / b.z)
end

@inline function /(a::Vec3, b::Float64)
  return Vec3(a.x/b, a.y/b, a.z/b)
end

# Dot product

@inline function ⋅(a::Vec3, b::Vec3)
  return a.x*b.x +
         a.y*b.y +
         a.z*b.z
end

# Cross product
@inline function x(a::Vec3, b::Vec3)
  return Vec3(a.y*b.z - a.z*b.y,
              a.z*b.x - a.x*b.z,
              a.x*b.y - a.y*b.x)
end

@inline function mag(a::Vec3)
  return sqrt(a.x^2 + a.y^2 + a.z^2)
end

end
