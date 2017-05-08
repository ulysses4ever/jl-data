using GZip
using JLD
using ProgressMeter

@doc "Initial guess for how many nonzero entries will be read in" ->
const INITIAL_SIZE_GUESS = 1_000_000

@doc "Fudge factor used to reallocate storage vectors" ->
const SLACK_FACTOR = 1.25

@doc "Update progress bar each time this many lines are read" ->
const UPDATE_LINE_INTERVAL = 500

@doc """
Read VCF files into a [0,1,2]-genotype matrix

Implementation note:

    This is a very simplistic VCF file reader that skips a lot of the data
    stored in the file.

    All header lines are ignored.

    Only field 2 (the chromosomal position) and fields 10+ (the variants) are
    read in.

    The phases of the variants are ignored.

Input:

    filename: Name of VCF file. Can be compressed in GZip format

Output:

    Is: Row indexes of variants
    Js: Column indexes of variants
    Vs: Number of variants at position I for sample J

Side effects:

    Also displays progress meter

Reference:

    Based on the VCF Version 4.2 Specification at

    http://samtools.github.io/hts-specs/VCFv4.2.pdf
""" ->
function Base.read(filename)
    Is = Int32[]
    Js = Int32[]
    Vs = Int8[]
    sizehint!(Is, INITIAL_SIZE_GUESS)
    sizehint!(Js, INITIAL_SIZE_GUESS)
    sizehint!(Vs, INITIAL_SIZE_GUESS)

    csize = filesize(filename)
    p = Progress(csize, 2, "", 50) #Progress bar

    mode = :startline
    lineno = pos = posstart = rowid = fieldidx = skiplines = 0
    thisentry = 0
    colid = 1
    tmpbuf = IOBuffer(19)
    n = 0

    #Now actually try to read file
    if csize==0
        warn("File $filename is empty")
        @goto done
    end

    stream = if endswith(filename, ".gz")
        GZip.open(filename)
    else
        Mmap.mmap(filename)
        #except e
        #    if isa(e, ArgumentError) && e.msg == "requested size must be > 0, got 0"
        #        warn("File $filename is empty")
        #        @goto done
        #    end
        #end
    end

    #Iterate through file
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
                    colid = thisentry = 0
                end
            end

        elseif mode == :readdata
            if c == '0' && position(tmpbuf)==0
                continue

            elseif '0' ≤ c ≤ '9' || c == '.'
                seek(tmpbuf, position(tmpbuf)+1)
                #write(tmpbuf, c)

            elseif c == '\n'
                rowid += 1
                mode = :savedata

            elseif (c == '\t' || c == '\r')
                #Reset IO buffer
                if position(tmpbuf) > 0
                    thisentry += 1
                    seek(tmpbuf, 0)
                end
                colid += 1
                mode = :savedata

            elseif (c == '|' || c == '\\') #Ploidy divider
                #Reset IO buffer
                if position(tmpbuf) > 0
                    thisentry += 1
                    seek(tmpbuf, 0)
                end
                mode = :savedata

            elseif c==':' #Extra genome-level data I don't understand
                mode = :skipfield

            else
                println(mode)
                println(takebuf_array(tmpbuf))
                error("Unknown char $(Char(c)) (0x$(hex(c))) on line $lineno, file offset $n")
            end

        elseif mode == :skipfield
            if c == '\t'
                mode = :readdata
            elseif c == '\n'
                mode = :startline
            end
        end

        if mode == :savedata
            if lineno % UPDATE_LINE_INTERVAL == 0 #Update progress bar
                coffset = position(stream, true)
                update!(p, coffset)
            end

            if position(tmpbuf) > 0
                push!(Is, rowid)
                push!(Js, colid)
                push!(Vs, thisentry) #parse(Int8, takebuf_array(tmpbuf)))

                if length(Vs) == INITIAL_SIZE_GUESS
                    #More data than initially guessed
                    #Estimate memory consumption and resize in-memory storage
                    coffset = position(stream, true)
                    estnnz = ceil(Int, length(Vs)*csize/coffset)
                    info("Number of nonzero entries read so far:", length(Vs))
                    info("Estimated number of nonzero entries:", estnnz)
                    estnnz = ceil(Int, SLACK_FACTOR*estnnz)
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

    if length(Vs) > 0
        nrows = maximum(Is)
        ncols = maximum(Js)
        println("Number of rows: ", nrows)
        println("Number of cols: ", ncols)
        println("Average density: ", length(Vs)/(nrows*ncols))
    end

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
#Read in list of files from command line
#If no files specified, Read all .vcf.gz and .vcf files in current directory
#Saves data as a sparse matrix in coordinate (IJV) format to jld
filelist = length(ARGS) > 0 ? ARGS : filter(f->(endswith(f, ".vcf") ||
    endswith(f, ".vcf.gz")), readdir())

for filename in filelist
    destfilename = if count(x->x=='.', filename) > 2
        #The 1000 genomes project files have names like
        #ALL.chr9.phase3_shapeit2_mvncall_integrated_v5a.20130502.genotypes.vcf.gz
        #map to chr9.jld
        string(split(filename, ".")[2], ".jld")
    else #Safe choice
        string(filename, ".jld")
    end

    #Don't process file if it already exists
    if isfile(destfilename)
        warn("Output file $destfilename already exists. Skipping.")
        continue
    end

    info("Reading $filename:")

    @time (Is, Js, Vs) = read(filename)

    info("Saving sparse matrix to $destfilename:")
    @time JLD.save(destfilename, "I", Is, "J", Js, "V", Vs, compress=true)
end

