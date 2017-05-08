include("baltic-metagenomes/PFAMtable.jl")

PFAM_desc_table = tabdict("baltic-metagenomes/PFAM_desc_table")

PFAM_table = readtable("baltic-metagenomes/allsite_PFAM_table_readnums.tdt", separator='\t')

x60B_9_combined = PFAM_table[:x60B_9_replicate] + PFAM_table[:x60B_9]
x63E_6_combined = PFAM_table[:x63E_6_A] + PFAM_table[:x63E_6_B]
x65C_4_combined = PFAM_table[:x65C_4_replicate] + PFAM_table[:x65C_4]

PFAM_table_noreps = DataFrame()
PFAM_table_noreps[:PFAM_Model] = PFAM_table[:PFAM_Model]
PFAM_table_noreps[:x59E_13_B] = PFAM_table[:x59E_13_B]
PFAM_table_noreps[:x59E_21] = PFAM_table[:x59E_21]
PFAM_table_noreps[:x59E_25] = PFAM_table[:x59E_25]
PFAM_table_noreps[:x60B_9] = x60B_9_combined
PFAM_table_noreps[:x60B_13] = PFAM_table[:x60B_13]
PFAM_table_noreps[:x60B_28] = PFAM_table[:x60B_28]
PFAM_table_noreps[:x63E_6] = x63E_6_combined
PFAM_table_noreps[:x63E_24] = PFAM_table[:x63E_24]
PFAM_table_noreps[:x65C_4] = x65C_4_combined
PFAM_table_noreps[:x65C_10] = PFAM_table[:x65C_10]

metadata = readtable("baltic-metagenomes/sample_metadata.txt", separator='\t')

metadata_noreps = metadata[[1,2,3,4,6,7,8,10,11,13],:]

Baltic_rpoB_eq = reads_to_rpob_equiv(PFAM_table)

Baltic_rpoB_eq_noreps = reads_to_rpob_equiv(PFAM_table_noreps)

sample_names_noreps = ["59E-13","59E-21","59E-25","60B-9","60B-13","60B-28","63E-6","63E-24","65C-4","65C-10"]

#Figure 3 correlation

methane_correlation = plotcorrelation(["MCR_alpha"],Baltic_rpoB_eq_noreps,:CH4_mM,metadata_noreps)
draw(SVG("methane_correlation_V2.1.svg",5inch,4inch), methane_correlation)

correlation("MCR_alpha",Baltic_rpoB_eq_noreps,:CH4_mM,metadata_noreps)

#Pearson's = 0.976

#Figure 4 plotting commands

energy_correlation = plotcorrelation(["POR","PFL-like","ETF","CdhC"],Baltic_rpoB_eq_noreps,:TOC_pc,metadata_noreps)
draw(SVG("energy_correlation_V2.1.svg",5inch,4inch), energy_correlation)

#Figure 5 plotting commands

ironsulfur_correlation = plotcorrelation(["Fer4"],Baltic_rpoB_eq_noreps,:TOC_pc,metadata_noreps)
draw(SVG("ironsulfur_correlation_V2.1.svg",5inch,4inch), ironsulfur_correlation)

#Figure 6 plotting commands

salinity_correlation = plotcorrelation(["Na_H_antiporter","OpuAC","Dehalogenase"],Baltic_rpoB_eq_noreps,:Salinity,metadata_noreps)
draw(SVG("salinity_correlation_V2.1.svg",5inch,4inch), salinity_correlation)

correlation("Na_H_antiporter",Baltic_rpoB_eq_noreps,:Salinity,metadata_noreps)
correlation("OpuAC",Baltic_rpoB_eq_noreps,:Salinity,metadata_noreps)


#Figure 7 plotting commands

mutation_correlation = plotcorrelation(["DNA_mis_repair"],Baltic_rpoB_eq_noreps,:TOC_pc,metadata_noreps)
draw(SVG("mutation_correlation_V2.1.svg",5inch,4inch), mutation_correlation)

