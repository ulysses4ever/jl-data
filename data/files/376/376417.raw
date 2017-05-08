module ReferenceMicrocalFiles

function getljhpaths()
	datadir = normpath(joinpath( dirname(@__FILE__), "../ljh"))
	fnames = filter(p->endswith(p,".ljh"), readdir(datadir))
	[joinpath(datadir, fname) for fname in fnames]
end

# package code goes here

end # module
