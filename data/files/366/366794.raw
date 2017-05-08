function plot_spectrogram(s, fs)
  # function to plot spectrogram
  # Inputs: s  - sound vector
  #         fs - sampling frequency
  # Output: S  - STFT representation of input sound vector
  #         * and a spectrogram plot

  # calculate spectrogram
  S = spectrogram(s[:,1], convert(Int, 25e-3*fs), convert(Int, 10e-3*fs); window=hanning)

  # get time frames and frequency bins
  t = time(S)
  f = freq(S)

  # create new figure
  figure()
  imshow(flipud(log10(power(S))), extent=[first(t), last(t), fs*first(f), fs*last(f)], aspect="auto")

  # add label
  xlabel("Time (samples)")
  ylabel("Frequency (Hz)")

  S
end