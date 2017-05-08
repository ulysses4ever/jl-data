using DataFrames
using GLM
using Gadfly
using Compose

function tabdict(filename)
	desc_table = Dict()
	for line in eachline(open(filename))
		desc_table[split(line, '\t')[1]] = strip(split(line, '\t')[2],'\n')
	end
	
	return desc_table
end

function reads_to_rpob_equiv(pfam_df)
	#Get the names of the PFAM models for RpoB
	RpoB_models = ["RNA_pol_Rpb2_1","RNA_pol_Rpb2_2","RNA_pol_Rpb2_3","RNA_pol_Rpb2_4","RNA_pol_Rpb2_45","RNA_pol_Rpb2_5","RNA_pol_Rpb2_6","RNA_pol_Rpb2_7"]
	
	#Get their lengths
	RpoB_model_lengths = Array(Float64,0)
	PFAM_lengths = tabdict("Pfam-A.lengths")
	for model in RpoB_models
		append!(RpoB_model_lengths, [float(PFAM_lengths[model])])
	end
		
	#Calculate RpoB reads per aa for each sample
	RpoB_reads_per_aa = Array(Float64,0)
	for sample in names(pfam_df)
		RpoB_reads = Array(Float64,0)
		if sample != :PFAM_Model
			for RpoB_model in RpoB_models
				append!(RpoB_reads,float(pfam_df[pfam_df[:PFAM_Model] .== RpoB_model, sample]))
			end
			data_for_linear_regression = DataFrame(reads=RpoB_reads,aa=RpoB_model_lengths)
			append!(RpoB_reads_per_aa,[coef(lm(reads~aa,data_for_linear_regression))[2]])
		end
	end
	
	#Calculate RpoB equivalents for every PFAM model in your dataset
	rpoB_table_output = DataFrame(PFAM_Model = [])
	for colnum in 2:size(PFAM_table)[2]
		rpoB_table_output[names(pfam_df)[colnum]] = []
	end
	for rownum in 1:size(pfam_df)[1]
		model_name = pfam_df[rownum,:PFAM_Model]
		readnums = Array(pfam_df[rownum,2:size(PFAM_table)[2]])
		pfam_length = float(PFAM_lengths[model_name])
		reads_per_aa = []
		for readnum in readnums
			push!(reads_per_aa, readnum / pfam_length)
		end
		RpoB_equivalents = []
		for (i, reads) in enumerate(reads_per_aa)
			push!(RpoB_equivalents, reads / RpoB_reads_per_aa[i])
		end
		newrow = DataFrame(PFAM_Model = model_name)
		for colnum in 2:size(PFAM_table)[2]
			newrow[names(pfam_df)[colnum]] = RpoB_equivalents[colnum-1]
		end
		rpoB_table_output = vcat(rpoB_table_output,newrow)
	end
	return rpoB_table_output
end

function plotcorrelation(modelnames,rpoB_eq_table,parameter,metadata_table)
    data_to_plot = []
    key_labels =[]

    #Getting data out of the big table and putting it into a small data frame using the melt command to pivot that dataframe
    for modelname in modelnames
        single_model = melt(rpoB_eq_table[rpoB_eq_table[:PFAM_Model] .== modelname, :], :PFAM_Model)
        single_model[:param] = metadata_table[parameter]
        single_model[:PFAM_full] = strip(PFAM_desc_table[modelname],'\"')
        push!(data_to_plot, single_model)
	end

    #Putting all the data frames for each PFAM model together
    all_data_to_plot = data_to_plot[1]
    if length(data_to_plot) > 1
        for i in 2:length(data_to_plot)
            all_data_to_plot = vcat(all_data_to_plot, data_to_plot[i])
        end
    end
    
    #Plotting all of that data together
    plot(all_data_to_plot, x=:param,y=:value, color=:PFAM_full,
    Theme(default_color=color(colorant"black"),
    panel_stroke=color(colorant"black"),
    grid_color=color(colorant"gray"),
    major_label_font="Helvetica",
    major_label_color=color(colorant"black"),
    key_title_color=color(colorant"white"),
    minor_label_font="Helvetica",
    key_label_font="Helvetica",
    minor_label_color=color(colorant"black"),
    key_position=:bottom),
    Guide.xlabel(string(parameter)), 
    Guide.ylabel("rpoB equivalents")
    #Guide.annotation(compose(context(), text(rpoB_eq,metadata_subset,sample_names)))
    )
