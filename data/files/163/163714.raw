include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcError.jl")
using PyPlot

if isdir("flux")
    rm("flux",recursive=true)
end

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = TSTOP/300

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)

# Initialize number of parameters to be varied
num_rate = 375
num_sat = 525
num_cont = 34

params_best = readdlm("Best/params")

 #Check that params is of correct length
if ~(num_rate+num_sat+num_cont==length(params_best) || num_rate+num_sat==length(params_best))
    throw("Wrong number of parameters")
end

 #Add rate constants to data_dictionary
rate = params_best[1:num_rate]
data_dictionary["RATE_CONSTANT_ARRAY"] = rate

 #Add saturation constants to data_dictionary
sat = params_best[num_rate+1:num_rate+num_sat]
sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
sat_vector[find(sat_vector.>0)] = sat
data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))

#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,59] = 0.001
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,91] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,60] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,61] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,62] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,63] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,64] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,65] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,66] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,67] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,68] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,69] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,70] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,71] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,72] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,73] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,74] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,75] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,76] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,77] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,78] = 0.2
#data_dictionary["SATURATION_CONSTANT_ARRAY"][167,79] = 0.2

experiment_data_dictionary = data_dictionary["EXPERIMENT_DATA_DICTIONARY"]

tic()
Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
time_elapsed = toc()

Error,Keys = CalcError(experiment_data_dictionary,Tsim,X)
cost = sum(Error)

glc = experiment_data_dictionary["M_glc_D_c"].raw_measurement_array
pyr = experiment_data_dictionary["M_pyr_c"].raw_measurement_array
lac = experiment_data_dictionary["M_lac_D_c"].raw_measurement_array
ac = experiment_data_dictionary["M_ac_c"].raw_measurement_array
succ = experiment_data_dictionary["M_succ_c"].raw_measurement_array
mal = experiment_data_dictionary["M_mal_L_c"].raw_measurement_array
CAT = experiment_data_dictionary["CAT"].raw_measurement_array

atp = experiment_data_dictionary["M_atp_c"].raw_measurement_array
adp = experiment_data_dictionary["M_adp_c"].raw_measurement_array
amp = experiment_data_dictionary["M_amp_c"].raw_measurement_array
axp = atp+adp+amp
axp[:,1] = atp[:,1]
gtp = experiment_data_dictionary["M_gtp_c"].raw_measurement_array
gdp = experiment_data_dictionary["M_gdp_c"].raw_measurement_array
gmp = experiment_data_dictionary["M_gmp_c"].raw_measurement_array
gxp = gtp+gdp+gmp
gxp[:,1] = gtp[:,1]
ctp = experiment_data_dictionary["M_ctp_c"].raw_measurement_array
cdp = experiment_data_dictionary["M_cdp_c"].raw_measurement_array
cmp = experiment_data_dictionary["M_cmp_c"].raw_measurement_array
cxp = ctp+cdp+cmp
cxp[:,1] = ctp[:,1]
utp = experiment_data_dictionary["M_utp_c"].raw_measurement_array
udp = experiment_data_dictionary["M_udp_c"].raw_measurement_array
ump = experiment_data_dictionary["M_ump_c"].raw_measurement_array
uxp = utp+udp+ump
uxp[:,1] = utp[:,1]

xxp = axp+gxp+cxp+uxp
xxp[:,1] = axp[:,1]

ala = experiment_data_dictionary["M_ala_L_c"].raw_measurement_array
asp = experiment_data_dictionary["M_asp_L_c"].raw_measurement_array
cys = experiment_data_dictionary["M_cys_L_c"].raw_measurement_array
gln = experiment_data_dictionary["M_gln_L_c"].raw_measurement_array
gly = experiment_data_dictionary["M_gly_L_c"].raw_measurement_array
phe = experiment_data_dictionary["M_phe_L_c"].raw_measurement_array
ser = experiment_data_dictionary["M_ser_L_c"].raw_measurement_array
thr = experiment_data_dictionary["M_thr_L_c"].raw_measurement_array

