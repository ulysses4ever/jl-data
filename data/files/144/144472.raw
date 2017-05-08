
const cosmic_fl = joinpath(homedir(), "haplox/Bone/data/cosmic/CosmicCompleteExport.tsv")

function numsamplesofcancer(cancer)
    sampleids =  Set{ASCIIString}()
    open(cosmic_fl) do file
        header = readline(file)
        header  = split(header, "\t")
        while !eof(file)
            line = readline(file)
            row  = split(line, "\t")
            if row[8] != cancer
                continue
            end
            sample_id = convert(ASCIIString,row[6])
            push!(sampleids, sample_id)
        end
    end
    #@show sampleids
    length(sampleids)
end

function samplerecordsofcancer(cancer, threshold)
    sampleid_numrecords =  Dict{ASCIIString,Int64}()
    open(cosmic_fl) do file
        header = readline(file)
        header  = split(header, "\t")
        while !eof(file)
            line = readline(file)
            row  = split(line, "\t")
            if row[8] != cancer
                continue
            end
            sample_id = convert(ASCIIString,row[6])
            if in(sample_id, keys(sampleid_numrecords))
                sampleid_numrecords[sample_id] += 1
            else
                sampleid_numrecords[sample_id] = 1
            end
        end
    end
    #@show sampleids
    length(filter(x->x[2]>threshold, sort(collect(sampleid_numrecords),by=x->x[2],rev=true)))
end

@show samplerecordsofcancer("small_intestine", 4)


