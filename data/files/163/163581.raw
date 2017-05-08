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

figure("GXP",figsize=(16,10))
subplot(3,3,1)
title("3: UTP --> UDP")
plot(Tsim,vec(flux_array[3,:]))
subplot(3,3,2)
title("93: [] --> UMP")
plot(Tsim,vec(flux_array[93,:]))
subplot(3,3,3)
title("94: UMP --> UDP")
plot(Tsim,vec(flux_array[94,:]))
subplot(3,3,4)
title("95: UDP --> UTP")
plot(Tsim,vec(flux_array[95,:]))
subplot(3,3,5)
title("96: UTP --> []")
plot(Tsim,vec(flux_array[96,:]))
subplot(3,3,6)
title("154: UTP --> []")
plot(Tsim,vec(flux_array[154,:]))
subplot(3,3,7)
title("162: UMP --> UTP")
plot(Tsim,vec(flux_array[162,:]))
subplot(3,3,8)
title("163: UMP --> UTP")
plot(Tsim,vec(flux_array[163,:]))
tight_layout()
