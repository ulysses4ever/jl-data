
##
# types.jl
# Alle types die door de berekeningen gebruikt worden
##

##
# DiscMethode
#  - L2
#  - L2C
# Properties:
#  - toString
##
abstract DiscMethode


##
# BWP
#  - EvwVgl
#  - AdvecDiff
#  - Fisher
# Properties:
#  - toString
#  - analyticSol (true als er een exacte oplossing bestaat, anders false)
#  - parameters (b, chi, gamma)
##
abstract BWP # BeginWaardeProbleem

##
# ResultSet
##
type ResultSet
	followUpDiff	::Array{Float64}
	exactError		::Array{Float64}
	maxVals			::Array{Float64}
	plotSamples		::Array{Float64,2}
	meshSamples		::Array{Float64,2}

	trackMiddle		::Bool
	xsMiddle		::Array{Float64}

	dx				::Float64
	dt				::Float64
	T				::Float64
	Nx_mesh			::Integer
	Nt_mesh			::Integer
	
	a				::Float64
	BWP				::BWP
	disc			::DiscMethode
	
end

include("disc.jl")
include("disc_L2.jl")
include("disc_L2C.jl")
include("disc_GL.jl")
include("BWP_evwVgl.jl")
include("BWP_advecDiff.jl")
include("BWP_fisher.jl")
include("BWP_heatPi.jl")
include("BWP_grayScott.jl")

types = {
	"ResultSet" => ResultSet,
	"AdvecDiff" => AdvecDiff,
	"EvwVgl"	=> EvwVgl,
	"Fisher"	=> Fisher,
	"L2"		=> L2,
	"L2C"		=> L2C,
	"GL"		=> GL
}

convert(::Type{ResultSet}, d::Dict{String,Any}) = 
	ResultSet(
		d["followUpDiff"],
		d["exactError"],
		d["maxVals"],
		[d["plotSamples"][i][j] for j in 1:length(d["plotSamples"][1]), i in 1:length(d["plotSamples"]) ],
		[d["meshSamples"][i][j] for j in 1:length(d["meshSamples"][1]), i in 1:length(d["meshSamples"]) ],
		get(d, "trackMiddle", false),
		get(d, "xsMiddle", [0.0]),
		d["dx"],
		d["dt"],
		d["T"],
		d["Nx_mesh"],
		d["Nt_mesh"],
		d["a"],
		convert(types[d["BWP"]["toString"]], d["BWP"]),
		convert(types[d["disc"]["toString"]], d["disc"])
	)
