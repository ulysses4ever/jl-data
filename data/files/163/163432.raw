Flux_early = readdlm("Flux_early")
Flux_mid = readdlm("Flux_mid")
Flux_late = readdlm("Flux_late")

#----------------------------------------------------------------------------------------
# Glycolysis
glc_g6p_early = Flux_early[1,:]+Flux_early[2,:]+Flux_early[3,:]+Flux_early[4,:]+Flux_early[5,:]
g6p_f6p_early = Flux_early[6,:]-Flux_early[7,:]
f6p_fdp_early = Flux_early[8,:]
fdp_g3p_early = Flux_early[10,:]-Flux_early[11,:]
g3p_dpg_early = Flux_early[14,:]-Flux_early[15,:]
dpg_threepg_early = Flux_early[16,:]-Flux_early[17,:]
threepg_twopg_early = Flux_early[18,:]-Flux_early[19,:]
twopg_pep_early = Flux_early[20,:]-Flux_early[21,:]
pep_pyr_early = Flux_early[22,:]

# TCA cycle
pyr_accoa_early = Flux_early[25,:]
pep_oaa_early = Flux_early[24,:]
oaa_pep_early = Flux_early[23,:]
mal_pyr_early = Flux_early[59,:]+Flux_early[60,:]
oaa_cit_early = Flux_early[43,:]
cit_icit_early = Flux_early[44,:]-Flux_early[45,:]
icit_akg_early = Flux_early[46,:]-Flux_early[47,:]
akg_succoa_early = Flux_early[48,:]
succoa_succ_early = Flux_early[50,:]-Flux_early[49,:]
succ_fum_early = Flux_early[51,:]
fum_mal_early = Flux_early[53,:]-Flux_early[54,:]
mal_oaa_early = Flux_early[55,:]-Flux_early[56,:]

# Isocitrate lyase
icit_succ_early = Flux_early[57,:]
accoa_mal_early = Flux_early[58,:]

# Pentose phosphate
g6p_sixpgl_early = Flux_early[27,:]-Flux_early[28,:]
sixpgl_sixpgc_early = Flux_early[29,:]
sixpgc_ru5p_early = Flux_early[30,:]
ru5p_xu5p_early = Flux_early[31,:]-Flux_early[32,:]
ru5p_r5p_early = Flux_early[34,:]-Flux_early[33,:]
xu5p_s7p_early = Flux_early[37,:]-Flux_early[38,:]
s7p_e4p_early = Flux_early[35,:]-Flux_early[36,:]
xu5p_g3p_early = Flux_early[39,:]-Flux_early[40,:]

# Entner-Doudoroff
sixpgc_twoddg6p_early = Flux_early[41,:]
twoddg6p_g3p_early = Flux_early[42,:]

# NADPH/NADH transfer
nadph_nadh_early = Flux_early[75,:]
nadh_nadph_early = Flux_early[76,:]

glc_g6p_early_m = mean(glc_g6p_early)
g6p_f6p_early_m = mean(g6p_f6p_early)
f6p_fdp_early_m = mean(f6p_fdp_early)
fdp_g3p_early_m = mean(fdp_g3p_early)
g3p_dpg_early_m = mean(g3p_dpg_early)
dpg_threepg_early_m = mean(dpg_threepg_early)
threepg_twopg_early_m = mean(threepg_twopg_early)
twopg_pep_early_m = mean(twopg_pep_early)
pep_pyr_early_m = mean(pep_pyr_early)
pyr_accoa_early_m = mean(pyr_accoa_early)
pep_oaa_early_m = mean(pep_oaa_early)
oaa_pep_early_m = mean(oaa_pep_early)
mal_pyr_early_m = mean(mal_pyr_early)
oaa_cit_early_m = mean(oaa_cit_early)
cit_icit_early_m = mean(cit_icit_early)
icit_akg_early_m = mean(icit_akg_early)
akg_succoa_early_m = mean(akg_succoa_early)
succoa_succ_early_m = mean(succoa_succ_early)
succ_fum_early_m = mean(succ_fum_early)
fum_mal_early_m = mean(fum_mal_early)
mal_oaa_early_m = mean(mal_oaa_early)
icit_succ_early_m = mean(icit_succ_early)
accoa_mal_early_m = mean(accoa_mal_early)
g6p_sixpgl_early_m = mean(g6p_sixpgl_early)
sixpgl_sixpgc_early_m = mean(sixpgl_sixpgc_early)
sixpgc_ru5p_early_m = mean(sixpgc_ru5p_early)
ru5p_xu5p_early_m = mean(ru5p_xu5p_early)
ru5p_r5p_early_m = mean(ru5p_r5p_early)
xu5p_s7p_early_m = mean(xu5p_s7p_early)
s7p_e4p_early_m = mean(s7p_e4p_early)
xu5p_g3p_early_m = mean(xu5p_g3p_early)
sixpgc_twoddg6p_early_m = mean(sixpgc_twoddg6p_early)
twoddg6p_g3p_early_m = mean(twoddg6p_g3p_early)
nadph_nadh_early_m = mean(nadph_nadh_early)
nadh_nadph_early_m = mean(nadh_nadph_early)

