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
function Control(t,x,rate_vector,data_dictionary)
# ---------------------------------------------------------------------- #
# Control.jl was generated using the Kwatee code generation system.
# Username: nicholas
# Type: CFPS-JULIA
# Version: 1.0
# Generation timestamp: 05-11-2016 16:22:26
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# rate_vector - vector of reaction rates 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Set a default value for the allosteric control variables - 
const number_of_reactions = length(rate_vector);
control_vector = ones(number_of_reactions);
const control_parameter_array = data_dictionary["CONTROL_PARAMETER_ARRAY"];

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
M_glc_D_c = x[54];
M_pep_c = x[55];
M_pyr_c = x[56];
M_ac_c = x[57];
M_lac_D_c = x[58];
M_mal_L_c = x[59];
M_atp_c = x[60];
M_adp_c = x[61];
M_amp_c = x[62];
M_gtp_c = x[63];
M_gdp_c = x[64];
M_gmp_c = x[65];
M_utp_c = x[66];
M_udp_c = x[67];
M_ump_c = x[68];
M_ctp_c = x[69];
M_cdp_c = x[70];
M_cmp_c = x[71];
M_succ_c = x[72];
M_asp_L_c = x[73];
M_gly_L_c = x[74];
M_ile_L_c = x[75];
M_asn_L_c = x[76];
M_cys_L_c = x[77];
M_lys_L_c = x[78];
M_his_L_c = x[79];
M_ala_L_c = x[80];
M_phe_L_c = x[81];
M_pro_L_c = x[82];
M_ser_L_c = x[83];
M_thr_L_c = x[84];
M_trp_L_c = x[85];
M_tyr_L_c = x[86];
M_val_L_c = x[87];
M_met_L_c = x[88];
M_leu_L_c = x[89];
M_glu_L_c = x[90];
M_gln_L_c = x[91];
CAT = x[92];
M_o2_c = x[93];
M_co2_c = x[94];
M_pi_c = x[95];
M_nh4_c = x[96];
M_so4_c = x[97];
M_h_c = x[98];
M_h2o_c = x[99];
M_nad_c = x[100];
M_nadh_c = x[101];
M_nadp_c = x[102];
M_nadph_c = x[103];
E_R_PTS = x[104];
E_R_glk_atp = x[105];
E_R_glk_utp = x[106];
E_R_glk_ctp = x[107];
E_R_glk_gtp = x[108];
E_R_pgi = x[109];
E_R_pgi_R = x[110];
E_R_pfk = x[111];
E_R_fdp = x[112];
E_R_fbaA = x[113];
E_R_fbaA_R = x[114];
E_R_tpiA = x[115];
E_R_tpiA_R = x[116];
E_R_gapA = x[117];
E_R_gapA_R = x[118];
E_R_pgk = x[119];
E_R_pgk_R = x[120];
E_R_gpm = x[121];
E_R_gpm_R = x[122];
E_R_eno = x[123];
E_R_eno_R = x[124];
E_R_pyk = x[125];
E_R_pck = x[126];
E_R_ppc = x[127];
E_R_pdh = x[128];
E_R_pps = x[129];
E_R_zwf = x[130];
E_R_zwf_R = x[131];
E_R_pgl = x[132];
E_R_gnd = x[133];
E_R_rpe = x[134];
E_R_rpe_R = x[135];
E_R_rpi = x[136];
E_R_rpi_R = x[137];
E_R_talAB = x[138];
E_R_talAB_R = x[139];
E_R_tkt1 = x[140];
E_R_tkt1_R = x[141];
E_R_tkt2 = x[142];
E_R_tkt2_R = x[143];
E_R_edd = x[144];
E_R_eda = x[145];
E_R_gltA = x[146];
E_R_acn = x[147];
E_R_acn_R = x[148];
E_R_icd = x[149];
E_R_icd_R = x[150];
E_R_sucAB = x[151];
E_R_sucCD = x[152];
E_R_sucCD_R = x[153];
E_R_sdh = x[154];
E_R_frd = x[155];
E_R_fum = x[156];
E_R_fum_R = x[157];
E_R_mdh = x[158];
E_R_mdh_R = x[159];
E_R_aceA = x[160];
E_R_aceB = x[161];
E_R_maeA = x[162];
E_R_maeB = x[163];
E_R_pta = x[164];
E_R_pta_R = x[165];
E_R_ackA = x[166];
E_R_ackA_R = x[167];
E_R_acs = x[168];
E_R_adhE = x[169];
E_R_adhE_R = x[170];
E_R_ldh_f = x[171];
E_R_ldh_r = x[172];
E_R_pflAB = x[173];
E_R_cyd = x[174];
E_R_app = x[175];
E_R_atp = x[176];
E_R_nuo = x[177];
E_R_pnt1 = x[178];
E_R_pnt2 = x[179];
E_R_ndh1 = x[180];
E_R_ndh2 = x[181];
E_R_hack1 = x[182];
E_R_ppk = x[183];
E_R_ppa = x[184];
E_R_chor = x[185];
E_R_gar = x[186];
E_R_air = x[187];
E_R_aicar = x[188];
E_R_imp = x[189];
E_R_gmp = x[190];
E_R_gdp = x[191];
E_R_gtp = x[192];
E_R_amp = x[193];
E_R_adk = x[194];
E_R_adk_R = x[195];
E_R_ump = x[196];
E_R_udp = x[197];
E_R_utp = x[198];
E_R_ctp = x[199];
E_R_cdp = x[200];
E_R_cmp = x[201];
E_R_alaAC = x[202];
E_R_arg = x[203];
E_R_aspC = x[204];
E_R_asnB = x[205];
E_R_asnA = x[206];
E_R_cysEMK = x[207];
E_R_gltBD = x[208];
E_R_gdhA = x[209];
E_R_glnA = x[210];
E_R_glyA = x[211];
E_R_his = x[212];
E_R_ile = x[213];
E_R_leu = x[214];
E_R_lys = x[215];
E_R_met = x[216];
E_R_phe = x[217];
E_R_pro = x[218];
E_R_serABC = x[219];
E_R_thr = x[220];
E_R_trp = x[221];
E_R_tyr = x[222];
E_R_val = x[223];
E_R_arg_deg1 = x[224];
E_R_arg_deg2 = x[225];
E_R_arg_deg3 = x[226];
E_R_arg_deg4 = x[227];
E_R_arg_deg5 = x[228];
E_R_arg_deg6 = x[229];
E_R_thr_deg1 = x[230];
E_R_gly_deg = x[231];
E_R_thr_deg2 = x[232];
E_R_thr_deg3 = x[233];
E_R_thr_deg4 = x[234];
E_R_thr_deg5 = x[235];
E_R_mglx_deg = x[236];
E_R_mglx_deg_R = x[237];
E_R_ser_deg = x[238];
E_R_pro_deg = x[239];
E_R_trp_deg = x[240];
E_R_cys_deg = x[241];
E_R_ala_deg = x[242];
E_R_lys_deg = x[243];
E_R_gln_deg = x[244];
E_R_glu_deg = x[245];
E_R_gaba_deg1 = x[246];
E_R_gaba_deg2 = x[247];
E_R_asn_deg = x[248];
E_Ex_1 = x[249];
E_Ex_2 = x[250];
E_Ex_3 = x[251];
E_Ex_4 = x[252];
E_Ex_5 = x[253];
E_ATP_deg = x[254];
E_GTP_deg = x[255];
E_CTP_deg = x[256];
E_UTP_deg = x[257];
E_R_CAT = x[258];
E_R_amp_ppi = x[259];
E_R_amp_pi = x[260];
E_R_gmp_ppi = x[261];
E_R_gmp_pi = x[262];
E_R_cmp_ppi = x[263];
E_R_cmp_pi = x[264];
E_R_ump_ppi = x[265];
E_R_ump_pi = x[266];

