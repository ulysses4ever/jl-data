using SolveBio
using Base.Test

@test SolveBio.login()["is_active"]

# Depository tests

println("Running depository tests...")
@test SolveBio.Depository.list()["total"] > 240
@test SolveBio.Depository.get("ClinVar")["id"] == 223
@test SolveBio.Depository.get(223)["name"] == "ClinVar"
@test SolveBio.Depository.versions("ClinVar")["total"] > 24
println("Successfully ran all depository tests")