glc_g6p_early_s = std(glc_g6p_early)
g6p_f6p_early_s = std(g6p_f6p_early)
f6p_fdp_early_s = std(f6p_fdp_early)
fdp_g3p_early_s = std(fdp_g3p_early)
g3p_dpg_early_s = std(g3p_dpg_early)
dpg_threepg_early_s = std(dpg_threepg_early)
threepg_twopg_early_s = std(threepg_twopg_early)
twopg_pep_early_s = std(twopg_pep_early)
pep_pyr_early_s = std(pep_pyr_early)
pyr_accoa_early_s = std(pyr_accoa_early)
pep_oaa_early_s = std(pep_oaa_early)
oaa_pep_early_s = std(oaa_pep_early)
mal_pyr_early_s = std(mal_pyr_early)
oaa_cit_early_s = std(oaa_cit_early)
cit_icit_early_s = std(cit_icit_early)
icit_akg_early_s = std(icit_akg_early)
akg_succoa_early_s = std(akg_succoa_early)
succoa_succ_early_s = std(succoa_succ_early)
succ_fum_early_s = std(succ_fum_early)
fum_mal_early_s = std(fum_mal_early)
mal_oaa_early_s = std(mal_oaa_early)
icit_succ_early_s = std(icit_succ_early)
accoa_mal_early_s = std(accoa_mal_early)
g6p_sixpgl_early_s = std(g6p_sixpgl_early)
sixpgl_sixpgc_early_s = std(sixpgl_sixpgc_early)
sixpgc_ru5p_early_s = std(sixpgc_ru5p_early)
ru5p_xu5p_early_s = std(ru5p_xu5p_early)
ru5p_r5p_early_s = std(ru5p_r5p_early)
xu5p_s7p_early_s = std(xu5p_s7p_early)
s7p_e4p_early_s = std(s7p_e4p_early)
xu5p_g3p_early_s = std(xu5p_g3p_early)
sixpgc_twoddg6p_early_s = std(sixpgc_twoddg6p_early)
twoddg6p_g3p_early_s = std(twoddg6p_g3p_early)
nadph_nadh_early_s = std(nadph_nadh_early)
nadh_nadph_early_s = std(nadh_nadph_early)

writedlm("Early/mean/glc_g6p_early_m",glc_g6p_early_m)
writedlm("Early/mean/g6p_f6p_early_m",g6p_f6p_early_m)
writedlm("Early/mean/f6p_fdp_early_m",f6p_fdp_early_m)
writedlm("Early/mean/fdp_g3p_early_m",fdp_g3p_early_m)
writedlm("Early/mean/g3p_dpg_early_m",g3p_dpg_early_m)
writedlm("Early/mean/dpg_threepg_early_m",dpg_threepg_early_m)
writedlm("Early/mean/threepg_twopg_early_m",threepg_twopg_early_m)
writedlm("Early/mean/twopg_pep_early_m",twopg_pep_early_m)
writedlm("Early/mean/pep_pyr_early_m",pep_pyr_early_m)
writedlm("Early/mean/pyr_accoa_early_m",pyr_accoa_early_m)
writedlm("Early/mean/pep_oaa_early_m",pep_oaa_early_m)
writedlm("Early/mean/oaa_pep_early_m",oaa_pep_early_m)
writedlm("Early/mean/mal_pyr_early_m",mal_pyr_early_m)
writedlm("Early/mean/oaa_cit_early_m",oaa_cit_early_m)
writedlm("Early/mean/cit_icit_early_m",cit_icit_early_m)
writedlm("Early/mean/icit_akg_early_m",icit_akg_early_m)
writedlm("Early/mean/akg_succoa_early_m",akg_succoa_early_m)
writedlm("Early/mean/succoa_succ_early_m",succoa_succ_early_m)
writedlm("Early/mean/succ_fum_early_m",succ_fum_early_m)
writedlm("Early/mean/fum_mal_early_m",fum_mal_early_m)
writedlm("Early/mean/mal_oaa_early_m",mal_oaa_early_m)
writedlm("Early/mean/icit_succ_early_m",icit_succ_early_m)
writedlm("Early/mean/accoa_mal_early_m",accoa_mal_early_m)
writedlm("Early/mean/g6p_sixpgl_early_m",g6p_sixpgl_early_m)
writedlm("Early/mean/sixpgl_sixpgc_early_m",sixpgl_sixpgc_early_m)
writedlm("Early/mean/sixpgc_ru5p_early_m",sixpgc_ru5p_early_m)
writedlm("Early/mean/ru5p_xu5p_early_m",ru5p_xu5p_early_m)
writedlm("Early/mean/ru5p_r5p_early_m",ru5p_r5p_early_m)
writedlm("Early/mean/xu5p_s7p_early_m",xu5p_s7p_early_m)
writedlm("Early/mean/s7p_e4p_early_m",s7p_e4p_early_m)
writedlm("Early/mean/xu5p_g3p_early_m",xu5p_g3p_early_m)
writedlm("Early/mean/sixpgc_twoddg6p_early_m",sixpgc_twoddg6p_early_m)
writedlm("Early/mean/twoddg6p_g3p_early_m",twoddg6p_g3p_early_m)
writedlm("Early/mean/nadph_nadh_early_m",nadph_nadh_early_m)
writedlm("Early/mean/nadh_nadph_early_m",nadh_nadph_early_m)

