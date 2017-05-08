#!/usr/bin/env julia

using WAV
using MFCC

function readpost(file)
    fd = open(file)
    nframes, nphones = read(fd, Int32, 2);
    x = reshape(read(fd, Float32, nframes*nphones), int(nphones), int(nframes))
    phonetab = String[]
    for i=1:nphones
        data = Uint8[]
        while ((char=read(fd, Uint8)) != '\0')
            push!(data, char)
        end
        push!(phonetab, ASCIIString(data))
    end
    close(fd)
    x, phonetab
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

function phonedetect(wav::String, phone::String)
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

## center of gravity
function cog(p, minf=0, maxf=8000)
    p = vec(p)
    energy = sum(p)
    nf = size(p,1)
    freq = [minf:(maxf-minf)/nf:maxf][1:nf]
    return dot(p,freq) / energy
end

function startstop(sel, collar, sr, L)
    limit(iround((sel[1]/100 - collar)*sr), 1, L), limit(iround((sel[2]/100 + collar)*sr), 1, L)
end

function listen(x::Array, sel::Array; collar=0.3, sr=16000)
    L = size(x,1)
    nr = size(sel, 1)
    selection = falses(nr)
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
            if inp[1] == 'r'
                continue
            end
            selection[i] = inp[1] == 's'
            break
        end
    end
    hcat(1:nr, sel)[selection,:]
end

function listen(file::String, phone=["s", "sh"], thres=0.5)
    run(`sox $file -r 16000 single/in.wav`)
#    abswav = joinpath(pwd(), file)
    abswav = "single/in.wav"
    base = splitext(file)[1]
    print("Computing phone posteriors...")
    run(`sh ./run-posteriorgram in.wav`)
    x, phonetab = readpost("single/out.bin")
    println("done")
    sel = phonedetect(x, phonetab, phone, thres)
    w, sr = wavread(abswav)
    sel = listen(w, sel, sr=sr)
    outf = "$base.s.sel"
    fd = open(outf, "w")
    nr = size(sel,1)
    for i=1:nr
        println(fd, join(vcat(file, vec(sel[i,:])), "\t"))
    end
    close(fd)
    return outf, nr
end

function compute_cog_selection(x, s, sr=16000)
    p = powspec(vec(x), sr)
    L = size(p,2)
    for i in 1:size(s,1)
        slice = mean(p[:,limit(s[i,1],1,L):limit(s[i,2],1,L)], 2)
        println("line ", s[i,1], " cog ", cog(slice))
    end
end

if ! isinteractive()
    for file in ARGS
        println("Processing ", file)
        outf, nr = listen(file)
        println("$nr lines written to $outf")
    end
end
