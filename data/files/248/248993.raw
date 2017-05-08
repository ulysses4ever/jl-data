using FormulationLattice
using Base.Test

let
    A,B,C,D = Literal(), Literal(), Literal(), Literal()
    cl = A ∨ ((B ∨ C) ∧ D)
    cl2 = dnf(cl)
    @test cl2 == A ∨ (B ∧ D) ∨ (C ∧ D)
end