writedlm("Early/std/glc_g6p_early_s",glc_g6p_early_s)
writedlm("Early/std/g6p_f6p_early_s",g6p_f6p_early_s)
writedlm("Early/std/f6p_fdp_early_s",f6p_fdp_early_s)
writedlm("Early/std/fdp_g3p_early_s",fdp_g3p_early_s)
writedlm("Early/std/g3p_dpg_early_s",g3p_dpg_early_s)
writedlm("Early/std/dpg_threepg_early_s",dpg_threepg_early_s)
writedlm("Early/std/threepg_twopg_early_s",threepg_twopg_early_s)
writedlm("Early/std/twopg_pep_early_s",twopg_pep_early_s)
writedlm("Early/std/pep_pyr_early_s",pep_pyr_early_s)
writedlm("Early/std/pyr_accoa_early_s",pyr_accoa_early_s)
writedlm("Early/std/pep_oaa_early_s",pep_oaa_early_s)
writedlm("Early/std/oaa_pep_early_s",oaa_pep_early_s)
writedlm("Early/std/mal_pyr_early_s",mal_pyr_early_s)
writedlm("Early/std/oaa_cit_early_s",oaa_cit_early_s)
writedlm("Early/std/cit_icit_early_s",cit_icit_early_s)
writedlm("Early/std/icit_akg_early_s",icit_akg_early_s)
writedlm("Early/std/akg_succoa_early_s",akg_succoa_early_s)
writedlm("Early/std/succoa_succ_early_s",succoa_succ_early_s)
writedlm("Early/std/succ_fum_early_s",succ_fum_early_s)
writedlm("Early/std/fum_mal_early_s",fum_mal_early_s)
writedlm("Early/std/mal_oaa_early_s",mal_oaa_early_s)
writedlm("Early/std/icit_succ_early_s",icit_succ_early_s)
writedlm("Early/std/accoa_mal_early_s",accoa_mal_early_s)
writedlm("Early/std/g6p_sixpgl_early_s",g6p_sixpgl_early_s)
writedlm("Early/std/sixpgl_sixpgc_early_s",sixpgl_sixpgc_early_s)
writedlm("Early/std/sixpgc_ru5p_early_s",sixpgc_ru5p_early_s)
writedlm("Early/std/ru5p_xu5p_early_s",ru5p_xu5p_early_s)
writedlm("Early/std/ru5p_r5p_early_s",ru5p_r5p_early_s)
writedlm("Early/std/xu5p_s7p_early_s",xu5p_s7p_early_s)
writedlm("Early/std/s7p_e4p_early_s",s7p_e4p_early_s)
writedlm("Early/std/xu5p_g3p_early_s",xu5p_g3p_early_s)
writedlm("Early/std/sixpgc_twoddg6p_early_s",sixpgc_twoddg6p_early_s)
writedlm("Early/std/twoddg6p_g3p_early_s",twoddg6p_g3p_early_s)
writedlm("Early/std/nadph_nadh_early_s",nadph_nadh_early_s)
writedlm("Early/std/nadh_nadph_early_s",nadh_nadph_early_s)

#----------------------------------------------------------------------------------------
# Glycolysis
glc_g6p_mid = Flux_mid[1,:]+Flux_mid[2,:]+Flux_mid[3,:]+Flux_mid[4,:]+Flux_mid[5,:]
g6p_f6p_mid = Flux_mid[6,:]-Flux_mid[7,:]
f6p_fdp_mid = Flux_mid[8,:]
fdp_g3p_mid = Flux_mid[10,:]-Flux_mid[11,:]
g3p_dpg_mid = Flux_mid[14,:]-Flux_mid[15,:]
dpg_threepg_mid = Flux_mid[16,:]-Flux_mid[17,:]
threepg_twopg_mid = Flux_mid[18,:]-Flux_mid[19,:]
twopg_pep_mid = Flux_mid[20,:]-Flux_mid[21,:]
pep_pyr_mid = Flux_mid[22,:]

# TCA cycle
pyr_accoa_mid = Flux_mid[25,:]
pep_oaa_mid = Flux_mid[24,:]
oaa_pep_mid = Flux_mid[23,:]
mal_pyr_mid = Flux_mid[59,:]+Flux_mid[60,:]
oaa_cit_mid = Flux_mid[43,:]
cit_icit_mid = Flux_mid[44,:]-Flux_mid[45,:]
icit_akg_mid = Flux_mid[46,:]-Flux_mid[47,:]
akg_succoa_mid = Flux_mid[48,:]
succoa_succ_mid = Flux_mid[50,:]-Flux_mid[49,:]
succ_fum_mid = Flux_mid[51,:]
fum_mal_mid = Flux_mid[53,:]-Flux_mid[54,:]
mal_oaa_mid = Flux_mid[55,:]-Flux_mid[56,:]

# Isocitrate lyase
icit_succ_mid = Flux_mid[57,:]
accoa_mal_mid = Flux_mid[58,:]

