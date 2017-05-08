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
interProbs[:D] = 0.0; interProbs[:R] = 0.0; interProbs[:S] = 0.0; interProbs[:M] = 0.0; interProbs[:E] = 0.0; interProbs[:T] = 0.0; 
interProbs[:P] = 0.0; interProbs[:N] = 0.0; interProbs[:C] = 0.0; interProbs[:F] = 0.0; interProbs[:Q] = 0.0; interProbs[:V] = 0.0; 
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

finalInter = Dict{Symbol, Float64}()
interFile = open("interProbs.csv", "w")
#Calculate probability of interacting for every possible pair of amino acids in sequence
for i = 1:length(aaSeq)
				distance = 0
				for q = i:length(aaSeq)
								pairSeq = symbol(string(aaSeq[i], aaSeq[q]))
								println("Amino acid pair ==> $pairSeq")
								pairProbs = interProbs[pairSeq]
								println("Starting interaction likelihood ==> $pairProbs")
								distance = Float64(sizeTab[symbol(aaSeq[q])]) + Float64(distTab[pairSeq](q))
								interaction = Float64(interProbs[pairSeq])/distance
								println("Likelihood of interaction ==> $interaction")
								#writedlm(interaction)
				    df = "$pairSeq,$interaction"
				    print(df)
								write(interFile, df,"\n")
								finalInter[pairSeq] = interaction
				end
end
close(interFile)
for j = finalInter
				println(j)
end
