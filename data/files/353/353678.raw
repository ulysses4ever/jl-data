#Protein folding
#Create a dictionary for each amino acid, with a function with decaying likelihoood of interaction with other amino acids with distance. This will need to be done for each amino acid separately, or there may be a more concise way to group things. Could place each amino acid in their respective functional groups, then create the decaying function for functional classes that an amino acid may interact with. 0 will be used for the cases where no interaction occurs.
#Functional groups are : Nonpolar, Polar, Acidic, Basic
#Nonpolar - Dispersion and hydrophobic - these aa's will want to fold to the middle of the protein to avoid contact with H2O
#Polar - H-bonding - These are more likely to form hydrogen bonds with the surrounding aqueous environment. Not necessarily interacting with neighboring aa's, but will have an impact on folding.
#Acidic - Have a negative charge - H accepting, form H-bonds, ionic bonds
#Basic - Have a positive charge - H donors, ionic bonds.

#Using R to generate Poisson distribution for prob of interactions
using RCall
using DataFrames
#Read in the sequence
aaSeq  = readline()
aaSeq = chomp(aaSeq)

#Generate starting probabilities of interactions based on empirical evidence, and approximated using Poisson distribution
interProbs = Dict{Symbol, Float64}()
A = "ppois(0:9, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:AA] = A[1]; interProbs[:AD] = A[2]; interProbs[:AE] = A[2]; interProbs[:AK] = A[2]; interProbs[:AN] = A[3]; interProbs[:AS] = A[3];
interProbs[:AR] = A[4]; interProbs[:AQ] = A[4]; interProbs[:AH] = A[4]; interProbs[:AC] = A[5]; interProbs[:AP] = A[5]; interProbs[:AT] = A[6];
interProbs[:AW] = A[7]; interProbs[:AF] = A[7]; interProbs[:AI] = A[8]; interProbs[:AL] = A[8]; interProbs[:AV] = A[8]; interProbs[:AY] = A[9];
interProbs[:AM] = A[10]; interProbs[:AG] = 0.0; 
R = "ppois(0:7, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:RE] = R[1]; interProbs[:RD] = R[2]; interProbs[:RI] = R[3]; interProbs[:RK] = R[3]; interProbs[:RV] = R[3]; interProbs[:RL] = R[4]; 
interProbs[:RM] = R[4]; interProbs[:RF] = R[4]; interProbs[:RA] = R[5]; interProbs[:RH] = R[5]; interProbs[:RT] = R[5]; interProbs[:RC] = R[6]; 
interProbs[:RR] = R[6]; interProbs[:RW] = R[7]; interProbs[:RY] = R[7]; interProbs[:RQ] = R[8]; interProbs[:RN] = 0.0; interProbs[:RP] = 0.0; 
interProbs[:RS] = 0.0; interProbs[:RG] = 0.0;  
N = "ppois(0:11, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:NI] = N[1]; interProbs[:NL] = N[1]; interProbs[:NN] = N[2]; interProbs[:NF] = N[3]; interProbs[:NV] = N[3]; interProbs[:ND] = N[4]; 
interProbs[:NM] = N[5]; interProbs[:NA] = N[6]; interProbs[:NW] = N[7]; interProbs[:NY] = N[7]; interProbs[:NQ] = N[8]; interProbs[:NE] = N[8]; 
interProbs[:NS] = N[8]; interProbs[:NT] = N[8]; interProbs[:NC] = N[9]; interProbs[:NK] = N[10]; interProbs[:NP] = N[11]; interProbs[:NH] = N[12]; 
interProbs[:NR] = 0.0; interProbs[:NG] = 0.0;  
D = "ppois(0:11, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:DK] = D[1]; interProbs[:DL] = D[2]; interProbs[:DI] = D[2]; interProbs[:DR] = D[3]; interProbs[:DF] = D[4]; interProbs[:DV] = D[4]; 
interProbs[:DM] = D[5]; interProbs[:DS] = D[6]; interProbs[:DH] = D[7]; interProbs[:DE] = D[8]; interProbs[:DA] = D[8]; interProbs[:DW] = D[8]; 
interProbs[:DN] = D[9]; interProbs[:DT] = D[10]; interProbs[:DQ] = D[10]; interProbs[:DY] = D[11]; interProbs[:DP] = D[11]; interProbs[:DC] = D[11]; 
interProbs[:DD] = D[12]; interProbs[:DG] = 0.0;  
C = "ppois(8, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:CA] = C; interProbs[:CR] = C; interProbs[:CN] = C; interProbs[:CD] = C; interProbs[:CC] = C; interProbs[:CQ] = C; 
interProbs[:CE] = C; interProbs[:CH] = C; interProbs[:CI] = C; interProbs[:CL] = C; interProbs[:CK] = C; interProbs[:CM] = C; 
interProbs[:CF] = C; interProbs[:CP] = C; interProbs[:CS] = C; interProbs[:CT] = C; interProbs[:CW] = C; interProbs[:CY] = C; 
interProbs[:CV] = C; interProbs[:CG] = 0.0;  
Q = "ppois(0:8, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:QI] = Q[1]; interProbs[:QF] = Q[1]; interProbs[:QV] = Q[1]; interProbs[:QQ] = Q[2]; interProbs[:QL] = Q[3]; interProbs[:QM] = Q[4]; 
interProbs[:QA] = Q[4]; interProbs[:QN] = Q[5]; interProbs[:QD] = Q[5]; interProbs[:QH] = Q[6]; interProbs[:QY] = Q[6]; interProbs[:QC] = Q[6]; 
interProbs[:QE] = Q[7]; interProbs[:QS] = Q[7]; interProbs[:QP] = Q[8]; interProbs[:QR] = Q[9]; interProbs[:QT] = Q[9]; interProbs[:QW] = Q[9]; 
interProbs[:QK] =Q[9]; interProbs[:QG] = 0.0; 
E = "ppois(0:9, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:ER] = E[1]; interProbs[:EK] = E[1]; interProbs[:EI] = E[2]; interProbs[:EV] = E[2]; interProbs[:EL] = E[3]; interProbs[:EF] = E[3]; 
interProbs[:EM] = E[4]; interProbs[:ED] = E[4]; interProbs[:EA] = E[4]; interProbs[:EW] = E[5]; interProbs[:EY] = E[6]; interProbs[:EE] = E[6]; 
interProbs[:EN] = E[7]; interProbs[:EQ] = E[8]; interProbs[:EH] = E[8]; interProbs[:ES] = E[8]; interProbs[:EC] = E[9]; interProbs[:EP] = E[10]; 
interProbs[:ET] = E[10]; interProbs[:EG] = 0.0; 
H = "ppois(0:8, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:HD] = H[1]; interProbs[:HH] = H[1]; interProbs[:HI] = H[2]; interProbs[:HL] = H[3]; interProbs[:HF] = H[3]; interProbs[:HV] = H[3]; 
interProbs[:HM] = H[3]; interProbs[:HA] = H[4]; interProbs[:HR] = H[4]; interProbs[:HE] = H[5]; interProbs[:HS] = H[5]; interProbs[:HC] = H[6]; 
interProbs[:HQ] = H[6]; interProbs[:HK] = H[6]; interProbs[:HW] = H[6]; interProbs[:HP] = H[7]; interProbs[:HT] = H[8]; interProbs[:HY] = H[8]; 
interProbs[:HN] = H[9]; interProbs[:HG] = 0.0; 
I = "ppois(0:11, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:ID] = I[1]; interProbs[:IR] = I[2]; interProbs[:IN] = I[2]; interProbs[:IE] = I[2]; interProbs[:II] = I[3]; interProbs[:IQ] = I[4]; 
interProbs[:IH] = I[4]; interProbs[:IS] = I[4]; interProbs[:IK] = I[4]; interProbs[:IL] = I[5]; interProbs[:IV] = I[5]; interProbs[:IM] = I[6]; 
interProbs[:IP] = I[7]; interProbs[:IT] = I[8]; interProbs[:IW] = I[8]; interProbs[:IF] = I[9]; interProbs[:IC] = I[10]; interProbs[:IA] = I[11]; 
interProbs[:IY] = I[12]; interProbs[:IG] = 0.0; 
L = "ppois(0:12, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:LD] = L[1]; interProbs[:LN] = L[2]; interProbs[:LE] = L[3]; interProbs[:LR] = L[4]; interProbs[:LK] = L[4]; interProbs[:LS] = L[4]; 
interProbs[:LL] = L[5]; interProbs[:LI] = L[6]; interProbs[:LV] = L[6]; interProbs[:LQ] = L[7]; interProbs[:LH] = L[7]; interProbs[:LT] = L[7]; 
interProbs[:LC] = L[8]; interProbs[:LP] = L[8]; interProbs[:LF] = L[9]; interProbs[:LM] = L[10]; interProbs[:LW] = L[11]; interProbs[:LY] = L[12]; 
interProbs[:LA] = L[13]; interProbs[:LG] = 0.0; 
K = "ppois(0:12, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:KE] = K[1]; interProbs[:KD] = K[2]; interProbs[:KR] = K[3]; interProbs[:KA] = K[4]; interProbs[:KI] = K[4]; interProbs[:KL] = K[4]; 
interProbs[:KV] = K[4]; interProbs[:KF] = K[5]; interProbs[:KK] = K[6]; interProbs[:KP] = K[7]; interProbs[:KM] = K[7]; interProbs[:KC] = K[8];
interProbs[:KH] = K[8]; interProbs[:KW] = K[9]; interProbs[:KN] = K[10]; interProbs[:KQ] = K[11]; interProbs[:KT] = K[12]; interProbs[:KS] = K[13]; 
interProbs[:KY] = K[13]; interProbs[:KG] = 0.0; 
M = "ppois(0:9, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:MM] = M[1]; interProbs[:MD] = M[2]; interProbs[:MR] = M[3]; interProbs[:MN] = M[3]; interProbs[:ME] = M[3]; interProbs[:MH] = M[4]; 
interProbs[:MS] = M[4]; interProbs[:MQ] = M[5]; interProbs[:MK] = M[5]; interProbs[:MC] = M[6]; interProbs[:MP] = M[6]; interProbs[:MT] = M[6]; 
interProbs[:MW] = M[6]; interProbs[:MI] = M[7]; interProbs[:ML] = M[8]; interProbs[:MF] = M[8]; interProbs[:MV] = M[9]; interProbs[:MY] = M[10]; 
interProbs[:MA] = M[10]; interProbs[:MG] = 0.0; 
F = "ppois(0:11, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:FD] = F[1]; interProbs[:FE] = F[2]; interProbs[:FN] = F[2]; interProbs[:FR] = F[3]; interProbs[:FQ] = F[3]; interProbs[:FK] = F[4]; 
interProbs[:FH] = F[5]; interProbs[:FS] = F[5]; interProbs[:FT] = F[5]; interProbs[:FF] = F[6]; interProbs[:FI] = F[7]; interProbs[:FL] = F[7]; 
interProbs[:FV] = F[7]; interProbs[:FC] = F[8]; interProbs[:FA] = F[9]; interProbs[:FM] = F[9]; interProbs[:FW] = F[10]; interProbs[:FY] = F[11]; 
interProbs[:FP] = F[12]; interProbs[:FG] = 0.0; 
P = "ppois(0:8, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:PW] = P[1]; interProbs[:PY] = P[2]; interProbs[:PI] = P[3]; interProbs[:PD] = P[4]; interProbs[:PL] = P[4]; interProbs[:PK] = P[4]; 
interProbs[:PV] = P[4]; interProbs[:PA] = P[5]; interProbs[:PC] = P[5]; interProbs[:PM] = P[5]; interProbs[:PQ] = P[6]; interProbs[:PP] = P[6]; 
interProbs[:PN] = P[7]; interProbs[:PT] = P[7]; interProbs[:PH] = P[8]; interProbs[:PS] = P[8]; interProbs[:PE] = P[9]; interProbs[:PR] = 0; 
interProbs[:PF] = 0; interProbs[:PG] = 0.0; 
S = "ppois(0:11, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:SD] = S[1]; interProbs[:SL] = S[2]; interProbs[:SI] = S[3]; interProbs[:SV] = S[3]; interProbs[:SA] = S[4]; interProbs[:SM] = S[4]; 
interProbs[:SF] = S[4]; interProbs[:SN] = S[5]; interProbs[:SQ] = S[6]; interProbs[:SE] = S[6]; interProbs[:SH] = S[6]; interProbs[:SC] = S[7]; 
interProbs[:SY] = S[7]; interProbs[:SS] = S[8]; interProbs[:SP] = S[9]; interProbs[:ST] = S[10]; interProbs[:SW] = S[10]; interProbs[:SK] = S[11]; 
interProbs[:SR] = S[12]; interProbs[:SG] = 0.0; 
T = "ppois(0:11, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:TL] = T[1]; interProbs[:TF] = T[1]; interProbs[:TD] = T[2]; interProbs[:TI] = T[3]; interProbs[:TW] = T[3]; interProbs[:TV] = T[3]; 
interProbs[:TN] = T[4]; interProbs[:TR] = T[5]; interProbs[:TC] = T[5]; interProbs[:TM] = T[5]; interProbs[:TY] = T[5]; interProbs[:TT] = T[6]; 
interProbs[:TA] = T[7]; interProbs[:TP] = T[8]; interProbs[:TQ] = T[9]; interProbs[:TS] = T[10]; interProbs[:TK] = T[11]; interProbs[:TE] = T[12]; 
interProbs[:TH] = T[12]; interProbs[:TG] = 0.0; 
W = "ppois(0:9, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:WP] = W[1]; interProbs[:WD] = W[2]; interProbs[:WE] = W[3]; interProbs[:WN] = W[4]; interProbs[:WI] = W[5]; interProbs[:WT] = W[5]; 
interProbs[:WC] = W[5]; interProbs[:WH] = W[6]; interProbs[:WL] = W[7]; interProbs[:WK] = W[7]; interProbs[:WM] = W[7]; interProbs[:WF] = W[7]; 
interProbs[:WY] = W[7]; interProbs[:WV] = W[7]; interProbs[:WA] = W[8]; interProbs[:WR] = W[8]; interProbs[:WQ] = W[9]; interProbs[:WS] = W[9]; 
interProbs[:WW] = W[10]; interProbs[:WG] = 0.0;  
Y = "ppois(0:7, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:YP] = Y[1]; interProbs[:YD] = Y[2]; interProbs[:YE] = Y[2]; interProbs[:YN] = Y[2]; interProbs[:YQ] = Y[3]; interProbs[:YT] = Y[3]; 
interProbs[:YC] = Y[4]; interProbs[:YS] = Y[4]; interProbs[:YW] = Y[4]; interProbs[:YR] = Y[5]; interProbs[:YY] = Y[5]; interProbs[:YL] = Y[6]; 
interProbs[:YA] = Y[7]; interProbs[:YI] = Y[7]; interProbs[:YM] = Y[7]; interProbs[:YF] = Y[7]; interProbs[:YH] = Y[8]; interProbs[:YK] = Y[8]; 
interProbs[:YV] = Y[8]; interProbs[:YG] = 0.0; 
V = "ppois(0:10, lambda = 10, lower.tail = F)" |> rcopy
interProbs[:VD] = V[1]; interProbs[:VE] = V[2]; interProbs[:VR] = V[3]; interProbs[:VN] = V[3]; interProbs[:VQ] = V[4]; interProbs[:VK] = V[4]; 
interProbs[:VV] = V[5]; interProbs[:VI] = V[5]; interProbs[:VL] = V[5]; interProbs[:VS] = V[6]; interProbs[:VH] = V[6]; interProbs[:VF] = V[7]; 
interProbs[:VC] = V[8]; interProbs[:VP] = V[8]; interProbs[:VT] = V[8]; interProbs[:VA] = V[9]; interProbs[:VM] = V[9]; interProbs[:VW] = V[10]; 
interProbs[:VY] = V[11]; interProbs[:VG] = 0.0; 
G = 0.0
interProbs[:GA] = G; interProbs[:GR] = G; interProbs[:GN] = G; interProbs[:GD] = G; interProbs[:GC] = G; interProbs[:GQ] = G; 
interProbs[:GE] = G; interProbs[:GH] = G; interProbs[:GI] = G; interProbs[:GL] = G; interProbs[:GK] = G; interProbs[:GM] = G; 
interProbs[:GF] = G; interProbs[:GP] = G; interProbs[:GS] = G; interProbs[:GT] = G; interProbs[:GW] = G; interProbs[:GY] = G; 
interProbs[:GV] = G; interProbs[:GG] = G; 

