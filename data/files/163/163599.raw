CAT_early_m = readdlm("Early/mean/CAT_early_m")[1]
CAT_mid_m = readdlm("Mid/mean/CAT_mid_m")[1]
CAT_late_m = readdlm("Late/mean/CAT_late_m")[1]

fluxes = [
"glc_g6p",
"g6p_f6p",
"f6p_fdp",
"fdp_g3p",
"g3p_dpg",
"dpg_threepg",
"threepg_twopg",
"twopg_pep",
"pep_pyr",
"pyr_accoa",
"pep_oaa",
"oaa_pep",
"mal_pyr",
"oaa_cit",
"cit_icit",
"icit_akg",
"akg_succoa",
"succoa_succ",
"succ_fum",
"fum_mal",
"mal_oaa",
"icit_succ",
"accoa_mal",
"g6p_sixpgl",
"sixpgl_sixpgc",
"sixpgc_ru5p",
"ru5p_xu5p",
"ru5p_r5p",
"xu5p_s7p",
"s7p_e4p",
"xu5p_g3p",
"sixpgc_twoddg6p",
"twoddg6p_g3p",
"nadph_nadh",
"nadh_nadph"]

for flux in fluxes
    println("Flux: $flux")
    early_mean = readdlm("Early/mean/"*flux*"_early_m")[1]
    early_std = readdlm("Early/std/"*flux*"_early_s")[1]
    mid_mean = readdlm("Mid/mean/"*flux*"_mid_m")[1]
    mid_std = readdlm("Mid/std/"*flux*"_mid_s")[1]
    late_mean = readdlm("Late/mean/"*flux*"_late_m")[1]
    late_std = readdlm("Late/std/"*flux*"_late_s")[1]
    # Normalize to CAT flux
    early_mean /= CAT_early_m
    early_std /= CAT_early_m
    mid_mean /= CAT_mid_m
    mid_std /= CAT_mid_m
    late_mean /= CAT_late_m
    late_std /= CAT_late_m
    # Compute standard error
    early_std /= sqrt(18000)
    mid_std /= sqrt(18000)
    late_std /= sqrt(18000)
    println("$early_mean +/- $early_std")
    println("$mid_mean +/- $mid_std")
    println("$late_mean +/- $late_std")
    println()
end

