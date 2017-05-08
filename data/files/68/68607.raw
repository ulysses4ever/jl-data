using Lumberjack
using DataFrames
using GZip
using Inflate

function get_bismark_cx_report_filenames_with_metadata_from_plite_pipeline(
                      metadata_path, pipeline_path,run_number,num_jobs,step_name="methylationextractor",
                      report_name="bismark_dedup.CX_report.txt.gz")
    metadata=readtable(metadata_path)
    metadata=metadata[1:num_jobs]
    files = map( x->joinpath(pipeline_path, "output","run$run_number", "job$x",step_name, report_name), 0:(num_jobs-1) )
    metadata[:filename]=files
    return metadata
end

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
    last_count  = 0
    last_strand = ""
    cpg_dict = Dict()
    for key in sort(collect(keys(d)),lt=less_than )

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
    close(io)
    return file
end

function memory_read_gzip_file(filename)
    io = open(filename)
    Lumberjack.info("reading all")
    file_gz=readbytes(io)
    Lumberjack.info("finished reading all")
    Lumberjack.info("decompressing")
    file = gunzip(file_gz)
    Lumberjack.info("finished decompressing")
    Lumberjack.info("convert to ASCIIString")
    file_str=convert(ASCIIString,file)
    Lumberjack.info("finished conversion to ASCIIString")
    close(io)
    return file_str
end

function read_gzip_file(filename)
   gzio=gzopen(filename,"r")
   line_num =0
   lines=ASCIIString[]
   for line in eachline(gzio)
        line=chomp(line)
        push!(lines,line)
        line_num +=1
        if line_num % 1000000 == 0
            Lumberjack.info("full on speed like road runner $line_num already!")
        end
    end
    #pop!(lines) # clears out the final row which due to a bug in GZlib gives and empty string
    return lines
end

function get_coverage_dict!(d::Dict,filenames)
    for filename in filenames
        # open file and add counts to dictionary of CpGs
        (path,ext)=splitext(filename)
        Lumberjack.info("Processing $filename: Extension: $ext")
        if ext != ".gz"
            file_str=memory_read_file(filename)
        else
            file_str=memory_read_gzip_file(filename)
        end
        Lumberjack.info("split line")
        lines=split(file_str,'\n')
        Lumberjack.info("done split")
        idx =0
        for line in lines
            fields=split(line,'\t')
            if length(fields) == 7
                if fields[6] != "CG"
                   continue
                end
                d[ join( [ fields[1],fields[2],fields[3] ], "." )  ] = int64(fields[4]) + int64(fields[5])
                if idx % 1000000 == 0
                    Lumberjack.info("processed $idx rows")
                end
                idx+=1
            end
        end
    end
end

function get_coverage_dict_moabsA!(d::Dict,filenames)
    for filename in filenames
        # open file and add counts to dictionary of CpGs
        (path,ext)=splitext(filename)
        Lumberjack.info("Processing $filename: Extension: $ext")
        if ext != ".gz"
            file_str=memory_read_file(filename)
        else
            file_str=memory_read_gzip_file(filename)
        end
        Lumberjack.info("split line")
        lines=split(file_str,'\n')
        Lumberjack.info("done split")
        idx=0
        for line in lines
            fields=split(line,'\t')
            if length(fields) == 14
                d[ join( [ fields[1],fields[2],fields[3] ], "." )  ] = int64(fields[5]) + int64(fields[6])
            end
            if idx % 1000000 == 0
                Lumberjack.info("processed $idx rows")
            end
            idx +=1
        end
    end
end

function get_coverage_dict_moabs!(d::Dict,filenames)

     Lumberjack.info("GET_COVERAGE MOABS")

    for filename in filenames
        # open file and add counts to dictionary of CpGs
        (path,ext)=splitext(filename)
        Lumberjack.info("Processing $filename: Extension: $ext")
        if ext != ".gz"
            file_str=memory_read_file(filename)
        else
            file_str=memory_read_gzip_file(filename)
        end
        Lumberjack.info("split line")
        fields=split(file_str,['\t','\n'])
        Lumberjack.info("done split")
        file_str=""
        gc() #force garbage collection
        idx=0
        seq_id_idx=1
        start_idx = 2
        stop_idx=3
        t_count_idx=5
        c_count_idx=6
        len=length(fields)
        Lumberjack.info("Number of fields $len")
        while seq_id_idx < ( len - 14 )
            total=parseint(Int64, fields[t_count_idx] ) + parseint(Int64, fields[c_count_idx] )
            d[ join( [ fields[seq_id_idx],fields[start_idx],fields[stop_idx] ], '.') ] = total
            seq_id_idx  +=14
            start_idx   +=14
            stop_idx    +=14
            t_count_idx +=14
            c_count_idx +=14

            if seq_id_idx % (15 + 14*50000) == 0
                Lumberjack.info("PROCESSED $seq_id_idx rows")
            end
        end
    end
end

# generalise this a bit
function cpg_cumulative_coverage(cpg_dict)
      cov_counts = [0,0,0,0,0]
      tot = 0
      meth_count =0
      for value in values(cpg_dict)
          if value > 1
              cov_counts[1] +=1
          end
          if value > 3
              cov_counts[2] +=1
          end
          if value > 5
              cov_counts[3] +=1
          end
          if value > 10
             cov_counts[4] +=1
          end
          if value > 15
             cov_counts[5] +=1
          end
          tot +=1
          meth_count += value
      end
      return (meth_count / tot, cov_counts ./ tot )
end
function temporary_write(row,group,cpg_coverage::DataFrame, grouped_metadata::DataFrame,report_dir)
     cpg_coverage_copy=copy(cpg_coverage)
     cpg_coverage_copy[group] = grouped_metadata[1:row,group]
     output_file=joinpath(report_dir,"cpg_coverage-tmp-$row.tsv")
     writetable(output_file, cpg_coverage_copy)
     Lumberjack.info("Written tmp coverage table to $output_file")
end
function make_coverage_stats_table(metadata::DataFrame, group::Symbol, report_dir::ASCIIString; format="bismark-cx" )
    grouped_metadata = by( metadata, group,
        df ->  appendlist( df[:filename] )
    )
    cpg_coverage=DataFrame(depth=Float32[],gt_1=Float32[], gt_3=Float32[], gt_5=Float32[], gt_10=Float32[], gt_15=Float32[])

    Lumberjack.info("PROCESSING FOR $format")
    for row = 1:nrow( grouped_metadata)
       eachgroup = grouped_metadata[row,:]
       d=Dict{ASCIIString,Int64}()
       for files_tuple in eachgroup[:x1]
           files=files_tuple[1]
           if format == "bismark-cx"
             file=get_coverage_dict!(d,files)
           end

          if format == "moabs-cpg"
             file=get_coverage_dict_moabsA!(d,files)
          end
       end
       Lumberjack.info("Done group $row")
       cpg_dict=Dict()
       if format == "bismark_cx"
           cpg_dict= get_cpg_dinucleotide_dict(d)
       end
       if format == "moabs-cpg"
           cpg_dict= d
       end
       #Lumberjack.debug("cpg coverage dictionary: $cpg_dict")
       (depth,cov)=cpg_cumulative_coverage(cpg_dict)
       unshift!(cov,depth)
       push!(cpg_coverage,cov)
       temporary_write(row,group,cpg_coverage,grouped_metadata,report_dir)
    end
    cpg_coverage[group] = grouped_metadata[:,group]
    output_file=joinpath(report_dir,"cpg_coverage.tsv")
    writetable(output_file, cpg_coverage)
    Lumberjack.info("Written coverage table to $output_file")
    return cpg_coverage
end
