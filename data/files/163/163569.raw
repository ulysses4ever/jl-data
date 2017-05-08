using PyPlot

num_flux = convert(Int64,readcsv("flux/num_flux")[1])

freq = 1
flux_array = readdlm("flux/$freq")

for i in 2*freq:freq:num_flux
    flux = readdlm("flux/$i")
    flux_array = [flux_array flux]
end

flux_array = sortrows(flux_array')' # This sorts the columns of flux_array, in case timepoints are out of order

Tsim = vec(flux_array[1,:])
flux_array = flux_array[2:end,:]

writedlm("t_flux",t_flux)
writedlm("flux_array",flux_array)

figure("Q8",figsize=(18,6))
subplot(2,4,1)
title("51: consumes")
plot(Tsim,vec(flux_array[51,:]))
subplot(2,4,2)
title("71: produces")
plot(Tsim,vec(flux_array[71,:]))
subplot(2,4,3)
title("74: consumes")
plot(Tsim,vec(flux_array[74,:]))
subplot(2,4,4)
title("77: consumes")
plot(Tsim,vec(flux_array[77,:]))
subplot(2,4,5)
title("93: consumes")
plot(Tsim,vec(flux_array[93,:]))
subplot(2,4,6)
title("136: consumes")
plot(Tsim,vec(flux_array[136,:]))
subplot(2,4,7)
title("139: consumes")
plot(Tsim,vec(flux_array[139,:]))
subplot(2,4,8)
title("Net")
plot(Tsim,vec(-flux_array[51,:]+flux_array[71,:]-flux_array[74,:]-flux_array[77,:]-flux_array[93,:]+flux_array[136,:]-flux_array[139,:]))
tight_layout()
