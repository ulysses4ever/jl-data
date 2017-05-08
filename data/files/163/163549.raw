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

figure("GLY",figsize=(24,8))
subplot(2,3,1)
title("83: consumes")
plot(Tsim,vec(flux_array[83,:]))
subplot(2,3,2)
title("108: produces")
plot(Tsim,vec(flux_array[108,:]))
#subplot(2,3,3)
#title("127: produces")
#plot(Tsim,vec(flux_array[127,:]))
#subplot(2,3,4)
#title("128: consumes")
#plot(Tsim,vec(flux_array[128,:]))
#subplot(2,3,5)
#title("130: produces")
#plot(Tsim,vec(flux_array[130,:]))
subplot(2,3,4)
title("Net")
plot(Tsim,vec(flux_array[108,:]-flux_array[83,:]-10*flux_array[130,:]))
subplot(2,3,6)
title("155: consumes 10 units")
plot(Tsim,vec(flux_array[155,:]))
tight_layout()

