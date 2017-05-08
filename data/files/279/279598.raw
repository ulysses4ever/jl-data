
export Sign
export zero, positive, negative, nosign

import Base.show

bitstype 8 Sign

const zero     = reinterpret(Sign, 0x00)
const positive = reinterpret(Sign, 0x01)
const negative = reinterpret(Sign, 0x02)
const nosign   = reinterpret(Sign, 0x03)

function show(io::IO, x::Sign)
  if (x == zero)
    print(io, "zero")
  elseif (x == positive)
    print(io, "positive")
  elseif (x == negative)
    print(io, "negative")
  elseif (x == nosign)
    print(io, "nosign")
  else
    print(io, "invalid sign")
  end
end

function -(x::Sign)
  ix = reinterpret(Uint8, x)
  return reinterpret(Sign, ((ix << 1) | (ix >> 1)) & 0x03) 
end

function +(x::Sign, y::Sign)
  ix = reinterpret(Uint8, x)
  iy = reinterpret(Uint8, y)
  return reinterpret(Sign, ix | iy)
end

function -(x::Sign, y::Sign)
  return x + (-y)
end

function *(x::Sign, y::Sign)
  ix = reinterpret(Uint8, x)
  iy = reinterpret(Uint8, y)
  ir = uint8(ix * iy)
  return reinterpret(Sign, (ir | ir >> 2) & 0x03)
end

