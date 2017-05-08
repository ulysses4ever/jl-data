module CeeSR

import AudioIO
import DSP
import Glob
import WebRTCVAD
import MergeIterator

# Read an audio file from `path` and resample to `fs`

function read_audio(path,fs=8000)
    AudioIO.open(path) do f
        x = AudioIO.read(f)[:]
        WebRTCVAD.sinc_resample(x,AudioIO.samplerate(f),fs)
    end
end

function write_audio(x,path,fs=8000)
    AudioIO.open(path,"w",fs) do f
        write(f,x)
    end
end

# Read an audio file and scale to [-1,1]

function read_single(path,fs=8000)
    read_audio(path,fs)/(1<<15)
end

# read all .flac files in `folder` and pad to same length

function read(folder)
    fnames = Glob.glob("*.flac",folder)
    print(fnames)
    max_size = 0
    for s = fnames
        AudioIO.open(s) do f
            max_size = max(max_size, f.sfinfo.frames)
        end
    end
    n = length(fnames)
    x = zeros(max_size,n)
    for i = 1:n
        fname = fnames[i]
        y = read_audio(fname)
        x[1:length(y),i] = y
    end
    x
end

# Kaiser low pass FIR coefficients
# Computed in Matlab with the following:
#
# fs = 8000;
# stopband = 150;
# passband = 400;
# db= 10^(-1.5);
# highpass = [0 1];
# lowpass = [1 0];
# [n,Wn,beta,ftype] =kaiserord([stopband passband],highpass,[0.05 db],fs);
# hh = fir1(n,Wn,ftype,kaiser(n+1,beta),'noscale');

const hh = [
   0.0040,  0.0052,  0.0064,  0.0074,  0.0082,  0.0086,  0.0085,  0.0078,
   0.0065,  0.0044,  0.0016, -0.0021, -0.0065, -0.0116, -0.0172, -0.0234,
  -0.0298, -0.0363, -0.0427, -0.0489, -0.0545, -0.0593, -0.0633, -0.0663,
  -0.0681,  0.9313, -0.0681, -0.0663, -0.0633, -0.0593, -0.0545, -0.0489,
  -0.0427, -0.0363, -0.0298, -0.0234, -0.0172, -0.0116, -0.0065, -0.0021,
   0.0016,  0.0044,  0.0065,  0.0078,  0.0085,  0.0086,  0.0082,  0.0074,
   0.0064,  0.0052,  0.0040
  ]

# Compute energies for each frame
# `fs` can't really be changed because `hh` depends on it and is fixed

function energy(x,frame_size=80,fs=8000)
    h = mod(-size(x,1),frame_size)
    # padded signal length
    n = size(x,1)+h
    m = size(x,2)

    # filter all input signals with centered kaiser
    z = filt(hh,pad_post(x,length(hh)+h,0))
    z = z[(1:n)+div(length(hh),2),:]

    # calculate energies
    en = reshape(z,frame_size,div(n,frame_size),m);
    en = reshape(log(sum(en.*en,1)/frame_size),div(n,frame_size),m);
    en
end

function pad_post(x,l,v)
    vcat(x,fill(v,l,size(x,2)))
end

function pad_pre(x,l,v)
    vcat(fill(v,l,size(x,2)),x)
end

# compute silence thresholds
# `w` and `s` are the lengths of the smoothing windows, `l` is the minimum
# threshold
function sthresh(en, w=200, s=9, l=-18.2)
    n = size(en,1)
    m = size(en,2)

    # smooth
    z = filt(ones(s),s,pad_replicate(en,s))
    z = z[(1:n)+div(s,2)+s,:]

    # more filtering...
    y = pad_replicate(z,w)

    # min filter (sloooow)
    mi = zeros(n+w,m)
    for i=1:n+w
        mi[i,:] = minimum(y[(1:w)+i,:],1)
    end
    mi = mi[(1:n)+div(w,2),:]

    # mean filter
    me = filt(ones(w),w,y)

    me = me[(1:n)+div(w,2)+w,:]
    max(mi+max(2,0.7*(me-mi)),l)
end

function repeat_array(x,l)
    m = size(x,1)
    r = Array(eltype(x),l*m,size(x,2))
    for i=0:l-1
        r[i*m+1:(i+1)*m,:] = x
    end
    r
end

function pad_replicate(x,l)
    p1 = repeat_array(x[1,:],l)
    p2 = repeat_array(x[end,:],l)
    vcat(p1,x,p2)
end

# significant frame detection
# `en` energies
# `t` thresholds
# `w` smoothing window

function sad(en,t,w=100)
    n,m = size(en)
    z = pad_pre(en.>t,w,false)
    s = zeros(Bool,n,m)
    for i=1:n
        # frame is significant if energy is over threshold or if majority of the
        # last w frames were over threshold
        s[i,:] = z[i+w,:] | (sum(z[(1:w)+i,:],1)*2 .> w)
    end
    s
end

function single_sad(audio_file)
    x = read_single(audio_file)
    u = energy(x)
    t = sthresh(u)
    s = sad(u,t)
    to_intervals(s)
end

# convert significant events from boolean frame representation to interval
# representation

function to_intervals(frames,frame_size=80,fs=8000)
    intervals = zeros(0)
    if length(frames) == 0
        return intervals
    end
    prev = false
    for i=1:length(frames)
        if prev && !frames[i]
            push!(intervals,i*frame_size/fs)
        elseif !prev && frames[i]
            push!(intervals,i*frame_size/fs)
        end
        prev = frames[i]
    end
    # close last interval
    if frames[end]
        push!(intervals,length(frames)*frame_size/8000)
    end
    reshape(intervals,2,div(length(intervals),2))
end

function read_labels(path)
    readdlm(path,'\t')[:,1:2]'
end

# `p` predicted events
# `a` actual events

function compare_labels(p,a)
    pit = take(zip(p[:],repeated(1)),size(p,2)*2)
    ait = take(zip(a[:],repeated(2)),size(a,2)*2)
    r = zeros(2,2)
    state = [false,false]
    t = 0.0
    for x = MergeIterator.merge_iterator(pit,ait)
        r[(2-state)...] += x[1]-t
        state[x[2]] = !state[x[2]]
        t = x[1]
    end
    r
end

end

if !isinteractive()
    if length(ARGS) < 2
        println("usage: ceesr-vad <audio_file> <label_file>")
        return 0
    end
    pr = CeeSR.single_sad(ARGS[1])
    ac = CeeSR.read_labels(ARGS[2])
    cm = CeeSR.compare_labels(pr,ac)
    cm /= sum(cm)
    @printf("==Confusion matrix==  predicted\n")
    @printf("                      significant  insignificant\n")
    @printf("actual   significant  %4.3f        %4.3f\n", cm[1,:]...)
    @printf("       insignificant  %4.3f        %4.3f\n", cm[2,:]...)
    @printf("\n")
    @printf("==Classification metrics==\n")
    @printf("accuracy:  %4.3f\n", cm[1,1]+cm[2,2])
    @printf("precision: %4.3f\n", cm[1,1]/sum(cm[:,1]))
    @printf("f1-score:  %4.3f\n", 2*cm[1,1]/(2*cm[1,1]+cm[1,2]+cm[2,1]))
end
