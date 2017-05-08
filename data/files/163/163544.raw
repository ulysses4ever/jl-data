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

figure("AXPTotal",figsize=(16,12))
subplot(2,2,1)
title("90: IMP-->AMP")
plot(Tsim,vec(flux_array[90,:]))
subplot(2,2,2)
title("109: 3*ATP --> 2*ADP")
plot(Tsim,vec(flux_array[109,:]))
subplot(2,2,3)
title("151: ATP --> []")
plot(Tsim,vec(flux_array[151,:]))
subplot(2,2,4)
title("Net")
plot(Tsim,vec(flux_array[90,:]-flux_array[109,:]-flux_array[151,:]))
tight_layout()

