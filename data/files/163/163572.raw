using PyPlot

num_flux = convert(Int64,readcsv("flux/num_flux")[1])

freq = 10
flux_array = readcsv("flux/$freq")

for i in 2*freq:freq:num_flux
    flux = readcsv("flux/$i")
    flux_array = [flux_array flux]
end

flux_array = sortrows(flux_array')' # This sorts the columns of flux_array, in case timepoints are out of order

Tsim = vec(flux_array[1,:])
flux_array = flux_array[2:end,:]

figure("R5P",figsize=(18,6))
subplot(2,4,1)
title("33: consumes")
plot(Tsim,vec(flux_array[33,:]))
subplot(2,4,2)
title("34: produces")
plot(Tsim,vec(flux_array[34,:]))
subplot(2,4,3)
title("37: consumes")
plot(Tsim,vec(flux_array[37,:]))
subplot(2,4,4)
title("38: produces")
plot(Tsim,vec(flux_array[38,:]))
subplot(2,4,5)
title("83: consumes")
plot(Tsim,vec(flux_array[83,:]))
subplot(2,4,6)
title("93: consumes")
plot(Tsim,vec(flux_array[93,:]))
subplot(2,4,7)
title("109: consumes")
plot(Tsim,vec(flux_array[109,:]))
subplot(2,4,8)
title("118: consumes")
plot(Tsim,vec(flux_array[118,:]))
tight_layout()
