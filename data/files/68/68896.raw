module Eq


type Error <: Exception
    msg::String
end
error(s::String) = throw(Error(s))
error(s...) = error(string(s...))
Base.showerror(io::IO, e::Error) = print(io, e.msg)


immutable MomentTensor
    xx::Number
    yy::Number
    zz::Number
    xy::Number
    xz::Number
    yz::Number
end
MomentTensor() = MomentTensor(0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
for el in (:xx, :yy, :zz, :xy, :xz, :yz)
    @eval $el(m::MomentTensor) = m.$el
end
Base.show(io::IO, x::MomentTensor) = Base.print(io, "xx:$(xx(x))\tyy:$(yy(x))\tzz:$(zz(x))\txy:$(xy(x))\txz:$(xz(x))\tyz:$(yz(x))")

for op in (:+, :-)
    @eval begin
        ($op)(a::MomentTensor, b::MomentTensor) = MomentTensor($op(xx(a),
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
end
for op in (:*, :/)
    @eval begin
        ($op)(m::MomentTensor, a::Number) = MomentTensor($op(xx(m), a),
                                                         $op(yy(m), a),
                                                         $op(zz(m), a),
                                                         $op(xy(m), a),
                                                         $op(xz(m), a),
                                                         $op(yz(m), a))
    end
end
*(a::Number, m::MomentTensor) =*(m, a)

xyz(m::MomentTensor) = [xx(m) xy(m) xz(m)
                        xy(m) yy(m) yz(m)
                        xz(m) yz(m) zz(m)]

end
