module ReferenceMicrocalFiles

const ljhdir = normpath(joinpath( dirname(@__FILE__), "../ljh"))

type ReferenceMicrocalFile
	filename::AbstractString
	noise_filename::AbstractString
	line_energies_ev::Vector{Float64}
	note::ASCIIString
end
const dict = Dict()
function add_ref_file(key, fname, noisename, line_energies_ev, note)
	fname_full = joinpath(ljhdir, fname)
	noisename_full = joinpath(ljhdir, noisename)
	noisename_full  = isfile(noisename_full) ? noisename_full : ""
	dict[key] = ReferenceMicrocalFile(fname_full, noisename_full, line_energies_ev, note)
end
add_ref_file("tupac_calibronium", "20140516_tupac_calibronium_4_row_4hz_chan1.ljh", "", [4952.22, 5898.801, 6490.59, 6404.01, 6930.378, 7649.45, 8047.823, 7058.18, 5426.962, 8905.41, 4090.74, 7478.252],
"calibronium in microxsi meausrement in tupac, roughly 5 eV FWHM")
add_ref_file("tupac_fe_emission", "20150730_50mM_irontris_100ps_xes_chan1.ljh", "20150730_50mM_irontris_100ps_xes_noise_chan1.ljh", [6404.1, 7058.18],
"fe emission measurement from iron-tris-bypyridine excited by water-jet-laser-source in tupac, roughly 5 eV FWHM, large background, few counts")
add_ref_file("good_mnka_mystery", "20150707_D_chan13.ljh", "20150707_C_chan13.noi", [5898.801, 6490.59],
"mn emission measurement with xsi in mystery(?), measured by Kelsey, 2.5 eV predicted, 2.44 eV achieved")

end # module