interProbs[:G] = 0.0; interProbs[:L] = 0.0; interProbs[:W] = 0.0; interProbs[:K] = 0.0; interProbs[:A] = 0.0; interProbs[:I] = 0.0; 
interProbs[:Y] = 0.0; interProbs[:H] = 0.0; 

#Add the length of a peptide bond to each step away from the amino acid
function pepBond(x)
				0.8*x + 0.132
end

#Create a new table that will be called from in the loop to implement the pepBond function
distTab = Dict{Symbol,Function}()

for n in keys(interProbs)
				distTab[symbol(n)] = pepBond
end

#Table containing the relative sizes of amino acids, generated using their molecular weights
sizeTab = Dict{Symbol, Float64}()
sizeTab[:G] = 0.5705; sizeTab[:A] = 0.7109; sizeTab[:S] = 0.8708; sizeTab[:T] = 1.0111; sizeTab[:C] = 1.0315; sizeTab[:V] = 0.9914; 
sizeTab[:L] = 1.1316; sizeTab[:I] = 1.1316; sizeTab[:M] = 1.3119; sizeTab[:P] = 0.9712; sizeTab[:F] = 1.4718; sizeTab[:Y] = 1.6318; 
sizeTab[:W] = 1.8621; sizeTab[:D] = 1.1509; sizeTab[:E] = 1.2912; sizeTab[:N] = 1.1411; sizeTab[:Q] = 1.2814; sizeTab[:H] = 1.3714; 
sizeTab[:K] = 1.2817; sizeTab[:R] = 1.5619;
#First iteration
finalInter = Dict{Symbol, Float64}()
interFile = open("interProbs.csv", "w")
#Calculate probability of interacting for every possible pair of amino acids in sequence
for i = 1:length(aaSeq)
				distance = 0
				for q = i:length(aaSeq)
								if q-i > 1
								    pairSeq = symbol(string(aaSeq[i], aaSeq[q]))
								    pairProbs = interProbs[pairSeq]
								    distance = Float64(sizeTab[symbol(aaSeq[q])]) + Float64(distTab[pairSeq](abs(q-i)))
								    interaction = Float64(interProbs[pairSeq])/distance
								    interaction2 = Float64(interaction)
				        df = "$pairSeq,$interaction"
				        println(df)
								    write(interFile, df,"\n")
								    finalInter[pairSeq] = interaction
								else
								    pairSeq = symbol(string(aaSeq[i], aaSeq[q]))
												interaction = Float64(0)
												df = "$pairSeq,$interaction"
												write(interFile, df,"\n")
												finalInter[pairSeq] = interaction
								end
				end
