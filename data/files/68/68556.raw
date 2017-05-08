using Lumberjack

function appendlist(x)
    return (x,)
end

function less_than(a,b)
      (t,u,v)=split(a,'.')
      (x,y,z)=split(b,'.')
      if t == x && int(u) <= int(y)
          return true
      else
        return false
      end
end

function get_cpg_dinucleotide_dict(d::Dict)
    last_count  =0
    last_strand = ""
    cpg_dict = Dict()
    for key in sort(collect(keys(d)),lt=less_than )
        println("$key => $(d[key])")
        this_count = d[key]
        (this_seq_id,this_pos,this_strand)=split(key, '.' )
       # println(this_strand)
        if (last_strand == "+" ) && (int(last_pos) == (int(this_pos) - 1) )  && ( this_strand == "-") && ( this_seq_id == last_seq_id)
            cpg_dict[ join( [this_seq_id,last_pos,this_pos], ".") ] = this_count + last_count
        end
        (last_seq_id,last_pos,last_strand,last_count)=(this_seq_id,this_pos,this_strand, this_count)
    end
    return cpg_dict
end
# when there is a ragel parser, we read only what we want here
# - i.e. CG context
function memory_read_file(filename)
    io = open(filename)
    Lumberjack.info("reading all")
    file=readall(io)
    Lumberjack.info("finished reading all")
    Lumberjack.info("split line")
    lines=split(file,'\n')
    Lumberjack.info("done split")
    close(io)
    return lines
end

function get_coverage_dict!(d::Dict,filenames)
    for filename in filenames
        println("$filename")
        # open file and add counts to dictionary of CpGs
        lines=memory_read_file(filename)
        for line in lines
            fields=split(line,'\t')
            println("read $fields")
            if length(fields) == 7
                if fields[6] != "CG"
                   continue
                end
                d[ join( [ fields[1],fields[2],fields[3] ], "." )  ] = int(fields[4]) + int(fields[5])
            end
        end
    end
end

# generalise this a bit
function cpg_cumulative_coverage(cpg_dict)
      gt = [0,0,0,0,0]
      tot = 0
      meth_count =0
      for value in values(cpg_dict)
          if value > 1
              gt[1] +=1
          end
          if value > 3
              gt[2] +=1
          end
          if value > 5
              gt[3] +=1
          end
          if value > 10
             gt[4] +=1
          end
          if value > 15
             gt[5] +=1
          end
          tot +=1
          meth_count += value
      end
      return (meth_count / tot, gt ./ tot )
end

function make_coverage_stats_table(metadata::DataFrame, group::Symbol, report_dir::ASCIIString )
    grouped_metadata = by( metadata, group,
        df ->  appendlist( df[:filename] )
    )
    cpg_coverage=DataFrame(depth=Float32[],gt_1=Float32[], gt_3=Float32[], gt_5=Float32[], gt_10=Float32[], gt_15=Float32[])

    for row = 1:nrow( grouped_metadata)
       eachgroup = grouped_metadata[row,:]
       d=Dict()
       for files_tuple in eachgroup[:x1]
           files=files_tuple[1]
           file=get_coverage_dict!(d,files)
       end
       Lumberjack.info("Done group $row")
       cpg_dict= get_cpg_dinucleotide_dict(d)
       Lumberjack.debug("cpg coverage dictionary: $cpg_dict")
       (depth,cov)=cpg_cumulative_coverage(cpg_dict)
       unshift!(cov,depth)
       push!(cpg_coverage,cov)
    end
    cpg_coverage[group] = grouped_metadata[:,group]
    output_file=joinpath(report_dir,"cpg_coverage.tsv")
    writetable(output_file, cpg_coverage)
    Lumberjack.info("Written coverage table to $output_file")
    return cpg_coverage
end
