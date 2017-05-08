using DataFrames
using Gadfly
using Lumberjack
using Docile

"""
Abstract:  parses a bismark alignment report for the alignment statistics
Arguments: bismark_report_path - string to the bismark report path
Return:    Dictionary{String,Number}
             keys can be "mapp-eff", "seq-pairs"
"""
function parse_bismark_report(bismark_report_path::String)
    bismark_line_itr = eachline(open(bismark_report_path))

    tab_lines = filter(x->ismatch(r"\t",x), collect(bismark_line_itr) ) # if there is a tab keep it
    report_dict=Dict()

    # get the information we want
    seq_pairs = "Sequence pairs analysed in total"
    mapping_efficiency = "Mapping efficiency"
    paired_end_unique = "Number of paired-end alignments with a unique best hit" #:	e.g. 50039134
    paired_end_noalign = "Sequence pairs with no alignments under any condition" #:	e.g 4348666
    paired_end_multimap = "Sequence pairs did not map uniquely" #:	e.g. 9930619
    c_meth_cpg = "C methylated in CpG context:" #  e.g.  80.4%
    c_meth_chg = "C methylated in CHG context:" #  e.g.  0.2%
    c_meth_chh = "C methylated in CHH context:" #  e.g.  0.2%

    seq_pairs_rgx=Regex("$seq_pairs")
    mapping_efficiency_rgx=Regex("$mapping_efficiency")
    paired_end_unique_rgx = Regex("$paired_end_unique")
    paired_end_noalign_rgx = Regex("$paired_end_noalign")
    paired_end_multimap_rgx = Regex("$paired_end_multimap")
    c_meth_cpg_rgx = Regex("$c_meth_cpg")
    c_meth_chg_rgx = Regex("$c_meth_chg") #   0.2%
    c_meth_chh_rgx = Regex("$c_meth_chh")

    num_rgx = Regex("([0-9\.]+)")
    for line in tab_lines
        if ismatch(seq_pairs_rgx,line)
            num = match(num_rgx,line).captures[1]
            report_dict["seq-pairs"]=parsefloat(num)
        end

        if ismatch(mapping_efficiency_rgx,line)
            num = match(num_rgx,line).captures[1]
            report_dict["map-eff"]=parsefloat(num)
        end
    end
    return report_dict
end


"""
Abstract:  parses a set of bismark report files
Arguments:
    bismark_report_filenames: Vector of strings that are path names to bismark report files
Returns:
    Dictionary; key: statistic name, value: Vectors of Numbers; Each Vector holds the values for each sample in sampleinfo
"""
function parse_bismark_reports{T<:String}(bismark_report_paths::Vector{T} )
  master_report_dict=Dict()
  for bismark_report_path in bismark_report_paths
      report_dict = parse_bismark_report(bismark_report_path)
      Lumberjack.info("parsing: $bismark_report_path")
      for (key,value) in report_dict
          #assign to master dict, and push on number value
          if !haskey(master_report_dict,key)
             master_report_dict[key] = Any[]
          end
          push!( master_report_dict[key], value)
      end
  end
  return master_report_dict
end

"""
Abstract: appends bismark report statistics to sampleinfo
Arguments:
    sampleinfo   - DataFrame of samples information
    report_dict  - Dictionary; statistic -> Vectors of Numbers holding the values for each sample in sampleinfo
"""
function append_report_info_to_sampleinfo!(sampleinfo::DataFrame,report_dict::Dict)
    nrow_sampleinfo = nrow(sampleinfo)
    for (key, values) in report_dict
       num_values = length(values)
       if nrow_sampleinfo == num_values
           sampleinfo[symbol(key) ]=values
       else
           Lumberjack.error("Cannot add $key to metadata, number of values ($num_values) does not equal metadata rows ($nrow_sampleinfo) ")
       end
    end
end

# bismark_stats are the bismark outputs such as mapping efficiency
# datasource_groupby_field: e.g. strain,sex
# files - the filenames to the bismark report file
# for each of the bismark stats, create a box plot based on each of the
#  datasource_groupby_fields
"""
Abstract: Creates basic gadfly box plots of bismark statistics over various sample attributes
e.g. sex, strain, or whatever other condition is described in the sample information.
Arguments::
    sampleinfo                - DataFrame of sample information and bismark statistics
    bismark_stats             - Vector of names of the bismark statistic
    sampleinfo_groupby_fields - Vector of fields that bismark_stats should be plotted over
"""
function plot_bismark_summary{T<:String}(sampleinfo::DataFrame, bismark_stats::Vector{T},
                                         sampleinfo_groupby_fields::Vector{T})

    plots = Any[]
    theme = Theme(
         major_label_color=color("black"),
         minor_label_color=color("black"),
         major_label_font_size=18pt,
         minor_label_font_size=14pt
    )
    for statistic in bismark_stats
        for groupby_field in sampleinfo_groupby_fields
            p = Gadfly.plot( sampleinfo, x=groupby_field, y=statistic,Geom.boxplot, theme )
            push!(plots,p)
        end
    end
    return plots
end

"""
Abstract: This produces the bismark summary report.
Arguments:
    reportdir                 - path
    bismark_report_paths      - Vector of paths to bismark report files
    sampleinfo_path           - path to datasource
"""
function make_bismark_summary_report{T<:String}(reportdir::String, bismark_report_paths::Vector{T},
                                        sampleinfo_path::String, sampleinfo_groupby_fields::Vector{T};
                                        overwrite=false,
                                        bismark_stats=["seq-pairs","map-eff"])

    report_dict = parse_bismark_reports(bismark_report_paths)
    println("REPORT_DICT: $report_dict")
    sampleinfo = readtable(sampleinfo_path)
    append_report_info_to_sampleinfo!(sampleinfo,report_dict)
    plots=plot_bismark_summary(sampleinfo, bismark_stats,sampleinfo_groupby_fields)

    # if directory does not exist create it
    if(!isdir( reportdir))
       mkdir(reportdir)
    else
      Lumberjack.warn("$reportdir exists, overwrite is set to $overwrite")
      if overwrite
         error("Overwriting report directory disallowed.")
      end
    end

    # write sampleinfo+bismark_stats to directory
    datatable_path = joinpath(reportdir,"datatable.tsv")
    writetable(datatable_path,sampleinfo)
    println("DATATABLE SAVED TO $datatable_path")
    # draw plots to directory
    plotpath = joinpath(reportdir,"plots.png")
    Gadfly.draw( PNG(plotpath,24cm, 12cm)  , hstack(plots...) )
    println("PLOTS SAVED TO $plotpath")
end

# shift to Misc
# For each row in the datasource extract information into a dataframe
function get_bismark_report_filenames_from_plite_pipeline(pipeline_path,run_number,num_jobs,step_name="bismark",report_name="file1_1_val_1.fq_bismark_bt2_PE_report.txt")
    files = map( x->joinpath(pipeline_path, "output","run$run_number", "job$x",step_name, report_name), 0:(num_jobs-1) )
    return files
end
