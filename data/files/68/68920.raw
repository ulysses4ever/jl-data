module Eq

immutable MomentTensor{T}
    xx::T
    yy::T
    zz::T
    xy::T
    xz::T
    yz::T
end
MomentTensor() = MomentTensor(0.0, 0.0, 0.0, 0.0, 0.0, 0.0)


const _rtf_sign_from_xyz = Dict(:z => (:r, +1),
                                :y => (:t, -1),
                                :x => (:f, +1))
_ss(a::Symbol, b::Symbol) = symbol(string(a)*string(b))
for xyz1 in (:x, :y, :z), xyz2 in (:x, :y, :z)
    _el = _ss(sort([xyz1, xyz2])...)
    @eval $(_ss(xyz1, xyz2)){T}(m::MomentTensor{T}) = m.$_el
    (rtf1, sign1) = _rtf_sign_from_xyz[xyz1]
    (rtf2, sign2) = _rtf_sign_from_xyz[xyz2]
    @eval $(_ss(rtf1, rtf2)){T}(m::MomentTensor{T}) = $(sign1*sign2)*m.$_el
end


Base.show(io::IO, x::MomentTensor) = Base.print(io, "xx:$(xx(x))\tyy:$(yy(x))\tzz:$(zz(x))\txy:$(xy(x))\txz:$(xz(x))\tyz:$(yz(x))")


for op in (:+, :-)
    @eval ($op)(a::MomentTensor, b::MomentTensor) = MomentTensor($op(xx(a),
                                                                     xx(b)),
                                                                 $op(yy(a),
                                                                     yy(b)),
                                                                 $op(zz(a),
                                                                     zz(b)),
                                                                 $op(xy(a),
                                                                     xy(b)),
                                                                 $op(xz(a),
                                                                     xz(b)),
                                                                 $op(yz(a),
                                                                     yz(b)))
end
for op in (:*, :/)
    @eval ($op)(m::MomentTensor, a::Number) = MomentTensor($op(xx(m), a),
                                                           $op(yy(m), a),
                                                           $op(zz(m), a),
                                                           $op(xy(m), a),
                                                           $op(xz(m), a),
                                                           $op(yz(m), a))
end
*(a::Number, m::MomentTensor) =*(m, a)


xyz{T}(m::MomentTensor{T}) =
    [xx(m) xy(m) xz(m)
     yx(m) yy(m) yz(m)
     zx(m) zy(m) zz(m)]
rtf{T}(m::MomentTensor{T}) =
    [rr(m) rt(m) rf(m)
     tr(m) tt(m) tf(m)
     fr(m) ft(m) ff(m)]


function fixup_general_elastic_tensor!{T}(c::Array{T, 4})
    for l in 1:3, k in 1:3, j in 1:3, i in 1:3
        c_ijkl = c[i, j, k, l]
        c[j, i, k, l] = c_ijkl
        c[i, j, l, k] = c_ijkl
        c[k, l, i, j] = c_ijkl
    end
    c
end


function is_valid_general_elastic_tensor{T}(c::Array{T, 4})
    for l in 1:3, k in 1:3, j in 1:3, i in 1:3
        c_ijkl = c[i, j, k, l]
        (
         c_ijkl == c[k, l, i, j] &&
         c_ijkl == c[i, j, l, k] &&
         c_ijkl == c[l, k, i, j] &&
         c_ijkl == c[j, i, k, l] &&
         c_ijkl == c[k, l, j, i] &&
         c_ijkl == c[j, i, l, k] &&
         c_ijkl == c[l, k, j, i]
        ) || return false
    end
    true
end

end
