using DataFrames
using Gadfly
using Lumberjack

# For each row in the datasource extract information into a dataframe
function get_bismark_report_filenames_from_plite_pipeline(pipeline_path,run_number,num_jobs,step_name="bismark",report_name="file1_1_val_1.fq_bismark_bt2_PE_report.txt")
    files = map( x->joinpath(pipeline_path, "output","run$run_number", "job$x",step_name, report_name), 0:(num_jobs-1) )
    return files
end

function parse_bismark_report(bismark_report_filename)
  bismark_line_itr = eachline(open(bismark_report_filename))

  # if there is a tab keep it
  tab_lines = filter(x->ismatch(r"\t",x), collect(bismark_line_itr) )
  report_dict=Dict()

  # get the information we want
  seq_pairs = "Sequence pairs analysed in total"
  mapping_efficiency = "Mapping efficiency"
  paired_end_unique = "Number of paired-end alignments with a unique best hit" #:	50039134
  paired_end_noalign = "Sequence pairs with no alignments under any condition" #:	4348666
  paired_end_multimap = "Sequence pairs did not map uniquely" #:	9930619
  c_meth_cpg = "C methylated in CpG context:" #    80.4%
  c_meth_chg = "C methylated in CHG context:" #    0.2%
  c_meth_chh = "C methylated in CHH context:" #    0.2%

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
  #close(bismark_report_filename)
  return report_dict
end

function parse_bismark_reports(bismark_report_filenames)
  master_report_dict=Dict()
  for bismark_report_filename in bismark_report_filenames
      report_dict = parse_bismark_report(bismark_report_filename)
      Lumberjack.info("parsing: $bismark_report_filename")
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

function add_report_info_to_datasource!(datasource,report_dict)
    nrow_datasource = nrow(datasource)

    for (key, values) in report_dict
       num_values = length(values)
       if nrow_datasource == num_values
           datasource[symbol(key) ]=values
       else
           Lumberjack.error("Cannot add $key to metadata, number of values ($num_values) does not equal metadata rows ($nrow_datasource) ")
       end
    end
end

# bismark_stats are the bismark outputs such as mapping efficiency
# datasource_groupby_field: e.g. strain,sex
# files - the filenames to the bismark report file
# for each of the bismark stats, create a box plot based on each of the
#  datasource_groupby_fields
function plot_bismark_summary(files, metadata_path,  bismark_stats, datasource_groupby_fields)
    report_dict = parse_bismark_reports(files)
    metadata = readtable(metadata_path)
    add_report_info_to_datasource!(metadata,report_dict)
    plots = Any[]
    theme = Theme(
         major_label_color=color("black"),
         minor_label_color=color("black"),
         major_label_font_size=18pt,
         minor_label_font_size=14pt
    )
    for statistic in bismark_stats
        for groupby_field in datasource_groupby_fields
            p = Gadfly.plot( metadata, x=groupby_field, y=statistic,Geom.boxplot, theme )
            push!(plots,p)
        end
    end
    return (plots,metadata)
end


function make_bismark_report(reportdir, files, metadata_path, datasource_groupby_fields::Array{UTF8String}; overwrite=false)

    bismark_stats=["seq-pairs","map-eff"]
    (plots,metadata)=plot_bismark_summary(files,metadata_path,bismark_stats,datasource_groupby_fields)

    # if directory does not exist create it
    if(!isdir( reportdir))
       mkdir(reportdir)
    else
      Lumberjack.warn("$reportdir exists, overwrite is set to $overwrite")
      if overwrite
         error("Overwriting report directory not allowed.")
      end
    end

    # write metadata to directory
    datatable_path = joinpath(reportdir,"datatable.tsv")
    writetable(datatable_path,metadata)

    # draw plots to directory
    Gadfly.draw( PNG(joinpath(reportdir,"plots.png"),24cm, 12cm)  , hstack(plots...) )

end
