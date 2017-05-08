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

figure("PYR",figsize=(16,10))
subplot(5,5,1)
title("1: produces")
plot(Tsim,vec(flux_array[1,:]))
subplot(5,5,2)
title("22: produces")
plot(Tsim,vec(flux_array[22,:]))
subplot(5,5,3)
title("42: produces")
plot(Tsim,vec(flux_array[42,:]))
subplot(5,5,4)
title("59: produces")
plot(Tsim,vec(flux_array[59,:]))
subplot(5,5,5)
title("60: produces")
plot(Tsim,vec(flux_array[60,:]))
subplot(5,5,6)
title("69: produces")
plot(Tsim,vec(flux_array[69,:]))
subplot(5,5,7)
title("118: produces")
plot(Tsim,vec(flux_array[118,:]))
subplot(5,5,8)
title("25: consumes")
plot(Tsim,vec(flux_array[25,:]))
subplot(5,5,9)
title("26: consumes")
plot(Tsim,vec(flux_array[26,:]))
subplot(5,5,10)
title("68: consumes")
plot(Tsim,vec(flux_array[68,:]))
subplot(5,5,11)
title("70: consumes")
plot(Tsim,vec(flux_array[70,:]))
subplot(5,5,12)
title("99: consumes")
plot(Tsim,vec(flux_array[99,:]))
subplot(5,5,13)
title("110: consumes")
plot(Tsim,vec(flux_array[110,:]))
subplot(5,5,14)
title("111: consumes 2 units")
plot(Tsim,vec(flux_array[111,:]))
subplot(5,5,15)
title("112: consumes")
plot(Tsim,vec(flux_array[112,:]))
subplot(5,5,16)
title("120: consumes 2 units")
plot(Tsim,vec(flux_array[120,:]))
subplot(5,5,17)
title("132: consumes")
plot(Tsim,vec(flux_array[132,:]))
subplot(5,5,18)
title("133: produces")
plot(Tsim,vec(flux_array[133,:]))
subplot(5,5,19)
title("134: consumes")
plot(Tsim,vec(flux_array[134,:]))
subplot(5,5,20)
title("135: produces")
plot(Tsim,vec(flux_array[135,:]))
subplot(5,5,21)
title("137: produces")
plot(Tsim,vec(flux_array[137,:]))
subplot(5,5,22)
title("138: produces")
plot(Tsim,vec(flux_array[138,:]))
subplot(5,5,23)
title("139: produces")
plot(Tsim,vec(flux_array[139,:]))
tight_layout()






