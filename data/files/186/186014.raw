module TEA

using ..GutFlora

const Δ = 0x9e3779b9

function encrypt(v0::UInt32, v1::UInt32,
                 k0::UInt32, k1::UInt32, k2::UInt32, k3::UInt32)
  sum = 0x00000000
  for _ = 1:32
    sum += Δ
    v0 += ((v1<<4) + k0) $ (v1 + sum) $ ((v1>>5) + k1)
    v1 += ((v0<<4) + k2) $ (v0 + sum) $ ((v0>>5) + k3)
  end
  v0, v1
end

function encrypt(v::UInt64, k::UInt128)
  v0, v1 = split2(v)
  k0, k1, k2, k3 = split4(k)
  o0, o1 = encrypt(v0, v1, k0, k1, k2, k3)
  bitcat(o0, o1)
end

function decrypt(v0::UInt32, v1::UInt32,
                 k0::UInt32, k1::UInt32, k2::UInt32, k3::UInt32)
  sum = 0xC6EF3720
  for _ = 1:32
    v1 -= ((v0<<4) + k2) $ (v0 + sum) $ ((v0>>5) + k3)
    v0 -= ((v1<<4) + k0) $ (v1 + sum) $ ((v1>>5) + k1)
    sum -= Δ
  end
  v0, v1
end

function decrypt(v::UInt64, k::UInt128)
  v0, v1 = split2(v)
  k0, k1, k2, k3 = split4(k)
  o0, o1 = decrypt(v0, v1, k0, k1, k2, k3)
  bitcat(o0, o1)
end

end
