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

figure("ASP",figsize=(24,16))

subplot(4,3,1)
title("85: consumes")
plot(Tsim,vec(flux_array[85,:]))

subplot(4,3,2)
title("90: consumes")
plot(Tsim,vec(flux_array[90,:]))

subplot(4,3,3)
title("93: consumes")
plot(Tsim,vec(flux_array[93,:]))

subplot(4,3,4)
title("100: consumes")
plot(Tsim,vec(flux_array[100,:]))

subplot(4,3,5)
title("101: produces")
plot(Tsim,vec(flux_array[101,:]))

subplot(4,3,6)
title("102: consumes")
plot(Tsim,vec(flux_array[102,:]))

subplot(4,3,7)
title("103: consumes")
plot(Tsim,vec(flux_array[103,:]))

subplot(4,3,8)
title("112: consumes")
plot(Tsim,vec(flux_array[112,:]))

subplot(4,3,9)
title("113: consumes")
plot(Tsim,vec(flux_array[113,:]))

subplot(4,3,10)
title("117: consumes")
plot(Tsim,vec(flux_array[117,:]))

subplot(4,3,11)
title("145: produces")
plot(Tsim,vec(flux_array[145,:]))

subplot(4,3,12)
title("171: consumes 12 units")
plot(Tsim,vec(flux_array[171,:]))

tight_layout()