# Pentose phosphate
g6p_sixpgl_mid = Flux_mid[27,:]-Flux_mid[28,:]
sixpgl_sixpgc_mid = Flux_mid[29,:]
sixpgc_ru5p_mid = Flux_mid[30,:]
ru5p_xu5p_mid = Flux_mid[31,:]-Flux_mid[32,:]
ru5p_r5p_mid = Flux_mid[34,:]-Flux_mid[33,:]
xu5p_s7p_mid = Flux_mid[37,:]-Flux_mid[38,:]
s7p_e4p_mid = Flux_mid[35,:]-Flux_mid[36,:]
xu5p_g3p_mid = Flux_mid[39,:]-Flux_mid[40,:]

# Entner-Doudoroff
sixpgc_twoddg6p_mid = Flux_mid[41,:]
twoddg6p_g3p_mid = Flux_mid[42,:]

# NADPH/NADH transfer
nadph_nadh_mid = Flux_mid[75,:]
nadh_nadph_mid = Flux_mid[76,:]

glc_g6p_mid_m = mean(glc_g6p_mid)
g6p_f6p_mid_m = mean(g6p_f6p_mid)
f6p_fdp_mid_m = mean(f6p_fdp_mid)
fdp_g3p_mid_m = mean(fdp_g3p_mid)
g3p_dpg_mid_m = mean(g3p_dpg_mid)
dpg_threepg_mid_m = mean(dpg_threepg_mid)
threepg_twopg_mid_m = mean(threepg_twopg_mid)
twopg_pep_mid_m = mean(twopg_pep_mid)
pep_pyr_mid_m = mean(pep_pyr_mid)
pyr_accoa_mid_m = mean(pyr_accoa_mid)
pep_oaa_mid_m = mean(pep_oaa_mid)
oaa_pep_mid_m = mean(oaa_pep_mid)
mal_pyr_mid_m = mean(mal_pyr_mid)
oaa_cit_mid_m = mean(oaa_cit_mid)
cit_icit_mid_m = mean(cit_icit_mid)
icit_akg_mid_m = mean(icit_akg_mid)
akg_succoa_mid_m = mean(akg_succoa_mid)
succoa_succ_mid_m = mean(succoa_succ_mid)
succ_fum_mid_m = mean(succ_fum_mid)
fum_mal_mid_m = mean(fum_mal_mid)
mal_oaa_mid_m = mean(mal_oaa_mid)
icit_succ_mid_m = mean(icit_succ_mid)
accoa_mal_mid_m = mean(accoa_mal_mid)
g6p_sixpgl_mid_m = mean(g6p_sixpgl_mid)
sixpgl_sixpgc_mid_m = mean(sixpgl_sixpgc_mid)
sixpgc_ru5p_mid_m = mean(sixpgc_ru5p_mid)
ru5p_xu5p_mid_m = mean(ru5p_xu5p_mid)
ru5p_r5p_mid_m = mean(ru5p_r5p_mid)
xu5p_s7p_mid_m = mean(xu5p_s7p_mid)
s7p_e4p_mid_m = mean(s7p_e4p_mid)
xu5p_g3p_mid_m = mean(xu5p_g3p_mid)
sixpgc_twoddg6p_mid_m = mean(sixpgc_twoddg6p_mid)
twoddg6p_g3p_mid_m = mean(twoddg6p_g3p_mid)
nadph_nadh_mid_m = mean(nadph_nadh_mid)
nadh_nadph_mid_m = mean(nadh_nadph_mid)

glc_g6p_mid_s = std(glc_g6p_mid)
g6p_f6p_mid_s = std(g6p_f6p_mid)
f6p_fdp_mid_s = std(f6p_fdp_mid)
fdp_g3p_mid_s = std(fdp_g3p_mid)
g3p_dpg_mid_s = std(g3p_dpg_mid)
dpg_threepg_mid_s = std(dpg_threepg_mid)
threepg_twopg_mid_s = std(threepg_twopg_mid)
twopg_pep_mid_s = std(twopg_pep_mid)
pep_pyr_mid_s = std(pep_pyr_mid)
pyr_accoa_mid_s = std(pyr_accoa_mid)
pep_oaa_mid_s = std(pep_oaa_mid)
oaa_pep_mid_s = std(oaa_pep_mid)
mal_pyr_mid_s = std(mal_pyr_mid)
oaa_cit_mid_s = std(oaa_cit_mid)
cit_icit_mid_s = std(cit_icit_mid)
icit_akg_mid_s = std(icit_akg_mid)
akg_succoa_mid_s = std(akg_succoa_mid)
succoa_succ_mid_s = std(succoa_succ_mid)
succ_fum_mid_s = std(succ_fum_mid)
fum_mal_mid_s = std(fum_mal_mid)
mal_oaa_mid_s = std(mal_oaa_mid)
icit_succ_mid_s = std(icit_succ_mid)
accoa_mal_mid_s = std(accoa_mal_mid)
g6p_sixpgl_mid_s = std(g6p_sixpgl_mid)
sixpgl_sixpgc_mid_s = std(sixpgl_sixpgc_mid)
sixpgc_ru5p_mid_s = std(sixpgc_ru5p_mid)
ru5p_xu5p_mid_s = std(ru5p_xu5p_mid)
ru5p_r5p_mid_s = std(ru5p_r5p_mid)
xu5p_s7p_mid_s = std(xu5p_s7p_mid)
s7p_e4p_mid_s = std(s7p_e4p_mid)
xu5p_g3p_mid_s = std(xu5p_g3p_mid)
sixpgc_twoddg6p_mid_s = std(sixpgc_twoddg6p_mid)
twoddg6p_g3p_mid_s = std(twoddg6p_g3p_mid)
nadph_nadh_mid_s = std(nadph_nadh_mid)
nadh_nadph_mid_s = std(nadh_nadph_mid)

