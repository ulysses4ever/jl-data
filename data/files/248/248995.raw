using FormulationLattice
using Base.Test

let
    @Literals(A, B, C, D)
    cl = A ∨ ((B ∨ C) ∧ D)
    cl2 = dnf(cl)
    @test cl2 == A ∨ (B ∧ D) ∨ (C ∧ D)
end

let
    @Literals(A, B, C, D)
    cl = (A ∨ B) ∧ (C ∨ D)
    cl2 = dnf(cl)
    @test cl2 == (A ∧ C) ∨ (A ∧ D) ∨ (B ∧ C) ∨ (B ∧ D)
end

let
    @Literals(A, B, C, D)
    cl = (A ∨ B) ∧ C ∧ D
    cl2 = dnf(cl)
    @test cl2 == (A ∧ C ∧ D) ∨ (B ∧ C ∧ D)
end

let
    @Literals(A, B, C, D, E, F)
    cl = (A ∨ B) ∧ (C ∨ D) ∧ (E ∨ F)
    cl2 = dnf(cl)
    @test cl2 == (A ∧ C ∧ E) ∨ (A ∧ C ∧ F) ∨ (A ∧ D ∧ E) ∨ (A ∧ D ∧ F) ∨
                 (B ∧ C ∧ E) ∨ (B ∧ C ∧ F) ∨ (B ∧ D ∧ E) ∨ (B ∧ D ∧ F)
end
