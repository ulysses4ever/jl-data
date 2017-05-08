
# binchromosome.jl
options = [
	"--binWidth", "1000",
	"--nbins", "173",
	"--blacklist", "data/wgEncodeDacMapabilityConsensusExcludable.bed",
	"--dataRoot", "data/track_data",
	"--trackIds", "data/trackIds.json",
	"--nprocs", 2
]
run(`julia ../scripts/binchromosome.jl chr10 $options` |> "data/tmp_binchromosome.out")

# binchromosome.jl
options = [
	"--binWidth", "1000",
	"--nbins", "173",
	"--blacklist", "data/wgEncodeDacMapabilityConsensusExcludable.bed",
	"--dataRoot", "data/track_data",
	"--trackIds", "data/trackIds.json",
	"--nprocs", 2,
	"--sum",
	"-v"
]
run(`julia ../scripts/binchromosome.jl chr10 $options` |> "data/tmp_binchromosome.out")