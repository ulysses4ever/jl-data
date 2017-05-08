module EMLUserColumn
	using DanaTypes
	using DotPlusInheritance
	require("EMSOModelLibrary/JuliaEMSOModels/UserModels/UserTray.jl")
	using EMLUserTray
	using EMLstreams
	using EMLtypes
	require("EMSOModelLibrary/JuliaEMSOModels/stage_separators/reboiler.jl")
	using EMLreboiler
	using EMLtank
	require("EMSOModelLibrary/JuliaEMSOModels/stage_separators/condenser.jl")
	using EMLcondenser
	require("EMSOModelLibrary/JuliaEMSOModels/mixers_splitters/splitter.jl")
	using EMLsplitter
	require("EMSOModelLibrary/JuliaEMSOModels/stage_separators/tank.jl")
	using EMLtank
	require("EMSOModelLibrary/JuliaEMSOModels/pressure_changers/pump.jl")
	using EMLpump
	include("UserColumn/User_Section_ColumnBasic.jl")
	include("UserColumn/User_Section_Column.jl")
	include("UserColumn/User_Distillation_kettle_cond.jl")
	include("UserColumn/User_Distillation_thermosyphon_subcooling.jl")
	include("UserColumn/User_Distillation_thermosyphon_cond.jl")
end