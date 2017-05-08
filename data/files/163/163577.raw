using PyPlot

num_flux = convert(Int64,readcsv("flux/num_flux")[1])

freq = 50
flux_array = readcsv("flux/$freq")

for i in 2*freq:freq:num_flux
    flux = readcsv("flux/$i")
    flux_array = [flux_array flux]
end

flux_array = sortrows(flux_array')' # This sorts the columns of flux_array, in case timepoints are out of order

Tsim = vec(flux_array[1,:])
flux_array = flux_array[2:end,:]

figure("SUCC",figsize=(16,10))
subplot(4,4,1)
title("49: consumes")
plot(Tsim,vec(flux_array[49,:]),"blue")
subplot(4,4,2)
title("50: produces")
plot(Tsim,vec(flux_array[50,:]),"blue")
subplot(4,4,3)
title("51: consumes")
plot(Tsim,vec(flux_array[51,:]),"blue")
subplot(4,4,4)
title("52: produces")
plot(Tsim,vec(flux_array[52,:]),"blue")
subplot(4,4,5)
title("57: produces")
plot(Tsim,vec(flux_array[57,:]),"blue")
subplot(4,4,6)
title("112: produces")
plot(Tsim,vec(flux_array[112,:]),"blue")
subplot(4,4,7)
title("113: produces")
plot(Tsim,vec(flux_array[113,:]),"blue")
subplot(4,4,8)
title("121: produces")
plot(Tsim,vec(flux_array[121,:]),"blue")
subplot(4,4,9)
title("122: produces")
plot(Tsim,vec(flux_array[122,:]),"blue")
subplot(4,4,10)
title("123: produces")
plot(Tsim,vec(flux_array[123,:]),"blue")
subplot(4,4,11)
title("124: produces")
plot(Tsim,vec(flux_array[124,:]),"blue")
subplot(4,4,12)
title("125: produces")
plot(Tsim,vec(flux_array[125,:]),"blue")
subplot(4,4,13)
title("126: produces")
plot(Tsim,vec(flux_array[126,:]),"blue")
subplot(4,4,14)
title("143: produces")
plot(Tsim,vec(flux_array[143,:]),"blue")
subplot(4,4,15)
title("Net")
plot(Tsim,vec(-flux_array[49,:]+flux_array[50,:]-flux_array[51,:]+flux_array[52,:]+flux_array[57,:]+flux_array[112,:]+flux_array[113,:]+flux_array[121,:]+flux_array[122,:]+flux_array[123,:]+flux_array[124,:]+flux_array[125,:]+flux_array[126,:]+flux_array[143,:]),"blue")
#axis([0,3,0,15])
tight_layout()