transfer_function_vector = Float64[];
# type: inhibition actor: M_pep_c target: R_pfk
push!(transfer_function_vector,1.0 - control_parameter_array[1,1]*M_pep_c^control_parameter_array[1,2]/(1+control_parameter_array[1,1]*M_pep_c^control_parameter_array[1,2]));
control_vector[8] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: activation actor: M_pep_c target: R_fdp
push!(transfer_function_vector,control_parameter_array[2,1]*M_pep_c^control_parameter_array[2,2]/(1+control_parameter_array[2,1]*M_pep_c^control_parameter_array[2,2]));
control_vector[9] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: activation actor: M_fdp_c target: R_pyk
push!(transfer_function_vector,control_parameter_array[3,1]*M_fdp_c^control_parameter_array[3,2]/(1+control_parameter_array[3,1]*M_fdp_c^control_parameter_array[3,2]));
control_vector[22] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: inhibition actor: M_pep_c target: R_pck
push!(transfer_function_vector,1.0 - control_parameter_array[4,1]*M_pep_c^control_parameter_array[4,2]/(1+control_parameter_array[4,1]*M_pep_c^control_parameter_array[4,2]));
control_vector[23] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: activation actor: M_fdp_c target: R_ppc
push!(transfer_function_vector,control_parameter_array[5,1]*M_fdp_c^control_parameter_array[5,2]/(1+control_parameter_array[5,1]*M_fdp_c^control_parameter_array[5,2]));
control_vector[24] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: inhibition actor: M_pyr_c target: R_pdh
push!(transfer_function_vector,1.0 - control_parameter_array[6,1]*M_pyr_c^control_parameter_array[6,2]/(1+control_parameter_array[6,1]*M_pyr_c^control_parameter_array[6,2]));
control_vector[25] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: inhibition actor: M_pep_c target: R_pps
push!(transfer_function_vector,1.0 - control_parameter_array[7,1]*M_pep_c^control_parameter_array[7,2]/(1+control_parameter_array[7,1]*M_pep_c^control_parameter_array[7,2]));
control_vector[26] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: inhibition actor: M_akg_c target: R_gltA
push!(transfer_function_vector,1.0 - control_parameter_array[8,1]*M_akg_c^control_parameter_array[8,2]/(1+control_parameter_array[8,1]*M_akg_c^control_parameter_array[8,2]));
control_vector[43] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: inhibition actor: M_pep_c target: R_icd
push!(transfer_function_vector,1.0 - control_parameter_array[9,1]*M_pep_c^control_parameter_array[9,2]/(1+control_parameter_array[9,1]*M_pep_c^control_parameter_array[9,2]));
control_vector[46] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: inhibition actor: M_akg_c target: R_aceA
push!(transfer_function_vector,1.0 - control_parameter_array[10,1]*M_akg_c^control_parameter_array[10,2]/(1+control_parameter_array[10,1]*M_akg_c^control_parameter_array[10,2]));
# type: inhibition actor: M_pep_c target: R_aceA
push!(transfer_function_vector,1.0 - control_parameter_array[11,1]*M_pep_c^control_parameter_array[11,2]/(1+control_parameter_array[11,1]*M_pep_c^control_parameter_array[11,2]));
# type: inhibition actor: M_3pg_c target: R_aceA
push!(transfer_function_vector,1.0 - control_parameter_array[12,1]*M_3pg_c^control_parameter_array[12,2]/(1+control_parameter_array[12,1]*M_3pg_c^control_parameter_array[12,2]));
control_vector[57] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: inhibition actor: M_akg_c target: R_aceB
push!(transfer_function_vector,1.0 - control_parameter_array[13,1]*M_akg_c^control_parameter_array[13,2]/(1+control_parameter_array[13,1]*M_akg_c^control_parameter_array[13,2]));
# type: inhibition actor: M_pep_c target: R_aceB
push!(transfer_function_vector,1.0 - control_parameter_array[14,1]*M_pep_c^control_parameter_array[14,2]/(1+control_parameter_array[14,1]*M_pep_c^control_parameter_array[14,2]));
# type: inhibition actor: M_3pg_c target: R_aceB
push!(transfer_function_vector,1.0 - control_parameter_array[15,1]*M_3pg_c^control_parameter_array[15,2]/(1+control_parameter_array[15,1]*M_3pg_c^control_parameter_array[15,2]));
control_vector[58] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: inhibition actor: M_accoa_c target: R_maeB
push!(transfer_function_vector,1.0 - control_parameter_array[16,1]*M_accoa_c^control_parameter_array[16,2]/(1+control_parameter_array[16,1]*M_accoa_c^control_parameter_array[16,2]));
control_vector[60] = mean(transfer_function_vector);
transfer_function_vector = 0;

transfer_function_vector = Float64[];
# type: activation actor: M_pyr_c target: R_ldh_r
push!(transfer_function_vector,control_parameter_array[17,1]*M_pyr_c^control_parameter_array[17,2]/(1+control_parameter_array[17,1]*M_pyr_c^control_parameter_array[17,2]));
control_vector[69] = mean(transfer_function_vector);
transfer_function_vector = 0;

# Modify the rate_vector with the control variables - 
rate_vector = rate_vector.*control_vector;

# Return the modified rate vector - 
return rate_vector;
end
