using PDB
using FactCheck

const testdir = dirname(@__FILE__)

facts("148l") do
    open(joinpath(testdir, "pdb", "148l.pdb")) do f
        ent = parse_entry(f)
        @fact name(ent) => "148L"
        @fact length(models(ent)) => 1
        atoms = collect(eachatom(first(models(ent))))
        @fact atoms[1].serial => 1
        @fact atoms[2].serial => 2
    end
end

facts("7ahl") do
    open(joinpath(testdir, "pdb", "7ahl.pdb")) do f
        ent = parse_entry(f)
        @fact name(ent) => "7AHL"
        @fact length(models(ent)) => 1
        atoms = collect(eachatom(first(models(ent))))
        @fact atoms[1].serial => 1
        @fact atoms[2].serial => 2
    end
end
