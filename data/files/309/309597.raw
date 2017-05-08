immutable MassCG
    mass::Float64
    cg::Vector3{Float64}
end
MassCG() = MassCG(0.0,Vector3(0.0,0.0,0.0))

function +(a::MassCG,b::MassCG)
    mass = a.mass + b.mass
    cg = (a.mass*a.cg + b.mass*b.cg)/(a.mass+b.mass)
    MassCG(mass,cg)
end
