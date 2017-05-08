using ArgParse
s = ArgParseSettings()
@add_arg_table s begin
    "bed_file"
        help = "a file to read experiment ids from line by line"
        arg_type = ASCIIString
        default = "-"
    "--bin_width"
        help = "how many base pairs should each bin cover"
        arg_type = Int64
        default = 1000
    "--threshold"
        help = "how positions need to be defined"
        arg_type = Float64
        default = 0.5
    "--method"
        help = "how to summarize the data in each bin (sum [default], nonzero, average)"
        arg_type = ASCIIString
        default = "sum"
    "--quiet", "-q"
        help = "don't print anything"
        action = :store_true
end
args = parse_args(s)
bedFile = args["bed_file"]
binWidth = args["bin_width"]
threshold = args["threshold"]
method = args["method"]
quiet = args["quiet"]

using SeqUtils

# how long we consider each chromosome (a rough upper bound)
chromosomeLengths = {
    "chr1" => 250000000,
    "chr2" => 244000000,
    "chr3" => 199000000,
    "chr4" => 192000000,
    "chr5" => 181000000,
    "chr6" => 172000000,
    "chr7" => 160000000,
    "chr8" => 147000000,
    "chr9" => 142000000,
    "chr10" => 136000000,
    "chr11" => 136000000,
    "chr12" => 134000000,
    "chr13" => 116000000,
    "chr14" => 108000000,
    "chr15" => 103000000,
    "chr16" => 91000000,
    "chr17" => 82000000,
    "chr18" => 79000000,
    "chr19" => 60000000,
    "chr20" => 64000000,
    "chr21" => 49000000,
    "chr22" => 52000000,
    "chrX" => 156000000,
    "chrY" => 60000000
#    "chrM" => 16000 leave this out since it may be regulated differently
}

# the total number of bins we will use for the whole genome
totalBins = sum([int(ceil(chromosomeLengths[c]/binWidth)) for c in keys(chromosomeLengths)])

# read each input line and process the corresponding experiment
inStream = bedFile == "-" ? STDIN : open(bedFile)

# make a temporary directory
tmpId = randstring(30)
mkpath("/tmp/$tmpId")

# split the incoming file by chromosome into the temp dir
awkCmd = "{print > \"/tmp/$tmpId/\"\$1\".bg\"}"
run(inStream |> `awk $awkCmd`)

# parse each chromosome one at a time
binData = zeros(totalBins)
pos = 1
for chromosome in collect(keys(chromosomeLengths))
    nbins = int(ceil(chromosomeLengths[chromosome]/binWidth))

    # only parse if the chromosome has non-zero data
    if isfile("/tmp/$tmpId/$chromosome.bg")

        f = open("/tmp/$tmpId/$chromosome.bg")
        binData[pos:pos+nbins-1] = zerobin(
            binWidth,
            nbins,
            map(parsebedgraphline, eachline(f)),
            threshold=threshold,
            method=method
        )
        close(f)
        if !quiet println(STDERR, "binned $chromosome...") end
    end

    pos += nbins
end

writedlm(STDOUT, binData)


