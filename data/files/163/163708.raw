# ----------------------------------------------------------------------------------- #
# Copyright (c) 2016 Varnerlab
# School of Chemical Engineering Purdue University
# W. Lafayette IN 46907 USA

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
# copies of the Software, and to permit persons to whom the Software is 
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ----------------------------------------------------------------------------------- #
function Kinetics(t,x,data_dictionary)
# --------------------------------------------------------------------- #
# Kinetics.jl was generated using the Kwatee code generation system.
# Username: nicholas
# Type: CFPS-JULIA
# Version: 1.0
# Generation timestamp: 11-08-2016 14:46:40
# 
# Input arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary - parameter vector 
# 
# Return arguments: 
# rate_vector - rate vector 
# --------------------------------------------------------------------- #
# 
# Alias the species vector - 
M_g6p_c = x[1];
M_f6p_c = x[2];
M_fdp_c = x[3];
M_dhap_c = x[4];
M_g3p_c = x[5];
M_13dpg_c = x[6];
M_3pg_c = x[7];
M_2pg_c = x[8];
M_oaa_c = x[9];
M_coa_c = x[10];
M_accoa_c = x[11];
M_6pgl_c = x[12];
M_6pgc_c = x[13];
M_ru5p_D_c = x[14];
M_xu5p_D_c = x[15];
M_r5p_c = x[16];
M_s7p_c = x[17];
M_e4p_c = x[18];
M_2ddg6p_c = x[19];
M_cit_c = x[20];
M_icit_c = x[21];
M_akg_c = x[22];
M_succoa_c = x[23];
M_q8_c = x[24];
M_fum_c = x[25];
M_q8h2_c = x[26];
M_mql8_c = x[27];
M_mqn8_c = x[28];
M_glx_c = x[29];
M_actp_c = x[30];
M_ppi_c = x[31];
M_etoh_c = x[32];
M_for_c = x[33];
M_h_e = x[34];
M_chor_c = x[35];
M_gar_c = x[36];
M_10fthf_c = x[37];
M_air_c = x[38];
M_thf_c = x[39];
M_hco3_c = x[40];
M_aicar_c = x[41];
M_imp_c = x[42];
M_arg_L_c = x[43];
M_h2s_c = x[44];
M_mlthf_c = x[45];
M_5mthf_c = x[46];
M_urea_c = x[47];
M_h2o2_c = x[48];
M_mglx_c = x[49];
M_prop_c = x[50];
M_indole_c = x[51];
M_cadav_c = x[52];
M_gaba_c = x[53];
GENE_CAT = x[54];
RNAP = x[55];
OPEN_GENE_CAT = x[56];
mRNA_CAT = x[57];
RIBOSOME = x[58];
RIBOSOME_START_CAT = x[59];
M_ala_L_c_tRNA = x[60];
M_arg_L_c_tRNA = x[61];
M_asn_L_c_tRNA = x[62];
M_asp_L_c_tRNA = x[63];
M_cys_L_c_tRNA = x[64];
M_glu_L_c_tRNA = x[65];
M_gln_L_c_tRNA = x[66];
M_gly_L_c_tRNA = x[67];
M_his_L_c_tRNA = x[68];
M_ile_L_c_tRNA = x[69];
M_leu_L_c_tRNA = x[70];
M_lys_L_c_tRNA = x[71];
M_met_L_c_tRNA = x[72];
M_phe_L_c_tRNA = x[73];
M_pro_L_c_tRNA = x[74];
M_ser_L_c_tRNA = x[75];
M_thr_L_c_tRNA = x[76];
M_trp_L_c_tRNA = x[77];
M_tyr_L_c_tRNA = x[78];
M_val_L_c_tRNA = x[79];
PROTEIN_CAT = x[80];
tRNA = x[81];
M_glc_D_c = x[82];
M_pep_c = x[83];
M_pyr_c = x[84];
M_ac_c = x[85];
M_lac_D_c = x[86];
M_mal_L_c = x[87];
M_atp_c = x[88];
M_adp_c = x[89];
M_amp_c = x[90];
M_gtp_c = x[91];
M_gdp_c = x[92];
M_gmp_c = x[93];
M_utp_c = x[94];
M_udp_c = x[95];
M_ump_c = x[96];
M_ctp_c = x[97];
M_cdp_c = x[98];
M_cmp_c = x[99];
M_succ_c = x[100];
M_asp_L_c = x[101];
M_gly_L_c = x[102];
M_ile_L_c = x[103];
M_asn_L_c = x[104];
M_cys_L_c = x[105];
M_lys_L_c = x[106];
M_his_L_c = x[107];
M_ala_L_c = x[108];
M_phe_L_c = x[109];
M_pro_L_c = x[110];
M_ser_L_c = x[111];
M_thr_L_c = x[112];
M_trp_L_c = x[113];
M_tyr_L_c = x[114];
M_val_L_c = x[115];
M_met_L_c = x[116];
M_leu_L_c = x[117];
M_glu_L_c = x[118];
M_gln_L_c = x[119];
M_o2_c = x[120];
M_co2_c = x[121];
M_pi_c = x[122];
M_nh4_c = x[123];
M_so4_c = x[124];
M_h_c = x[125];
M_h2o_c = x[126];
M_nad_c = x[127];
M_nadh_c = x[128];
M_nadp_c = x[129];
M_nadph_c = x[130];
E_R_PTS = x[131];
E_R_glk_atp = x[132];
E_R_glk_utp = x[133];
E_R_glk_ctp = x[134];
E_R_glk_gtp = x[135];
E_R_pgi = x[136];
E_R_pgi_R = x[137];
E_R_pfk = x[138];
E_R_fdp = x[139];
E_R_fbaA = x[140];
E_R_fbaA_R = x[141];
E_R_tpiA = x[142];
E_R_tpiA_R = x[143];
E_R_gapA = x[144];
E_R_gapA_R = x[145];
E_R_pgk = x[146];
E_R_pgk_R = x[147];
E_R_gpm = x[148];
E_R_gpm_R = x[149];
E_R_eno = x[150];
E_R_eno_R = x[151];
E_R_pyk = x[152];
E_R_pck = x[153];
E_R_ppc = x[154];
E_R_pdh = x[155];
E_R_pps = x[156];
E_R_zwf = x[157];
E_R_zwf_R = x[158];
E_R_pgl = x[159];
E_R_gnd = x[160];
E_R_rpe = x[161];
E_R_rpe_R = x[162];
E_R_rpi = x[163];
E_R_rpi_R = x[164];
E_R_talAB = x[165];
E_R_talAB_R = x[166];
E_R_tkt1 = x[167];
E_R_tkt1_R = x[168];
E_R_tkt2 = x[169];
E_R_tkt2_R = x[170];
E_R_edd = x[171];
E_R_eda = x[172];
E_R_gltA = x[173];
E_R_acn = x[174];
E_R_acn_R = x[175];
E_R_icd = x[176];
E_R_icd_R = x[177];
E_R_sucAB = x[178];
E_R_sucCD = x[179];
E_R_sucCD_R = x[180];
E_R_sdh = x[181];
E_R_frd = x[182];
E_R_fum = x[183];
E_R_fum_R = x[184];
E_R_mdh = x[185];
E_R_mdh_R = x[186];
E_R_aceA = x[187];
E_R_aceB = x[188];
E_R_maeA = x[189];
E_R_maeB = x[190];
E_R_pta = x[191];
E_R_pta_R = x[192];
E_R_ackA = x[193];
E_R_ackA_R = x[194];
E_R_acs = x[195];
E_R_adhE = x[196];
E_R_adhE_R = x[197];
E_R_ldh_f = x[198];
E_R_ldh_r = x[199];
E_R_pflAB = x[200];
E_R_cyd = x[201];
E_R_app = x[202];
E_R_atp = x[203];
E_R_nuo = x[204];
E_R_pnt1 = x[205];
E_R_pnt2 = x[206];
E_R_ndh1 = x[207];
E_R_ndh2 = x[208];
E_R_hack1 = x[209];
E_R_ppk = x[210];
E_R_ppa = x[211];
E_R_chor = x[212];
E_R_gar = x[213];
E_R_air = x[214];
E_R_aicar = x[215];
E_R_imp = x[216];
E_R_gmp = x[217];
E_R_gdp = x[218];
E_R_gtp = x[219];
E_R_amp = x[220];
E_R_adk = x[221];
E_R_adk_R = x[222];
E_R_ump = x[223];
E_R_udp = x[224];
E_R_utp = x[225];
E_R_ctp = x[226];
E_R_cdp = x[227];
E_R_cmp = x[228];
E_R_alaAC = x[229];
E_R_arg = x[230];
E_R_aspC = x[231];
E_R_asnB = x[232];
E_R_asnA = x[233];
E_R_cysEMK = x[234];
E_R_gltBD = x[235];
E_R_gdhA = x[236];
E_R_glnA = x[237];
E_R_glyA = x[238];
E_R_his = x[239];
E_R_ile = x[240];
E_R_leu = x[241];
E_R_lys = x[242];
E_R_met = x[243];
E_R_phe = x[244];
E_R_pro = x[245];
E_R_serABC = x[246];
E_R_thr = x[247];
E_R_trp = x[248];
E_R_tyr = x[249];
E_R_val = x[250];
E_R_arg_deg1 = x[251];
E_R_arg_deg2 = x[252];
E_R_arg_deg3 = x[253];
E_R_arg_deg4 = x[254];
E_R_arg_deg5 = x[255];
E_R_arg_deg6 = x[256];
E_R_thr_deg1 = x[257];
E_R_gly_deg = x[258];
E_R_thr_deg2 = x[259];
E_R_thr_deg3 = x[260];
E_R_thr_deg4 = x[261];
E_R_thr_deg5 = x[262];
E_R_mglx_deg = x[263];
E_R_mglx_deg_R = x[264];
E_R_ser_deg = x[265];
E_R_pro_deg = x[266];
E_R_trp_deg = x[267];
E_R_cys_deg = x[268];
E_R_ala_deg = x[269];
E_R_lys_deg = x[270];
E_R_gln_deg = x[271];
E_R_glu_deg = x[272];
E_R_gaba_deg1 = x[273];
E_R_gaba_deg2 = x[274];
E_R_asn_deg = x[275];
E_Ex_1 = x[276];
E_Ex_2 = x[277];
E_Ex_3 = x[278];
E_Ex_4 = x[279];
E_Ex_5 = x[280];
E_ATP_deg = x[281];
E_GTP_deg = x[282];
E_CTP_deg = x[283];
E_UTP_deg = x[284];
E_R_amp_ppi = x[285];
E_R_amp_pi = x[286];
E_R_gmp_ppi = x[287];
E_R_gmp_pi = x[288];
E_R_cmp_ppi = x[289];
E_R_cmp_pi = x[290];
E_R_ump_ppi = x[291];
E_R_ump_pi = x[292];
E_transcriptional_initiation_CAT = x[293];
E_transcription_CAT = x[294];
E_mRNA_degradation_CAT = x[295];
E_translation_initiation_CAT = x[296];
E_translation_CAT = x[297];
E_tRNA_charging_M_ala_L_c_CAT = x[298];
E_tRNA_charging_M_arg_L_c_CAT = x[299];
E_tRNA_charging_M_asn_L_c_CAT = x[300];
E_tRNA_charging_M_asp_L_c_CAT = x[301];
E_tRNA_charging_M_cys_L_c_CAT = x[302];
E_tRNA_charging_M_glu_L_c_CAT = x[303];
E_tRNA_charging_M_gln_L_c_CAT = x[304];
E_tRNA_charging_M_gly_L_c_CAT = x[305];
E_tRNA_charging_M_his_L_c_CAT = x[306];
E_tRNA_charging_M_ile_L_c_CAT = x[307];
E_tRNA_charging_M_leu_L_c_CAT = x[308];
E_tRNA_charging_M_lys_L_c_CAT = x[309];
E_tRNA_charging_M_met_L_c_CAT = x[310];
E_tRNA_charging_M_phe_L_c_CAT = x[311];
E_tRNA_charging_M_pro_L_c_CAT = x[312];
E_tRNA_charging_M_ser_L_c_CAT = x[313];
E_tRNA_charging_M_thr_L_c_CAT = x[314];
E_tRNA_charging_M_trp_L_c_CAT = x[315];
E_tRNA_charging_M_tyr_L_c_CAT = x[316];
E_tRNA_charging_M_val_L_c_CAT = x[317];

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# R_PTS: M_pep_c+M_glc_D_c = M_g6p_c+M_pyr_c
tmp_reaction = rate_constant_array[1]*(E_R_PTS)*(M_pep_c/(saturation_constant_array[1,83] + M_pep_c))*(M_glc_D_c/(saturation_constant_array[1,82] + M_glc_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_glk_atp: M_atp_c+M_glc_D_c = M_adp_c+M_g6p_c+M_h_c
tmp_reaction = rate_constant_array[2]*(E_R_glk_atp)*(M_atp_c/(saturation_constant_array[2,88] + M_atp_c))*(M_glc_D_c/(saturation_constant_array[2,82] + M_glc_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_glk_utp: M_utp_c+M_glc_D_c = M_udp_c+M_g6p_c+M_h_c
tmp_reaction = rate_constant_array[3]*(E_R_glk_utp)*(M_utp_c/(saturation_constant_array[3,94] + M_utp_c))*(M_glc_D_c/(saturation_constant_array[3,82] + M_glc_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_glk_ctp: M_ctp_c+M_glc_D_c = M_cdp_c+M_g6p_c+M_h_c
tmp_reaction = rate_constant_array[4]*(E_R_glk_ctp)*(M_ctp_c/(saturation_constant_array[4,97] + M_ctp_c))*(M_glc_D_c/(saturation_constant_array[4,82] + M_glc_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_glk_gtp: M_gtp_c+M_glc_D_c = M_gdp_c+M_g6p_c+M_h_c
tmp_reaction = rate_constant_array[5]*(E_R_glk_gtp)*(M_gtp_c/(saturation_constant_array[5,91] + M_gtp_c))*(M_glc_D_c/(saturation_constant_array[5,82] + M_glc_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pgi: M_g6p_c = M_f6p_c
tmp_reaction = rate_constant_array[6]*(E_R_pgi)*(M_g6p_c/(saturation_constant_array[6,1] + M_g6p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pgi_R: M_f6p_c = M_g6p_c
tmp_reaction = rate_constant_array[7]*(E_R_pgi_R)*(M_f6p_c/(saturation_constant_array[7,2] + M_f6p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pfk: M_atp_c+M_f6p_c = M_adp_c+M_fdp_c+M_h_c
tmp_reaction = rate_constant_array[8]*(E_R_pfk)*(M_atp_c/(saturation_constant_array[8,88] + M_atp_c))*(M_f6p_c/(saturation_constant_array[8,2] + M_f6p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_fdp: M_fdp_c+M_h2o_c = M_f6p_c+M_pi_c
tmp_reaction = rate_constant_array[9]*(E_R_fdp)*(M_fdp_c/(saturation_constant_array[9,3] + M_fdp_c))*(M_h2o_c/(saturation_constant_array[9,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_fbaA: M_fdp_c = M_dhap_c+M_g3p_c
tmp_reaction = rate_constant_array[10]*(E_R_fbaA)*(M_fdp_c/(saturation_constant_array[10,3] + M_fdp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_fbaA_R: M_dhap_c+M_g3p_c = M_fdp_c
tmp_reaction = rate_constant_array[11]*(E_R_fbaA_R)*(M_dhap_c/(saturation_constant_array[11,4] + M_dhap_c))*(M_g3p_c/(saturation_constant_array[11,5] + M_g3p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_tpiA: M_dhap_c = M_g3p_c
tmp_reaction = rate_constant_array[12]*(E_R_tpiA)*(M_dhap_c/(saturation_constant_array[12,4] + M_dhap_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_tpiA_R: M_g3p_c = M_dhap_c
tmp_reaction = rate_constant_array[13]*(E_R_tpiA_R)*(M_g3p_c/(saturation_constant_array[13,5] + M_g3p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gapA: M_g3p_c+M_nad_c+M_pi_c = M_13dpg_c+M_h_c+M_nadh_c
tmp_reaction = rate_constant_array[14]*(E_R_gapA)*(M_g3p_c/(saturation_constant_array[14,5] + M_g3p_c))*(M_nad_c/(saturation_constant_array[14,127] + M_nad_c))*(M_pi_c/(saturation_constant_array[14,122] + M_pi_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gapA_R: M_13dpg_c+M_h_c+M_nadh_c = M_g3p_c+M_nad_c+M_pi_c
tmp_reaction = rate_constant_array[15]*(E_R_gapA_R)*(M_13dpg_c/(saturation_constant_array[15,6] + M_13dpg_c))*(M_h_c/(saturation_constant_array[15,125] + M_h_c))*(M_nadh_c/(saturation_constant_array[15,128] + M_nadh_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pgk: M_13dpg_c+M_adp_c = M_3pg_c+M_atp_c
tmp_reaction = rate_constant_array[16]*(E_R_pgk)*(M_13dpg_c/(saturation_constant_array[16,6] + M_13dpg_c))*(M_adp_c/(saturation_constant_array[16,89] + M_adp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pgk_R: M_3pg_c+M_atp_c = M_13dpg_c+M_adp_c
tmp_reaction = rate_constant_array[17]*(E_R_pgk_R)*(M_3pg_c/(saturation_constant_array[17,7] + M_3pg_c))*(M_atp_c/(saturation_constant_array[17,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gpm: M_3pg_c = M_2pg_c
tmp_reaction = rate_constant_array[18]*(E_R_gpm)*(M_3pg_c/(saturation_constant_array[18,7] + M_3pg_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gpm_R: M_2pg_c = M_3pg_c
tmp_reaction = rate_constant_array[19]*(E_R_gpm_R)*(M_2pg_c/(saturation_constant_array[19,8] + M_2pg_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_eno: M_2pg_c = M_h2o_c+M_pep_c
tmp_reaction = rate_constant_array[20]*(E_R_eno)*(M_2pg_c/(saturation_constant_array[20,8] + M_2pg_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_eno_R: M_h2o_c+M_pep_c = M_2pg_c
tmp_reaction = rate_constant_array[21]*(E_R_eno_R)*(M_h2o_c/(saturation_constant_array[21,126] + M_h2o_c))*(M_pep_c/(saturation_constant_array[21,83] + M_pep_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pyk: M_adp_c+M_h_c+M_pep_c = M_atp_c+M_pyr_c
tmp_reaction = rate_constant_array[22]*(E_R_pyk)*(M_adp_c/(saturation_constant_array[22,89] + M_adp_c))*(M_h_c/(saturation_constant_array[22,125] + M_h_c))*(M_pep_c/(saturation_constant_array[22,83] + M_pep_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pck: M_atp_c+M_oaa_c = M_adp_c+M_co2_c+M_pep_c
tmp_reaction = rate_constant_array[23]*(E_R_pck)*(M_atp_c/(saturation_constant_array[23,88] + M_atp_c))*(M_oaa_c/(saturation_constant_array[23,9] + M_oaa_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ppc: M_co2_c+M_h2o_c+M_pep_c = M_h_c+M_oaa_c+M_pi_c
tmp_reaction = rate_constant_array[24]*(E_R_ppc)*(M_co2_c/(saturation_constant_array[24,121] + M_co2_c))*(M_h2o_c/(saturation_constant_array[24,126] + M_h2o_c))*(M_pep_c/(saturation_constant_array[24,83] + M_pep_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pdh: M_coa_c+M_nad_c+M_pyr_c = M_accoa_c+M_co2_c+M_nadh_c
tmp_reaction = rate_constant_array[25]*(E_R_pdh)*(M_coa_c/(saturation_constant_array[25,10] + M_coa_c))*(M_nad_c/(saturation_constant_array[25,127] + M_nad_c))*(M_pyr_c/(saturation_constant_array[25,84] + M_pyr_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pps: M_atp_c+M_h2o_c+M_pyr_c = M_amp_c+2*M_h_c+M_pep_c+M_pi_c
tmp_reaction = rate_constant_array[26]*(E_R_pps)*(M_atp_c/(saturation_constant_array[26,88] + M_atp_c))*(M_h2o_c/(saturation_constant_array[26,126] + M_h2o_c))*(M_pyr_c/(saturation_constant_array[26,84] + M_pyr_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_zwf: M_g6p_c+M_nadp_c = M_6pgl_c+M_h_c+M_nadph_c
tmp_reaction = rate_constant_array[27]*(E_R_zwf)*(M_g6p_c/(saturation_constant_array[27,1] + M_g6p_c))*(M_nadp_c/(saturation_constant_array[27,129] + M_nadp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_zwf_R: M_6pgl_c+M_h_c+M_nadph_c = M_g6p_c+M_nadp_c
tmp_reaction = rate_constant_array[28]*(E_R_zwf_R)*(M_6pgl_c/(saturation_constant_array[28,12] + M_6pgl_c))*(M_h_c/(saturation_constant_array[28,125] + M_h_c))*(M_nadph_c/(saturation_constant_array[28,130] + M_nadph_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pgl: M_6pgl_c+M_h2o_c = M_6pgc_c+M_h_c
tmp_reaction = rate_constant_array[29]*(E_R_pgl)*(M_6pgl_c/(saturation_constant_array[29,12] + M_6pgl_c))*(M_h2o_c/(saturation_constant_array[29,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gnd: M_6pgc_c+M_nadp_c = M_co2_c+M_nadph_c+M_ru5p_D_c
tmp_reaction = rate_constant_array[30]*(E_R_gnd)*(M_6pgc_c/(saturation_constant_array[30,13] + M_6pgc_c))*(M_nadp_c/(saturation_constant_array[30,129] + M_nadp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_rpe: M_ru5p_D_c = M_xu5p_D_c
tmp_reaction = rate_constant_array[31]*(E_R_rpe)*(M_ru5p_D_c/(saturation_constant_array[31,14] + M_ru5p_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_rpe_R: M_xu5p_D_c = M_ru5p_D_c
tmp_reaction = rate_constant_array[32]*(E_R_rpe_R)*(M_xu5p_D_c/(saturation_constant_array[32,15] + M_xu5p_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_rpi: M_r5p_c = M_ru5p_D_c
tmp_reaction = rate_constant_array[33]*(E_R_rpi)*(M_r5p_c/(saturation_constant_array[33,16] + M_r5p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_rpi_R: M_ru5p_D_c = M_r5p_c
tmp_reaction = rate_constant_array[34]*(E_R_rpi_R)*(M_ru5p_D_c/(saturation_constant_array[34,14] + M_ru5p_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_talAB: M_g3p_c+M_s7p_c = M_e4p_c+M_f6p_c
tmp_reaction = rate_constant_array[35]*(E_R_talAB)*(M_g3p_c/(saturation_constant_array[35,5] + M_g3p_c))*(M_s7p_c/(saturation_constant_array[35,17] + M_s7p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_talAB_R: M_e4p_c+M_f6p_c = M_g3p_c+M_s7p_c
tmp_reaction = rate_constant_array[36]*(E_R_talAB_R)*(M_e4p_c/(saturation_constant_array[36,18] + M_e4p_c))*(M_f6p_c/(saturation_constant_array[36,2] + M_f6p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_tkt1: M_r5p_c+M_xu5p_D_c = M_g3p_c+M_s7p_c
tmp_reaction = rate_constant_array[37]*(E_R_tkt1)*(M_r5p_c/(saturation_constant_array[37,16] + M_r5p_c))*(M_xu5p_D_c/(saturation_constant_array[37,15] + M_xu5p_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_tkt1_R: M_g3p_c+M_s7p_c = M_r5p_c+M_xu5p_D_c
tmp_reaction = rate_constant_array[38]*(E_R_tkt1_R)*(M_g3p_c/(saturation_constant_array[38,5] + M_g3p_c))*(M_s7p_c/(saturation_constant_array[38,17] + M_s7p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_tkt2: M_e4p_c+M_xu5p_D_c = M_f6p_c+M_g3p_c
tmp_reaction = rate_constant_array[39]*(E_R_tkt2)*(M_e4p_c/(saturation_constant_array[39,18] + M_e4p_c))*(M_xu5p_D_c/(saturation_constant_array[39,15] + M_xu5p_D_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_tkt2_R: M_f6p_c+M_g3p_c = M_e4p_c+M_xu5p_D_c
tmp_reaction = rate_constant_array[40]*(E_R_tkt2_R)*(M_f6p_c/(saturation_constant_array[40,2] + M_f6p_c))*(M_g3p_c/(saturation_constant_array[40,5] + M_g3p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_edd: M_6pgc_c = M_2ddg6p_c+M_h2o_c
tmp_reaction = rate_constant_array[41]*(E_R_edd)*(M_6pgc_c/(saturation_constant_array[41,13] + M_6pgc_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_eda: M_2ddg6p_c = M_g3p_c+M_pyr_c
tmp_reaction = rate_constant_array[42]*(E_R_eda)*(M_2ddg6p_c/(saturation_constant_array[42,19] + M_2ddg6p_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gltA: M_accoa_c+M_h2o_c+M_oaa_c = M_cit_c+M_coa_c+M_h_c
tmp_reaction = rate_constant_array[43]*(E_R_gltA)*(M_accoa_c/(saturation_constant_array[43,11] + M_accoa_c))*(M_h2o_c/(saturation_constant_array[43,126] + M_h2o_c))*(M_oaa_c/(saturation_constant_array[43,9] + M_oaa_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_acn: M_cit_c = M_icit_c
tmp_reaction = rate_constant_array[44]*(E_R_acn)*(M_cit_c/(saturation_constant_array[44,20] + M_cit_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_acn_R: M_icit_c = M_cit_c
tmp_reaction = rate_constant_array[45]*(E_R_acn_R)*(M_icit_c/(saturation_constant_array[45,21] + M_icit_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_icd: M_icit_c+M_nadp_c = M_akg_c+M_co2_c+M_nadph_c
tmp_reaction = rate_constant_array[46]*(E_R_icd)*(M_icit_c/(saturation_constant_array[46,21] + M_icit_c))*(M_nadp_c/(saturation_constant_array[46,129] + M_nadp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_icd_R: M_akg_c+M_co2_c+M_nadph_c = M_icit_c+M_nadp_c
tmp_reaction = rate_constant_array[47]*(E_R_icd_R)*(M_akg_c/(saturation_constant_array[47,22] + M_akg_c))*(M_co2_c/(saturation_constant_array[47,121] + M_co2_c))*(M_nadph_c/(saturation_constant_array[47,130] + M_nadph_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_sucAB: M_akg_c+M_coa_c+M_nad_c = M_co2_c+M_nadh_c+M_succoa_c
tmp_reaction = rate_constant_array[48]*(E_R_sucAB)*(M_akg_c/(saturation_constant_array[48,22] + M_akg_c))*(M_coa_c/(saturation_constant_array[48,10] + M_coa_c))*(M_nad_c/(saturation_constant_array[48,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_sucCD: M_atp_c+M_coa_c+M_succ_c = M_adp_c+M_pi_c+M_succoa_c
tmp_reaction = rate_constant_array[49]*(E_R_sucCD)*(M_atp_c/(saturation_constant_array[49,88] + M_atp_c))*(M_coa_c/(saturation_constant_array[49,10] + M_coa_c))*(M_succ_c/(saturation_constant_array[49,100] + M_succ_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_sucCD_R: M_adp_c+M_pi_c+M_succoa_c = M_atp_c+M_coa_c+M_succ_c
tmp_reaction = rate_constant_array[50]*(E_R_sucCD_R)*(M_adp_c/(saturation_constant_array[50,89] + M_adp_c))*(M_pi_c/(saturation_constant_array[50,122] + M_pi_c))*(M_succoa_c/(saturation_constant_array[50,23] + M_succoa_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_sdh: M_q8_c+M_succ_c = M_fum_c+M_q8h2_c
tmp_reaction = rate_constant_array[51]*(E_R_sdh)*(M_q8_c/(saturation_constant_array[51,24] + M_q8_c))*(M_succ_c/(saturation_constant_array[51,100] + M_succ_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_frd: M_fum_c+M_mql8_c = M_mqn8_c+M_succ_c
tmp_reaction = rate_constant_array[52]*(E_R_frd)*(M_fum_c/(saturation_constant_array[52,25] + M_fum_c))*(M_mql8_c/(saturation_constant_array[52,27] + M_mql8_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_fum: M_fum_c+M_h2o_c = M_mal_L_c
tmp_reaction = rate_constant_array[53]*(E_R_fum)*(M_fum_c/(saturation_constant_array[53,25] + M_fum_c))*(M_h2o_c/(saturation_constant_array[53,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_fum_R: M_mal_L_c = M_fum_c+M_h2o_c
tmp_reaction = rate_constant_array[54]*(E_R_fum_R)*(M_mal_L_c/(saturation_constant_array[54,87] + M_mal_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_mdh: M_mal_L_c+M_nad_c = M_oaa_c+M_h_c+M_nadh_c
tmp_reaction = rate_constant_array[55]*(E_R_mdh)*(M_mal_L_c/(saturation_constant_array[55,87] + M_mal_L_c))*(M_nad_c/(saturation_constant_array[55,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_mdh_R: M_oaa_c+M_h_c+M_nadh_c = M_mal_L_c+M_nad_c
tmp_reaction = rate_constant_array[56]*(E_R_mdh_R)*(M_oaa_c/(saturation_constant_array[56,9] + M_oaa_c))*(M_h_c/(saturation_constant_array[56,125] + M_h_c))*(M_nadh_c/(saturation_constant_array[56,128] + M_nadh_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_aceA: M_icit_c = M_glx_c+M_succ_c
tmp_reaction = rate_constant_array[57]*(E_R_aceA)*(M_icit_c/(saturation_constant_array[57,21] + M_icit_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_aceB: M_accoa_c+M_glx_c+M_h2o_c = M_coa_c+M_h_c+M_mal_L_c
tmp_reaction = rate_constant_array[58]*(E_R_aceB)*(M_accoa_c/(saturation_constant_array[58,11] + M_accoa_c))*(M_glx_c/(saturation_constant_array[58,29] + M_glx_c))*(M_h2o_c/(saturation_constant_array[58,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_maeA: M_mal_L_c+M_nad_c = M_co2_c+M_nadh_c+M_pyr_c
tmp_reaction = rate_constant_array[59]*(E_R_maeA)*(M_mal_L_c/(saturation_constant_array[59,87] + M_mal_L_c))*(M_nad_c/(saturation_constant_array[59,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_maeB: M_mal_L_c+M_nadp_c = M_co2_c+M_nadph_c+M_pyr_c
tmp_reaction = rate_constant_array[60]*(E_R_maeB)*(M_mal_L_c/(saturation_constant_array[60,87] + M_mal_L_c))*(M_nadp_c/(saturation_constant_array[60,129] + M_nadp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pta: M_accoa_c+M_pi_c = M_actp_c+M_coa_c
tmp_reaction = rate_constant_array[61]*(E_R_pta)*(M_accoa_c/(saturation_constant_array[61,11] + M_accoa_c))*(M_pi_c/(saturation_constant_array[61,122] + M_pi_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pta_R: M_actp_c+M_coa_c = M_accoa_c+M_pi_c
tmp_reaction = rate_constant_array[62]*(E_R_pta_R)*(M_actp_c/(saturation_constant_array[62,30] + M_actp_c))*(M_coa_c/(saturation_constant_array[62,10] + M_coa_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ackA: M_actp_c+M_adp_c = M_ac_c+M_atp_c
tmp_reaction = rate_constant_array[63]*(E_R_ackA)*(M_actp_c/(saturation_constant_array[63,30] + M_actp_c))*(M_adp_c/(saturation_constant_array[63,89] + M_adp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ackA_R: M_ac_c+M_atp_c = M_actp_c+M_adp_c
tmp_reaction = rate_constant_array[64]*(E_R_ackA_R)*(M_ac_c/(saturation_constant_array[64,85] + M_ac_c))*(M_atp_c/(saturation_constant_array[64,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_acs: M_ac_c+M_atp_c+M_coa_c = M_accoa_c+M_amp_c+M_ppi_c
tmp_reaction = rate_constant_array[65]*(E_R_acs)*(M_ac_c/(saturation_constant_array[65,85] + M_ac_c))*(M_atp_c/(saturation_constant_array[65,88] + M_atp_c))*(M_coa_c/(saturation_constant_array[65,10] + M_coa_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_adhE: M_accoa_c+2*M_h_c+2*M_nadh_c = M_coa_c+M_etoh_c+2*M_nad_c
tmp_reaction = rate_constant_array[66]*(E_R_adhE)*(M_accoa_c/(saturation_constant_array[66,11] + M_accoa_c))*(M_h_c/(saturation_constant_array[66,125] + M_h_c))*(M_nadh_c/(saturation_constant_array[66,128] + M_nadh_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_adhE_R: M_coa_c+M_etoh_c+2*M_nad_c = M_accoa_c+2*M_h_c+2*M_nadh_c
tmp_reaction = rate_constant_array[67]*(E_R_adhE_R)*(M_coa_c/(saturation_constant_array[67,10] + M_coa_c))*(M_etoh_c/(saturation_constant_array[67,32] + M_etoh_c))*(M_nad_c/(saturation_constant_array[67,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ldh_f: M_pyr_c+M_nadh_c+M_h_c = M_lac_D_c+M_nad_c
tmp_reaction = rate_constant_array[68]*(E_R_ldh_f)*(M_pyr_c/(saturation_constant_array[68,84] + M_pyr_c))*(M_nadh_c/(saturation_constant_array[68,128] + M_nadh_c))*(M_h_c/(saturation_constant_array[68,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ldh_r: M_lac_D_c+M_nad_c = M_pyr_c+M_nadh_c+M_h_c
tmp_reaction = rate_constant_array[69]*(E_R_ldh_r)*(M_lac_D_c/(saturation_constant_array[69,86] + M_lac_D_c))*(M_nad_c/(saturation_constant_array[69,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pflAB: M_coa_c+M_pyr_c = M_accoa_c+M_for_c
tmp_reaction = rate_constant_array[70]*(E_R_pflAB)*(M_coa_c/(saturation_constant_array[70,10] + M_coa_c))*(M_pyr_c/(saturation_constant_array[70,84] + M_pyr_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_cyd: 2*M_h_c+0.5*M_o2_c+M_q8h2_c = M_h2o_c+M_q8_c+2*M_h_e
tmp_reaction = rate_constant_array[71]*(E_R_cyd)*(M_h_c/(saturation_constant_array[71,125] + M_h_c))*(M_o2_c/(saturation_constant_array[71,120] + M_o2_c))*(M_q8h2_c/(saturation_constant_array[71,26] + M_q8h2_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_app: 2*M_h_c+M_mql8_c+0.5*M_o2_c = M_h2o_c+M_mqn8_c+2*M_h_e
tmp_reaction = rate_constant_array[72]*(E_R_app)*(M_h_c/(saturation_constant_array[72,125] + M_h_c))*(M_mql8_c/(saturation_constant_array[72,27] + M_mql8_c))*(M_o2_c/(saturation_constant_array[72,120] + M_o2_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_atp: M_adp_c+M_pi_c+4*M_h_e = M_atp_c+3*M_h_c+M_h2o_c
tmp_reaction = rate_constant_array[73]*(E_R_atp)*(M_adp_c/(saturation_constant_array[73,89] + M_adp_c))*(M_pi_c/(saturation_constant_array[73,122] + M_pi_c))*(M_h_e/(saturation_constant_array[73,34] + M_h_e));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_nuo: 3*M_h_c+M_nadh_c+M_q8_c = M_nad_c+M_q8h2_c+2*M_h_e
tmp_reaction = rate_constant_array[74]*(E_R_nuo)*(M_h_c/(saturation_constant_array[74,125] + M_h_c))*(M_nadh_c/(saturation_constant_array[74,128] + M_nadh_c))*(M_q8_c/(saturation_constant_array[74,24] + M_q8_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pnt1: M_nad_c+M_nadph_c = M_nadh_c+M_nadp_c
tmp_reaction = rate_constant_array[75]*(E_R_pnt1)*(M_nad_c/(saturation_constant_array[75,127] + M_nad_c))*(M_nadph_c/(saturation_constant_array[75,130] + M_nadph_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pnt2: M_nadh_c+M_nadp_c+2*M_h_e = 2*M_h_c+M_nad_c+M_nadph_c
tmp_reaction = rate_constant_array[76]*(E_R_pnt2)*(M_nadh_c/(saturation_constant_array[76,128] + M_nadh_c))*(M_nadp_c/(saturation_constant_array[76,129] + M_nadp_c))*(M_h_e/(saturation_constant_array[76,34] + M_h_e));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ndh1: M_h_c+M_nadh_c+M_q8_c = M_nad_c+M_q8h2_c
tmp_reaction = rate_constant_array[77]*(E_R_ndh1)*(M_h_c/(saturation_constant_array[77,125] + M_h_c))*(M_nadh_c/(saturation_constant_array[77,128] + M_nadh_c))*(M_q8_c/(saturation_constant_array[77,24] + M_q8_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ndh2: M_h_c+M_mqn8_c+M_nadh_c = M_mql8_c+M_nad_c
tmp_reaction = rate_constant_array[78]*(E_R_ndh2)*(M_h_c/(saturation_constant_array[78,125] + M_h_c))*(M_mqn8_c/(saturation_constant_array[78,28] + M_mqn8_c))*(M_nadh_c/(saturation_constant_array[78,128] + M_nadh_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_hack1: M_atp_c+M_h2o_c = M_adp_c+M_h_c+M_pi_c
tmp_reaction = rate_constant_array[79]*(E_R_hack1)*(M_atp_c/(saturation_constant_array[79,88] + M_atp_c))*(M_h2o_c/(saturation_constant_array[79,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ppk: M_atp_c+M_pi_c = M_adp_c+M_ppi_c
tmp_reaction = rate_constant_array[80]*(E_R_ppk)*(M_atp_c/(saturation_constant_array[80,88] + M_atp_c))*(M_pi_c/(saturation_constant_array[80,122] + M_pi_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ppa: M_ppi_c+M_h2o_c = 2*M_pi_c+M_h_c
tmp_reaction = rate_constant_array[81]*(E_R_ppa)*(M_ppi_c/(saturation_constant_array[81,31] + M_ppi_c))*(M_h2o_c/(saturation_constant_array[81,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_chor: M_e4p_c+2*M_pep_c+M_nadph_c+M_atp_c = M_chor_c+M_nadp_c+M_adp_c+4*M_pi_c
tmp_reaction = rate_constant_array[82]*(E_R_chor)*(M_e4p_c/(saturation_constant_array[82,18] + M_e4p_c))*(M_pep_c/(saturation_constant_array[82,83] + M_pep_c))*(M_nadph_c/(saturation_constant_array[82,130] + M_nadph_c))*(M_atp_c/(saturation_constant_array[82,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gar: M_r5p_c+M_gln_L_c+M_gly_L_c+2*M_atp_c+M_h2o_c = M_gar_c+M_glu_L_c+M_adp_c+M_amp_c+M_pi_c+M_ppi_c+7*M_h_c
tmp_reaction = rate_constant_array[83]*(E_R_gar)*(M_r5p_c/(saturation_constant_array[83,16] + M_r5p_c))*(M_gln_L_c/(saturation_constant_array[83,119] + M_gln_L_c))*(M_gly_L_c/(saturation_constant_array[83,102] + M_gly_L_c))*(M_atp_c/(saturation_constant_array[83,88] + M_atp_c))*(M_h2o_c/(saturation_constant_array[83,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_air: M_gar_c+M_10fthf_c+M_gln_L_c+2*M_atp_c+M_h2o_c = M_air_c+M_thf_c+M_glu_L_c+2*M_adp_c+2*M_pi_c+3*M_h_c
tmp_reaction = rate_constant_array[84]*(E_R_air)*(M_gar_c/(saturation_constant_array[84,36] + M_gar_c))*(M_10fthf_c/(saturation_constant_array[84,37] + M_10fthf_c))*(M_gln_L_c/(saturation_constant_array[84,119] + M_gln_L_c))*(M_atp_c/(saturation_constant_array[84,88] + M_atp_c))*(M_h2o_c/(saturation_constant_array[84,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_aicar: M_air_c+M_asp_L_c+2*M_atp_c+M_hco3_c = M_aicar_c+M_fum_c+2*M_adp_c+2*M_h_c+2*M_pi_c
tmp_reaction = rate_constant_array[85]*(E_R_aicar)*(M_air_c/(saturation_constant_array[85,38] + M_air_c))*(M_asp_L_c/(saturation_constant_array[85,101] + M_asp_L_c))*(M_atp_c/(saturation_constant_array[85,88] + M_atp_c))*(M_hco3_c/(saturation_constant_array[85,40] + M_hco3_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_imp: M_aicar_c+M_10fthf_c = M_imp_c+M_thf_c+M_h2o_c
tmp_reaction = rate_constant_array[86]*(E_R_imp)*(M_aicar_c/(saturation_constant_array[86,41] + M_aicar_c))*(M_10fthf_c/(saturation_constant_array[86,37] + M_10fthf_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gmp: M_imp_c+M_atp_c+M_gln_L_c+M_nad_c+2*M_h2o_c = M_gmp_c+M_amp_c+M_glu_L_c+M_nadh_c+3*M_h_c+M_ppi_c
tmp_reaction = rate_constant_array[87]*(E_R_gmp)*(M_imp_c/(saturation_constant_array[87,42] + M_imp_c))*(M_atp_c/(saturation_constant_array[87,88] + M_atp_c))*(M_gln_L_c/(saturation_constant_array[87,119] + M_gln_L_c))*(M_nad_c/(saturation_constant_array[87,127] + M_nad_c))*(M_h2o_c/(saturation_constant_array[87,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gdp: M_gmp_c+M_atp_c = M_gdp_c+M_adp_c
tmp_reaction = rate_constant_array[88]*(E_R_gdp)*(M_gmp_c/(saturation_constant_array[88,93] + M_gmp_c))*(M_atp_c/(saturation_constant_array[88,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gtp: M_gdp_c+M_atp_c = M_gtp_c+M_adp_c
tmp_reaction = rate_constant_array[89]*(E_R_gtp)*(M_gdp_c/(saturation_constant_array[89,92] + M_gdp_c))*(M_atp_c/(saturation_constant_array[89,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_amp: M_asp_L_c+M_imp_c+M_gtp_c = M_amp_c+M_gdp_c+M_pi_c+2*M_h_c+M_fum_c
tmp_reaction = rate_constant_array[90]*(E_R_amp)*(M_asp_L_c/(saturation_constant_array[90,101] + M_asp_L_c))*(M_imp_c/(saturation_constant_array[90,42] + M_imp_c))*(M_gtp_c/(saturation_constant_array[90,91] + M_gtp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_adk: M_amp_c+M_atp_c = 2*M_adp_c
tmp_reaction = rate_constant_array[91]*(E_R_adk)*(M_amp_c/(saturation_constant_array[91,90] + M_amp_c))*(M_atp_c/(saturation_constant_array[91,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_adk_R: 2*M_adp_c = M_amp_c+M_atp_c
tmp_reaction = rate_constant_array[92]*(E_R_adk_R)*(M_adp_c/(saturation_constant_array[92,89] + M_adp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ump: M_gln_L_c+M_asp_L_c+M_r5p_c+M_q8_c+3*M_atp_c+M_hco3_c = M_ump_c+M_glu_L_c+M_q8h2_c+2*M_h_c+2*M_adp_c+M_amp_c+2*M_pi_c+M_ppi_c+M_co2_c
tmp_reaction = rate_constant_array[93]*(E_R_ump)*(M_gln_L_c/(saturation_constant_array[93,119] + M_gln_L_c))*(M_asp_L_c/(saturation_constant_array[93,101] + M_asp_L_c))*(M_r5p_c/(saturation_constant_array[93,16] + M_r5p_c))*(M_q8_c/(saturation_constant_array[93,24] + M_q8_c))*(M_atp_c/(saturation_constant_array[93,88] + M_atp_c))*(M_hco3_c/(saturation_constant_array[93,40] + M_hco3_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_udp: M_ump_c+M_atp_c = M_udp_c+M_adp_c
tmp_reaction = rate_constant_array[94]*(E_R_udp)*(M_ump_c/(saturation_constant_array[94,96] + M_ump_c))*(M_atp_c/(saturation_constant_array[94,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_utp: M_udp_c+M_atp_c = M_utp_c+M_adp_c
tmp_reaction = rate_constant_array[95]*(E_R_utp)*(M_udp_c/(saturation_constant_array[95,95] + M_udp_c))*(M_atp_c/(saturation_constant_array[95,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ctp: M_utp_c+M_gln_L_c+M_atp_c+M_h2o_c = M_ctp_c+M_glu_L_c+M_adp_c+M_pi_c+3*M_h_c
tmp_reaction = rate_constant_array[96]*(E_R_ctp)*(M_utp_c/(saturation_constant_array[96,94] + M_utp_c))*(M_gln_L_c/(saturation_constant_array[96,119] + M_gln_L_c))*(M_atp_c/(saturation_constant_array[96,88] + M_atp_c))*(M_h2o_c/(saturation_constant_array[96,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_cdp: M_ctp_c+M_h2o_c = M_cdp_c+M_pi_c+M_h_c
tmp_reaction = rate_constant_array[97]*(E_R_cdp)*(M_ctp_c/(saturation_constant_array[97,97] + M_ctp_c))*(M_h2o_c/(saturation_constant_array[97,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_cmp: M_cdp_c+M_h2o_c = M_cmp_c+M_pi_c+M_h_c
tmp_reaction = rate_constant_array[98]*(E_R_cmp)*(M_cdp_c/(saturation_constant_array[98,98] + M_cdp_c))*(M_h2o_c/(saturation_constant_array[98,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_alaAC: M_pyr_c+M_glu_L_c = M_ala_L_c+M_akg_c
tmp_reaction = rate_constant_array[99]*(E_R_alaAC)*(M_pyr_c/(saturation_constant_array[99,84] + M_pyr_c))*(M_glu_L_c/(saturation_constant_array[99,118] + M_glu_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_arg: M_glu_L_c+M_accoa_c+4*M_atp_c+M_nadph_c+3*M_h2o_c+M_gln_L_c+M_asp_L_c+M_co2_c = M_arg_L_c+M_coa_c+5*M_h_c+3*M_adp_c+3*M_pi_c+M_nadp_c+M_akg_c+M_ac_c+M_amp_c+M_ppi_c+M_fum_c
tmp_reaction = rate_constant_array[100]*(E_R_arg)*(M_glu_L_c/(saturation_constant_array[100,118] + M_glu_L_c))*(M_accoa_c/(saturation_constant_array[100,11] + M_accoa_c))*(M_atp_c/(saturation_constant_array[100,88] + M_atp_c))*(M_nadph_c/(saturation_constant_array[100,130] + M_nadph_c))*(M_h2o_c/(saturation_constant_array[100,126] + M_h2o_c))*(M_gln_L_c/(saturation_constant_array[100,119] + M_gln_L_c))*(M_asp_L_c/(saturation_constant_array[100,101] + M_asp_L_c))*(M_co2_c/(saturation_constant_array[100,121] + M_co2_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_aspC: M_glu_L_c+M_oaa_c = M_asp_L_c+M_akg_c
tmp_reaction = rate_constant_array[101]*(E_R_aspC)*(M_glu_L_c/(saturation_constant_array[101,118] + M_glu_L_c))*(M_oaa_c/(saturation_constant_array[101,9] + M_oaa_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_asnB: M_asp_L_c+M_gln_L_c+M_h2o_c+M_atp_c = M_asn_L_c+M_glu_L_c+M_h_c+M_ppi_c+M_amp_c
tmp_reaction = rate_constant_array[102]*(E_R_asnB)*(M_asp_L_c/(saturation_constant_array[102,101] + M_asp_L_c))*(M_gln_L_c/(saturation_constant_array[102,119] + M_gln_L_c))*(M_h2o_c/(saturation_constant_array[102,126] + M_h2o_c))*(M_atp_c/(saturation_constant_array[102,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_asnA: M_asp_L_c+M_atp_c+M_nh4_c = M_asn_L_c+M_h_c+M_ppi_c+M_amp_c
tmp_reaction = rate_constant_array[103]*(E_R_asnA)*(M_asp_L_c/(saturation_constant_array[103,101] + M_asp_L_c))*(M_atp_c/(saturation_constant_array[103,88] + M_atp_c))*(M_nh4_c/(saturation_constant_array[103,123] + M_nh4_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_cysEMK: M_ser_L_c+M_accoa_c+M_h2s_c = M_cys_L_c+M_coa_c+M_h_c+M_ac_c
tmp_reaction = rate_constant_array[104]*(E_R_cysEMK)*(M_ser_L_c/(saturation_constant_array[104,111] + M_ser_L_c))*(M_accoa_c/(saturation_constant_array[104,11] + M_accoa_c))*(M_h2s_c/(saturation_constant_array[104,44] + M_h2s_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gltBD: M_gln_L_c+M_akg_c+M_nadph_c+M_h_c = 2*M_glu_L_c+M_nadp_c
tmp_reaction = rate_constant_array[105]*(E_R_gltBD)*(M_gln_L_c/(saturation_constant_array[105,119] + M_gln_L_c))*(M_akg_c/(saturation_constant_array[105,22] + M_akg_c))*(M_nadph_c/(saturation_constant_array[105,130] + M_nadph_c))*(M_h_c/(saturation_constant_array[105,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gdhA: M_akg_c+M_nadph_c+M_nh4_c+M_h_c = M_glu_L_c+M_h2o_c+M_nadp_c
tmp_reaction = rate_constant_array[106]*(E_R_gdhA)*(M_akg_c/(saturation_constant_array[106,22] + M_akg_c))*(M_nadph_c/(saturation_constant_array[106,130] + M_nadph_c))*(M_nh4_c/(saturation_constant_array[106,123] + M_nh4_c))*(M_h_c/(saturation_constant_array[106,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_glnA: M_glu_L_c+M_atp_c+M_nh4_c = M_gln_L_c+M_h_c+M_adp_c+M_pi_c
tmp_reaction = rate_constant_array[107]*(E_R_glnA)*(M_glu_L_c/(saturation_constant_array[107,118] + M_glu_L_c))*(M_atp_c/(saturation_constant_array[107,88] + M_atp_c))*(M_nh4_c/(saturation_constant_array[107,123] + M_nh4_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_glyA: M_ser_L_c+M_thf_c = M_gly_L_c+M_h2o_c+M_mlthf_c
tmp_reaction = rate_constant_array[108]*(E_R_glyA)*(M_ser_L_c/(saturation_constant_array[108,111] + M_ser_L_c))*(M_thf_c/(saturation_constant_array[108,39] + M_thf_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_his: M_gln_L_c+M_r5p_c+3*M_atp_c+2*M_nad_c+3*M_h2o_c = M_his_L_c+M_akg_c+M_aicar_c+2*M_adp_c+2*M_nadh_c+M_pi_c+2*M_ppi_c+6*M_h_c
tmp_reaction = rate_constant_array[109]*(E_R_his)*(M_gln_L_c/(saturation_constant_array[109,119] + M_gln_L_c))*(M_r5p_c/(saturation_constant_array[109,16] + M_r5p_c))*(M_atp_c/(saturation_constant_array[109,88] + M_atp_c))*(M_nad_c/(saturation_constant_array[109,127] + M_nad_c))*(M_h2o_c/(saturation_constant_array[109,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ile: M_thr_L_c+2*M_h_c+M_pyr_c+M_nadph_c+M_glu_L_c = M_ile_L_c+M_h2o_c+M_nh4_c+M_co2_c+M_nadp_c+M_akg_c
tmp_reaction = rate_constant_array[110]*(E_R_ile)*(M_thr_L_c/(saturation_constant_array[110,112] + M_thr_L_c))*(M_h_c/(saturation_constant_array[110,125] + M_h_c))*(M_pyr_c/(saturation_constant_array[110,84] + M_pyr_c))*(M_nadph_c/(saturation_constant_array[110,130] + M_nadph_c))*(M_glu_L_c/(saturation_constant_array[110,118] + M_glu_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_leu: 2*M_pyr_c+M_glu_L_c+M_h_c+M_nad_c+M_nadph_c+M_accoa_c = M_leu_L_c+2*M_co2_c+M_nadp_c+M_coa_c+M_nadh_c+M_akg_c
tmp_reaction = rate_constant_array[111]*(E_R_leu)*(M_pyr_c/(saturation_constant_array[111,84] + M_pyr_c))*(M_glu_L_c/(saturation_constant_array[111,118] + M_glu_L_c))*(M_h_c/(saturation_constant_array[111,125] + M_h_c))*(M_nad_c/(saturation_constant_array[111,127] + M_nad_c))*(M_nadph_c/(saturation_constant_array[111,130] + M_nadph_c))*(M_accoa_c/(saturation_constant_array[111,11] + M_accoa_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_lys: M_asp_L_c+M_atp_c+2*M_nadph_c+2*M_h_c+M_pyr_c+M_succoa_c+M_glu_L_c = M_lys_L_c+M_adp_c+M_pi_c+2*M_nadp_c+M_coa_c+M_akg_c+M_succ_c+M_co2_c
tmp_reaction = rate_constant_array[112]*(E_R_lys)*(M_asp_L_c/(saturation_constant_array[112,101] + M_asp_L_c))*(M_atp_c/(saturation_constant_array[112,88] + M_atp_c))*(M_nadph_c/(saturation_constant_array[112,130] + M_nadph_c))*(M_h_c/(saturation_constant_array[112,125] + M_h_c))*(M_pyr_c/(saturation_constant_array[112,84] + M_pyr_c))*(M_succoa_c/(saturation_constant_array[112,23] + M_succoa_c))*(M_glu_L_c/(saturation_constant_array[112,118] + M_glu_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_met: M_asp_L_c+M_cys_L_c+M_succoa_c+M_atp_c+2*M_nadph_c+M_5mthf_c = M_met_L_c+M_coa_c+M_succ_c+M_adp_c+M_pi_c+2*M_nadp_c+M_thf_c+M_nh4_c+M_pyr_c
tmp_reaction = rate_constant_array[113]*(E_R_met)*(M_asp_L_c/(saturation_constant_array[113,101] + M_asp_L_c))*(M_cys_L_c/(saturation_constant_array[113,105] + M_cys_L_c))*(M_succoa_c/(saturation_constant_array[113,23] + M_succoa_c))*(M_atp_c/(saturation_constant_array[113,88] + M_atp_c))*(M_nadph_c/(saturation_constant_array[113,130] + M_nadph_c))*(M_5mthf_c/(saturation_constant_array[113,46] + M_5mthf_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_phe: M_chor_c+M_h_c+M_glu_L_c = M_phe_L_c+M_co2_c+M_h2o_c+M_akg_c
tmp_reaction = rate_constant_array[114]*(E_R_phe)*(M_chor_c/(saturation_constant_array[114,35] + M_chor_c))*(M_h_c/(saturation_constant_array[114,125] + M_h_c))*(M_glu_L_c/(saturation_constant_array[114,118] + M_glu_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pro: M_glu_L_c+M_atp_c+2*M_h_c+2*M_nadph_c = M_pro_L_c+M_adp_c+2*M_nadp_c+M_pi_c+M_h2o_c
tmp_reaction = rate_constant_array[115]*(E_R_pro)*(M_glu_L_c/(saturation_constant_array[115,118] + M_glu_L_c))*(M_atp_c/(saturation_constant_array[115,88] + M_atp_c))*(M_h_c/(saturation_constant_array[115,125] + M_h_c))*(M_nadph_c/(saturation_constant_array[115,130] + M_nadph_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_serABC: M_3pg_c+M_nad_c+M_glu_L_c+M_h2o_c = M_ser_L_c+M_nadh_c+M_h_c+M_akg_c+M_pi_c
tmp_reaction = rate_constant_array[116]*(E_R_serABC)*(M_3pg_c/(saturation_constant_array[116,7] + M_3pg_c))*(M_nad_c/(saturation_constant_array[116,127] + M_nad_c))*(M_glu_L_c/(saturation_constant_array[116,118] + M_glu_L_c))*(M_h2o_c/(saturation_constant_array[116,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_thr: M_asp_L_c+2*M_atp_c+2*M_nadph_c+M_h_c+M_h2o_c = M_thr_L_c+2*M_adp_c+2*M_pi_c+2*M_nadp_c
tmp_reaction = rate_constant_array[117]*(E_R_thr)*(M_asp_L_c/(saturation_constant_array[117,101] + M_asp_L_c))*(M_atp_c/(saturation_constant_array[117,88] + M_atp_c))*(M_nadph_c/(saturation_constant_array[117,130] + M_nadph_c))*(M_h_c/(saturation_constant_array[117,125] + M_h_c))*(M_h2o_c/(saturation_constant_array[117,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_trp: M_chor_c+M_gln_L_c+M_ser_L_c+M_r5p_c+2*M_atp_c = M_trp_L_c+M_glu_L_c+M_pyr_c+M_ppi_c+2*M_h2o_c+M_co2_c+M_g3p_c+2*M_adp_c+M_h_c
tmp_reaction = rate_constant_array[118]*(E_R_trp)*(M_chor_c/(saturation_constant_array[118,35] + M_chor_c))*(M_gln_L_c/(saturation_constant_array[118,119] + M_gln_L_c))*(M_ser_L_c/(saturation_constant_array[118,111] + M_ser_L_c))*(M_r5p_c/(saturation_constant_array[118,16] + M_r5p_c))*(M_atp_c/(saturation_constant_array[118,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_tyr: M_chor_c+M_glu_L_c+M_nad_c = M_tyr_L_c+M_akg_c+M_nadh_c+M_co2_c
tmp_reaction = rate_constant_array[119]*(E_R_tyr)*(M_chor_c/(saturation_constant_array[119,35] + M_chor_c))*(M_glu_L_c/(saturation_constant_array[119,118] + M_glu_L_c))*(M_nad_c/(saturation_constant_array[119,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_val: 2*M_pyr_c+2*M_h_c+M_nadph_c+M_glu_L_c = M_val_L_c+M_co2_c+M_nadp_c+M_h2o_c+M_akg_c
tmp_reaction = rate_constant_array[120]*(E_R_val)*(M_pyr_c/(saturation_constant_array[120,84] + M_pyr_c))*(M_h_c/(saturation_constant_array[120,125] + M_h_c))*(M_nadph_c/(saturation_constant_array[120,130] + M_nadph_c))*(M_glu_L_c/(saturation_constant_array[120,118] + M_glu_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_arg_deg1: M_arg_L_c+5.0*M_h2o_c+M_atp_c+M_o2_c+2.0*M_nad_c+M_akg_c = 4.0*M_h_c+M_co2_c+M_urea_c+M_glu_L_c+M_pi_c+M_adp_c+M_nh4_c+M_h2o2_c+2.0*M_nadh_c+M_succ_c
tmp_reaction = rate_constant_array[121]*(E_R_arg_deg1)*(M_arg_L_c/(saturation_constant_array[121,43] + M_arg_L_c))*(M_h2o_c/(saturation_constant_array[121,126] + M_h2o_c))*(M_atp_c/(saturation_constant_array[121,88] + M_atp_c))*(M_o2_c/(saturation_constant_array[121,120] + M_o2_c))*(M_nad_c/(saturation_constant_array[121,127] + M_nad_c))*(M_akg_c/(saturation_constant_array[121,22] + M_akg_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_arg_deg2: M_arg_L_c+5.0*M_h2o_c+M_atp_c+M_o2_c+M_nad_c+M_nadp_c+M_akg_c = 4.0*M_h_c+M_co2_c+M_urea_c+M_glu_L_c+M_pi_c+M_adp_c+M_nh4_c+M_h2o2_c+M_nadh_c+M_nadph_c+M_succ_c
tmp_reaction = rate_constant_array[122]*(E_R_arg_deg2)*(M_arg_L_c/(saturation_constant_array[122,43] + M_arg_L_c))*(M_h2o_c/(saturation_constant_array[122,126] + M_h2o_c))*(M_atp_c/(saturation_constant_array[122,88] + M_atp_c))*(M_o2_c/(saturation_constant_array[122,120] + M_o2_c))*(M_nad_c/(saturation_constant_array[122,127] + M_nad_c))*(M_nadp_c/(saturation_constant_array[122,129] + M_nadp_c))*(M_akg_c/(saturation_constant_array[122,22] + M_akg_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_arg_deg3: M_arg_L_c+5.0*M_h2o_c+M_atp_c+M_o2_c+2.0*M_nadp_c+M_akg_c = 4.0*M_h_c+M_co2_c+M_urea_c+M_glu_L_c+M_pi_c+M_adp_c+M_nh4_c+M_h2o2_c+2.0*M_nadph_c+M_succ_c
tmp_reaction = rate_constant_array[123]*(E_R_arg_deg3)*(M_arg_L_c/(saturation_constant_array[123,43] + M_arg_L_c))*(M_h2o_c/(saturation_constant_array[123,126] + M_h2o_c))*(M_atp_c/(saturation_constant_array[123,88] + M_atp_c))*(M_o2_c/(saturation_constant_array[123,120] + M_o2_c))*(M_nadp_c/(saturation_constant_array[123,129] + M_nadp_c))*(M_akg_c/(saturation_constant_array[123,22] + M_akg_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_arg_deg4: M_arg_L_c+3.0*M_h2o_c+2.0*M_akg_c+2.0*M_nad_c = 3.0*M_h_c+M_co2_c+M_urea_c+2.0*M_glu_L_c+2.0*M_nadh_c+M_succ_c
tmp_reaction = rate_constant_array[124]*(E_R_arg_deg4)*(M_arg_L_c/(saturation_constant_array[124,43] + M_arg_L_c))*(M_h2o_c/(saturation_constant_array[124,126] + M_h2o_c))*(M_akg_c/(saturation_constant_array[124,22] + M_akg_c))*(M_nad_c/(saturation_constant_array[124,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_arg_deg5: M_arg_L_c+3.0*M_h2o_c+2.0*M_akg_c+M_nad_c+M_nadp_c = 3.0*M_h_c+M_co2_c+M_urea_c+2.0*M_glu_L_c+M_nadh_c+M_nadph_c+M_succ_c
tmp_reaction = rate_constant_array[125]*(E_R_arg_deg5)*(M_arg_L_c/(saturation_constant_array[125,43] + M_arg_L_c))*(M_h2o_c/(saturation_constant_array[125,126] + M_h2o_c))*(M_akg_c/(saturation_constant_array[125,22] + M_akg_c))*(M_nad_c/(saturation_constant_array[125,127] + M_nad_c))*(M_nadp_c/(saturation_constant_array[125,129] + M_nadp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_arg_deg6: M_arg_L_c+M_accoa_c+4.0*M_h2o_c+M_akg_c+M_nad_c = M_coa_c+M_h_c+M_co2_c+2.0*M_nh4_c+2.0*M_glu_L_c+M_nadh_c+M_succ_c
tmp_reaction = rate_constant_array[126]*(E_R_arg_deg6)*(M_arg_L_c/(saturation_constant_array[126,43] + M_arg_L_c))*(M_accoa_c/(saturation_constant_array[126,11] + M_accoa_c))*(M_h2o_c/(saturation_constant_array[126,126] + M_h2o_c))*(M_akg_c/(saturation_constant_array[126,22] + M_akg_c))*(M_nad_c/(saturation_constant_array[126,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_thr_deg1: M_thr_L_c+M_nad_c+M_coa_c = M_nadh_c+M_h_c+M_accoa_c+M_gly_L_c
tmp_reaction = rate_constant_array[127]*(E_R_thr_deg1)*(M_thr_L_c/(saturation_constant_array[127,112] + M_thr_L_c))*(M_nad_c/(saturation_constant_array[127,127] + M_nad_c))*(M_coa_c/(saturation_constant_array[127,10] + M_coa_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gly_deg: M_gly_L_c+M_accoa_c+M_h_c+M_o2_c+M_h2o_c = M_coa_c+M_co2_c+M_h2o2_c+M_nh4_c+M_mglx_c
tmp_reaction = rate_constant_array[128]*(E_R_gly_deg)*(M_gly_L_c/(saturation_constant_array[128,102] + M_gly_L_c))*(M_accoa_c/(saturation_constant_array[128,11] + M_accoa_c))*(M_h_c/(saturation_constant_array[128,125] + M_h_c))*(M_o2_c/(saturation_constant_array[128,120] + M_o2_c))*(M_h2o_c/(saturation_constant_array[128,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_thr_deg2: M_thr_L_c+M_nad_c+M_o2_c+M_h2o_c = M_nadh_c+M_co2_c+M_h2o2_c+M_nh4_c+M_mglx_c
tmp_reaction = rate_constant_array[129]*(E_R_thr_deg2)*(M_thr_L_c/(saturation_constant_array[129,112] + M_thr_L_c))*(M_nad_c/(saturation_constant_array[129,127] + M_nad_c))*(M_o2_c/(saturation_constant_array[129,120] + M_o2_c))*(M_h2o_c/(saturation_constant_array[129,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_thr_deg3: M_thr_L_c+M_coa_c+M_nad_c = M_gly_L_c+M_accoa_c+M_nadh_c+M_h_c
tmp_reaction = rate_constant_array[130]*(E_R_thr_deg3)*(M_thr_L_c/(saturation_constant_array[130,112] + M_thr_L_c))*(M_coa_c/(saturation_constant_array[130,10] + M_coa_c))*(M_nad_c/(saturation_constant_array[130,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_thr_deg4: M_thr_L_c+M_pi_c+M_adp_c = M_h_c+M_h2o_c+M_for_c+M_atp_c+M_prop_c
tmp_reaction = rate_constant_array[131]*(E_R_thr_deg4)*(M_thr_L_c/(saturation_constant_array[131,112] + M_thr_L_c))*(M_pi_c/(saturation_constant_array[131,122] + M_pi_c))*(M_adp_c/(saturation_constant_array[131,89] + M_adp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_thr_deg5: M_thr_L_c+M_h_c+M_pyr_c+M_nadph_c+M_glu_L_c = 2.0*M_h2o_c+M_co2_c+M_nadp_c+M_akg_c+M_ile_L_c
tmp_reaction = rate_constant_array[132]*(E_R_thr_deg5)*(M_thr_L_c/(saturation_constant_array[132,112] + M_thr_L_c))*(M_h_c/(saturation_constant_array[132,125] + M_h_c))*(M_pyr_c/(saturation_constant_array[132,84] + M_pyr_c))*(M_nadph_c/(saturation_constant_array[132,130] + M_nadph_c))*(M_glu_L_c/(saturation_constant_array[132,118] + M_glu_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_mglx_deg: M_mglx_c+M_nadp_c+M_h2o_c = M_pyr_c+M_nadph_c+M_h_c
tmp_reaction = rate_constant_array[133]*(E_R_mglx_deg)*(M_mglx_c/(saturation_constant_array[133,49] + M_mglx_c))*(M_nadp_c/(saturation_constant_array[133,129] + M_nadp_c))*(M_h2o_c/(saturation_constant_array[133,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_mglx_deg_R: M_pyr_c+M_nadph_c+M_h_c = M_mglx_c+M_nadp_c+M_h2o_c
tmp_reaction = rate_constant_array[134]*(E_R_mglx_deg_R)*(M_pyr_c/(saturation_constant_array[134,84] + M_pyr_c))*(M_nadph_c/(saturation_constant_array[134,130] + M_nadph_c))*(M_h_c/(saturation_constant_array[134,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ser_deg: M_ser_L_c = M_nh4_c+M_pyr_c
tmp_reaction = rate_constant_array[135]*(E_R_ser_deg)*(M_ser_L_c/(saturation_constant_array[135,111] + M_ser_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_pro_deg: M_pro_L_c+M_q8_c+2.0*M_h2o_c+M_nad_c = 2.0*M_h_c+M_q8h2_c+M_nadh_c+M_glu_L_c
tmp_reaction = rate_constant_array[136]*(E_R_pro_deg)*(M_pro_L_c/(saturation_constant_array[136,110] + M_pro_L_c))*(M_q8_c/(saturation_constant_array[136,24] + M_q8_c))*(M_h2o_c/(saturation_constant_array[136,126] + M_h2o_c))*(M_nad_c/(saturation_constant_array[136,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_trp_deg: M_trp_L_c+M_h2o_c = M_indole_c+M_nh4_c+M_pyr_c
tmp_reaction = rate_constant_array[137]*(E_R_trp_deg)*(M_trp_L_c/(saturation_constant_array[137,113] + M_trp_L_c))*(M_h2o_c/(saturation_constant_array[137,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_cys_deg: M_cys_L_c+M_h2o_c = M_h2s_c+M_nh4_c+M_pyr_c
tmp_reaction = rate_constant_array[138]*(E_R_cys_deg)*(M_cys_L_c/(saturation_constant_array[138,105] + M_cys_L_c))*(M_h2o_c/(saturation_constant_array[138,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ala_deg: M_ala_L_c+M_h2o_c+M_q8_c = M_q8h2_c+M_nh4_c+M_pyr_c
tmp_reaction = rate_constant_array[139]*(E_R_ala_deg)*(M_ala_L_c/(saturation_constant_array[139,108] + M_ala_L_c))*(M_h2o_c/(saturation_constant_array[139,126] + M_h2o_c))*(M_q8_c/(saturation_constant_array[139,24] + M_q8_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_lys_deg: M_lys_L_c = M_co2_c+M_cadav_c
tmp_reaction = rate_constant_array[140]*(E_R_lys_deg)*(M_lys_L_c/(saturation_constant_array[140,106] + M_lys_L_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gln_deg: M_gln_L_c+M_h2o_c = M_nh4_c+M_glu_L_c
tmp_reaction = rate_constant_array[141]*(E_R_gln_deg)*(M_gln_L_c/(saturation_constant_array[141,119] + M_gln_L_c))*(M_h2o_c/(saturation_constant_array[141,126] + M_h2o_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_glu_deg: M_glu_L_c+M_h_c = M_co2_c+M_gaba_c
tmp_reaction = rate_constant_array[142]*(E_R_glu_deg)*(M_glu_L_c/(saturation_constant_array[142,118] + M_glu_L_c))*(M_h_c/(saturation_constant_array[142,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gaba_deg1: M_gaba_c+M_akg_c+M_h2o_c+M_nad_c = M_succ_c+M_glu_L_c+2*M_h_c+M_nadh_c
tmp_reaction = rate_constant_array[143]*(E_R_gaba_deg1)*(M_gaba_c/(saturation_constant_array[143,53] + M_gaba_c))*(M_akg_c/(saturation_constant_array[143,22] + M_akg_c))*(M_h2o_c/(saturation_constant_array[143,126] + M_h2o_c))*(M_nad_c/(saturation_constant_array[143,127] + M_nad_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gaba_deg2: M_gaba_c+M_akg_c+M_h2o_c+M_nadp_c = M_succ_c+M_glu_L_c+2*M_h_c+M_nadph_c
tmp_reaction = rate_constant_array[144]*(E_R_gaba_deg2)*(M_gaba_c/(saturation_constant_array[144,53] + M_gaba_c))*(M_akg_c/(saturation_constant_array[144,22] + M_akg_c))*(M_h2o_c/(saturation_constant_array[144,126] + M_h2o_c))*(M_nadp_c/(saturation_constant_array[144,129] + M_nadp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_asn_deg: M_asn_L_c+M_h2o_c+M_adp_c+M_pi_c = M_nh4_c+M_asp_L_c+M_atp_c
tmp_reaction = rate_constant_array[145]*(E_R_asn_deg)*(M_asn_L_c/(saturation_constant_array[145,104] + M_asn_L_c))*(M_h2o_c/(saturation_constant_array[145,126] + M_h2o_c))*(M_adp_c/(saturation_constant_array[145,89] + M_adp_c))*(M_pi_c/(saturation_constant_array[145,122] + M_pi_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Ex_1: [] = M_o2_c
tmp_reaction = rate_constant_array[146]*(E_Ex_1);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Ex_2: [] = M_co2_c
tmp_reaction = rate_constant_array[147]*(E_Ex_2);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Ex_3: [] = M_pi_c
tmp_reaction = rate_constant_array[148]*(E_Ex_3);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Ex_4: [] = M_nh4_c
tmp_reaction = rate_constant_array[149]*(E_Ex_4);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Ex_5: [] = M_so4_c
tmp_reaction = rate_constant_array[150]*(E_Ex_5);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# ATP_deg: M_atp_c = []
tmp_reaction = rate_constant_array[151]*(E_ATP_deg)*(M_atp_c/(saturation_constant_array[151,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# GTP_deg: M_gtp_c = []
tmp_reaction = rate_constant_array[152]*(E_GTP_deg)*(M_gtp_c/(saturation_constant_array[152,91] + M_gtp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# CTP_deg: M_ctp_c = []
tmp_reaction = rate_constant_array[153]*(E_CTP_deg)*(M_ctp_c/(saturation_constant_array[153,97] + M_ctp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# UTP_deg: M_utp_c = []
tmp_reaction = rate_constant_array[154]*(E_UTP_deg)*(M_utp_c/(saturation_constant_array[154,94] + M_utp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_amp_ppi: M_amp_c+M_ppi_c+4*M_h_c = M_atp_c+M_h2o_c
tmp_reaction = rate_constant_array[155]*(E_R_amp_ppi)*(M_amp_c/(saturation_constant_array[155,90] + M_amp_c))*(M_ppi_c/(saturation_constant_array[155,31] + M_ppi_c))*(M_h_c/(saturation_constant_array[155,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_amp_pi: M_amp_c+2*M_pi_c+6*M_h_c = M_atp_c+2*M_h2o_c
tmp_reaction = rate_constant_array[156]*(E_R_amp_pi)*(M_amp_c/(saturation_constant_array[156,90] + M_amp_c))*(M_pi_c/(saturation_constant_array[156,122] + M_pi_c))*(M_h_c/(saturation_constant_array[156,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gmp_ppi: M_gmp_c+M_ppi_c+4*M_h_c = M_gtp_c+M_h2o_c
tmp_reaction = rate_constant_array[157]*(E_R_gmp_ppi)*(M_gmp_c/(saturation_constant_array[157,93] + M_gmp_c))*(M_ppi_c/(saturation_constant_array[157,31] + M_ppi_c))*(M_h_c/(saturation_constant_array[157,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_gmp_pi: M_gmp_c+2*M_pi_c+6*M_h_c = M_gtp_c+2*M_h2o_c
tmp_reaction = rate_constant_array[158]*(E_R_gmp_pi)*(M_gmp_c/(saturation_constant_array[158,93] + M_gmp_c))*(M_pi_c/(saturation_constant_array[158,122] + M_pi_c))*(M_h_c/(saturation_constant_array[158,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_cmp_ppi: M_cmp_c+M_ppi_c+4*M_h_c = M_ctp_c+M_h2o_c
tmp_reaction = rate_constant_array[159]*(E_R_cmp_ppi)*(M_cmp_c/(saturation_constant_array[159,99] + M_cmp_c))*(M_ppi_c/(saturation_constant_array[159,31] + M_ppi_c))*(M_h_c/(saturation_constant_array[159,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_cmp_pi: M_cmp_c+2*M_pi_c+6*M_h_c = M_ctp_c+2*M_h2o_c
tmp_reaction = rate_constant_array[160]*(E_R_cmp_pi)*(M_cmp_c/(saturation_constant_array[160,99] + M_cmp_c))*(M_pi_c/(saturation_constant_array[160,122] + M_pi_c))*(M_h_c/(saturation_constant_array[160,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ump_ppi: M_ump_c+M_ppi_c+4*M_h_c = M_utp_c+M_h2o_c
tmp_reaction = rate_constant_array[161]*(E_R_ump_ppi)*(M_ump_c/(saturation_constant_array[161,96] + M_ump_c))*(M_ppi_c/(saturation_constant_array[161,31] + M_ppi_c))*(M_h_c/(saturation_constant_array[161,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R_ump_pi: M_ump_c+2*M_pi_c+6*M_h_c = M_utp_c+2*M_h2o_c
tmp_reaction = rate_constant_array[162]*(E_R_ump_pi)*(M_ump_c/(saturation_constant_array[162,96] + M_ump_c))*(M_pi_c/(saturation_constant_array[162,122] + M_pi_c))*(M_h_c/(saturation_constant_array[162,125] + M_h_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# transcriptional_initiation_CAT: GENE_CAT+RNAP = OPEN_GENE_CAT
tmp_reaction = rate_constant_array[163]*(E_transcriptional_initiation_CAT)*(GENE_CAT/(saturation_constant_array[163,54] + GENE_CAT))*(RNAP/(saturation_constant_array[163,55] + RNAP));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# transcription_CAT: OPEN_GENE_CAT+151*M_gtp_c+144*M_ctp_c+189*M_utp_c+176*M_atp_c = mRNA_CAT+GENE_CAT+RNAP+1320*M_pi_c
tmp_reaction = rate_constant_array[164]*(E_transcription_CAT)*(OPEN_GENE_CAT/(saturation_constant_array[164,56] + OPEN_GENE_CAT))*(M_gtp_c/(saturation_constant_array[164,91] + M_gtp_c))*(M_ctp_c/(saturation_constant_array[164,97] + M_ctp_c))*(M_utp_c/(saturation_constant_array[164,94] + M_utp_c))*(M_atp_c/(saturation_constant_array[164,88] + M_atp_c));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# mRNA_degradation_CAT: mRNA_CAT = 151*M_gmp_c+144*M_cmp_c+189*M_ump_c+176*M_amp_c
tmp_reaction = rate_constant_array[165]*(E_mRNA_degradation_CAT)*(mRNA_CAT/(saturation_constant_array[165,57] + mRNA_CAT));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# translation_initiation_CAT: mRNA_CAT+RIBOSOME = RIBOSOME_START_CAT
tmp_reaction = rate_constant_array[166]*(E_translation_initiation_CAT)*(mRNA_CAT/(saturation_constant_array[166,57] + mRNA_CAT))*(RIBOSOME/(saturation_constant_array[166,58] + RIBOSOME));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# translation_CAT: RIBOSOME_START_CAT+438*M_gtp_c+15.0*M_ala_L_c_tRNA+5.0*M_arg_L_c_tRNA+10.0*M_asn_L_c_tRNA+12.0*M_asp_L_c_tRNA+5.0*M_cys_L_c_tRNA+12.0*M_glu_L_c_tRNA+13.0*M_gln_L_c_tRNA+10.0*M_gly_L_c_tRNA+12.0*M_his_L_c_tRNA+9.0*M_ile_L_c_tRNA+13.0*M_leu_L_c_tRNA+12.0*M_lys_L_c_tRNA+9.0*M_met_L_c_tRNA+20.0*M_phe_L_c_tRNA+7.0*M_pro_L_c_tRNA+10.0*M_ser_L_c_tRNA+13.0*M_thr_L_c_tRNA+5.0*M_trp_L_c_tRNA+11.0*M_tyr_L_c_tRNA+16.0*M_val_L_c_tRNA = RIBOSOME+mRNA_CAT+PROTEIN_CAT+438*M_gdp_c+438*M_pi_c+219*tRNA
tmp_reaction = rate_constant_array[167]*(E_translation_CAT)*(RIBOSOME_START_CAT/(saturation_constant_array[167,59] + RIBOSOME_START_CAT))*(M_gtp_c/(saturation_constant_array[167,91] + M_gtp_c))*(M_ala_L_c_tRNA/(saturation_constant_array[167,60] + M_ala_L_c_tRNA))*(M_arg_L_c_tRNA/(saturation_constant_array[167,61] + M_arg_L_c_tRNA))*(M_asn_L_c_tRNA/(saturation_constant_array[167,62] + M_asn_L_c_tRNA))*(M_asp_L_c_tRNA/(saturation_constant_array[167,63] + M_asp_L_c_tRNA))*(M_cys_L_c_tRNA/(saturation_constant_array[167,64] + M_cys_L_c_tRNA))*(M_glu_L_c_tRNA/(saturation_constant_array[167,65] + M_glu_L_c_tRNA))*(M_gln_L_c_tRNA/(saturation_constant_array[167,66] + M_gln_L_c_tRNA))*(M_gly_L_c_tRNA/(saturation_constant_array[167,67] + M_gly_L_c_tRNA))*(M_his_L_c_tRNA/(saturation_constant_array[167,68] + M_his_L_c_tRNA))*(M_ile_L_c_tRNA/(saturation_constant_array[167,69] + M_ile_L_c_tRNA))*(M_leu_L_c_tRNA/(saturation_constant_array[167,70] + M_leu_L_c_tRNA))*(M_lys_L_c_tRNA/(saturation_constant_array[167,71] + M_lys_L_c_tRNA))*(M_met_L_c_tRNA/(saturation_constant_array[167,72] + M_met_L_c_tRNA))*(M_phe_L_c_tRNA/(saturation_constant_array[167,73] + M_phe_L_c_tRNA))*(M_pro_L_c_tRNA/(saturation_constant_array[167,74] + M_pro_L_c_tRNA))*(M_ser_L_c_tRNA/(saturation_constant_array[167,75] + M_ser_L_c_tRNA))*(M_thr_L_c_tRNA/(saturation_constant_array[167,76] + M_thr_L_c_tRNA))*(M_trp_L_c_tRNA/(saturation_constant_array[167,77] + M_trp_L_c_tRNA))*(M_tyr_L_c_tRNA/(saturation_constant_array[167,78] + M_tyr_L_c_tRNA))*(M_val_L_c_tRNA/(saturation_constant_array[167,79] + M_val_L_c_tRNA));
push!(rate_vector,tmp_reaction);

#if (t > .99 && t < 1.01)
#    println("t: ",t)
#    println("k: ",rate_constant_array[167])
#    println("E: ",E_translation_CAT)
#    println("RIBOSOME: ",(RIBOSOME_START_CAT/(saturation_constant_array[167,59] + RIBOSOME_START_CAT)))
#    println("438*gtp: ",(M_gtp_c/(saturation_constant_array[167,91] + M_gtp_c)))
#    println("15.0*ala: ",saturation_constant_array[167,60])
#    println("5.0*arg: ",saturation_constant_array[167,61])
#    println("10.0*asn: ",saturation_constant_array[167,62])
#    println("12.0*asp: ",(M_asp_L_c_tRNA/(saturation_constant_array[167,63] + M_asp_L_c_tRNA)))
#    println("5.0*cys: ",(M_cys_L_c_tRNA/(saturation_constant_array[167,64] + M_cys_L_c_tRNA)))
#    println("12.0*glu: ",(M_glu_L_c_tRNA/(saturation_constant_array[167,65] + M_glu_L_c_tRNA)))
#    println("13.0*gln: ",(M_gln_L_c_tRNA/(saturation_constant_array[167,66] + M_gln_L_c_tRNA)))
#    println("10.0*gly: ",(M_gly_L_c_tRNA/(saturation_constant_array[167,67] + M_gly_L_c_tRNA)))
#    println("12.0*his: ",(M_his_L_c_tRNA/(saturation_constant_array[167,68] + M_his_L_c_tRNA)))
#    println("9.0*ile: ",(M_ile_L_c_tRNA/(saturation_constant_array[167,69] + M_ile_L_c_tRNA)))
#    println("13.0*leu: ",(M_leu_L_c_tRNA/(saturation_constant_array[167,70] + M_leu_L_c_tRNA)))
#    println("12.0*lys: ",(M_lys_L_c_tRNA/(saturation_constant_array[167,71] + M_lys_L_c_tRNA)))
#    println("9.0*met: ",(M_met_L_c_tRNA/(saturation_constant_array[167,72] + M_met_L_c_tRNA)))
#    println("20.0*phe: ",(M_phe_L_c_tRNA/(saturation_constant_array[167,73] + M_phe_L_c_tRNA)))
#    println("7.0*pro: ",(M_pro_L_c_tRNA/(saturation_constant_array[167,74] + M_pro_L_c_tRNA)))
#    println("10.0*ser: ",(M_ser_L_c_tRNA/(saturation_constant_array[167,75] + M_ser_L_c_tRNA)))
#    println("13.0*thr: ",(M_thr_L_c_tRNA/(saturation_constant_array[167,76] + M_thr_L_c_tRNA)))
#    println("5.0*trp: ",(M_trp_L_c_tRNA/(saturation_constant_array[167,77] + M_trp_L_c_tRNA)))
#    println("11.0*tyr: ",(M_tyr_L_c_tRNA/(saturation_constant_array[167,78] + M_tyr_L_c_tRNA)))
#    println("16.0*val: ",(M_val_L_c_tRNA/(saturation_constant_array[167,79] + M_val_L_c_tRNA)))
#    println("Rate: ",tmp_reaction)
#end

tmp_reaction = 0;

# tRNA_charging_M_ala_L_c_CAT: 15.0*M_ala_L_c+15.0*M_atp_c+15.0*tRNA = 15.0*M_ala_L_c_tRNA+15.0*M_amp_c+30.0*M_pi_c
tmp_reaction = rate_constant_array[168]*(E_tRNA_charging_M_ala_L_c_CAT)*(M_ala_L_c/(saturation_constant_array[168,108] + M_ala_L_c))*(M_atp_c/(saturation_constant_array[168,88] + M_atp_c))*(tRNA/(saturation_constant_array[168,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_arg_L_c_CAT: 5.0*M_arg_L_c+5.0*M_atp_c+5.0*tRNA = 5.0*M_arg_L_c_tRNA+5.0*M_amp_c+10.0*M_pi_c
tmp_reaction = rate_constant_array[169]*(E_tRNA_charging_M_arg_L_c_CAT)*(M_arg_L_c/(saturation_constant_array[169,43] + M_arg_L_c))*(M_atp_c/(saturation_constant_array[169,88] + M_atp_c))*(tRNA/(saturation_constant_array[169,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_asn_L_c_CAT: 10.0*M_asn_L_c+10.0*M_atp_c+10.0*tRNA = 10.0*M_asn_L_c_tRNA+10.0*M_amp_c+20.0*M_pi_c
tmp_reaction = rate_constant_array[170]*(E_tRNA_charging_M_asn_L_c_CAT)*(M_asn_L_c/(saturation_constant_array[170,104] + M_asn_L_c))*(M_atp_c/(saturation_constant_array[170,88] + M_atp_c))*(tRNA/(saturation_constant_array[170,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_asp_L_c_CAT: 12.0*M_asp_L_c+12.0*M_atp_c+12.0*tRNA = 12.0*M_asp_L_c_tRNA+12.0*M_amp_c+24.0*M_pi_c
tmp_reaction = rate_constant_array[171]*(E_tRNA_charging_M_asp_L_c_CAT)*(M_asp_L_c/(saturation_constant_array[171,101] + M_asp_L_c))*(M_atp_c/(saturation_constant_array[171,88] + M_atp_c))*(tRNA/(saturation_constant_array[171,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_cys_L_c_CAT: 5.0*M_cys_L_c+5.0*M_atp_c+5.0*tRNA = 5.0*M_cys_L_c_tRNA+5.0*M_amp_c+10.0*M_pi_c
tmp_reaction = rate_constant_array[172]*(E_tRNA_charging_M_cys_L_c_CAT)*(M_cys_L_c/(saturation_constant_array[172,105] + M_cys_L_c))*(M_atp_c/(saturation_constant_array[172,88] + M_atp_c))*(tRNA/(saturation_constant_array[172,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_glu_L_c_CAT: 12.0*M_glu_L_c+12.0*M_atp_c+12.0*tRNA = 12.0*M_glu_L_c_tRNA+12.0*M_amp_c+24.0*M_pi_c
tmp_reaction = rate_constant_array[173]*(E_tRNA_charging_M_glu_L_c_CAT)*(M_glu_L_c/(saturation_constant_array[173,118] + M_glu_L_c))*(M_atp_c/(saturation_constant_array[173,88] + M_atp_c))*(tRNA/(saturation_constant_array[173,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_gln_L_c_CAT: 13.0*M_gln_L_c+13.0*M_atp_c+13.0*tRNA = 13.0*M_gln_L_c_tRNA+13.0*M_amp_c+26.0*M_pi_c
tmp_reaction = rate_constant_array[174]*(E_tRNA_charging_M_gln_L_c_CAT)*(M_gln_L_c/(saturation_constant_array[174,119] + M_gln_L_c))*(M_atp_c/(saturation_constant_array[174,88] + M_atp_c))*(tRNA/(saturation_constant_array[174,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_gly_L_c_CAT: 10.0*M_gly_L_c+10.0*M_atp_c+10.0*tRNA = 10.0*M_gly_L_c_tRNA+10.0*M_amp_c+20.0*M_pi_c
tmp_reaction = rate_constant_array[175]*(E_tRNA_charging_M_gly_L_c_CAT)*(M_gly_L_c/(saturation_constant_array[175,102] + M_gly_L_c))*(M_atp_c/(saturation_constant_array[175,88] + M_atp_c))*(tRNA/(saturation_constant_array[175,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_his_L_c_CAT: 12.0*M_his_L_c+12.0*M_atp_c+12.0*tRNA = 12.0*M_his_L_c_tRNA+12.0*M_amp_c+24.0*M_pi_c
tmp_reaction = rate_constant_array[176]*(E_tRNA_charging_M_his_L_c_CAT)*(M_his_L_c/(saturation_constant_array[176,107] + M_his_L_c))*(M_atp_c/(saturation_constant_array[176,88] + M_atp_c))*(tRNA/(saturation_constant_array[176,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_ile_L_c_CAT: 9.0*M_ile_L_c+9.0*M_atp_c+9.0*tRNA = 9.0*M_ile_L_c_tRNA+9.0*M_amp_c+18.0*M_pi_c
tmp_reaction = rate_constant_array[177]*(E_tRNA_charging_M_ile_L_c_CAT)*(M_ile_L_c/(saturation_constant_array[177,103] + M_ile_L_c))*(M_atp_c/(saturation_constant_array[177,88] + M_atp_c))*(tRNA/(saturation_constant_array[177,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_leu_L_c_CAT: 13.0*M_leu_L_c+13.0*M_atp_c+13.0*tRNA = 13.0*M_leu_L_c_tRNA+13.0*M_amp_c+26.0*M_pi_c
tmp_reaction = rate_constant_array[178]*(E_tRNA_charging_M_leu_L_c_CAT)*(M_leu_L_c/(saturation_constant_array[178,117] + M_leu_L_c))*(M_atp_c/(saturation_constant_array[178,88] + M_atp_c))*(tRNA/(saturation_constant_array[178,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_lys_L_c_CAT: 12.0*M_lys_L_c+12.0*M_atp_c+12.0*tRNA = 12.0*M_lys_L_c_tRNA+12.0*M_amp_c+24.0*M_pi_c
tmp_reaction = rate_constant_array[179]*(E_tRNA_charging_M_lys_L_c_CAT)*(M_lys_L_c/(saturation_constant_array[179,106] + M_lys_L_c))*(M_atp_c/(saturation_constant_array[179,88] + M_atp_c))*(tRNA/(saturation_constant_array[179,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_met_L_c_CAT: 9.0*M_met_L_c+9.0*M_atp_c+9.0*tRNA = 9.0*M_met_L_c_tRNA+9.0*M_amp_c+18.0*M_pi_c
tmp_reaction = rate_constant_array[180]*(E_tRNA_charging_M_met_L_c_CAT)*(M_met_L_c/(saturation_constant_array[180,116] + M_met_L_c))*(M_atp_c/(saturation_constant_array[180,88] + M_atp_c))*(tRNA/(saturation_constant_array[180,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_phe_L_c_CAT: 20.0*M_phe_L_c+20.0*M_atp_c+20.0*tRNA = 20.0*M_phe_L_c_tRNA+20.0*M_amp_c+40.0*M_pi_c
tmp_reaction = rate_constant_array[181]*(E_tRNA_charging_M_phe_L_c_CAT)*(M_phe_L_c/(saturation_constant_array[181,109] + M_phe_L_c))*(M_atp_c/(saturation_constant_array[181,88] + M_atp_c))*(tRNA/(saturation_constant_array[181,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_pro_L_c_CAT: 7.0*M_pro_L_c+7.0*M_atp_c+7.0*tRNA = 7.0*M_pro_L_c_tRNA+7.0*M_amp_c+14.0*M_pi_c
tmp_reaction = rate_constant_array[182]*(E_tRNA_charging_M_pro_L_c_CAT)*(M_pro_L_c/(saturation_constant_array[182,110] + M_pro_L_c))*(M_atp_c/(saturation_constant_array[182,88] + M_atp_c))*(tRNA/(saturation_constant_array[182,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_ser_L_c_CAT: 10.0*M_ser_L_c+10.0*M_atp_c+10.0*tRNA = 10.0*M_ser_L_c_tRNA+10.0*M_amp_c+20.0*M_pi_c
tmp_reaction = rate_constant_array[183]*(E_tRNA_charging_M_ser_L_c_CAT)*(M_ser_L_c/(saturation_constant_array[183,111] + M_ser_L_c))*(M_atp_c/(saturation_constant_array[183,88] + M_atp_c))*(tRNA/(saturation_constant_array[183,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_thr_L_c_CAT: 13.0*M_thr_L_c+13.0*M_atp_c+13.0*tRNA = 13.0*M_thr_L_c_tRNA+13.0*M_amp_c+26.0*M_pi_c
tmp_reaction = rate_constant_array[184]*(E_tRNA_charging_M_thr_L_c_CAT)*(M_thr_L_c/(saturation_constant_array[184,112] + M_thr_L_c))*(M_atp_c/(saturation_constant_array[184,88] + M_atp_c))*(tRNA/(saturation_constant_array[184,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_trp_L_c_CAT: 5.0*M_trp_L_c+5.0*M_atp_c+5.0*tRNA = 5.0*M_trp_L_c_tRNA+5.0*M_amp_c+10.0*M_pi_c
tmp_reaction = rate_constant_array[185]*(E_tRNA_charging_M_trp_L_c_CAT)*(M_trp_L_c/(saturation_constant_array[185,113] + M_trp_L_c))*(M_atp_c/(saturation_constant_array[185,88] + M_atp_c))*(tRNA/(saturation_constant_array[185,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_tyr_L_c_CAT: 11.0*M_tyr_L_c+11.0*M_atp_c+11.0*tRNA = 11.0*M_tyr_L_c_tRNA+11.0*M_amp_c+22.0*M_pi_c
tmp_reaction = rate_constant_array[186]*(E_tRNA_charging_M_tyr_L_c_CAT)*(M_tyr_L_c/(saturation_constant_array[186,114] + M_tyr_L_c))*(M_atp_c/(saturation_constant_array[186,88] + M_atp_c))*(tRNA/(saturation_constant_array[186,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# tRNA_charging_M_val_L_c_CAT: 16.0*M_val_L_c+16.0*M_atp_c+16.0*tRNA = 16.0*M_val_L_c_tRNA+16.0*M_amp_c+32.0*M_pi_c
tmp_reaction = rate_constant_array[187]*(E_tRNA_charging_M_val_L_c_CAT)*(M_val_L_c/(saturation_constant_array[187,115] + M_val_L_c))*(M_atp_c/(saturation_constant_array[187,88] + M_atp_c))*(tRNA/(saturation_constant_array[187,81] + tRNA));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_PTS = []
tmp_reaction = rate_constant_array[188]*E_R_PTS;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_glk_atp = []
tmp_reaction = rate_constant_array[189]*E_R_glk_atp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_glk_utp = []
tmp_reaction = rate_constant_array[190]*E_R_glk_utp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_glk_ctp = []
tmp_reaction = rate_constant_array[191]*E_R_glk_ctp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_glk_gtp = []
tmp_reaction = rate_constant_array[192]*E_R_glk_gtp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pgi = []
tmp_reaction = rate_constant_array[193]*E_R_pgi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pgi_R = []
tmp_reaction = rate_constant_array[194]*E_R_pgi_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pfk = []
tmp_reaction = rate_constant_array[195]*E_R_pfk;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_fdp = []
tmp_reaction = rate_constant_array[196]*E_R_fdp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_fbaA = []
tmp_reaction = rate_constant_array[197]*E_R_fbaA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_fbaA_R = []
tmp_reaction = rate_constant_array[198]*E_R_fbaA_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_tpiA = []
tmp_reaction = rate_constant_array[199]*E_R_tpiA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_tpiA_R = []
tmp_reaction = rate_constant_array[200]*E_R_tpiA_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gapA = []
tmp_reaction = rate_constant_array[201]*E_R_gapA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gapA_R = []
tmp_reaction = rate_constant_array[202]*E_R_gapA_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pgk = []
tmp_reaction = rate_constant_array[203]*E_R_pgk;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pgk_R = []
tmp_reaction = rate_constant_array[204]*E_R_pgk_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gpm = []
tmp_reaction = rate_constant_array[205]*E_R_gpm;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gpm_R = []
tmp_reaction = rate_constant_array[206]*E_R_gpm_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_eno = []
tmp_reaction = rate_constant_array[207]*E_R_eno;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_eno_R = []
tmp_reaction = rate_constant_array[208]*E_R_eno_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pyk = []
tmp_reaction = rate_constant_array[209]*E_R_pyk;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pck = []
tmp_reaction = rate_constant_array[210]*E_R_pck;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ppc = []
tmp_reaction = rate_constant_array[211]*E_R_ppc;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pdh = []
tmp_reaction = rate_constant_array[212]*E_R_pdh;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pps = []
tmp_reaction = rate_constant_array[213]*E_R_pps;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_zwf = []
tmp_reaction = rate_constant_array[214]*E_R_zwf;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_zwf_R = []
tmp_reaction = rate_constant_array[215]*E_R_zwf_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pgl = []
tmp_reaction = rate_constant_array[216]*E_R_pgl;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gnd = []
tmp_reaction = rate_constant_array[217]*E_R_gnd;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_rpe = []
tmp_reaction = rate_constant_array[218]*E_R_rpe;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_rpe_R = []
tmp_reaction = rate_constant_array[219]*E_R_rpe_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_rpi = []
tmp_reaction = rate_constant_array[220]*E_R_rpi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_rpi_R = []
tmp_reaction = rate_constant_array[221]*E_R_rpi_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_talAB = []
tmp_reaction = rate_constant_array[222]*E_R_talAB;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_talAB_R = []
tmp_reaction = rate_constant_array[223]*E_R_talAB_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_tkt1 = []
tmp_reaction = rate_constant_array[224]*E_R_tkt1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_tkt1_R = []
tmp_reaction = rate_constant_array[225]*E_R_tkt1_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_tkt2 = []
tmp_reaction = rate_constant_array[226]*E_R_tkt2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_tkt2_R = []
tmp_reaction = rate_constant_array[227]*E_R_tkt2_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_edd = []
tmp_reaction = rate_constant_array[228]*E_R_edd;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_eda = []
tmp_reaction = rate_constant_array[229]*E_R_eda;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gltA = []
tmp_reaction = rate_constant_array[230]*E_R_gltA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_acn = []
tmp_reaction = rate_constant_array[231]*E_R_acn;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_acn_R = []
tmp_reaction = rate_constant_array[232]*E_R_acn_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_icd = []
tmp_reaction = rate_constant_array[233]*E_R_icd;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_icd_R = []
tmp_reaction = rate_constant_array[234]*E_R_icd_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_sucAB = []
tmp_reaction = rate_constant_array[235]*E_R_sucAB;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_sucCD = []
tmp_reaction = rate_constant_array[236]*E_R_sucCD;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_sucCD_R = []
tmp_reaction = rate_constant_array[237]*E_R_sucCD_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_sdh = []
tmp_reaction = rate_constant_array[238]*E_R_sdh;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_frd = []
tmp_reaction = rate_constant_array[239]*E_R_frd;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_fum = []
tmp_reaction = rate_constant_array[240]*E_R_fum;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_fum_R = []
tmp_reaction = rate_constant_array[241]*E_R_fum_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_mdh = []
tmp_reaction = rate_constant_array[242]*E_R_mdh;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_mdh_R = []
tmp_reaction = rate_constant_array[243]*E_R_mdh_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_aceA = []
tmp_reaction = rate_constant_array[244]*E_R_aceA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_aceB = []
tmp_reaction = rate_constant_array[245]*E_R_aceB;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_maeA = []
tmp_reaction = rate_constant_array[246]*E_R_maeA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_maeB = []
tmp_reaction = rate_constant_array[247]*E_R_maeB;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pta = []
tmp_reaction = rate_constant_array[248]*E_R_pta;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pta_R = []
tmp_reaction = rate_constant_array[249]*E_R_pta_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ackA = []
tmp_reaction = rate_constant_array[250]*E_R_ackA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ackA_R = []
tmp_reaction = rate_constant_array[251]*E_R_ackA_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_acs = []
tmp_reaction = rate_constant_array[252]*E_R_acs;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_adhE = []
tmp_reaction = rate_constant_array[253]*E_R_adhE;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_adhE_R = []
tmp_reaction = rate_constant_array[254]*E_R_adhE_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ldh_f = []
tmp_reaction = rate_constant_array[255]*E_R_ldh_f;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ldh_r = []
tmp_reaction = rate_constant_array[256]*E_R_ldh_r;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pflAB = []
tmp_reaction = rate_constant_array[257]*E_R_pflAB;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_cyd = []
tmp_reaction = rate_constant_array[258]*E_R_cyd;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_app = []
tmp_reaction = rate_constant_array[259]*E_R_app;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_atp = []
tmp_reaction = rate_constant_array[260]*E_R_atp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_nuo = []
tmp_reaction = rate_constant_array[261]*E_R_nuo;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pnt1 = []
tmp_reaction = rate_constant_array[262]*E_R_pnt1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pnt2 = []
tmp_reaction = rate_constant_array[263]*E_R_pnt2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ndh1 = []
tmp_reaction = rate_constant_array[264]*E_R_ndh1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ndh2 = []
tmp_reaction = rate_constant_array[265]*E_R_ndh2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_hack1 = []
tmp_reaction = rate_constant_array[266]*E_R_hack1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ppk = []
tmp_reaction = rate_constant_array[267]*E_R_ppk;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ppa = []
tmp_reaction = rate_constant_array[268]*E_R_ppa;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_chor = []
tmp_reaction = rate_constant_array[269]*E_R_chor;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gar = []
tmp_reaction = rate_constant_array[270]*E_R_gar;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_air = []
tmp_reaction = rate_constant_array[271]*E_R_air;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_aicar = []
tmp_reaction = rate_constant_array[272]*E_R_aicar;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_imp = []
tmp_reaction = rate_constant_array[273]*E_R_imp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gmp = []
tmp_reaction = rate_constant_array[274]*E_R_gmp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gdp = []
tmp_reaction = rate_constant_array[275]*E_R_gdp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gtp = []
tmp_reaction = rate_constant_array[276]*E_R_gtp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_amp = []
tmp_reaction = rate_constant_array[277]*E_R_amp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_adk = []
tmp_reaction = rate_constant_array[278]*E_R_adk;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_adk_R = []
tmp_reaction = rate_constant_array[279]*E_R_adk_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ump = []
tmp_reaction = rate_constant_array[280]*E_R_ump;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_udp = []
tmp_reaction = rate_constant_array[281]*E_R_udp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_utp = []
tmp_reaction = rate_constant_array[282]*E_R_utp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ctp = []
tmp_reaction = rate_constant_array[283]*E_R_ctp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_cdp = []
tmp_reaction = rate_constant_array[284]*E_R_cdp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_cmp = []
tmp_reaction = rate_constant_array[285]*E_R_cmp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_alaAC = []
tmp_reaction = rate_constant_array[286]*E_R_alaAC;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_arg = []
tmp_reaction = rate_constant_array[287]*E_R_arg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_aspC = []
tmp_reaction = rate_constant_array[288]*E_R_aspC;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_asnB = []
tmp_reaction = rate_constant_array[289]*E_R_asnB;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_asnA = []
tmp_reaction = rate_constant_array[290]*E_R_asnA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_cysEMK = []
tmp_reaction = rate_constant_array[291]*E_R_cysEMK;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gltBD = []
tmp_reaction = rate_constant_array[292]*E_R_gltBD;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gdhA = []
tmp_reaction = rate_constant_array[293]*E_R_gdhA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_glnA = []
tmp_reaction = rate_constant_array[294]*E_R_glnA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_glyA = []
tmp_reaction = rate_constant_array[295]*E_R_glyA;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_his = []
tmp_reaction = rate_constant_array[296]*E_R_his;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ile = []
tmp_reaction = rate_constant_array[297]*E_R_ile;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_leu = []
tmp_reaction = rate_constant_array[298]*E_R_leu;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_lys = []
tmp_reaction = rate_constant_array[299]*E_R_lys;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_met = []
tmp_reaction = rate_constant_array[300]*E_R_met;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_phe = []
tmp_reaction = rate_constant_array[301]*E_R_phe;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pro = []
tmp_reaction = rate_constant_array[302]*E_R_pro;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_serABC = []
tmp_reaction = rate_constant_array[303]*E_R_serABC;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_thr = []
tmp_reaction = rate_constant_array[304]*E_R_thr;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_trp = []
tmp_reaction = rate_constant_array[305]*E_R_trp;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_tyr = []
tmp_reaction = rate_constant_array[306]*E_R_tyr;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_val = []
tmp_reaction = rate_constant_array[307]*E_R_val;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_arg_deg1 = []
tmp_reaction = rate_constant_array[308]*E_R_arg_deg1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_arg_deg2 = []
tmp_reaction = rate_constant_array[309]*E_R_arg_deg2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_arg_deg3 = []
tmp_reaction = rate_constant_array[310]*E_R_arg_deg3;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_arg_deg4 = []
tmp_reaction = rate_constant_array[311]*E_R_arg_deg4;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_arg_deg5 = []
tmp_reaction = rate_constant_array[312]*E_R_arg_deg5;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_arg_deg6 = []
tmp_reaction = rate_constant_array[313]*E_R_arg_deg6;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_thr_deg1 = []
tmp_reaction = rate_constant_array[314]*E_R_thr_deg1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gly_deg = []
tmp_reaction = rate_constant_array[315]*E_R_gly_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_thr_deg2 = []
tmp_reaction = rate_constant_array[316]*E_R_thr_deg2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_thr_deg3 = []
tmp_reaction = rate_constant_array[317]*E_R_thr_deg3;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_thr_deg4 = []
tmp_reaction = rate_constant_array[318]*E_R_thr_deg4;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_thr_deg5 = []
tmp_reaction = rate_constant_array[319]*E_R_thr_deg5;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_mglx_deg = []
tmp_reaction = rate_constant_array[320]*E_R_mglx_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_mglx_deg_R = []
tmp_reaction = rate_constant_array[321]*E_R_mglx_deg_R;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ser_deg = []
tmp_reaction = rate_constant_array[322]*E_R_ser_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_pro_deg = []
tmp_reaction = rate_constant_array[323]*E_R_pro_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_trp_deg = []
tmp_reaction = rate_constant_array[324]*E_R_trp_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_cys_deg = []
tmp_reaction = rate_constant_array[325]*E_R_cys_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ala_deg = []
tmp_reaction = rate_constant_array[326]*E_R_ala_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_lys_deg = []
tmp_reaction = rate_constant_array[327]*E_R_lys_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gln_deg = []
tmp_reaction = rate_constant_array[328]*E_R_gln_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_glu_deg = []
tmp_reaction = rate_constant_array[329]*E_R_glu_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gaba_deg1 = []
tmp_reaction = rate_constant_array[330]*E_R_gaba_deg1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gaba_deg2 = []
tmp_reaction = rate_constant_array[331]*E_R_gaba_deg2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_asn_deg = []
tmp_reaction = rate_constant_array[332]*E_R_asn_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Ex_1 = []
tmp_reaction = rate_constant_array[333]*E_Ex_1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Ex_2 = []
tmp_reaction = rate_constant_array[334]*E_Ex_2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Ex_3 = []
tmp_reaction = rate_constant_array[335]*E_Ex_3;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Ex_4 = []
tmp_reaction = rate_constant_array[336]*E_Ex_4;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Ex_5 = []
tmp_reaction = rate_constant_array[337]*E_Ex_5;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_ATP_deg = []
tmp_reaction = rate_constant_array[338]*E_ATP_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_GTP_deg = []
tmp_reaction = rate_constant_array[339]*E_GTP_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_CTP_deg = []
tmp_reaction = rate_constant_array[340]*E_CTP_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_UTP_deg = []
tmp_reaction = rate_constant_array[341]*E_UTP_deg;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_amp_ppi = []
tmp_reaction = rate_constant_array[342]*E_R_amp_ppi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_amp_pi = []
tmp_reaction = rate_constant_array[343]*E_R_amp_pi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gmp_ppi = []
tmp_reaction = rate_constant_array[344]*E_R_gmp_ppi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_gmp_pi = []
tmp_reaction = rate_constant_array[345]*E_R_gmp_pi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_cmp_ppi = []
tmp_reaction = rate_constant_array[346]*E_R_cmp_ppi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_cmp_pi = []
tmp_reaction = rate_constant_array[347]*E_R_cmp_pi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ump_ppi = []
tmp_reaction = rate_constant_array[348]*E_R_ump_ppi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R_ump_pi = []
tmp_reaction = rate_constant_array[349]*E_R_ump_pi;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_transcriptional_initiation_CAT = []
tmp_reaction = rate_constant_array[350]*E_transcriptional_initiation_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_transcription_CAT = []
tmp_reaction = rate_constant_array[351]*E_transcription_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_mRNA_degradation_CAT = []
tmp_reaction = rate_constant_array[352]*E_mRNA_degradation_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_translation_initiation_CAT = []
tmp_reaction = rate_constant_array[353]*E_translation_initiation_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_translation_CAT = []
tmp_reaction = rate_constant_array[354]*E_translation_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_ala_L_c_CAT = []
tmp_reaction = rate_constant_array[355]*E_tRNA_charging_M_ala_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_arg_L_c_CAT = []
tmp_reaction = rate_constant_array[356]*E_tRNA_charging_M_arg_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_asn_L_c_CAT = []
tmp_reaction = rate_constant_array[357]*E_tRNA_charging_M_asn_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_asp_L_c_CAT = []
tmp_reaction = rate_constant_array[358]*E_tRNA_charging_M_asp_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_cys_L_c_CAT = []
tmp_reaction = rate_constant_array[359]*E_tRNA_charging_M_cys_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_glu_L_c_CAT = []
tmp_reaction = rate_constant_array[360]*E_tRNA_charging_M_glu_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_gln_L_c_CAT = []
tmp_reaction = rate_constant_array[361]*E_tRNA_charging_M_gln_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_gly_L_c_CAT = []
tmp_reaction = rate_constant_array[362]*E_tRNA_charging_M_gly_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_his_L_c_CAT = []
tmp_reaction = rate_constant_array[363]*E_tRNA_charging_M_his_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_ile_L_c_CAT = []
tmp_reaction = rate_constant_array[364]*E_tRNA_charging_M_ile_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_leu_L_c_CAT = []
tmp_reaction = rate_constant_array[365]*E_tRNA_charging_M_leu_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_lys_L_c_CAT = []
tmp_reaction = rate_constant_array[366]*E_tRNA_charging_M_lys_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_met_L_c_CAT = []
tmp_reaction = rate_constant_array[367]*E_tRNA_charging_M_met_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_phe_L_c_CAT = []
tmp_reaction = rate_constant_array[368]*E_tRNA_charging_M_phe_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_pro_L_c_CAT = []
tmp_reaction = rate_constant_array[369]*E_tRNA_charging_M_pro_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_ser_L_c_CAT = []
tmp_reaction = rate_constant_array[370]*E_tRNA_charging_M_ser_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_thr_L_c_CAT = []
tmp_reaction = rate_constant_array[371]*E_tRNA_charging_M_thr_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_trp_L_c_CAT = []
tmp_reaction = rate_constant_array[372]*E_tRNA_charging_M_trp_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_tyr_L_c_CAT = []
tmp_reaction = rate_constant_array[373]*E_tRNA_charging_M_tyr_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_tRNA_charging_M_val_L_c_CAT = []
tmp_reaction = rate_constant_array[374]*E_tRNA_charging_M_val_L_c_CAT;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
