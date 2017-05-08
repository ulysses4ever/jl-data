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

figure("GXP",figsize=(16,10))
subplot(3,3,1)
title("5: GTP --> GDP")
plot(Tsim,vec(flux_array[5,:]))
subplot(3,3,2)
title("87: [] --> GMP")
plot(Tsim,vec(flux_array[87,:]))
subplot(3,3,3)
title("88: GMP --> GDP")
plot(Tsim,vec(flux_array[88,:]))
subplot(3,3,4)
title("89: GDP --> GTP")
plot(Tsim,vec(flux_array[89,:]))
subplot(3,3,5)
title("90: GTP --> GDP")
plot(Tsim,vec(flux_array[90,:]))
subplot(3,3,6)
title("127: GTP --> []")
plot(Tsim,vec(flux_array[127,:]))
subplot(3,3,7)
title("130: 438*GTP --> 438*GDP")
plot(Tsim,vec(flux_array[130,:]))
subplot(3,3,8)
title("133: GMP --> GTP")
plot(Tsim,vec(flux_array[133,:]))
subplot(3,3,9)
title("134: GMP --> GTP")
plot(Tsim,vec(flux_array[134,:]))
tight_layout()
