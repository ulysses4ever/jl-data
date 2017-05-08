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

figure("NADPH",figsize=(23,6))
subplot(3,7,1)
title("27: produces")
plot(Tsim,vec(flux_array[27,:]))
subplot(3,7,2)
title("28: consumes")
plot(Tsim,vec(flux_array[28,:]))
subplot(3,7,3)
title("30: produces")
plot(Tsim,vec(flux_array[30,:]))
subplot(3,7,4)
title("46: produces")
plot(Tsim,vec(flux_array[46,:]))
subplot(3,7,5)
title("47: consumes")
plot(Tsim,vec(flux_array[47,:]))
subplot(3,7,6)
title("60: produces")
plot(Tsim,vec(flux_array[60,:]))
subplot(3,7,7)
title("75: consumes")
plot(Tsim,vec(flux_array[75,:]))
subplot(3,7,8)
title("76: produces")
plot(Tsim,vec(flux_array[76,:]))
subplot(3,7,9)
title("82: consumes")
plot(Tsim,vec(flux_array[82,:]))
subplot(3,7,10)
title("100: consumes")
plot(Tsim,vec(flux_array[100,:]))
subplot(3,7,11)
title("105: consumes")
plot(Tsim,vec(flux_array[105,:]))
subplot(3,7,12)
title("106: consumes")
plot(Tsim,vec(flux_array[106,:]))
subplot(3,7,13)
title("110: consumes")
plot(Tsim,vec(flux_array[110,:]))
subplot(3,7,14)
title("111: consumes")
plot(Tsim,vec(flux_array[111,:]))
subplot(3,7,15)
title("112: consumes")
plot(Tsim,vec(flux_array[112,:]))
subplot(3,7,16)
title("113: consumes")
plot(Tsim,vec(flux_array[113,:]))
subplot(3,7,17)
title("115: consumes")
plot(Tsim,vec(flux_array[115,:]))
subplot(3,7,18)
title("117: consumes")
plot(Tsim,vec(flux_array[117,:]))
subplot(3,7,19)
title("120: consumes")
plot(Tsim,vec(flux_array[120,:]))
tight_layout()