writedlm("Mid/mean/glc_g6p_mid_m",glc_g6p_mid_m)
writedlm("Mid/mean/g6p_f6p_mid_m",g6p_f6p_mid_m)
writedlm("Mid/mean/f6p_fdp_mid_m",f6p_fdp_mid_m)
writedlm("Mid/mean/fdp_g3p_mid_m",fdp_g3p_mid_m)
writedlm("Mid/mean/g3p_dpg_mid_m",g3p_dpg_mid_m)
writedlm("Mid/mean/dpg_threepg_mid_m",dpg_threepg_mid_m)
writedlm("Mid/mean/threepg_twopg_mid_m",threepg_twopg_mid_m)
writedlm("Mid/mean/twopg_pep_mid_m",twopg_pep_mid_m)
writedlm("Mid/mean/pep_pyr_mid_m",pep_pyr_mid_m)
writedlm("Mid/mean/pyr_accoa_mid_m",pyr_accoa_mid_m)
writedlm("Mid/mean/pep_oaa_mid_m",pep_oaa_mid_m)
writedlm("Mid/mean/oaa_pep_mid_m",oaa_pep_mid_m)
writedlm("Mid/mean/mal_pyr_mid_m",mal_pyr_mid_m)
writedlm("Mid/mean/oaa_cit_mid_m",oaa_cit_mid_m)
writedlm("Mid/mean/cit_icit_mid_m",cit_icit_mid_m)
writedlm("Mid/mean/icit_akg_mid_m",icit_akg_mid_m)
writedlm("Mid/mean/akg_succoa_mid_m",akg_succoa_mid_m)
writedlm("Mid/mean/succoa_succ_mid_m",succoa_succ_mid_m)
writedlm("Mid/mean/succ_fum_mid_m",succ_fum_mid_m)
writedlm("Mid/mean/fum_mal_mid_m",fum_mal_mid_m)
writedlm("Mid/mean/mal_oaa_mid_m",mal_oaa_mid_m)
writedlm("Mid/mean/icit_succ_mid_m",icit_succ_mid_m)
writedlm("Mid/mean/accoa_mal_mid_m",accoa_mal_mid_m)
writedlm("Mid/mean/g6p_sixpgl_mid_m",g6p_sixpgl_mid_m)
writedlm("Mid/mean/sixpgl_sixpgc_mid_m",sixpgl_sixpgc_mid_m)
writedlm("Mid/mean/sixpgc_ru5p_mid_m",sixpgc_ru5p_mid_m)
writedlm("Mid/mean/ru5p_xu5p_mid_m",ru5p_xu5p_mid_m)
writedlm("Mid/mean/ru5p_r5p_mid_m",ru5p_r5p_mid_m)
writedlm("Mid/mean/xu5p_s7p_mid_m",xu5p_s7p_mid_m)
writedlm("Mid/mean/s7p_e4p_mid_m",s7p_e4p_mid_m)
writedlm("Mid/mean/xu5p_g3p_mid_m",xu5p_g3p_mid_m)
writedlm("Mid/mean/sixpgc_twoddg6p_mid_m",sixpgc_twoddg6p_mid_m)
writedlm("Mid/mean/twoddg6p_g3p_mid_m",twoddg6p_g3p_mid_m)
writedlm("Mid/mean/nadph_nadh_mid_m",nadph_nadh_mid_m)
writedlm("Mid/mean/nadh_nadph_mid_m",nadh_nadph_mid_m)

