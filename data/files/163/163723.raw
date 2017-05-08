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

figure("ARG",figsize=(24,8))

subplot(3,3,1)
title("100: produces")
plot(Tsim,vec(flux_array[100,:]))

subplot(3,3,2)
title("121: consumes")
plot(Tsim,vec(flux_array[121,:]))

subplot(3,3,3)
title("122: consumes")
plot(Tsim,vec(flux_array[122,:]))

subplot(3,3,4)
title("123: consumes")
plot(Tsim,vec(flux_array[123,:]))

subplot(3,3,5)
title("124: consumes")
plot(Tsim,vec(flux_array[124,:]))

subplot(3,3,6)
title("125: consumes")
plot(Tsim,vec(flux_array[125,:]))

subplot(3,3,7)
title("126: consumes")
plot(Tsim,vec(flux_array[126,:]))

subplot(3,3,8)
title("167: consumes 5 units")
plot(Tsim,vec(flux_array[167,:]))

subplot(3,3,9)
title("169: consumes 5 units")
plot(Tsim,vec(flux_array[169,:]))

tight_layout()

