using ReferenceMicrocalFiles
using Base.Test

# write your own tests here
@test 1 == 1
for (k,v) in ReferenceMicrocalFiles.dict
  @test isfile(v.filename)
  @test isfile(v.noise_filename) || v.noise_filename == ""
  @test !isempty(v.note)
  @test !isempty(v.line_energies_ev)
end