writedlm("Mid/std/glc_g6p_mid_s",glc_g6p_mid_s)
writedlm("Mid/std/g6p_f6p_mid_s",g6p_f6p_mid_s)
writedlm("Mid/std/f6p_fdp_mid_s",f6p_fdp_mid_s)
writedlm("Mid/std/fdp_g3p_mid_s",fdp_g3p_mid_s)
writedlm("Mid/std/g3p_dpg_mid_s",g3p_dpg_mid_s)
writedlm("Mid/std/dpg_threepg_mid_s",dpg_threepg_mid_s)
writedlm("Mid/std/threepg_twopg_mid_s",threepg_twopg_mid_s)
writedlm("Mid/std/twopg_pep_mid_s",twopg_pep_mid_s)
writedlm("Mid/std/pep_pyr_mid_s",pep_pyr_mid_s)
writedlm("Mid/std/pyr_accoa_mid_s",pyr_accoa_mid_s)
writedlm("Mid/std/pep_oaa_mid_s",pep_oaa_mid_s)
writedlm("Mid/std/oaa_pep_mid_s",oaa_pep_mid_s)
writedlm("Mid/std/mal_pyr_mid_s",mal_pyr_mid_s)
writedlm("Mid/std/oaa_cit_mid_s",oaa_cit_mid_s)
writedlm("Mid/std/cit_icit_mid_s",cit_icit_mid_s)
writedlm("Mid/std/icit_akg_mid_s",icit_akg_mid_s)
writedlm("Mid/std/akg_succoa_mid_s",akg_succoa_mid_s)
writedlm("Mid/std/succoa_succ_mid_s",succoa_succ_mid_s)
writedlm("Mid/std/succ_fum_mid_s",succ_fum_mid_s)
writedlm("Mid/std/fum_mal_mid_s",fum_mal_mid_s)
writedlm("Mid/std/mal_oaa_mid_s",mal_oaa_mid_s)
writedlm("Mid/std/icit_succ_mid_s",icit_succ_mid_s)
writedlm("Mid/std/accoa_mal_mid_s",accoa_mal_mid_s)
writedlm("Mid/std/g6p_sixpgl_mid_s",g6p_sixpgl_mid_s)
writedlm("Mid/std/sixpgl_sixpgc_mid_s",sixpgl_sixpgc_mid_s)
writedlm("Mid/std/sixpgc_ru5p_mid_s",sixpgc_ru5p_mid_s)
writedlm("Mid/std/ru5p_xu5p_mid_s",ru5p_xu5p_mid_s)
writedlm("Mid/std/ru5p_r5p_mid_s",ru5p_r5p_mid_s)
writedlm("Mid/std/xu5p_s7p_mid_s",xu5p_s7p_mid_s)
writedlm("Mid/std/s7p_e4p_mid_s",s7p_e4p_mid_s)
writedlm("Mid/std/xu5p_g3p_mid_s",xu5p_g3p_mid_s)
writedlm("Mid/std/sixpgc_twoddg6p_mid_s",sixpgc_twoddg6p_mid_s)
writedlm("Mid/std/twoddg6p_g3p_mid_s",twoddg6p_g3p_mid_s)
writedlm("Mid/std/nadph_nadh_mid_s",nadph_nadh_mid_s)
writedlm("Mid/std/nadh_nadph_mid_s",nadh_nadph_mid_s)


#----------------------------------------------------------------------------------------
# Glycolysis
glc_g6p_late = Flux_late[1,:]+Flux_late[2,:]+Flux_late[3,:]+Flux_late[4,:]+Flux_late[5,:]
g6p_f6p_late = Flux_late[6,:]-Flux_late[7,:]
f6p_fdp_late = Flux_late[8,:]
fdp_g3p_late = Flux_late[10,:]-Flux_late[11,:]
g3p_dpg_late = Flux_late[14,:]-Flux_late[15,:]
dpg_threepg_late = Flux_late[16,:]-Flux_late[17,:]
threepg_twopg_late = Flux_late[18,:]-Flux_late[19,:]
twopg_pep_late = Flux_late[20,:]-Flux_late[21,:]
pep_pyr_late = Flux_late[22,:]

# TCA cycle
pyr_accoa_late = Flux_late[25,:]
pep_oaa_late = Flux_late[24,:]
oaa_pep_late = Flux_late[23,:]
mal_pyr_late = Flux_late[59,:]+Flux_late[60,:]
oaa_cit_late = Flux_late[43,:]
cit_icit_late = Flux_late[44,:]-Flux_late[45,:]
icit_akg_late = Flux_late[46,:]-Flux_late[47,:]
akg_succoa_late = Flux_late[48,:]
succoa_succ_late = Flux_late[50,:]-Flux_late[49,:]
succ_fum_late = Flux_late[51,:]
fum_mal_late = Flux_late[53,:]-Flux_late[54,:]
mal_oaa_late = Flux_late[55,:]-Flux_late[56,:]

# Isocitrate lyase
icit_succ_late = Flux_late[57,:]
accoa_mal_late = Flux_late[58,:]

# Pentose phosphate
g6p_sixpgl_late = Flux_late[27,:]-Flux_late[28,:]
sixpgl_sixpgc_late = Flux_late[29,:]
sixpgc_ru5p_late = Flux_late[30,:]
ru5p_xu5p_late = Flux_late[31,:]-Flux_late[32,:]
ru5p_r5p_late = Flux_late[34,:]-Flux_late[33,:]
xu5p_s7p_late = Flux_late[37,:]-Flux_late[38,:]
s7p_e4p_late = Flux_late[35,:]-Flux_late[36,:]
xu5p_g3p_late = Flux_late[39,:]-Flux_late[40,:]

# Entner-Doudoroff
sixpgc_twoddg6p_late = Flux_late[41,:]
twoddg6p_g3p_late = Flux_late[42,:]

# NADPH/NADH transfer
nadph_nadh_late = Flux_late[75,:]
nadh_nadph_late = Flux_late[76,:]

