function plot_spectrogram(s, fs, nFFT, nShift, winType)
    S = spectrogram(s[:,1], convert(Int, nFFT),
                    convert(Int, nShift); window=winType)
    t = time(S)
    f = freq(S)
    imshow(flipud(log10(power(S))), extent=[first(t), last(t),
             fs*first(f), fs*last(f)], aspect="auto")
    S
end