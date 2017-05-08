using GZip
using JLD
using ProgressMeter

#Eat the second argument for non-GZip IOstreams
Base.position(b::Base.AbstractIOBuffer, ::Bool) = position(b)

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
    Is = Int64[]
    Js = Int64[]
    Vs = Int8[]
    sizehint!(Is, INITIAL_SIZE_GUESS)
    sizehint!(Js, INITIAL_SIZE_GUESS)
    sizehint!(Vs, INITIAL_SIZE_GUESS)

    csize = filesize(filename)
    p = Progress(csize, 2, "", 50) #Progress bar

    mode = :startline
    lineno = pos = fieldidx = skiplines = 0
    thisentry = 0
    rowid = colid = 1
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
        IOBuffer(Mmap.mmap(filename))
    end

    #Iterate through file
    while true
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
                    seek(tmpbuf, 0)
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
                #Horrible hack to force tmpbuf pointer forward without storing a value
                tmpbuf.ptr += 1
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

            elseif c==':' #Extra genome-level data I don't understand
                mode = :skipfield

            else
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

            if thisentry != 0#position(tmpbuf) > 0
                push!(Is, pos)
                push!(Js, colid)
                push!(Vs, thisentry) #parse(Int8, takebuf_array(tmpbuf)))
                thisentry = 0

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

        eof(stream) && break
    end

    @label done

    finish!(p)
    println("Actual number of header lines:", skiplines)
    println("Actual number of record lines:", lineno-skiplines)
    println("Actual number of nonzeros:", length(Vs))

    if length(Vs) > 0
        nrows = maximum(Is)
        ncols = maximum(Js)
        println("Number of record rows: ", rowid)
        println("Number of logical rows: ", nrows)
        println("Number of logical cols: ", ncols)
        println("Average density: ", length(Vs)/(Int64(nrows)*Int64(ncols)))
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
        if n<0 || !('0'<=c<='9')
            error(string(Char(c),':',s,':',n))
        end
    end
    n
end

#Main driver
#Read in list of files from command line
#If no files specified, Read all .vcf.gz and .vcf files in current directory
#Saves data as a sparse matrix in coordinate (IJV) format to jld

cd(joinpath("1000genomesdata", "raw"))
filelist = length(ARGS) > 0 ? ARGS : filter(f->(endswith(f, ".vcf") ||
    endswith(f, ".vcf.gz")), readdir())

for filename in filelist
    destfilename = joinpath("..", "parsed", string(filename[1:end-(endswith(filename, "vcf.gz") ? 6 :
        3)], "jld"))

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

