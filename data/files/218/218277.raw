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

# Dataset tests

println("Running dataset tests...")
@test SolveBio.Dataset.list()["total"] > 200
ds = SolveBio.Dataset.get("ClinVar/ClinVar")
@test ds["created_at"] == "2015-07-16T23:07:02Z"
@test ds["depository"] == "ClinVar"
@test ds["name"] == "ClinVar"
@test ds["documents_count"] > 1e5
ds = SolveBio.Dataset.search("ClinVar/ClinVar")
@test ds["total"] > 1e5
@test ds["genome_build"] == "GRCh37"
println("Successfully ran all dataset tests")