asn	= experiment_data_dictionary["M_asn_L_c"].raw_measurement_array
his	= experiment_data_dictionary["M_his_L_c"].raw_measurement_array
ile	= experiment_data_dictionary["M_ile_L_c"].raw_measurement_array
leu	= experiment_data_dictionary["M_leu_L_c"].raw_measurement_array
lys	= experiment_data_dictionary["M_lys_L_c"].raw_measurement_array
met	= experiment_data_dictionary["M_met_L_c"].raw_measurement_array
pro	= experiment_data_dictionary["M_pro_L_c"].raw_measurement_array
trp = experiment_data_dictionary["M_trp_L_c"].raw_measurement_array
tyr	= experiment_data_dictionary["M_tyr_L_c"].raw_measurement_array
val	= experiment_data_dictionary["M_val_L_c"].raw_measurement_array

species = ["GLC" 82;"PYR" 84;"LAC" 86;"AC" 85;"SUCC" 100;"MAL" 87;"CAT" 80;"XXP" (88,89,90,91,92,93,94,95,96,97,98,99);"ATP" 88;"ADP" 89;"AMP" 90;"AXP" (88,89,90);"GTP" 91;"GDP" 92;"GMP" 93;"GXP" (91,92,93);"CTP" 97;"CDP" 98;"CMP" 99;"CXP" (97,98,99);"UTP" 94;"UDP" 95;"UMP" 96;"UXP" (94,95,96);"ALA" 108;"ARG" 43;"ASN" 104;"ASP" 101;"CYS" 105;"GLN" 119;"GLU" 118;"GLY" 102;"HIS" 107;"ILE" 103;"LEU" 117;"LYS" 106;"MET" 116;"PHE" 109;"PRO" 110;"SER" 111;"THR" 112;"TRP" 113;"TYR" 114;"VAL" 115]

glc[:,1] *= TSTOP/3
pyr[:,1] *= TSTOP/3
lac[:,1] *= TSTOP/3
ac[:,1] *= TSTOP/3
succ[:,1] *= TSTOP/3
mal[:,1] *= TSTOP/3
CAT[:,1] *= TSTOP/3
atp[:,1] *= TSTOP/3
adp[:,1] *= TSTOP/3
amp[:,1] *= TSTOP/3
axp[:,1] *= TSTOP/3
gtp[:,1] *= TSTOP/3
gdp[:,1] *= TSTOP/3
gmp[:,1] *= TSTOP/3
gxp[:,1] *= TSTOP/3
ctp[:,1] *= TSTOP/3
cdp[:,1] *= TSTOP/3
cmp[:,1] *= TSTOP/3
cxp[:,1] *= TSTOP/3
utp[:,1] *= TSTOP/3
udp[:,1] *= TSTOP/3
ump[:,1] *= TSTOP/3
uxp[:,1] *= TSTOP/3
xxp[:,1] *= TSTOP/3
ala[:,1] *= TSTOP/3
asp[:,1] *= TSTOP/3
cys[:,1] *= TSTOP/3
gln[:,1] *= TSTOP/3
gly[:,1] *= TSTOP/3
phe[:,1] *= TSTOP/3
ser[:,1] *= TSTOP/3
thr[:,1] *= TSTOP/3
asn[:,1] *= TSTOP/3
his[:,1] *= TSTOP/3
ile[:,1] *= TSTOP/3
leu[:,1] *= TSTOP/3
lys[:,1] *= TSTOP/3
met[:,1] *= TSTOP/3
pro[:,1] *= TSTOP/3
trp[:,1] *= TSTOP/3
tyr[:,1] *= TSTOP/3
val[:,1] *= TSTOP/3

figure("Carbon",figsize=(23,7))
figure("Energy",figsize=(20,12.5))
figure("Amino",figsize=(15,12.5))
figure("TXTL",figsize=(23,16))
figure("tRNA",figsize=(23,16))

figure("Carbon")

subplot(2,4,1)
errorbar(glc[:,1],glc[:,2],glc[:,3],fmt="ro",color="k",linewidth=2,linewidth=2)
axis([0,TSTOP,0,40])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:10:40)
ylabel("Glucose (mM)")
xlabel("Time (h)")

