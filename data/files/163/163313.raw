using Interpolations

function CalcError(experiment_data_dictionary,Tsim,X)

# Initialize arrays
Error = Float64[]
Keys = AbstractString[]

# Define dictionary of weights
Weight = Dict()
Weight["CAT"] = 50
Weight["M_glc_D_c"] = 30
Weight["M_pyr_c"] = 50
Weight["M_lac_D_c"] = 15
Weight["M_ac_c"] = 15
Weight["M_succ_c"] = 15
Weight["M_mal_L_c"] = 15
Weight["M_atp_c"] = 5
Weight["M_adp_c"] = 10
Weight["M_amp_c"] = 20
Weight["M_gtp_c"] = 10
Weight["M_gdp_c"] = 5
Weight["M_gmp_c"] = 20
Weight["M_ctp_c"] = 10
Weight["M_cdp_c"] = 10
Weight["M_cmp_c"] = 10
Weight["M_utp_c"] = 10
Weight["M_udp_c"] = 20
Weight["M_ump_c"] = 10
Weight["M_ala_L_c"] = 5
Weight["M_asn_L_c"] = 10
Weight["M_asp_L_c"] = 5
Weight["M_cys_L_c"] = 5
Weight["M_gln_L_c"] = 30
Weight["M_gly_L_c"] = 2
Weight["M_his_L_c"] = 5
Weight["M_ile_L_c"] = 5
Weight["M_leu_L_c"] = 2
Weight["M_lys_L_c"] = 10
Weight["M_met_L_c"] = 2
Weight["M_phe_L_c"] = 2
Weight["M_pro_L_c"] = 5
Weight["M_ser_L_c"] = 2
Weight["M_thr_L_c"] = 5
Weight["M_trp_L_c"] = 2
Weight["M_tyr_L_c"] = 2
Weight["M_val_L_c"] = 2

for (key,dataset) in experiment_data_dictionary
    # Get raw data and timepoints
    raw_array = dataset.raw_measurement_array
    data_tps = raw_array[:,1]
    data_vals = raw_array[:,2]
    # Interpolate simulation array to fit dataset
    index = dataset.model_index
    sim = X[:,index]
    itp = interpolate((Tsim,),sim,Gridded(Linear()))
    sim_itp = itp[data_tps]
    # Calculate error
    norm_diff = (sim_itp-data_vals)/maximum(data_vals)
    error = sum(norm_diff.^2)
    # Weight certain datasets as more important
    error *= Weight[key]
    # Push to arrays
    push!(Error,error)
    push!(Keys,key)
end

return Error,Keys
end
