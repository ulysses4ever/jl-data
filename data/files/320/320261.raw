module ReferenceMicrocalFiles

const ljhdir = normpath(joinpath( dirname(@__FILE__), "../ljh"))

type ReferenceMicrocalFile
	filename::AbstractString
	noise_filename::AbstractString
	line_energies_ev::Vector{Float64}
end
const dict = Dict()
function add_ref_file(key, fname, noisename, line_energies_ev)
	fname_full = joinpath(ljhdir, fname)
	noisename_full = joinpath(ljhdir, noisename)
	noisename_full  = isfile(noisename) ? noisename_full : ""
	dict[key] = ReferenceMicrocalFile(fname_full, noisename_full, line_energies_ev)
end
add_ref_file("tupac_calibronium", "20140516_tupac_calibronium_4_row_4hz_chan1.ljh", "", [4952.22, 5898.801, 6490.59, 6404.01, 6930.378, 7649.45, 8047.823, 7058.18, 5426.962, 8905.41, 4090.74, 7478.252])
add_ref_file("tupac_fe_emission", "20150730_50mM_irontris_100ps_xes_chan1.ljh", "20150730_50mM_irontris_100ps_xes_noise_chan1.ljh", [6404.1, 7058.18] )

# package code goes here

end # module