glc_g6p_late_m = mean(glc_g6p_late)
g6p_f6p_late_m = mean(g6p_f6p_late)
f6p_fdp_late_m = mean(f6p_fdp_late)
fdp_g3p_late_m = mean(fdp_g3p_late)
g3p_dpg_late_m = mean(g3p_dpg_late)
dpg_threepg_late_m = mean(dpg_threepg_late)
threepg_twopg_late_m = mean(threepg_twopg_late)
twopg_pep_late_m = mean(twopg_pep_late)
pep_pyr_late_m = mean(pep_pyr_late)
pyr_accoa_late_m = mean(pyr_accoa_late)
pep_oaa_late_m = mean(pep_oaa_late)
oaa_pep_late_m = mean(oaa_pep_late)
mal_pyr_late_m = mean(mal_pyr_late)
oaa_cit_late_m = mean(oaa_cit_late)
cit_icit_late_m = mean(cit_icit_late)
icit_akg_late_m = mean(icit_akg_late)
akg_succoa_late_m = mean(akg_succoa_late)
succoa_succ_late_m = mean(succoa_succ_late)
succ_fum_late_m = mean(succ_fum_late)
fum_mal_late_m = mean(fum_mal_late)
mal_oaa_late_m = mean(mal_oaa_late)
icit_succ_late_m = mean(icit_succ_late)
accoa_mal_late_m = mean(accoa_mal_late)
g6p_sixpgl_late_m = mean(g6p_sixpgl_late)
sixpgl_sixpgc_late_m = mean(sixpgl_sixpgc_late)
sixpgc_ru5p_late_m = mean(sixpgc_ru5p_late)
ru5p_xu5p_late_m = mean(ru5p_xu5p_late)
ru5p_r5p_late_m = mean(ru5p_r5p_late)
xu5p_s7p_late_m = mean(xu5p_s7p_late)
s7p_e4p_late_m = mean(s7p_e4p_late)
xu5p_g3p_late_m = mean(xu5p_g3p_late)
sixpgc_twoddg6p_late_m = mean(sixpgc_twoddg6p_late)
twoddg6p_g3p_late_m = mean(twoddg6p_g3p_late)
nadph_nadh_late_m = mean(nadph_nadh_late)
nadh_nadph_late_m = mean(nadh_nadph_late)

glc_g6p_late_s = std(glc_g6p_late)
g6p_f6p_late_s = std(g6p_f6p_late)
f6p_fdp_late_s = std(f6p_fdp_late)
fdp_g3p_late_s = std(fdp_g3p_late)
g3p_dpg_late_s = std(g3p_dpg_late)
dpg_threepg_late_s = std(dpg_threepg_late)
threepg_twopg_late_s = std(threepg_twopg_late)
twopg_pep_late_s = std(twopg_pep_late)
pep_pyr_late_s = std(pep_pyr_late)
pyr_accoa_late_s = std(pyr_accoa_late)
pep_oaa_late_s = std(pep_oaa_late)
oaa_pep_late_s = std(oaa_pep_late)
mal_pyr_late_s = std(mal_pyr_late)
oaa_cit_late_s = std(oaa_cit_late)
cit_icit_late_s = std(cit_icit_late)
icit_akg_late_s = std(icit_akg_late)
akg_succoa_late_s = std(akg_succoa_late)
succoa_succ_late_s = std(succoa_succ_late)
succ_fum_late_s = std(succ_fum_late)
fum_mal_late_s = std(fum_mal_late)
mal_oaa_late_s = std(mal_oaa_late)
icit_succ_late_s = std(icit_succ_late)
accoa_mal_late_s = std(accoa_mal_late)
g6p_sixpgl_late_s = std(g6p_sixpgl_late)
sixpgl_sixpgc_late_s = std(sixpgl_sixpgc_late)
sixpgc_ru5p_late_s = std(sixpgc_ru5p_late)
ru5p_xu5p_late_s = std(ru5p_xu5p_late)
ru5p_r5p_late_s = std(ru5p_r5p_late)
xu5p_s7p_late_s = std(xu5p_s7p_late)
s7p_e4p_late_s = std(s7p_e4p_late)
xu5p_g3p_late_s = std(xu5p_g3p_late)
sixpgc_twoddg6p_late_s = std(sixpgc_twoddg6p_late)
twoddg6p_g3p_late_s = std(twoddg6p_g3p_late)
nadph_nadh_late_s = std(nadph_nadh_late)
nadh_nadph_late_s = std(nadh_nadph_late)

