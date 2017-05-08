using GZip
using ProgressMeter

Base.start(::GZip.GZipStream) = 0
Base.next(s::GZip.GZipStream, st::Int) = GZip.read(s, UInt8), st+1 # position(s, true)
Base.done(s::GZip.GZipStream, st::Int) = eof(s)
#Base.length(s::GZip.GZipStream) = filesize(s.name)

@doc """
Read VCF files

This is a very simplistic VCF file reader that skips a lot of the data stored in the file.

All header lines are ignored.

Only field 2 (the chromosomal position) and fields 10+ (the variants) are read in.

The phase of the variant is ignored.

Input:

    filename: Name of VCF file. Can be compressed in GZip format

Output:

    idxs: Vector of chromosomal positions
    data: Vector of vectors of variants
    nnzcols: Vector of nonzero variants at each position

Also display progress meter
""" ->
function readvcf(filename)
    csize = filesize(filename)

    #gc_enable(false)
    stream = if endswith(filename, ".gz")
        GZip.open(filename)
    else
        Mmap.mmap(filename)
    end

    info("Reading $filename:")
    p = Progress(csize, 2, "", 50) #Progress bar

    idxs = Int[]
    #data = Vector{Int}[]
    #linedata = Int[]
    nnzcols = Int[]
    sizehint!(idxs, 5000)
    sizehint!(nnzcols, 5000)
    mode = :startline
    lineno = pos = posstart = fieldidx = nnzcol = skiplines = 0
    tmpbuf = IOBuffer(19)
    n = 0
    while true
    #for c in stream
        c = read(stream, UInt8)
        n += 1
        if mode == :startline
            lineno += 1
            fieldidx = 1
            mode = c == '#' ? :skipline : :seekpos #Skip comment

        elseif mode == :skipline
            if c == '\n'
                skiplines += 1
                mode = :startline
            end

        elseif mode == :seekpos
            startline = false

            if c == '\t'
                fieldidx += 1

                if fieldidx==2
                    mode = :readpos
                end
            end

        elseif mode == :readpos
            if c == '\t'
                pos = parse(Int64, takebuf_array(tmpbuf))
                fieldidx = 3
                mode = :seekdata
            else
                write(tmpbuf, c)
            end

        elseif mode == :seekdata
            if c == '\t'
                fieldidx += 1
                if fieldidx == 10
                    mode = :readdata
                    #push!(data, Int[])
                    #linedata = data[end]
                    nnzcol = 0
                    #if length(data) > 1
                    #    sizehint!(linedata, length(data[end-2]))
                    #end
                end
            end

        elseif mode == :readdata
            if c == '0'
                #push!(linedata, 0)
                continue

            elseif '0' <= c < '9'
                #push!(linedata, c-UInt8('0'))
                nnzcol += 1

            elseif c == '\n'
                mode = :startline
                push!(idxs, pos)
                #push!(data, linedata)
                push!(nnzcols, nnzcol)

                if lineno%500==0 #Update progress bar every 500 lines
                    coffset = position(stream, true)
                    update!(p, coffset)
                end

                if (lineno-skiplines)==5000 #Estimate memory consumption
                    coffset = position(stream, true)
                    estimatedlines = ceil(Int, csize/coffset*(lineno-skiplines))
                    println("Estimated number of lines:", estimatedlines)
                    sizehint!(idxs, estimatedlines)
                    sizehint!(nnzcols, estimatedlines)
                end

                #Debug: try only first 5000 lines
                #if lineno==5000
                #    @goto done
                #end

            elseif !(c == '\t' || c == '|' || c == '\\' || c == '\r')
                error("Unknown char $c ($(Uint(c))) on line $lineno, file offset $n`")
            end
        end

        eof(stream) && break
    end

    @label done

    println("Actual number of header lines:", skiplines)
    println("Actual number of record lines:", lineno-skiplines)

    println("Row density in rows: ", length(idxs)/idxs[end])
    println("Average column nonzeros: ", mean(nnzcols))#/length(data[1]))

    try
        close(stream)
    end

    #gc_enable(true)
    #idxs, data, nnzcols
    idxs, nnzcols
end

function Base.parse(::Type{Int64}, s::AbstractArray{UInt8})
    n = zero(Int64)
    for c in s
        n = 10*n + (c - UInt8('0'))
    end
    n
end

@time (idxs, nnzcols) = readvcf("ALL.chr1.phase3_shapeit2_mvncall_integrated_v5a.20130502.genotypes.vcf.gz")
#@time (idxs, data, nnzcols) = readvcf("try.vcf")

using JLD
#@time JLD.save("chr1.jld", "idxs", idxs, "data", data, "nnzcols", nnzcols, compress=true)
@time JLD.save("chr1.jld", "idxs", idxs, "nnzcols", nnzcols, compress=true)

