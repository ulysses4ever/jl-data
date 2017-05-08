module EMLUserColumn
	using DanaTypes
	using DotPlusInheritance
	using Reexport
	@reexport using ...UserModels.EMLUserTray
	import EMLtypes.length
	@reexport using ...stage_separators.EMLreboiler
	import EMLtypes.length
	@reexport using ...stage_separators.EMLcondenser
	import EMLtypes.length
	@reexport using ...mixers_splitters.EMLsplitter
	import EMLtypes.length
	@reexport using ...stage_separators.EMLtank
	import EMLtypes.length
	@reexport using ...pressure_changers.EMLpump
	import EMLtypes.length
	include("UserColumn/User_Section_ColumnBasic.jl")
	include("UserColumn/User_Section_Column.jl")
	include("UserColumn/User_Distillation_kettle_cond.jl")
	include("UserColumn/User_Distillation_thermosyphon_subcooling.jl")
	include("UserColumn/User_Distillation_thermosyphon_cond.jl")
end