#!/usr/bin/env julia

using Compat
using WAV
using MFCC
using DataFrames

function wavfilter(xsr)
    (x, sr) = xsr
    return (vec(mean(x,2)), float(sr))
end


function readpost(file, phones=true)
    fd = open(file)
    nframes, nphones = read(fd, Int32, 2);
    x = reshape(read(fd, Float32, nframes*nphones), @compat Int(nphones), @compat Int(nframes))
    phones || return x
    phonetab = AbstractString[]
    for i=1:nphones
        data = UInt8[]
        while ((char=read(fd, UInt8)) != '\0')
            push!(data, char)
        end
        push!(phonetab, ASCIIString(data))
    end
    close(fd)
    x, phonetab
end

## read in a kaldi matrix
function readark(file)
    iterator = eachline(pipeline(`/Users/david/bin/kaldi/copy-matrix ark:$file ark,t:-`, ))
    d = Dict{AbstractString,Matrix{Float32}}()
    rows = Vector{Float32}[]
    index = ""
    for line in iterator
        line=chomp(line)
        if line[end] == '['
            index = split(line)[1]
            rows = Matrix{Float32}[]
            continue
        end
        last = line[end] == ']'
        numbers = split(line)
        if last
            pop!(numbers)
        end
        push!(rows, [parse(Float32,s) for s in numbers]')
        if last
            d[index] = vcat(rows...)
        end
    end
    d
end



function disp(x, phonetab, norm=true)
    if norm
        x ./= sum(x, 1)
    end
    writedlm("out.txt", x)
    writedlm("phonetab.txt", phonetab)
    run(`./posteriorgram.R`)
    run(`open out.pdf`)
end

function entropy(p::Vector)
    ent = 0
    for x in p
        if x>0
            ent -= x*log(x)
        end
    end
    ent
end

entropy(p::Matrix, dim=1) = mapslices(entropy, p, dim)

function addent(x, tab)
    ent = entropy(x)
    ent ./= maximum(ent)
    vcat(ent, x), vcat("H", tab)
end

function phonedetect(x, phonetab, phone, thres=0.5, gap=5)
    rows = findin(phonetab, [phone])
    length(rows) > 0 || error("Phone $phone not found")
    hit = [0, int(vec(sum(x[rows,:],1)) .> thres), 0]
    d = diff(hit)
    starts = find(d .== 1)
    stops = find(d .== -1)-1
    ## fill in the gaps
    i = 1
    while i < length(starts)
        if starts[i+1] - stops[i] ≤ gap
            splice!(starts, i+1)
            splice!(stops, i)
        else
            i += 1
        end
    end
    hcat(starts, stops)
end

function phonedetect(wav::AbstractString, phone::AbstractString)
    abswav = joinpath(pwd(), wav)
    print("Computing phone posteriors...")
    run(`./run-posteriorgram $abswav`)
    x, phonetab = readpost("single/out.bin")
    println("done")
    phonedetect(x, phonetab, phone)

end

function play(x::Array, sr=16000)
    wavwrite(x, sr, "/tmp/out.wav")
    run(`play -q -V1 /tmp/out.wav`)
end

limit(x, mi, ma) = max(mi, min(ma, x))

function startstop(sel, collar, sr, L)
    limit(iround((sel[1]/100 - collar)*sr), 1, L), limit(iround((sel[2]/100 + collar)*sr), 1, L)
end

function listen(x::Array, sel::Array; collar=0.3, sr=16000)
    L = size(x,1)
    nr = size(sel, 1)
    selection = falses(nr)
    input = Array(AbstractString, nr)

    for i=1:nr
        colstart, colstop = startstop(sel[i,:], collar, sr, L)
        start, stop = startstop(sel[i,:], 0, sr, L)
        while true
            print(@sprintf("Nr %3d. Listen for s", i))
            play(x[start:stop], sr)
            sleep(0.2)
            print(".")
            play(x[colstart:colstop], sr)
            sleep(0.2)
            print("s: ")
            play(x[start:stop], sr)
            inp = readline(STDIN)
            input[i] = chomp(inp)
            words = split(inp)
            if length(words) == 1 && words[1][1] == 'r'
                continue
            else
                selection[i] = length(words) > 0
                break
            end
        end
    end
    hcat(1:nr, sel, input)[selection,:]
end

function listen(file::AbstractString, phone=["s", "sh"], thres=0.5)
    run(`sox $file -r 16000 single/in.wav`)
#    abswav = joinpath(pwd(), file)
    abswav = "single/in.wav"
    base = splitext(file)[1]
    print("Computing phone posteriors...")
    run(`sh ./run-posteriorgram in.wav`)
    x, phonetab = readpost("single/out.bin")
    println("done")
    sel = phonedetect(x, phonetab, phone, thres)
    norig = size(sel, 1)
    w, sr = wavread(abswav)
    sel = listen(w, sel, collar=0.6, sr=sr)
    outf = "$base.s.sel"
    fd = open(outf, "w")
    nr = size(sel,1)
    for i=1:nr
        println(fd, join(vcat(file, vec(sel[i,:])), "\t"))
    end
    close(fd)
    return outf, nr, norig
end

## center of gravity for a slice of a power spec
function cog(p; minf=0, maxf=8000)
    p = vec(p)
    energy = sum(p)
    nf = size(p,1)
    freq = collect(minf:(maxf-minf)/nf:maxf)[1:nf]
    return dot(p,freq) / energy
end

function compute_cog_selection(x, s, sr=16000)
    p = powspec(vec(x), sr, steptime=0.01, wintime=0.03)
    L = size(p,2)
    nsel = size(s, 1)
    res = Array(Float64, nsel)
    for i in 1:nsel
        if s[i,2]-2 ≥ s[i,1]    # require minimum suration of 3 frames for powerspec computation
            slice = mean(p[:,limit(s[i,1],1,L):limit(s[i,2]-2,1,L)], 2)
            res[i] = cog(slice, maxf=sr/2)
        else
            res[i] = NaN
        end
    end
    res
end

## reads a .s.sel file from disc and the corresponding sound file
function readsel(file::AbstractString)
    sel = readdlm(file)
    wavf = unique(sel[:,1])[1]
    sel = sel[:,3:end]
#    tmp = tempname() * ".wav"
#    run(`sox $wavf -r 16000 $tmp`)
    try
        wav, sr = wavread(wavf) |> wavfilter
        return sel, wav, sr
    catch
        return sel, nothing, nothing
    end
end

## parallel:
## addprocs(4)
## @everywhere reload("posteriorgram.jl")

## center-of-gravity of energy in a powerspectrum, given files
function cog_files{S<:AbstractString}(filelist::Vector{S})
    @parallel (vcat) for f in filelist
        s, x, sr = readsel(f)
        if x != nothing
            s = s[find(s[:,2]-s[:,1] .≥ 2), :] # only consider entries of at least 30 ms for powspec wintime
            c = compute_cog_selection(x, s[:,1:2], sr)
            subj, cohort, part = split(replace(basename(f), ".s.sel", ""), "-", limit=3)
            subj, sex, r = [subj[r] for r in (1:4, 5, 6:6)]
            DataFrame(cog=c, subject=subj, sex=sex, r=parse(Int, r), c=parse(Int, cohort), part=part,
            start=s[:,1]/100, stop=s[:,2]/100, phoneme=s[:,3], word=s[:,4])
        else
            println("Could not process ", f)
            DataFrame()
        end
    end
end

function run_cog(listfile::AbstractString="sel.list")
    sel = vec(readdlm(listfile, ASCIIString))
    addprocs(4)
    @everywhere include("posteriorgram.jl")
    res = cog_files(sel)
    rmprocs(workers())
    return res
end

## main
if ! isinteractive() && myid() == 1
    for file in ARGS
        println("Processing ", file)
        outf, nr, norig = listen(file)
        nfa = norig - nr
        println("$nr lines written to $outf, you judged $nfa false alarms")
    end
end