end
close(interFile)
#Getting the maximum, and using it to make the first fold
maxInter2 = maximum(values(finalInter))
maxInter = Float64(maxInter2)
println(maxInter)
maxKey = collect(keys(finalInter))[indmax(collect(values(finalInter)))]
maxKey = string(maxKey)
firstAA = Char(maxKey[1])
secondAA = Char(maxKey[2])
reg_string_tmp = "$firstAA[A-Z]{1,5}$secondAA"
reg_string = Regex(reg_string_tmp)
search_str = search(aaSeq, reg_string)
println("$firstAA - $secondAA")
println(search_str)

distTab2 = Dict{Symbol,Function}()

for n in keys(interProbs)
				distTab2[symbol(n)] = pepBond
end
aaSeq2 = replace(aaSeq, reg_string, "")
aaSeq2 = string(aaSeq2)
#Second iteration using the folded sequence
finalInter2 = Dict{Symbol, Float64}()
interFile2 = open("interProbs2.csv", "w")
for i = 1:length(aaSeq2)
				distance = 0
				for q = i:length(aaSeq2)
								if q-i > 1
								    pairSeq = symbol(string(aaSeq2[i], aaSeq2[q]))
								    pairProbs = interProbs[pairSeq]
								    distance2 = Float64(sizeTab[symbol(aaSeq2[q])]) + Float64(distTab2[pairSeq](abs(q-i)))
								    interaction2 = Float64(interProbs[pairSeq])/distance2
				        df2 = "$pairSeq,$interaction2"
				        println(df2)
								    write(interFile2, df2,"\n")
								    finalInter2[pairSeq] = interaction2
								else
								    pairSeq = symbol(string(aaSeq2[i], aaSeq2[q]))
												interaction2 = Float64(0)
												df2 = "$pairSeq,$interaction2"
												write(interFile2, df2,"\n")
												finalInter2[pairSeq] = interaction2
								end
				end
end
close(interFile2)

#Making the second fold
maxInter3 = maximum(values(finalInter2))
maxInter4 = Float64(maxInter3)
println(maxInter4)
maxKey4 = collect(keys(finalInter2))[indmax(collect(values(finalInter2)))]
maxKey4 = string(maxKey4)
firstAA2 = Char(maxKey4[1])
secondAA2 = Char(maxKey4[2])
reg_string_tmp2 = "$firstAA2[A-Z]{1,5}$secondAA2"
reg_string2 = Regex(reg_string_tmp2)
search_str2 = search(aaSeq2, reg_string2)
println("$firstAA2 - $secondAA2")
println(search_str2)

aaSeq3 = replace(aaSeq2, reg_string2, "")

#Third iteration
distTab3 = Dict{Symbol,Function}()