subplot(2,4,3)
errorbar(pyr[:,1],pyr[:,2],pyr[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,15])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:5:15)
ylabel("Pyruvate (mM)")
xlabel("Time (h)")

subplot(2,4,4)
errorbar(lac[:,1],lac[:,2],lac[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,20])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:5:20)
ylabel("Lactate (mM)")
xlabel("Time (h)")

subplot(2,4,5)
errorbar(ac[:,1],ac[:,2],ac[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,50])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:10:50)
ylabel("Acetate (mM)")
xlabel("Time (h)")

subplot(2,4,6)
errorbar(succ[:,1],succ[:,2],succ[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("Succinate (mM)")
xlabel("Time (h)")

subplot(2,4,7)
errorbar(mal[:,1],mal[:,2],mal[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,10])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:2:10)
ylabel("Malate (mM)")
xlabel("Time (h)")

subplot(2,4,2)
errorbar(CAT[:,1],1000*CAT[:,2],1000*CAT[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,25])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:5:25)
ylabel("CAT (μM)")
xlabel("Time (h)")

subplot(2,4,8)
errorbar(xxp[:,1],xxp[:,2],xxp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,8])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:2:8)
ylabel("Energy Total (mM)")
xlabel("Time (h)")





figure("Energy")

subplot(4,4,1)
errorbar(atp[:,1],atp[:,2],atp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,2])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.5:2)
ylabel("ATP (mM)")
xlabel("Time (h)")

subplot(4,4,5)
errorbar(adp[:,1],adp[:,2],adp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,.8])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.2:.8)
ylabel("ADP (mM)")
xlabel("Time (h)")

subplot(4,4,9)
errorbar(amp[:,1],amp[:,2],amp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,.5])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.1:.5)
ylabel("AMP (mM)")
xlabel("Time (h)")

subplot(4,4,13)
errorbar(axp[:,1],axp[:,2],axp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,2])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.5:2)
ylabel("Σ AXP (mM)")
xlabel("Time (h)")

subplot(4,4,2)
errorbar(gtp[:,1],gtp[:,2],gtp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,1.5])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.5:1.5)
ylabel("GTP (mM)")
xlabel("Time (h)")

subplot(4,4,6)
errorbar(gdp[:,1],gdp[:,2],gdp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,.8])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.2:.8)
ylabel("GDP (mM)")
xlabel("Time (h)")

subplot(4,4,10)
errorbar(gmp[:,1],gmp[:,2],gmp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,.4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.1:.4)
ylabel("GMP (mM)")
xlabel("Time (h)")

subplot(4,4,14)
errorbar(gxp[:,1],gxp[:,2],gxp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,2])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.5:2)
ylabel("Σ GXP (mM)")
xlabel("Time (h)")

subplot(4,4,3)
errorbar(ctp[:,1],ctp[:,2],ctp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,1])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.2:1)
ylabel("CTP (mM)")
xlabel("Time (h)")

subplot(4,4,7)
errorbar(cdp[:,1],cdp[:,2],cdp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,.8])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.2:.8)
ylabel("CDP (mM)")
xlabel("Time (h)")

subplot(4,4,11)
errorbar(cmp[:,1],cmp[:,2],cmp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,.8])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.2:.8)
ylabel("CMP (mM)")
xlabel("Time (h)")

subplot(4,4,15)
errorbar(cxp[:,1],cxp[:,2],cxp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,2])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.5:2)
ylabel("Σ CXP (mM)")
xlabel("Time (h)")

subplot(4,4,4)
errorbar(utp[:,1],utp[:,2],utp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,1])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.2:1)
ylabel("UTP (mM)")
xlabel("Time (h)")

subplot(4,4,8)
errorbar(udp[:,1],udp[:,2],udp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,.6])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.2:.6)
ylabel("UDP (mM)")
xlabel("Time (h)")

subplot(4,4,12)
errorbar(ump[:,1],ump[:,2],ump[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,.3])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.1:.3)
ylabel("UMP (mM)")
xlabel("Time (h)")

subplot(4,4,16)
errorbar(uxp[:,1],uxp[:,2],uxp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,1.5])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:.5:1.5)
ylabel("Σ UXP (mM)")
xlabel("Time (h)")





