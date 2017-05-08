

function test_scalarpullsink(facade)
	loadDataflow(facade, joinpath(Pkg.dir("ubitrack"), "test", "test_scalar_sinks.dfg"))
	sink = getPullSinkScalarDouble(facade, "pattern_1")
	
	startDataflow(facade)
	ts = now()
	value = pull_value(sink, ts)
	println("Received: ", value, " for ts: ", ts)

	stopDataflow(facade)
	clearDataflow(facade)
end