writedlm("Late/mean/glc_g6p_late_m",glc_g6p_late_m)
writedlm("Late/mean/g6p_f6p_late_m",g6p_f6p_late_m)
writedlm("Late/mean/f6p_fdp_late_m",f6p_fdp_late_m)
writedlm("Late/mean/fdp_g3p_late_m",fdp_g3p_late_m)
writedlm("Late/mean/g3p_dpg_late_m",g3p_dpg_late_m)
writedlm("Late/mean/dpg_threepg_late_m",dpg_threepg_late_m)
writedlm("Late/mean/threepg_twopg_late_m",threepg_twopg_late_m)
writedlm("Late/mean/twopg_pep_late_m",twopg_pep_late_m)
writedlm("Late/mean/pep_pyr_late_m",pep_pyr_late_m)
writedlm("Late/mean/pyr_accoa_late_m",pyr_accoa_late_m)
writedlm("Late/mean/pep_oaa_late_m",pep_oaa_late_m)
writedlm("Late/mean/oaa_pep_late_m",oaa_pep_late_m)
writedlm("Late/mean/mal_pyr_late_m",mal_pyr_late_m)
writedlm("Late/mean/oaa_cit_late_m",oaa_cit_late_m)
writedlm("Late/mean/cit_icit_late_m",cit_icit_late_m)
writedlm("Late/mean/icit_akg_late_m",icit_akg_late_m)
writedlm("Late/mean/akg_succoa_late_m",akg_succoa_late_m)
writedlm("Late/mean/succoa_succ_late_m",succoa_succ_late_m)
writedlm("Late/mean/succ_fum_late_m",succ_fum_late_m)
writedlm("Late/mean/fum_mal_late_m",fum_mal_late_m)
writedlm("Late/mean/mal_oaa_late_m",mal_oaa_late_m)
writedlm("Late/mean/icit_succ_late_m",icit_succ_late_m)
writedlm("Late/mean/accoa_mal_late_m",accoa_mal_late_m)
writedlm("Late/mean/g6p_sixpgl_late_m",g6p_sixpgl_late_m)
writedlm("Late/mean/sixpgl_sixpgc_late_m",sixpgl_sixpgc_late_m)
writedlm("Late/mean/sixpgc_ru5p_late_m",sixpgc_ru5p_late_m)
writedlm("Late/mean/ru5p_xu5p_late_m",ru5p_xu5p_late_m)
writedlm("Late/mean/ru5p_r5p_late_m",ru5p_r5p_late_m)
writedlm("Late/mean/xu5p_s7p_late_m",xu5p_s7p_late_m)
writedlm("Late/mean/s7p_e4p_late_m",s7p_e4p_late_m)
writedlm("Late/mean/xu5p_g3p_late_m",xu5p_g3p_late_m)
writedlm("Late/mean/sixpgc_twoddg6p_late_m",sixpgc_twoddg6p_late_m)
writedlm("Late/mean/twoddg6p_g3p_late_m",twoddg6p_g3p_late_m)
writedlm("Late/mean/nadph_nadh_late_m",nadph_nadh_late_m)
writedlm("Late/mean/nadh_nadph_late_m",nadh_nadph_late_m)

writedlm("Late/std/glc_g6p_late_s",glc_g6p_late_s)
writedlm("Late/std/g6p_f6p_late_s",g6p_f6p_late_s)
writedlm("Late/std/f6p_fdp_late_s",f6p_fdp_late_s)
writedlm("Late/std/fdp_g3p_late_s",fdp_g3p_late_s)
writedlm("Late/std/g3p_dpg_late_s",g3p_dpg_late_s)
writedlm("Late/std/dpg_threepg_late_s",dpg_threepg_late_s)
writedlm("Late/std/threepg_twopg_late_s",threepg_twopg_late_s)
writedlm("Late/std/twopg_pep_late_s",twopg_pep_late_s)
writedlm("Late/std/pep_pyr_late_s",pep_pyr_late_s)
writedlm("Late/std/pyr_accoa_late_s",pyr_accoa_late_s)
writedlm("Late/std/pep_oaa_late_s",pep_oaa_late_s)
writedlm("Late/std/oaa_pep_late_s",oaa_pep_late_s)
writedlm("Late/std/mal_pyr_late_s",mal_pyr_late_s)
writedlm("Late/std/oaa_cit_late_s",oaa_cit_late_s)
writedlm("Late/std/cit_icit_late_s",cit_icit_late_s)
writedlm("Late/std/icit_akg_late_s",icit_akg_late_s)
writedlm("Late/std/akg_succoa_late_s",akg_succoa_late_s)
writedlm("Late/std/succoa_succ_late_s",succoa_succ_late_s)
writedlm("Late/std/succ_fum_late_s",succ_fum_late_s)
writedlm("Late/std/fum_mal_late_s",fum_mal_late_s)
writedlm("Late/std/mal_oaa_late_s",mal_oaa_late_s)
writedlm("Late/std/icit_succ_late_s",icit_succ_late_s)
writedlm("Late/std/accoa_mal_late_s",accoa_mal_late_s)
writedlm("Late/std/g6p_sixpgl_late_s",g6p_sixpgl_late_s)
writedlm("Late/std/sixpgl_sixpgc_late_s",sixpgl_sixpgc_late_s)
writedlm("Late/std/sixpgc_ru5p_late_s",sixpgc_ru5p_late_s)
writedlm("Late/std/ru5p_xu5p_late_s",ru5p_xu5p_late_s)
writedlm("Late/std/ru5p_r5p_late_s",ru5p_r5p_late_s)
writedlm("Late/std/xu5p_s7p_late_s",xu5p_s7p_late_s)
writedlm("Late/std/s7p_e4p_late_s",s7p_e4p_late_s)
writedlm("Late/std/xu5p_g3p_late_s",xu5p_g3p_late_s)
writedlm("Late/std/sixpgc_twoddg6p_late_s",sixpgc_twoddg6p_late_s)
writedlm("Late/std/twoddg6p_g3p_late_s",twoddg6p_g3p_late_s)
writedlm("Late/std/nadph_nadh_late_s",nadph_nadh_late_s)
writedlm("Late/std/nadh_nadph_late_s",nadh_nadph_late_s)