figure("Amino")

subplot(5,4,1)
errorbar(ala[:,1],ala[:,2],ala[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,10])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:2:10)
ylabel("ALA (mM)")
xlabel("Time (h)")

subplot(5,4,2)
axis([0,TSTOP,0,15])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:5:15)
ylabel("ARG (mM)")
xlabel("Time (h)")

subplot(5,4,3)
errorbar(asn[:,1],asn[:,2],asn[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("ASN (mM)")
xlabel("Time (h)")

subplot(5,4,4)
errorbar(asp[:,1],asp[:,2],asp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,3])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:TSTOP)
ylabel("ASP (mM)")
xlabel("Time (h)")

subplot(5,4,5)
errorbar(cys[:,1],cys[:,2],cys[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("CYS (mM)")
xlabel("Time (h)")

subplot(5,4,6)
errorbar(gln[:,1],gln[:,2],gln[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("GLN (mM)")
xlabel("Time (h)")

subplot(5,4,7)
axis([0,TSTOP,0,200])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:50:200)
ylabel("GLU (mM)")
xlabel("Time (h)")

subplot(5,4,8)
errorbar(gly[:,1],gly[:,2],gly[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("GLY (mM)")
xlabel("Time (h)")

subplot(5,4,9)
errorbar(his[:,1],his[:,2],his[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("HIS (mM)")
xlabel("Time (h)")

subplot(5,4,10)
errorbar(ile[:,1],ile[:,2],ile[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("ILE (mM)")
xlabel("Time (h)")

subplot(5,4,11)
errorbar(leu[:,1],leu[:,2],leu[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("LEU (mM)")
xlabel("Time (h)")

subplot(5,4,12)
errorbar(lys[:,1],lys[:,2],lys[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("LYS (mM)")
xlabel("Time (h)")

subplot(5,4,13)
errorbar(met[:,1],met[:,2],met[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("MET (mM)")
xlabel("Time (h)")

subplot(5,4,14)
errorbar(phe[:,1],phe[:,2],phe[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("PHE (mM)")
xlabel("Time (h)")

subplot(5,4,15)
errorbar(pro[:,1],pro[:,2],pro[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("PRO (mM)")
xlabel("Time (h)")

subplot(5,4,16)
errorbar(ser[:,1],ser[:,2],ser[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("SER (mM)")
xlabel("Time (h)")

subplot(5,4,17)
errorbar(thr[:,1],thr[:,2],thr[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("THR (mM)")
xlabel("Time (h)")

subplot(5,4,18)
errorbar(trp[:,1],trp[:,2],trp[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("TRP (mM)")
xlabel("Time (h)")

subplot(5,4,19)
errorbar(tyr[:,1],tyr[:,2],tyr[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,3])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:3)
ylabel("TYR (mM)")
xlabel("Time (h)")

subplot(5,4,20)
errorbar(val[:,1],val[:,2],val[:,3],fmt="ro",color="k",linewidth=2)
axis([0,TSTOP,0,4])
plt[:xticks](0:1:TSTOP)
plt[:yticks](0:1:4)
ylabel("VAL (mM)")
xlabel("Time (h)")





for j in 1:size(species,1)
    str = species[j,1]
    index = species[j,2]
    
    amino_ = [1 5 9 13 2 6 10 14 3 7 11 15 4 8 12 16]
    core_ = [1 3 4 5 6 7 2 8]
    
    if j < 9
        figure("Carbon")
        subplot(2,4,core_[j])
    elseif j >= 9 && j < 25
        figure("Energy")
        subplot(4,4,amino_[j-8])
    else
        figure("Amino")
        subplot(5,4,j-8-16)
    end
    
    if typeof(index) == Int
        tmp = X[:,index]
    elseif typeof(index) == Tuple{Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
    elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
    else
        throw("Wrong type")
    end
    
    if str == "CAT"
        tmp *= 1000
    end
    
    plot(Tsim,tmp,"red",linewidth=1.5)
    
    tight_layout()
end





figure("TXTL")

subplot(3,3,1)
plot(Tsim,X[:,54],"red")
axis([0,3,0,10])
plt[:xticks](0:1:3)
plt[:yticks](0:2:10)
ylabel("GENE_CAT (mM)")
xlabel("Time (h)")

subplot(3,3,2)
plot(Tsim,X[:,55],"red")
axis([0,3,0,10])
plt[:xticks](0:1:3)
plt[:yticks](0:2:10)
ylabel("RNAP (mM)")
xlabel("Time (h)")

subplot(3,3,3)
plot(Tsim,X[:,56],"red")
axis([0,3,0,6])
plt[:xticks](0:1:3)
plt[:yticks](0:2:6)
ylabel("OPEN_GENE_CAT (mM)")
xlabel("Time (h)")

subplot(3,3,4)
plot(Tsim,X[:,57],"red")
axis([0,3,0,0.01])
plt[:xticks](0:1:3)
plt[:yticks](0:0.002:0.01)
ylabel("mRNA_CAT (mM)")
xlabel("Time (h)")

subplot(3,3,5)
plot(Tsim,X[:,58],"red")
axis([0,3,0,12])
plt[:xticks](0:1:3)
plt[:yticks](0:2:12)
ylabel("Ribosome (mM)")
xlabel("Time (h)")

subplot(3,3,6)
plot(Tsim,X[:,59],"red")
axis([0,3,0,0.01])
plt[:xticks](0:1:3)
plt[:yticks](0:0.002:0.01)
ylabel("Ribosome_START_CAT (mM)")
xlabel("Time (h)")

subplot(3,3,7)
plot(Tsim,X[:,81],"red")
axis([0,3,0,10])
plt[:xticks](0:1:3)
plt[:yticks](0:2:10)
ylabel("tRNA (mM)")
xlabel("Time (h)")

subplot(3,3,8)
plot(Tsim,X[:,60]+X[:,61]+X[:,62]+X[:,63]+X[:,64]+X[:,65]+X[:,66]+X[:,67]+X[:,68]+X[:,69]+X[:,70]+X[:,71]+X[:,72]+X[:,73]+X[:,74]+X[:,75]+X[:,76]+X[:,77]+X[:,78]+X[:,79],"red")
axis([0,3,0,12])
plt[:xticks](0:1:3)
plt[:yticks](0:2:12)
ylabel("AA_tRNA (mM)")
xlabel("Time (h)")      

subplot(3,3,9)
plot(Tsim,X[:,80],"red")
#axis([0,3,0,1e-12])
plt[:xticks](0:1:3)
#plt[:yticks](0:2e-13:1e-12)
ylabel("PROTEIN_CAT (mM)")
xlabel("Time (h)")

tight_layout()




figure("tRNA")

subplot(5,4,1)
plot(Tsim,X[:,60],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("ala_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,2)
plot(Tsim,X[:,61],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("arg_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,3)
plot(Tsim,X[:,62],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("asn_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,4)
plot(Tsim,X[:,63],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("asp_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,5)
plot(Tsim,X[:,64],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("cys_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,6)
plot(Tsim,X[:,65],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("glu_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,7)
plot(Tsim,X[:,66],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("gln_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,8)
plot(Tsim,X[:,67],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("gly_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,9)
plot(Tsim,X[:,68],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("his_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,10)
plot(Tsim,X[:,69],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("ile_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,11)
plot(Tsim,X[:,70],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("leu_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,12)
plot(Tsim,X[:,71],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("lys_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,13)
plot(Tsim,X[:,72],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("met_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,14)
plot(Tsim,X[:,73],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("phe_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,15)
plot(Tsim,X[:,74],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("pro_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,16)
plot(Tsim,X[:,75],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("ser_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,17)
plot(Tsim,X[:,76],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("thr_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,18)
plot(Tsim,X[:,77],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("trp_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,19)
plot(Tsim,X[:,78],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("tyr_tRNA (mM)")
xlabel("Time (h)")

subplot(5,4,20)
plot(Tsim,X[:,79],"red")
axis([0,3,0,1])
plt[:xticks](0:1:3)
plt[:yticks](0:.25:1)
ylabel("val_tRNA (mM)")
xlabel("Time (h)")

tight_layout()




