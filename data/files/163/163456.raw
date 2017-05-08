#Cost = Float64[]
#for i in 1:100
#    cost = readdlm("Rand100/$i/cost")[1]
#    push!(Cost,cost)
#end


num_data = [
"M_thr_L_c" 9
"M_trp_L_c" 9
"M_cys_L_c" 9
"M_glc_D_c" 6
"M_ac_c" 6
"M_lys_L_c" 9
"M_gdp_c" 8
"M_leu_L_c" 9
"M_val_L_c" 9
"M_met_L_c" 9
"M_ala_L_c" 9
"M_ump_c" 8
"M_ctp_c" 8
"M_phe_L_c" 9
"M_utp_c" 8
"M_succ_c" 6
"M_tyr_L_c" 9
"M_ile_L_c" 9
"M_gtp_c" 8
"M_pyr_c" 6
"M_asn_L_c" 9
"M_gln_L_c" 9
"M_pro_L_c" 9
"M_mal_L_c" 6
"M_cmp_c" 8
"M_udp_c" 8
"CAT" 8
"M_gmp_c" 8
"M_atp_c" 8
"M_amp_c" 8
"M_adp_c" 8
"M_cdp_c" 8
"M_asp_L_c" 9
"M_lac_D_c" 6
"M_gly_L_c" 9
"M_his_L_c" 9
"M_ser_L_c" 9]


KE = readdlm("Rand100_100/1/KE")

for i in 2:100
    ke = readdlm("Rand100_100/$i/KE")
    if ke[:,1] == KE[:,1]
        KE = [KE ke[:,2]]
    else
        throw("Out of order")
    end
end

order = [4;27;20;34;5;16;24;29;31;30;19;7;28;13;32;25;15;26;12;11;21;33;3;22;35;36;18;8;6;10;
14;23;37;1;2;17;9]

ke_order = KE[order,:]

#writedlm("Rand100100/KE",KE)
writedlm("Rand100_100/KE",KE)


#M = 815
ke_ = copy(ke_order)
for i in 1:37
    species = ke_[i,1]
    N = num_data[find(num_data[:,1].==species),2][1]
    ke_[i,2:end] = N*log(convert(Array{Float64},ke_[i,2:end])/N) #+2*M
end


m = zeros(37,1)
s = zeros(37,1)
for i in 1:37
    tmp = convert(Array{Float64},ke_[i,2:end])
    m[i] = mean(tmp)
    s[i] = std(tmp)
end


Table = [ke_[:,1] m s]
writedlm("Rand100_100/Table",Table)







