## read VCF (variant calling format) files

function read_vcf(path::AbstractString, as = SnpMatrix)

    # TODO:
    # support IndelMatrix
    # support SNP3+ (create one SNP per ALT allele)
    # support FILTERing
    # support phased genotypes

    ### static variables
    cols_fix = "#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\tFORMAT"
    sep = '\t'
    cols = Vector{AbstractString}()
    fstream = open(path)

    ### collect attributes
    nsnps = 0
    ninds = 0
    while !eof(fstream)
        line = readline(fstream)
        nline = length(line)
        if (nline <= 1)
            continue
        elseif (line[1] != '#')
            fields = split(line, sep)
            if ( length(fields[5]) > 1 || length(fields[4]) > 1 )
                # skip SNP3+, INDEL
                continue
            end
            nsnps += 1
        elseif (length(line) >= 45 && line[1:45] == cols_fix)
            cols = split(line, sep)
            ninds = length(cols) - 9
        end
    end

    ### check
    if (nsnps < 1)
        error("number of biallelic SNPs < 1")
    end
    if (ninds < 0)
        error("no header line found, or number of individuals < 1")
    end

    ### collect data
    inf = LocusInfo(
        Vector{AbstractString}(nsnps),
        Vector{AbstractString}(nsnps),
        Vector{Integer}(nsnps),
        Vector{AbstractString}(nsnps),
        Vector{AbstractString}(nsnps)
        )
    dat = SnpData(ninds, nsnps)
    fill!(dat, 0)
    isnp = 0
    seekstart(fstream)
    while !eof(fstream)
        line = readline(fstream)
        if (length(line) <= 1)
            continue
        elseif (line[1] != '#')
            fields = split(line, sep)
            # skip SNP3+, INDEL
            if ( length(fields[5]) == 1 && length(fields[4]) == 1 )
                isnp += 1
                inf.chrom[isnp] = fields[1]
                inf.pos[isnp] = parse(Int, fields[2])
                inf.locusid[isnp] = fields[3]
                inf.allele1[isnp] = fields[4]
                inf.allele2[isnp] = fields[5]
                for iind = 1:ninds - 9
                    field = fields[iind + 9]
                    if (length(field) < 3)
                        continue
                    end
                    g = fields[iind+9][1:3]
                    if ( g == "0/0" )
                        dat[iind, isnp] = 1
                    elseif ( g == "0/1" )
                        dat[iind, isnp] = 2
                    elseif ( g == "1/1" )
                        dat[iind, isnp] = 3
                    end
                end
            end
        end     
    end

    ### return
    if as == SnpMatrix
        obj = SnpMatrix(dat, inf, cols[10:end])
    else
        print("error: unsupported return type")
        obj = []
    end
    return(obj)

end