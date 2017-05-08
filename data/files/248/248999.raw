using FormulationLattice
using Base.Test

let
    @Literals(A, B, C, D)
    cl = A ∨ ((B ∨ C) ∧ D)
    formtrack = FormulaState[]
    cl2 = dnf(cl, formtrack)
    @test cl2 == A ∨ (B ∧ D) ∨ (C ∧ D)
end

let
    @Literals(A, B, C, D)
    cl = (A ∨ B) ∧ (C ∨ D)
    formtrack = FormulaState[]
    cl2 = dnf(cl, formtrack)
    @test cl2 == (A ∧ C) ∨ (A ∧ D) ∨ (B ∧ C) ∨ (B ∧ D)
end

let
    @Literals(A, B, C, D)
    cl = (A ∨ B) ∧ C ∧ D
    formtrack = FormulaState[]
    cl2 = dnf(cl, formtrack)
    @test cl2 == (A ∧ C ∧ D) ∨ (B ∧ C ∧ D)
end

let
    @Literals(A, B, C, D, E, F)
    cl = (A ∨ B) ∧ (C ∨ D) ∧ (E ∨ F)
    formtrack = FormulaState[]
    cl2 = dnf(cl, formtrack)
    @test cl2 == (A ∧ C ∧ E) ∨ (A ∧ C ∧ F) ∨ (A ∧ D ∧ E) ∨ (A ∧ D ∧ F) ∨
                 (B ∧ C ∧ E) ∨ (B ∧ C ∧ F) ∨ (B ∧ D ∧ E) ∨ (B ∧ D ∧ F)
end

let
    @Literals(A12, A13)
    @Literals(B12, B13)
    @Literals(C12, C13)
    cl = (A12 ∨ B12 ∨ C12) ∧ (A13 ∨ B13 ∨ C13)
    formtrack = FormulaState[]
    cl2 = dnf(cl, formtrack)
    @test cl2 == (A12 ∧ A13) ∨ (A12 ∧ B13) ∨ (A12 ∧ C13) ∨
                 (B12 ∧ A13) ∨ (B12 ∧ B13) ∨ (B12 ∧ C13) ∨
                 (C12 ∧ A13) ∨ (C12 ∧ B13) ∨ (C12 ∧ C13)
end

let
    @Literals(A12, A13, A23)
    @Literals(B12, B13, B23)
    @Literals(C12, C13, C23)
    cl = (A12 ∨ B12 ∨ C12) ∧ (A13 ∨ B13 ∨ C13) ∧ (A23 ∨ B23 ∨ C23)
    @Literals(A12, A13)
    @Literals(B12, B13)
    @Literals(C12, C13)
    cl = (A12 ∨ B12 ∨ C12) ∧ (A13 ∨ B13 ∨ C13)
    formtrack = FormulaState[]
    cl2 = dnf(cl, formtrack)
    @test cl2 == (A12 ∧ A13 ∧ A23) ∨ (A12 ∧ A13 ∧ B23) ∨ (A12 ∧ A13 ∧ C23) ∨ (A12 ∧ B13 ∧ A23) ∨ (A12 ∧ B13 ∧ B23) ∨ (A12 ∧ B13 ∧ C23) ∨ (A12 ∧ C13 ∧ A23) ∨ (A12 ∧ C13 ∧ B23) ∨ (A12 ∧ C13 ∧ C23) ∨
                 (B12 ∧ A13 ∧ A23) ∨ (B12 ∧ A13 ∧ B23) ∨ (B12 ∧ A13 ∧ C23) ∨ (B12 ∧ B13 ∧ A23) ∨ (B12 ∧ B13 ∧ B23) ∨ (B12 ∧ B13 ∧ C23) ∨ (B12 ∧ C13 ∧ A23) ∨ (B12 ∧ C13 ∧ B23) ∨ (B12 ∧ C13 ∧ C23) ∨
                 (C12 ∧ A13 ∧ A23) ∨ (C12 ∧ A13 ∧ B23) ∨ (C12 ∧ A13 ∧ C23) ∨ (C12 ∧ B13 ∧ A23) ∨ (C12 ∧ B13 ∧ B23) ∨ (C12 ∧ B13 ∧ C23) ∨ (C12 ∧ C13 ∧ A23) ∨ (C12 ∧ C13 ∧ B23) ∨ (C12 ∧ C13 ∧ C23)
end

let
    @Literals(A12, A13, A14, A23, A24, A34)
    @Literals(B12, B13, B14, B23, B24, B34)
    @Literals(C12, C13, C14, C23, C24, C34)
    @Literals(D12, D13, D14, D23, D24, D34)
    cl = (A12 ∨ B12 ∨ C12 ∨ D12) ∧ (A13 ∨ B13 ∨ C13 ∨ D13) ∧
         (A14 ∨ B14 ∨ C14 ∨ D14) ∧ (A23 ∨ B23 ∨ C23 ∨ D23) ∧
         (A24 ∨ B24 ∨ C24 ∨ D24) ∧ (A34 ∨ B34 ∨ C34 ∨ D34)
    formtrack = FormulaState[]
    cl2 = dnf(cl, formtrack)
    @test length(cl2.clauses) == 4096
    @test all(cl2.clauses) do x
        length(x.clauses) == 6 &&
        isa(x,And) &&
        all(y -> isa(y,Literal), x.clauses)
    end
end