end

function plotmodel(modelnames, rpoB_eq_table, reads_table, sample_names)
    data_to_plot = []
    key_labels =[]

    #Getting data out of the big table and putting it into a small data frame using the melt command to pivot that dataframe
    for (i, modelname) in enumerate(modelnames)
        single_model = melt(rpoB_eq_table[rpoB_eq_table[:PFAM_Model] .== modelname, :], :PFAM_Model)
        single_model_reads = melt(reads_table[reads_table[:PFAM_Model] .== modelname, :], :PFAM_Model)
        single_reads = []
        for readnum in single_model_reads[:value]
            push!(single_reads,string(readnum))
        end
        single_model[:reads] = single_reads
        single_model[:sample] = sample_names
    relative_plot_position = 1:length(sample_names)
    relative_plot_position = relative_plot_position + 0.5 - i*(1/length(modelnames))
    single_model[:read_plot_pos] = relative_plot_position
        push!(data_to_plot, single_model)
    	push!(key_labels, PFAM_desc_table[modelname])
	end
    
    all_data_to_plot = data_to_plot[1]
    if length(data_to_plot) > 1
        for i in 2:length(data_to_plot)
            all_data_to_plot = vcat(all_data_to_plot, data_to_plot[i])
        end
    end
    
    #plotting
    modelplot = plot(all_data_to_plot, x=:value,y=:sample, colour=:PFAM_Model, Geom.bar(position=:dodge,orientation=:horizontal),
    Guide.ylabel(""),
    Guide.xlabel("rpoB equivalents"),
    	Theme(bar_highlight=color(colorant"black"),
    	key_position=:bottom,
    	default_color=color(colorant"black"),
    	panel_stroke=color(colorant"black"),
    	grid_color=color(colorant"gray"),
    	major_label_font="Helvetica",
    	major_label_color=color(colorant"black"),
    	key_title_color=color(colorant"white"),
    	minor_label_font="Helvetica",
    	key_label_font="Helvetica",
    	minor_label_color=color(colorant"black"),
		point_label_font_size=6pt),
	Guide.annotation(compose(context(),
    text(all_data_to_plot[:value]+0.01,all_data_to_plot[:read_plot_pos],all_data_to_plot[:reads],[hleft])))
    )
end

function comparemodel(model1,model2,rpoB_eq_table)
	comparison_array = []
	for i in 2:size(rpoB_eq_table)[2]
		append!(comparison_array, vec(Array(dfsubset(Baltic_rpoB_eq,:PFAM_Model,[model1])[i])/Array(dfsubset(Baltic_rpoB_eq,:PFAM_Model,[model2])[i])))
	end
	return comparison_array
end

function plotratio(model1,model2,rpoB_eq_table)
	ratios = comparemodel(model1,model2,rpoB_eq_table)
	modelplot = plot(y=ratios, x=sample_names, Geom.bar())
	return modelplot
end

function correlation(modelname,rpoB_eq_table,parameter,metadata_table)
     single_model = melt(rpoB_eq_table[rpoB_eq_table[:PFAM_Model] .== modelname, :], :PFAM_Model)
     single_model[:param] = metadata_table[parameter]
    return cor(single_model[:param],single_model[:value])
end

function ice_vs_holocene(modelname)
	holocene = vec(Array(Baltic_rpoB_eq[Baltic_rpoB_eq[:PFAM_Model] .== modelname,[:x59E_13_B,:x63E_6_A,:x63E_6_B,:x65C_4,:x65C_4_replicate]]))
	ice_age = vec(Array(Baltic_rpoB_eq[Baltic_rpoB_eq[:PFAM_Model] .== modelname,[:x59E_21,:x59E_25,:x60B_9,:x60B_9_replicate,:x60B_13,:x60B_28,:x63E_24,:x65C_10]]))
	new_holocene = Float64[]
	for item in holocene
		push!(new_holocene, item)
	end
	new_ice_age = Float64[]
	for item in ice_age
		push!(new_ice_age, item)
	end
	return MannWhitneyUTest(new_holocene, new_ice_age)
end