for n in keys(interProbs)
				distTab3[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq3 = string(aaSeq3)
finalInter3 = Dict{Symbol, Float64}()
interFile3 = open("interProbs3.csv", "w")
for i = 1:length(aaSeq3)
				distance = 0
				for q = i:length(aaSeq3)
								if q-i > 1
								    pairSeq = symbol(string(aaSeq3[i], aaSeq3[q]))
								    pairProbs = interProbs[pairSeq]
								    distance3 = Float64(sizeTab[symbol(aaSeq3[q])]) + Float64(distTab3[pairSeq](abs(q-i)))
								    interaction3 = Float64(interProbs[pairSeq])/distance3
				        df3 = "$pairSeq,$interaction3"
				        println(df3)
								    write(interFile3, df3,"\n")
								    finalInter3[pairSeq] = interaction3
								else
								    pairSeq = symbol(string(aaSeq3[i], aaSeq3[q]))
												interaction3 = Float64(0)
												df3 = "$pairSeq,$interaction3"
												write(interFile3, df3,"\n")
												finalInter3[pairSeq] = interaction3
								end
				end
end
close(interFile3)
for j = finalInter3
				println(j)
end

#Making the second fold
maxInter5 = maximum(values(finalInter3))
maxInter6 = Float64(maxInter5)
println(maxInter6)
maxKey5 = collect(keys(finalInter3))[indmax(collect(values(finalInter3)))]
maxKey5 = string(maxKey5)
firstAA3 = Char(maxKey5[1])
secondAA3 = Char(maxKey5[2])
reg_string_tmp3 = "$firstAA3[A-Z]{1,5}$secondAA3"
reg_string3 = Regex(reg_string_tmp3)
search_str3 = search(aaSeq3, reg_string3)
println("$firstAA3 - $secondAA3")
println(search_str3)

aaSeq4 = replace(aaSeq3, reg_string3, "")

#Third iteration
distTab4 = Dict{Symbol,Function}()

for n in keys(interProbs)
				distTab4[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq4 = string(aaSeq4)
finalInter4 = Dict{Symbol, Float64}()
interFile4 = open("interProbs4.csv", "w")
for i = 1:length(aaSeq4)
				distance = 0
				for q = i:length(aaSeq4)
								if q-i > 1
								    pairSeq = symbol(string(aaSeq4[i], aaSeq4[q]))
								    pairProbs = interProbs[pairSeq]
								    distance4 = Float64(sizeTab[symbol(aaSeq4[q])]) + Float64(distTab4[pairSeq](abs(q-i)))
								    interaction4 = Float64(interProbs[pairSeq])/distance4
				        df4 = "$pairSeq,$interaction4"
				        println(df4)
								    write(interFile4, df4,"\n")
								    finalInter4[pairSeq] = interaction4
								else
								    pairSeq = symbol(string(aaSeq4[i], aaSeq4[q]))
												interaction4 = Float64(0)
												df4 = "$pairSeq,$interaction4"
												write(interFile4, df4,"\n")
												finalInter4[pairSeq] = interaction4
								end
				end
end
close(interFile4)
for j = finalInter4
				println(j)
end

#Making the second fold
maxInter7 = maximum(values(finalInter4))
maxInter8 = Float64(maxInter7)
println(maxInter8)
maxKey6 = collect(keys(finalInter4))[indmax(collect(values(finalInter4)))]
maxKey6 = string(maxKey6)
firstAA4 = Char(maxKey6[1])
secondAA4 = Char(maxKey6[2])
reg_string_tmp4 = "$firstAA4[A-Z]{1,5}$secondAA4"
reg_string4 = Regex(reg_string_tmp4)
search_str4 = search(aaSeq4, reg_string4)
println("$firstAA4 - $secondAA4")
println(search_str4)

aaSeq5 = replace(aaSeq4, reg_string4, "")

distTab5 = Dict{Symbol,Function}()

 for n in keys(interProbs)
     distTab5[symbol(n)] = pepBond
 end
 #println(aaSeq)
 #println(aaSeq2)
 aaSeq5 = string(aaSeq5)
 finalInter5 = Dict{Symbol, Float64}()
 interFile5 = open("interProbs5.csv", "w")
 for i = 1:length(aaSeq5)
     distance = 0
     for q = i:length(aaSeq5)
         if q-i > 1
             pairSeq = symbol(string(aaSeq5[i], aaSeq5[q]))
             pairProbs = interProbs[pairSeq]
             distance5 = Float64(sizeTab[symbol(aaSeq5[q])]) + Float64(distTab5[pairSeq](abs(q-i)))
             interaction5 = Float64(interProbs[pairSeq])/distance5
             df5 = "$pairSeq,$interaction5"
             println(df5)
             write(interFile5, df5,"\n")
             finalInter5[pairSeq] = interaction5
         else
             pairSeq = symbol(string(aaSeq5[i], aaSeq5[q]))
             interaction5 = Float64(0)
             df5 = "$pairSeq,$interaction5"
             write(interFile5, df5,"\n")
             finalInter5[pairSeq] = interaction5
         end
     end
 end
 close(interFile5)
 for j = finalInter5
     println(j)
 end

 #Making the second fold
 maxInter9 = maximum(values(finalInter5))
 maxInter10 = Float64(maxInter9)
 println(maxInter10)
 maxKey7 = collect(keys(finalInter5))[indmax(collect(values(finalInter5)))]
 maxKey7 = string(maxKey7)
 firstAA5 = Char(maxKey7[1])
 secondAA5 = Char(maxKey7[2])
 reg_string_tmp5 = "$firstAA5[A-Z]{1,5}$secondAA5"
 reg_string5 = Regex(reg_string_tmp5)
 search_str5 = search(aaSeq5, reg_string5)
 println("$firstAA5 - $secondAA5")
 println(search_str5)

 aaSeq6 = replace(aaSeq5, reg_string5, "")

distTab6 = Dict{Symbol,Function}()

 for n in keys(interProbs)
     distTab6[symbol(n)] = pepBond
 end
 #println(aaSeq)
 #println(aaSeq2)
 aaSeq6 = string(aaSeq6)
 finalInter6 = Dict{Symbol, Float64}()
 interFile6 = open("interProbs6.csv", "w")
 for i = 1:length(aaSeq6)
     distance = 0
     for q = i:length(aaSeq6)
         if q-i > 1
             pairSeq = symbol(string(aaSeq6[i], aaSeq6[q]))
             pairProbs = interProbs[pairSeq]
             distance6 = Float64(sizeTab[symbol(aaSeq6[q])]) + Float64(distTab6[pairSeq](abs(q-i)))
             interaction6 = Float64(interProbs[pairSeq])/distance6
             df6 = "$pairSeq,$interaction6"
             println(df6)
             write(interFile6, df6,"\n")
             finalInter6[pairSeq] = interaction6
         else
             pairSeq = symbol(string(aaSeq6[i], aaSeq6[q]))
             interaction6 = Float64(0)
             df6 = "$pairSeq,$interaction6"
             write(interFile6, df6,"\n")
             finalInter6[pairSeq] = interaction6
         end
     end
 end
 close(interFile6)
 for j = finalInter6
     println(j)
 end

 #Making the second fold
 maxInter11 = maximum(values(finalInter6))
 maxInter12 = Float64(maxInter11)
 println(maxInter12)
 maxKey8 = collect(keys(finalInter6))[indmax(collect(values(finalInter6)))]
 maxKey8 = string(maxKey8)
 firstAA6 = Char(maxKey8[1])
 secondAA6 = Char(maxKey8[2])
 reg_string_tmp6 = "$firstAA6[A-Z]{1,5}$secondAA6"
 reg_string6 = Regex(reg_string_tmp6)
 search_str6 = search(aaSeq6, reg_string6)
 println("$firstAA6 - $secondAA6")
 println(search_str6)

aaSeq7 = replace(aaSeq6, reg_string6, "")

distTab7 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab7[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq7 = string(aaSeq7)
finalInter7 = Dict{Symbol, Float64}()
interFile7 = open("interProbs7.csv", "w")
for i = 1:length(aaSeq7)
    distance = 0
    for q = i:length(aaSeq7)
        if q-i > 1
            pairSeq = symbol(string(aaSeq7[i], aaSeq7[q]))
            pairProbs = interProbs[pairSeq]
            distance7 = Float64(sizeTab[symbol(aaSeq7[q])]) + Float64(distTab7[pairSeq](abs(q-i)))
            interaction7 = Float64(interProbs[pairSeq])/distance7
            df7 = "$pairSeq,$interaction7"
            println(df7)
            write(interFile7, df7,"\n")
            finalInter7[pairSeq] = interaction7
        else
            pairSeq = symbol(string(aaSeq7[i], aaSeq7[q]))
            interaction7 = Float64(0)
            df7 = "$pairSeq,$interaction7"
            write(interFile7, df7,"\n")
            finalInter7[pairSeq] = interaction7
        end
    end
end
close(interFile7)
for j = finalInter7
    println(j)
end

#Making the second fold
maxInter13 = maximum(values(finalInter7))
maxInter14 = Float64(maxInter13)
println(maxInter14)
maxKey9 = collect(keys(finalInter7))[indmax(collect(values(finalInter7)))]
maxKey9 = string(maxKey9)
firstAA7 = Char(maxKey9[1])
secondAA7 = Char(maxKey9[2])
reg_string_tmp7 = "$firstAA7[A-Z]{1,5}$secondAA7"
reg_string7 = Regex(reg_string_tmp7)
search_str7 = search(aaSeq7, reg_string7)
println("$firstAA7 - $secondAA7")
println(search_str7)
aaSeq8 = replace(aaSeq7, reg_string7, "")

distTab8 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab8[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq8 = string(aaSeq8)
finalInter8 = Dict{Symbol, Float64}()
interFile8 = open("interProbs8.csv", "w")
for i = 1:length(aaSeq8)
    distance = 0
    for q = i:length(aaSeq8)
        if q-i > 1
            pairSeq = symbol(string(aaSeq8[i], aaSeq8[q]))
            pairProbs = interProbs[pairSeq]
            distance8 = Float64(sizeTab[symbol(aaSeq8[q])]) + Float64(distTab8[pairSeq](abs(q-i)))
            interaction8 = Float64(interProbs[pairSeq])/distance8
            df8 = "$pairSeq,$interaction8"
            println(df8)
            write(interFile8, df8,"\n")
            finalInter8[pairSeq] = interaction8
        else
            pairSeq = symbol(string(aaSeq8[i], aaSeq8[q]))
            interaction8 = Float64(0)
            df8 = "$pairSeq,$interaction8"
            write(interFile8, df8,"\n")
            finalInter8[pairSeq] = interaction8
        end
    end
end
close(interFile8)
for j = finalInter8
    println(j)
end

#Making the second fold
maxInter15 = maximum(values(finalInter8))
maxInter16 = Float64(maxInter15)
println(maxInter16)
maxKey8 = collect(keys(finalInter8))[indmax(collect(values(finalInter8)))]
maxKey8 = string(maxKey8)
firstAA8 = Char(maxKey8[1])
secondAA8 = Char(maxKey8[2])
reg_string_tmp8 = "$firstAA8[A-Z]{1,5}$secondAA8"
reg_string8 = Regex(reg_string_tmp8)
search_str8 = search(aaSeq8, reg_string8)
println("$firstAA8 - $secondAA8")
println(search_str8)
aaSeq9 = replace(aaSeq8, reg_string8, "")


distTab9 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab9[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq9 = string(aaSeq9)
finalInter9 = Dict{Symbol, Float64}()
interFile9 = open("interProbs9.csv", "w")
for i = 1:length(aaSeq9)
    distance = 0
    for q = i:length(aaSeq9)
        if q-i > 1
            pairSeq = symbol(string(aaSeq9[i], aaSeq9[q]))
            pairProbs = interProbs[pairSeq]
            distance9 = Float64(sizeTab[symbol(aaSeq9[q])]) + Float64(distTab9[pairSeq](abs(q-i)))
            interaction9 = Float64(interProbs[pairSeq])/distance9
            df9 = "$pairSeq,$interaction9"
            println(df9)
            write(interFile9, df9,"\n")
            finalInter9[pairSeq] = interaction9
        else
            pairSeq = symbol(string(aaSeq9[i], aaSeq9[q]))
            interaction9 = Float64(0)
            df9 = "$pairSeq,$interaction9"
            write(interFile9, df9,"\n")
            finalInter9[pairSeq] = interaction9
        end
    end
end
close(interFile9)
for j = finalInter9
    println(j)
end

#Making the second fold
maxInter17 = maximum(values(finalInter9))
maxInter18 = Float64(maxInter17)
println(maxInter18)
maxKey9 = collect(keys(finalInter9))[indmax(collect(values(finalInter9)))]
maxKey9 = string(maxKey9)
firstAA9 = Char(maxKey9[1])
secondAA9 = Char(maxKey9[2])
reg_string_tmp9 = "$firstAA9[A-Z]{1,5}$secondAA9"
reg_string9 = Regex(reg_string_tmp9)
search_str9 = search(aaSeq9, reg_string9)
println("$firstAA9 - $secondAA9")
println(search_str9)

aaSeq10 = replace(aaSeq9, reg_string9, "")

distTab10 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab10[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq10 = string(aaSeq10)
finalInter10 = Dict{Symbol, Float64}()
interFile10 = open("interProbs10.csv", "w")
for i = 1:length(aaSeq10)
    distance = 0
    for q = i:length(aaSeq10)
        if q-i > 1
            pairSeq = symbol(string(aaSeq10[i], aaSeq10[q]))
            pairProbs = interProbs[pairSeq]
            distance10 = Float64(sizeTab[symbol(aaSeq10[q])]) + Float64(distTab10[pairSeq](abs(q-i)))
            interaction10 = Float64(interProbs[pairSeq])/distance10
            df10 = "$pairSeq,$interaction10"
            println(df10)
            write(interFile10, df10,"\n")
            finalInter10[pairSeq] = interaction10
        else
            pairSeq = symbol(string(aaSeq10[i], aaSeq10[q]))
            interaction10 = Float64(0)
            df10 = "$pairSeq,$interaction10"
            write(interFile10, df10,"\n")
            finalInter10[pairSeq] = interaction10
        end
    end
end
close(interFile10)
for j = finalInter10
    println(j)
end

#Making the second fold
maxInter19 = maximum(values(finalInter10))
maxInter20 = Float64(maxInter19)
println(maxInter20)
maxKey10 = collect(keys(finalInter10))[indmax(collect(values(finalInter10)))]
maxKey10 = string(maxKey10)
firstAA10 = Char(maxKey10[1])
secondAA10 = Char(maxKey10[2])
reg_string_tmp10 = "$firstAA10[A-Z]{1,5}$secondAA10"
reg_string10 = Regex(reg_string_tmp10)
search_str10 = search(aaSeq10, reg_string10)
println("$firstAA10 - $secondAA10")
println(search_str10)

aaSeq11 = replace(aaSeq10, reg_string10, "")

distTab11 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab11[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq11 = string(aaSeq11)
finalInter11 = Dict{Symbol, Float64}()
interFile11 = open("interProbs11.csv", "w")
for i = 1:length(aaSeq11)
    distance = 0
    for q = i:length(aaSeq11)
        if q-i > 1
            pairSeq = symbol(string(aaSeq11[i], aaSeq11[q]))
            pairProbs = interProbs[pairSeq]
            distance11 = Float64(sizeTab[symbol(aaSeq11[q])]) + Float64(distTab11[pairSeq](abs(q-i)))
            interaction11 = Float64(interProbs[pairSeq])/distance11
            df11 = "$pairSeq,$interaction11"
            println(df11)
            write(interFile11, df11,"\n")
            finalInter11[pairSeq] = interaction11
        else
            pairSeq = symbol(string(aaSeq11[i], aaSeq11[q]))
            interaction11 = Float64(0)
            df11 = "$pairSeq,$interaction11"
            write(interFile11, df11,"\n")
            finalInter11[pairSeq] = interaction11
        end
    end
end
close(interFile11)
for j = finalInter11
    println(j)
end

#Making the second fold
maxInter21 = maximum(values(finalInter11))
maxInter22 = Float64(maxInter21)
println(maxInter22)
maxKey11 = collect(keys(finalInter11))[indmax(collect(values(finalInter11)))]
maxKey11 = string(maxKey11)
firstAA11 = Char(maxKey11[1])
secondAA11 = Char(maxKey11[2])
reg_string_tmp11 = "$firstAA11[A-Z]{1,5}$secondAA11"
reg_string11 = Regex(reg_string_tmp11)
search_str11 = search(aaSeq11, reg_string11)
println("$firstAA11 - $secondAA11")
println(search_str11)

aaSeq12 = replace(aaSeq11, reg_string11, "")

distTab12 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab12[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq12 = string(aaSeq12)
finalInter12 = Dict{Symbol, Float64}()
interFile12 = open("interProbs12.csv", "w")
for i = 1:length(aaSeq12)
    distance = 0
    for q = i:length(aaSeq12)
        if q-i > 1
            pairSeq = symbol(string(aaSeq12[i], aaSeq12[q]))
            pairProbs = interProbs[pairSeq]
            distance12 = Float64(sizeTab[symbol(aaSeq12[q])]) + Float64(distTab12[pairSeq](abs(q-i)))
            interaction12 = Float64(interProbs[pairSeq])/distance12
            df12 = "$pairSeq,$interaction12"
            println(df12)
            write(interFile12, df12,"\n")
            finalInter12[pairSeq] = interaction12
        else
            pairSeq = symbol(string(aaSeq12[i], aaSeq12[q]))
            interaction12 = Float64(0)
            df12 = "$pairSeq,$interaction12"
            write(interFile12, df12,"\n")
            finalInter12[pairSeq] = interaction12
        end
    end
end
close(interFile12)
for j = finalInter12
    println(j)
end

#Making the second fold
maxInter23 = maximum(values(finalInter12))
maxInter24 = Float64(maxInter23)
println(maxInter24)
maxKey12 = collect(keys(finalInter12))[indmax(collect(values(finalInter12)))]
maxKey12 = string(maxKey12)
firstAA12 = Char(maxKey12[1])
secondAA12 = Char(maxKey12[2])
reg_string_tmp12 = "$firstAA12[A-Z]{1,5}$secondAA12"
reg_string12 = Regex(reg_string_tmp12)
search_str12 = search(aaSeq12, reg_string12)
println("$firstAA12 - $secondAA12")
println(search_str12)

aaSeq13 = replace(aaSeq12, reg_string12, "")

distTab13 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab13[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq13 = string(aaSeq13)
finalInter13 = Dict{Symbol, Float64}()
interFile13 = open("interProbs13.csv", "w")
for i = 1:length(aaSeq13)
    distance = 0
    for q = i:length(aaSeq13)
        if q-i > 1
            pairSeq = symbol(string(aaSeq13[i], aaSeq13[q]))
            pairProbs = interProbs[pairSeq]
            distance13 = Float64(sizeTab[symbol(aaSeq13[q])]) + Float64(distTab13[pairSeq](abs(q-i)))
            interaction13 = Float64(interProbs[pairSeq])/distance13
            df13 = "$pairSeq,$interaction13"
            println(df13)
            write(interFile13, df13,"\n")
            finalInter13[pairSeq] = interaction13
        else
            pairSeq = symbol(string(aaSeq13[i], aaSeq13[q]))
            interaction13 = Float64(0)
            df13 = "$pairSeq,$interaction13"
            write(interFile13, df13,"\n")
            finalInter13[pairSeq] = interaction13
        end
    end
end
close(interFile13)
for j = finalInter13
    println(j)
end

#Making the second fold
maxInter25 = maximum(values(finalInter13))
maxInter26 = Float64(maxInter25)
println(maxInter26)
maxKey13 = collect(keys(finalInter13))[indmax(collect(values(finalInter13)))]
maxKey13 = string(maxKey13)
firstAA13 = Char(maxKey13[1])
secondAA13 = Char(maxKey13[2])
reg_string_tmp13 = "$firstAA13[A-Z]{1,5}$secondAA13"
reg_string13 = Regex(reg_string_tmp13)
search_str13 = search(aaSeq13, reg_string13)
println("$firstAA13 - $secondAA13")
println(search_str13)

aaSeq14 = replace(aaSeq13, reg_string13, "")

distTab14 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab14[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq14 = string(aaSeq14)
finalInter14 = Dict{Symbol, Float64}()
interFile14 = open("interProbs14.csv", "w")
for i = 1:length(aaSeq14)
    distance = 0
    for q = i:length(aaSeq14)
        if q-i > 1
            pairSeq = symbol(string(aaSeq14[i], aaSeq14[q]))
            pairProbs = interProbs[pairSeq]
            distance14 = Float64(sizeTab[symbol(aaSeq14[q])]) + Float64(distTab14[pairSeq](abs(q-i)))
            interaction14 = Float64(interProbs[pairSeq])/distance14
            df14 = "$pairSeq,$interaction14"
            println(df14)
            write(interFile14, df14,"\n")
            finalInter14[pairSeq] = interaction14
        else
            pairSeq = symbol(string(aaSeq14[i], aaSeq14[q]))
            interaction14 = Float64(0)
            df14 = "$pairSeq,$interaction14"
            write(interFile14, df14,"\n")
            finalInter14[pairSeq] = interaction14
        end
    end
end
close(interFile14)
for j = finalInter14
    println(j)
end

#Making the second fold
maxInter27 = maximum(values(finalInter14))
maxInter28 = Float64(maxInter27)
println(maxInter28)
maxKey14 = collect(keys(finalInter14))[indmax(collect(values(finalInter14)))]
maxKey14 = string(maxKey14)
firstAA14 = Char(maxKey14[1])
secondAA14 = Char(maxKey14[2])
reg_string_tmp14 = "$firstAA14[A-Z]{1,5}$secondAA14"
reg_string14 = Regex(reg_string_tmp14)
search_str14 = search(aaSeq14, reg_string14)
println("$firstAA14 - $secondAA14")
println(search_str14)

aaSeq15 = replace(aaSeq14, reg_string14, "")

distTab15 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab15[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq15 = string(aaSeq15)
finalInter15 = Dict{Symbol, Float64}()
interFile15 = open("interProbs15.csv", "w")
for i = 1:length(aaSeq15)
    distance = 0
    for q = i:length(aaSeq15)
        if q-i > 1
            pairSeq = symbol(string(aaSeq15[i], aaSeq15[q]))
            pairProbs = interProbs[pairSeq]
            distance15 = Float64(sizeTab[symbol(aaSeq15[q])]) + Float64(distTab15[pairSeq](abs(q-i)))
            interaction15 = Float64(interProbs[pairSeq])/distance15
            df15 = "$pairSeq,$interaction15"
            println(df15)
            write(interFile15, df15,"\n")
            finalInter15[pairSeq] = interaction15
        else
            pairSeq = symbol(string(aaSeq15[i], aaSeq15[q]))
            interaction15 = Float64(0)
            df15 = "$pairSeq,$interaction15"
            write(interFile15, df15,"\n")
            finalInter15[pairSeq] = interaction15
        end
    end
end
close(interFile15)
for j = finalInter15
    println(j)
end

#Making the second fold
maxInter29 = maximum(values(finalInter15))
maxInter30 = Float64(maxInter29)
println(maxInter30)
maxKey15 = collect(keys(finalInter15))[indmax(collect(values(finalInter15)))]
maxKey15 = string(maxKey15)
firstAA15 = Char(maxKey15[1])
secondAA15 = Char(maxKey15[2])
reg_string_tmp15 = "$firstAA15[A-Z]{1,5}$secondAA15"
reg_string15 = Regex(reg_string_tmp15)
search_str15 = search(aaSeq15, reg_string15)
println("$firstAA15 - $secondAA15")
println(search_str15)

aaSeq16 = replace(aaSeq15, reg_string15, "")

distTab16 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab16[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq16 = string(aaSeq16)
finalInter16 = Dict{Symbol, Float64}()
interFile16 = open("interProbs16.csv", "w")
for i = 1:length(aaSeq16)
    distance = 0
    for q = i:length(aaSeq16)
        if q-i > 1
            pairSeq = symbol(string(aaSeq16[i], aaSeq16[q]))
            pairProbs = interProbs[pairSeq]
            distance16 = Float64(sizeTab[symbol(aaSeq16[q])]) + Float64(distTab16[pairSeq](abs(q-i)))
            interaction16 = Float64(interProbs[pairSeq])/distance16
            df16 = "$pairSeq,$interaction16"
            println(df16)
            write(interFile16, df16,"\n")
            finalInter16[pairSeq] = interaction16
        else
            pairSeq = symbol(string(aaSeq16[i], aaSeq16[q]))
            interaction16 = Float64(0)
            df16 = "$pairSeq,$interaction16"
            write(interFile16, df16,"\n")
            finalInter16[pairSeq] = interaction16
        end
    end
end
close(interFile16)
for j = finalInter16
    println(j)
end

#Making the second fold
maxInter31 = maximum(values(finalInter16))
maxInter32 = Float64(maxInter31)
println(maxInter32)
maxKey16 = collect(keys(finalInter16))[indmax(collect(values(finalInter16)))]
maxKey16 = string(maxKey16)
firstAA16 = Char(maxKey16[1])
secondAA16 = Char(maxKey16[2])
reg_string_tmp16 = "$firstAA16[A-Z]{1,5}$secondAA16"
reg_string16 = Regex(reg_string_tmp16)
search_str16 = search(aaSeq16, reg_string16)
println("$firstAA16 - $secondAA16")
println(search_str16)

aaSeq17 = replace(aaSeq16, reg_string16, "")

distTab17 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab17[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq17 = string(aaSeq17)
finalInter17 = Dict{Symbol, Float64}()
interFile17 = open("interProbs17.csv", "w")
for i = 1:length(aaSeq17)
    distance = 0
    for q = i:length(aaSeq17)
        if q-i > 1
            pairSeq = symbol(string(aaSeq17[i], aaSeq17[q]))
            pairProbs = interProbs[pairSeq]
            distance17 = Float64(sizeTab[symbol(aaSeq17[q])]) + Float64(distTab17[pairSeq](abs(q-i)))
            interaction17 = Float64(interProbs[pairSeq])/distance17
            df17 = "$pairSeq,$interaction17"
            println(df17)
            write(interFile17, df17,"\n")
            finalInter17[pairSeq] = interaction17
        else
            pairSeq = symbol(string(aaSeq17[i], aaSeq17[q]))
            interaction17 = Float64(0)
            df17 = "$pairSeq,$interaction17"
            write(interFile17, df17,"\n")
            finalInter17[pairSeq] = interaction17
        end
    end
end
close(interFile17)
for j = finalInter17
    println(j)
end

#Making the second fold
maxInter33 = maximum(values(finalInter17))
maxInter34 = Float64(maxInter33)
println(maxInter34)
maxKey17 = collect(keys(finalInter17))[indmax(collect(values(finalInter17)))]
maxKey17 = string(maxKey17)
firstAA17 = Char(maxKey17[1])
secondAA17 = Char(maxKey17[2])
reg_string_tmp17 = "$firstAA17[A-Z]{1,5}$secondAA17"
reg_string17 = Regex(reg_string_tmp17)
search_str17 = search(aaSeq17, reg_string17)
println("$firstAA17 - $secondAA17")
println(search_str17)

aaSeq18 = replace(aaSeq17, reg_string17, "")

distTab18 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab18[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq18 = string(aaSeq18)
finalInter18 = Dict{Symbol, Float64}()
interFile18 = open("interProbs18.csv", "w")
for i = 1:length(aaSeq18)
    distance = 0
    for q = i:length(aaSeq18)
        if q-i > 1
            pairSeq = symbol(string(aaSeq18[i], aaSeq18[q]))
            pairProbs = interProbs[pairSeq]
            distance18 = Float64(sizeTab[symbol(aaSeq18[q])]) + Float64(distTab18[pairSeq](abs(q-i)))
            interaction18 = Float64(interProbs[pairSeq])/distance18
            df18 = "$pairSeq,$interaction18"
            println(df18)
            write(interFile18, df18,"\n")
            finalInter18[pairSeq] = interaction18
        else
            pairSeq = symbol(string(aaSeq18[i], aaSeq18[q]))
            interaction18 = Float64(0)
            df18 = "$pairSeq,$interaction18"
            write(interFile18, df18,"\n")
            finalInter18[pairSeq] = interaction18
        end
    end
end
close(interFile18)
for j = finalInter18
    println(j)
end

#Making the second fold
maxInter35 = maximum(values(finalInter18))
maxInter36 = Float64(maxInter35)
println(maxInter36)
maxKey18 = collect(keys(finalInter18))[indmax(collect(values(finalInter18)))]
maxKey18 = string(maxKey18)
firstAA18 = Char(maxKey18[1])
secondAA18 = Char(maxKey18[2])
reg_string_tmp18 = "$firstAA18[A-Z]{1,5}$secondAA18"
reg_string18 = Regex(reg_string_tmp18)
search_str18 = search(aaSeq18, reg_string18)
println("$firstAA18 - $secondAA18")
println(search_str18)

aaSeq19 = replace(aaSeq18, reg_string18, "")

distTab19 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab19[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq19 = string(aaSeq19)
finalInter19 = Dict{Symbol, Float64}()
interFile19 = open("interProbs19.csv", "w")
for i = 1:length(aaSeq19)
    distance = 0
    for q = i:length(aaSeq19)
        if q-i > 1
            pairSeq = symbol(string(aaSeq19[i], aaSeq19[q]))
            pairProbs = interProbs[pairSeq]
            distance19 = Float64(sizeTab[symbol(aaSeq19[q])]) + Float64(distTab19[pairSeq](abs(q-i)))
            interaction19 = Float64(interProbs[pairSeq])/distance19
            df19 = "$pairSeq,$interaction19"
            println(df19)
            write(interFile19, df19,"\n")
            finalInter19[pairSeq] = interaction19
        else
            pairSeq = symbol(string(aaSeq19[i], aaSeq19[q]))
            interaction19 = Float64(0)
            df19 = "$pairSeq,$interaction19"
            write(interFile19, df19,"\n")
            finalInter19[pairSeq] = interaction19
        end
    end
end
close(interFile19)
for j = finalInter19
    println(j)
end

#Making the second fold
maxInter37 = maximum(values(finalInter19))
maxInter38 = Float64(maxInter37)
println(maxInter38)
maxKey19 = collect(keys(finalInter19))[indmax(collect(values(finalInter19)))]
maxKey19 = string(maxKey19)
firstAA19 = Char(maxKey19[1])
secondAA19 = Char(maxKey19[2])
reg_string_tmp19 = "$firstAA19[A-Z]{1,5}$secondAA19"
reg_string19 = Regex(reg_string_tmp19)
search_str19 = search(aaSeq19, reg_string19)
println("$firstAA19 - $secondAA19")
println(search_str19)

aaSeq20 = replace(aaSeq19, reg_string19, "")

distTab20 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab20[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq20 = string(aaSeq20)
finalInter20 = Dict{Symbol, Float64}()
interFile20 = open("interProbs20.csv", "w")
for i = 1:length(aaSeq20)
    distance = 0
    for q = i:length(aaSeq20)
        if q-i > 1
            pairSeq = symbol(string(aaSeq20[i], aaSeq20[q]))
            pairProbs = interProbs[pairSeq]
            distance20 = Float64(sizeTab[symbol(aaSeq20[q])]) + Float64(distTab20[pairSeq](abs(q-i)))
            interaction20 = Float64(interProbs[pairSeq])/distance20
            df20 = "$pairSeq,$interaction20"
            println(df20)
            write(interFile20, df20,"\n")
            finalInter20[pairSeq] = interaction20
        else
            pairSeq = symbol(string(aaSeq20[i], aaSeq20[q]))
            interaction20 = Float64(0)
            df20 = "$pairSeq,$interaction20"
            write(interFile20, df20,"\n")
            finalInter20[pairSeq] = interaction20
        end
    end
end
close(interFile20)
for j = finalInter20
    println(j)
end

#Making the second fold
maxInter39 = maximum(values(finalInter20))
maxInter40 = Float64(maxInter39)
println(maxInter40)
maxKey20 = collect(keys(finalInter20))[indmax(collect(values(finalInter20)))]
maxKey20 = string(maxKey20)
firstAA20 = Char(maxKey20[1])
secondAA20 = Char(maxKey20[2])
reg_string_tmp20 = "$firstAA20[A-Z]{1,5}$secondAA20"
reg_string20 = Regex(reg_string_tmp20)
search_str20 = search(aaSeq20, reg_string20)
println("$firstAA20 - $secondAA20")
println(search_str20)

aaSeq21 = replace(aaSeq20, reg_string20, "")

distTab21 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab21[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq21 = string(aaSeq21)
finalInter21 = Dict{Symbol, Float64}()
interFile21 = open("interProbs21.csv", "w")
for i = 1:length(aaSeq21)
    distance = 0
    for q = i:length(aaSeq21)
        if q-i > 1
            pairSeq = symbol(string(aaSeq21[i], aaSeq21[q]))
            pairProbs = interProbs[pairSeq]
            distance21 = Float64(sizeTab[symbol(aaSeq21[q])]) + Float64(distTab21[pairSeq](abs(q-i)))
            interaction21 = Float64(interProbs[pairSeq])/distance21
            df21 = "$pairSeq,$interaction21"
            println(df21)
            write(interFile21, df21,"\n")
            finalInter21[pairSeq] = interaction21
        else
            pairSeq = symbol(string(aaSeq21[i], aaSeq21[q]))
            interaction21 = Float64(0)
            df21 = "$pairSeq,$interaction21"
            write(interFile21, df21,"\n")
            finalInter21[pairSeq] = interaction21
        end
    end
end
close(interFile21)
for j = finalInter21
    println(j)
end

#Making the second fold
maxInter41 = maximum(values(finalInter21))
maxInter42 = Float64(maxInter41)
println(maxInter42)
maxKey21 = collect(keys(finalInter21))[indmax(collect(values(finalInter21)))]
maxKey21 = string(maxKey21)
firstAA21 = Char(maxKey21[1])
secondAA21 = Char(maxKey21[2])
reg_string_tmp21 = "$firstAA21[A-Z]{1,5}$secondAA21"
reg_string21 = Regex(reg_string_tmp21)
search_str21 = search(aaSeq21, reg_string21)
println("$firstAA21 - $secondAA21")
println(search_str21)

aaSeq22 = replace(aaSeq21, reg_string21, "")

distTab22 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab22[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq22 = string(aaSeq22)
finalInter22 = Dict{Symbol, Float64}()
interFile22 = open("interProbs22.csv", "w")
for i = 1:length(aaSeq22)
    distance = 0
    for q = i:length(aaSeq22)
        if q-i > 1
            pairSeq = symbol(string(aaSeq22[i], aaSeq22[q]))
            pairProbs = interProbs[pairSeq]
            distance22 = Float64(sizeTab[symbol(aaSeq22[q])]) + Float64(distTab22[pairSeq](abs(q-i)))
            interaction22 = Float64(interProbs[pairSeq])/distance22
            df22 = "$pairSeq,$interaction22"
            println(df22)
            write(interFile22, df22,"\n")
            finalInter22[pairSeq] = interaction22
        else
            pairSeq = symbol(string(aaSeq22[i], aaSeq22[q]))
            interaction22 = Float64(0)
            df22 = "$pairSeq,$interaction22"
            write(interFile22, df22,"\n")
            finalInter22[pairSeq] = interaction22
        end
    end
end
close(interFile22)
for j = finalInter22
    println(j)
end

#Making the second fold
maxInter43 = maximum(values(finalInter22))
maxInter44 = Float64(maxInter43)
println(maxInter44)
maxKey22 = collect(keys(finalInter22))[indmax(collect(values(finalInter22)))]
maxKey22 = string(maxKey22)
firstAA22 = Char(maxKey22[1])
secondAA22 = Char(maxKey22[2])
reg_string_tmp22 = "$firstAA22[A-Z]{1,5}$secondAA22"
reg_string22 = Regex(reg_string_tmp22)
search_str22 = search(aaSeq22, reg_string22)
println("$firstAA22 - $secondAA22")
println(search_str22)

aaSeq23 = replace(aaSeq22, reg_string22, "")

distTab23 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab23[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq23 = string(aaSeq23)
finalInter23 = Dict{Symbol, Float64}()
interFile23 = open("interProbs23.csv", "w")
for i = 1:length(aaSeq23)
    distance = 0
    for q = i:length(aaSeq23)
        if q-i > 1
            pairSeq = symbol(string(aaSeq23[i], aaSeq23[q]))
            pairProbs = interProbs[pairSeq]
            distance23 = Float64(sizeTab[symbol(aaSeq23[q])]) + Float64(distTab23[pairSeq](abs(q-i)))
            interaction23 = Float64(interProbs[pairSeq])/distance23
            df23 = "$pairSeq,$interaction23"
            println(df23)
            write(interFile23, df23,"\n")
            finalInter23[pairSeq] = interaction23
        else
            pairSeq = symbol(string(aaSeq23[i], aaSeq23[q]))
            interaction23 = Float64(0)
            df23 = "$pairSeq,$interaction23"
            write(interFile23, df23,"\n")
            finalInter23[pairSeq] = interaction23
        end
    end
end
close(interFile23)
for j = finalInter23
    println(j)
end

#Making the second fold
maxInter45 = maximum(values(finalInter23))
maxInter46 = Float64(maxInter45)
println(maxInter46)
maxKey23 = collect(keys(finalInter23))[indmax(collect(values(finalInter23)))]
maxKey23 = string(maxKey23)
firstAA23 = Char(maxKey23[1])
secondAA23 = Char(maxKey23[2])
reg_string_tmp23 = "$firstAA23[A-Z]{1,5}$secondAA23"
reg_string23 = Regex(reg_string_tmp23)
search_str23 = search(aaSeq23, reg_string23)
println("$firstAA23 - $secondAA23")
println(search_str23)

aaSeq24 = replace(aaSeq23, reg_string23, "")

distTab24 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab24[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq24 = string(aaSeq24)
finalInter24 = Dict{Symbol, Float64}()
interFile24 = open("interProbs24.csv", "w")
for i = 1:length(aaSeq24)
    distance = 0
    for q = i:length(aaSeq24)
        if q-i > 1
            pairSeq = symbol(string(aaSeq24[i], aaSeq24[q]))
            pairProbs = interProbs[pairSeq]
            distance24 = Float64(sizeTab[symbol(aaSeq24[q])]) + Float64(distTab24[pairSeq](abs(q-i)))
            interaction24 = Float64(interProbs[pairSeq])/distance24
            df24 = "$pairSeq,$interaction24"
            println(df24)
            write(interFile24, df24,"\n")
            finalInter24[pairSeq] = interaction24
        else
            pairSeq = symbol(string(aaSeq24[i], aaSeq24[q]))
            interaction24 = Float64(0)
            df24 = "$pairSeq,$interaction24"
            write(interFile24, df24,"\n")
            finalInter24[pairSeq] = interaction24
        end
    end
end
close(interFile24)
for j = finalInter24
    println(j)
end

#Making the second fold
maxInter47 = maximum(values(finalInter24))
maxInter48 = Float64(maxInter47)
println(maxInter48)
maxKey24 = collect(keys(finalInter24))[indmax(collect(values(finalInter24)))]
maxKey24 = string(maxKey24)
firstAA24 = Char(maxKey24[1])
secondAA24 = Char(maxKey24[2])
reg_string_tmp24 = "$firstAA24[A-Z]{1,5}$secondAA24"
reg_string24 = Regex(reg_string_tmp24)
search_str24 = search(aaSeq24, reg_string24)
println("$firstAA24 - $secondAA24")
println(search_str24)

aaSeq25 = replace(aaSeq24, reg_string24, "")

distTab25 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab25[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq25 = string(aaSeq25)
finalInter25 = Dict{Symbol, Float64}()
interFile25 = open("interProbs25.csv", "w")
for i = 1:length(aaSeq25)
    distance = 0
    for q = i:length(aaSeq25)
        if q-i > 1
            pairSeq = symbol(string(aaSeq25[i], aaSeq25[q]))
            pairProbs = interProbs[pairSeq]
            distance25 = Float64(sizeTab[symbol(aaSeq25[q])]) + Float64(distTab25[pairSeq](abs(q-i)))
            interaction25 = Float64(interProbs[pairSeq])/distance25
            df25 = "$pairSeq,$interaction25"
            println(df25)
            write(interFile25, df25,"\n")
            finalInter25[pairSeq] = interaction25
        else
            pairSeq = symbol(string(aaSeq25[i], aaSeq25[q]))
            interaction25 = Float64(0)
            df25 = "$pairSeq,$interaction25"
            write(interFile25, df25,"\n")
            finalInter25[pairSeq] = interaction25
        end
    end
end
close(interFile25)
for j = finalInter25
    println(j)
end

#Making the second fold
maxInter49 = maximum(values(finalInter25))
maxInter50 = Float64(maxInter49)
println(maxInter50)
maxKey25 = collect(keys(finalInter25))[indmax(collect(values(finalInter25)))]
maxKey25 = string(maxKey25)
firstAA25 = Char(maxKey25[1])
secondAA25 = Char(maxKey25[2])
reg_string_tmp25 = "$firstAA25[A-Z]{1,5}$secondAA25"
reg_string25 = Regex(reg_string_tmp25)
search_str25 = search(aaSeq25, reg_string25)
println("$firstAA25 - $secondAA25")
println(search_str25)

aaSeq26 = replace(aaSeq25, reg_string25, "")

distTab26 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab26[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq26 = string(aaSeq26)
finalInter26 = Dict{Symbol, Float64}()
interFile26 = open("interProbs26.csv", "w")
for i = 1:length(aaSeq26)
    distance = 0
    for q = i:length(aaSeq26)
        if q-i > 1
            pairSeq = symbol(string(aaSeq26[i], aaSeq26[q]))
            pairProbs = interProbs[pairSeq]
            distance26 = Float64(sizeTab[symbol(aaSeq26[q])]) + Float64(distTab26[pairSeq](abs(q-i)))
            interaction26 = Float64(interProbs[pairSeq])/distance26
            df26 = "$pairSeq,$interaction26"
            println(df26)
            write(interFile26, df26,"\n")
            finalInter26[pairSeq] = interaction26
        else
            pairSeq = symbol(string(aaSeq26[i], aaSeq26[q]))
            interaction26 = Float64(0)
            df26 = "$pairSeq,$interaction26"
            write(interFile26, df26,"\n")
            finalInter26[pairSeq] = interaction26
        end
    end
end
close(interFile26)
for j = finalInter26
    println(j)
end

#Making the second fold
maxInter51 = maximum(values(finalInter26))
maxInter52 = Float64(maxInter51)
println(maxInter52)
maxKey26 = collect(keys(finalInter26))[indmax(collect(values(finalInter26)))]
maxKey26 = string(maxKey26)
firstAA26 = Char(maxKey26[1])
secondAA26 = Char(maxKey26[2])
reg_string_tmp26 = "$firstAA26[A-Z]{1,5}$secondAA26"
reg_string26 = Regex(reg_string_tmp26)
search_str26 = search(aaSeq26, reg_string26)
println("$firstAA26 - $secondAA26")
println(search_str26)

aaSeq27 = replace(aaSeq26, reg_string26, "")

distTab27 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab27[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq27 = string(aaSeq27)
finalInter27 = Dict{Symbol, Float64}()
interFile27 = open("interProbs27.csv", "w")
for i = 1:length(aaSeq27)
    distance = 0
    for q = i:length(aaSeq27)
        if q-i > 1
            pairSeq = symbol(string(aaSeq27[i], aaSeq27[q]))
            pairProbs = interProbs[pairSeq]
            distance27 = Float64(sizeTab[symbol(aaSeq27[q])]) + Float64(distTab27[pairSeq](abs(q-i)))
            interaction27 = Float64(interProbs[pairSeq])/distance27
            df27 = "$pairSeq,$interaction27"
            println(df27)
            write(interFile27, df27,"\n")
            finalInter27[pairSeq] = interaction27
        else
            pairSeq = symbol(string(aaSeq27[i], aaSeq27[q]))
            interaction27 = Float64(0)
            df27 = "$pairSeq,$interaction27"
            write(interFile27, df27,"\n")
            finalInter27[pairSeq] = interaction27
        end
    end
end
close(interFile27)
for j = finalInter27
    println(j)
end

#Making the second fold
maxInter53 = maximum(values(finalInter27))
maxInter54 = Float64(maxInter53)
println(maxInter54)
maxKey27 = collect(keys(finalInter27))[indmax(collect(values(finalInter27)))]
maxKey27 = string(maxKey27)
firstAA27 = Char(maxKey27[1])
secondAA27 = Char(maxKey27[2])
reg_string_tmp27 = "$firstAA27[A-Z]{1,5}$secondAA27"
reg_string27 = Regex(reg_string_tmp27)
search_str27 = search(aaSeq27, reg_string27)
println("$firstAA27 - $secondAA27")
println(search_str27)

aaSeq28 = replace(aaSeq27, reg_string27, "")

distTab28 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab28[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq28 = string(aaSeq28)
finalInter28 = Dict{Symbol, Float64}()
interFile28 = open("interProbs28.csv", "w")
for i = 1:length(aaSeq28)
    distance = 0
    for q = i:length(aaSeq28)
        if q-i > 1
            pairSeq = symbol(string(aaSeq28[i], aaSeq28[q]))
            pairProbs = interProbs[pairSeq]
            distance28 = Float64(sizeTab[symbol(aaSeq28[q])]) + Float64(distTab28[pairSeq](abs(q-i)))
            interaction28 = Float64(interProbs[pairSeq])/distance28
            df28 = "$pairSeq,$interaction28"
            println(df28)
            write(interFile28, df28,"\n")
            finalInter28[pairSeq] = interaction28
        else
            pairSeq = symbol(string(aaSeq28[i], aaSeq28[q]))
            interaction28 = Float64(0)
            df28 = "$pairSeq,$interaction28"
            write(interFile28, df28,"\n")
            finalInter28[pairSeq] = interaction28
        end
    end
end
close(interFile28)
for j = finalInter28
    println(j)
end

#Making the second fold
maxInter55 = maximum(values(finalInter28))
maxInter56 = Float64(maxInter55)
println(maxInter56)
maxKey28 = collect(keys(finalInter28))[indmax(collect(values(finalInter28)))]
maxKey28 = string(maxKey28)
firstAA28 = Char(maxKey28[1])
secondAA28 = Char(maxKey28[2])
reg_string_tmp28 = "$firstAA28[A-Z]{1,5}$secondAA28"
reg_string28 = Regex(reg_string_tmp28)
search_str28 = search(aaSeq28, reg_string28)
println("$firstAA28 - $secondAA28")
println(search_str28)

aaSeq29 = replace(aaSeq28, reg_string28, "")

distTab29 = Dict{Symbol,Function}()

for n in keys(interProbs)
    distTab29[symbol(n)] = pepBond
end
#println(aaSeq)
#println(aaSeq2)
aaSeq29 = string(aaSeq29)
finalInter29 = Dict{Symbol, Float64}()
interFile29 = open("interProbs29.csv", "w")
for i = 1:length(aaSeq29)
    distance = 0
    for q = i:length(aaSeq29)
        if q-i > 1
            pairSeq = symbol(string(aaSeq29[i], aaSeq29[q]))
            pairProbs = interProbs[pairSeq]
            distance29 = Float64(sizeTab[symbol(aaSeq29[q])]) + Float64(distTab29[pairSeq](abs(q-i)))
            interaction29 = Float64(interProbs[pairSeq])/distance29
            df29 = "$pairSeq,$interaction29"
            println(df29)
            write(interFile29, df29,"\n")
            finalInter29[pairSeq] = interaction29
        else
            pairSeq = symbol(string(aaSeq29[i], aaSeq29[q]))
            interaction29 = Float64(0)
            df29 = "$pairSeq,$interaction29"
            write(interFile29, df29,"\n")
            finalInter29[pairSeq] = interaction29
        end
    end
end
close(interFile29)
for j = finalInter29
    println(j)
end

#Making the second fold
maxInter57 = maximum(values(finalInter29))
maxInter58 = Float64(maxInter57)
println(maxInter58)
maxKey29 = collect(keys(finalInter29))[indmax(collect(values(finalInter29)))]
maxKey29 = string(maxKey29)
firstAA29 = Char(maxKey29[1])
secondAA29 = Char(maxKey29[2])
reg_string_tmp29 = "$firstAA29[A-Z]{1,5}$secondAA29"
reg_string29 = Regex(reg_string_tmp29)
search_str29 = search(aaSeq29, reg_string29)
println("$firstAA29 - $secondAA29")
println(search_str29)

aaSeq30 = replace(aaSeq29, reg_string29, "")

println(aaSeq)
println(aaSeq2)
println(aaSeq3)
println(aaSeq4)
println(aaSeq5)
println(aaSeq6)
println(aaSeq7)
println(aaSeq8)
println(aaSeq9)
println(aaSeq10)
println(aaSeq11)
println(aaSeq12)
println(aaSeq13)
println(aaSeq14)
println(aaSeq15)
println(aaSeq16)
println(aaSeq17)
println(aaSeq18)
println(aaSeq19)
println(aaSeq20)
println(aaSeq21)
println(aaSeq22)
println(aaSeq23)
println(aaSeq24)
println(aaSeq25)
println(aaSeq26)
println(aaSeq27)
println(aaSeq28)
println(aaSeq29)
println(aaSeq30)
