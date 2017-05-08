include("PFAMtable.jl")

PFAM_desc_table = tabdict("PFAM_desc_table")

sample_names = ["59E-13","59E-21","59E-25","60B-9","60B-9-replicate","60B-13","60B-28","63E-6-A","63E-6-B","63E-24","65C-4","65C-4-replicate","65C-10"]

PFAM_table = readtable("allsite_PFAM_table_readnums.tdt", separator='\t')

metadata = readtable("sample_metadata.txt", separator='\t')

Baltic_rpoB_eq = reads_to_rpob_equiv(PFAM_table)

#Figure 3 plotting commands

methane_correlation = plotcorrelation(["MCR_alpha"],Baltic_rpoB_eq,:CH4_mM,metadata)
draw(SVG("methane_correlation.svg",5inch,4inch), methane_correlation)

methane_barplot = plotmodel(["MCR_alpha"],Baltic_rpoB_eq,PFAM_table,sample_names)
draw(SVG("methane_barplot.svg",5inch,4inch), methane_barplot)

#Figure 4 plotting commands

energy_correlation = plotcorrelation(["POR","PFL-like","ETF","CdhC"],Baltic_rpoB_eq,:TOC_pc,metadata)
draw(SVG("energy_correlation.svg",5inch,4inch), energy_correlation)

energy_barplot = plotmodel(["POR","PFL-like","ETF","CdhC"],Baltic_rpoB_eq,PFAM_table,sample_names)
draw(SVG("energy_barplot.svg",5inch,4inch), energy_barplot)

#Figure 5 plotting commands

ironsulfur_correlation = plotcorrelation(["Fer4"],Baltic_rpoB_eq,:TOC_pc,metadata)
draw(SVG("ironsulfur_correlation.svg",5inch,4inch), ironsulfur_correlation)

ironsulfur_barplot = plotmodel(["Fer4"],Baltic_rpoB_eq,PFAM_table,sample_names)
draw(SVG("ironsulfur_barplot.svg",5inch,4inch), ironsulfur_barplot)

#Figure 6 plotting commands

salinity_correlation = plotcorrelation(["Na_H_antiporter","OpuAC","Dehalogenase"],Baltic_rpoB_eq,:Salinity,metadata)
draw(SVG("salinity_correlation.svg",5inch,4inch), salinity_correlation)

salinity_barplot = plotmodel(["Na_H_antiporter","OpuAC","Dehalogenase"],Baltic_rpoB_eq,PFAM_table,sample_names)
draw(SVG("salinity_barplot.svg",5inch,4inch), salinity_barplot)

#Figure 7 plotting commands

mutation_correlation = plotcorrelation(["DNA_mis_repair"],Baltic_rpoB_eq,:TOC_pc,metadata)
draw(SVG("mutation_correlation.svg",5inch,4inch), mutation_correlation)

mutation_barplot = plotmodel(["DNA_mis_repair"],Baltic_rpoB_eq,PFAM_table,sample_names)
draw(SVG("mutation_barplot.svg",5inch,4inch), mutation_barplot)

#Other plots (not used in paper)
acetate_correlation = plotcorrelation(["SIR2","CdhC","CdhD","Acetate_kinase"],Baltic_rpoB_eq,:TOC_pc,metadata)
draw(SVG("acetate_correlation.svg",5inch,4inch), acetate_correlation)

acetate_barplot = plotmodel(["SIR2","CdhC","CdhD","Acetate_kinase"],Baltic_rpoB_eq,PFAM_table,sample_names)
draw(SVG("acetate_barplot.svg",5inch,4inch), acetate_barplot)

pyruvate_correlation = plotcorrelation(["POR","PFL-like","ETF"],Baltic_rpoB_eq,:TOC_pc,metadata)
draw(SVG("pyruvate_correlation.svg",5inch,4inch), pyruvate_correlation)

pyruvate_barplot = plotmodel(["POR","PFL-like","ETF"],Baltic_rpoB_eq,PFAM_table,sample_names)
draw(SVG("pyruvate_barplot.svg",5inch,4inch), pyruvate_barplot)


pyruvate_correlation = plotcorrelation(["POR","PFL-like","ETF","Rnf_Nqr"],Baltic_rpoB_eq,:TOC_pc,metadata)
draw(SVG("pyruvate_correlation.svg",5inch,4inch), pyruvate_correlation)


pyruvate_barplot = plotmodel(["POR","PFL-like","ETF"],Baltic_rpoB_eq,PFAM_table,sample_names)


ferredoxin_barplot = plotmodel(["POR","PFL-like","ETF"],Baltic_rpoB_eq,PFAM_table,sample_names)

ferredoxin_barplot = plotmodel(["Fer4","Fer4_2","Fer4_3","Fer4_4","Fer4_5","Fer4_6","Fer4_7","Fer4_8","Fer4_9","Fer4_10","Fer4_11","Fer4_12","Fer4_13","Fer4_14","Fer4_15","Fer4_16","Fer4_17","Fer4_18","Fer4_19","Fer4_20","Fer4_21"],Baltic_rpoB_eq,PFAM_table,sample_names)

acetate_correlation = plotcorrelation(["PFL-like","Acetate_kinase","POR","CdhC"],Baltic_rpoB_eq,:TOC_pc,metadata)
draw(SVG("pyruvate_correlation.svg",5inch,4inch), pyruvate_correlation)

wood_ljungdahl = plotcorrelation(["FTHFS","THF_DHG_CYH",],Baltic_rpoB_eq,:TOC_pc,metadata)


#ATP synthase c subunits - ion specificity plot ordered by salinity - supplemental figure
ATPsynt_ion = readtable("ATP-synt-c-ion.txt", separator='\t')
sort!(ATPsynt_ion, cols=(:Salinity))
ATPsynt_ion_str_n = []

for item in ATPsynt_ion[:n]
	push!(ATPsynt_ion_str_n, string(item))
end

atp_plot = plot(ATPsynt_ion, y=:ATP_c_Na, x=:sample, Geom.bar(),
	Guide.ylabel("Na+ ATP synthase fraction"),
	Guide.xlabel(""),
		Theme(bar_highlight=color(colorant"black"),
		panel_stroke=color(colorant"black"),
		grid_color=color(colorant"gray"),
    	major_label_font="Helvetica",
    	major_label_color=color(colorant"black"),
    	key_title_color=color(colorant"white"),
    	minor_label_font="Helvetica",
    	key_label_font="Helvetica",
    	minor_label_color=color(colorant"black")
    	),
	Guide.annotation(compose(context(),
	    text(1:12,ATPsynt_ion[:ATP_c_Na]+0.01,ATPsynt_ion_str_n))
		),
		Scale.y_continuous(minvalue=0, maxvalue=0.6)
	)

draw(SVG("atp_ion.svg",5inch,4inch), atp_plot)

