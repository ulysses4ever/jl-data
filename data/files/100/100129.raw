using GZip
using JLD
using ProgressMeter

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
function read(filename)
    csize = filesize(filename)

    stream = if endswith(filename, ".gz")
        GZip.open(filename)
    else
        Mmap.mmap(filename)
    end

    p = Progress(csize, 2, "", 50) #Progress bar

    Is = Int[]
    Js = Int[]
    Vs = Int8[]
    sizehint!(Is, 500000)
    sizehint!(Js, 500000)
    sizehint!(Vs, 500000)

    mode = :startline
    lineno = pos = posstart = rowid = fieldidx = nnzcol = skiplines = 0
    colid = 1
    tmpbuf = IOBuffer(19)
    n = 0
    while true
        c = try
            read(stream, UInt8)
        catch EOFError
            break
        end
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
                    nnzcol = 0
                    colid = 0
                end
            end

        elseif mode == :readdata
            if c == '0' && position(tmpbuf)==0
                continue

            elseif '0' ≤ c ≤ '9'
                write(tmpbuf, c)

            elseif c == '\n'
                rowid += 1
                mode = :savedata

            elseif (c == '\t' || c == '|' || c == '\\' || c == '\r')
                #Reset IO buffer
                colid += 1
                mode = :savedata
            else
                error("Unknown char $c ($(Uint(c))) on line $lineno, file offset $n`")
            end
        end
        if mode == :savedata
            if lineno%500==0 #Update progress bar every 500 lines
                coffset = position(stream, true)
                update!(p, coffset)
            end

            if position(tmpbuf) > 0
                push!(Is, rowid)
                push!(Js, colid)
                push!(Vs, parse(Int8, takebuf_array(tmpbuf)))

                if length(Vs) == 500000 #Estimate memory consumption
                    coffset = position(stream, true)
                    estnnz = ceil(Int, length(Vs)*csize/coffset)
                    info("Number of nonzero entries read so far:", length(Vs))
                    info("Estimated number of nonzero entries:", estnnz)
                    estnnz = ceil(Int, 1.1*estnnz)
                    sizehint!(Is, estnnz)
                    sizehint!(Js, estnnz)
                    sizehint!(Vs, estnnz)
                end
            end

            mode = c=='\n' ? :startline : :readdata
        end
    end

    @label done

    finish!(p)
    println("Actual number of header lines:", skiplines)
    println("Actual number of record lines:", lineno-skiplines)
    println("Actual number of nonzeros:", length(Vs))

    nrows = maximum(Is)
    ncols = maximum(Js)
    println("Number of rows: ", nrows)
    println("Number of cols: ", ncols)
    println("Average density: ", length(Vs)/(nrows*ncols))

    try
        close(stream)
    end

    Is, Js, Vs
end

function Base.parse{T<:Integer}(::Type{T}, s::AbstractArray{UInt8})
    n = zero(T)
    @fastmath for c in s
        n::T = 10n + (c - T(0x30))
    end
    n
end

#Main driver
#Read all .vcf.gz files in current directory and saves data as a sparse matrix
#in coordinate (IJV) format to jld
for filename in readdir()
    endswith(filename, ".vcf.gz") || continue
    destfilename = string(split(filename, ".")[2], ".jld")

    isfile(destfilename) && continue

    info("Reading $filename:")

    @time (Is, Js, Vs) = readvcf(filename)

    info("Saving sparse matrix to $destfilename:")
    @time JLD.save(destfilename, "I", Is, "J", Js, "V", Vs, compress=true)
end

