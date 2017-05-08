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

figure("GLN",figsize=(24,16))
subplot(4,4,1)
title("83: consumes")
plot(Tsim,vec(flux_array[83,:]))
subplot(4,4,2)
title("84: consumes")
plot(Tsim,vec(flux_array[84,:]))
subplot(4,4,3)
title("87: consumes")
plot(Tsim,vec(flux_array[87,:]))
subplot(4,4,4)
title("93: consumes")
plot(Tsim,vec(flux_array[93,:]))
subplot(4,4,5)
title("96: consumes")
plot(Tsim,vec(flux_array[96,:]))
subplot(4,4,6)
title("100: consumes")
plot(Tsim,vec(flux_array[100,:]))
subplot(4,4,7)
title("102: consumes 10 units")
plot(Tsim,vec(flux_array[102,:]))
subplot(4,4,8)
title("105: consumes")
plot(Tsim,vec(flux_array[105,:]))
subplot(4,4,9)
title("107: produces")
plot(Tsim,vec(flux_array[107,:]))
subplot(4,4,10)
title("109: consumes")
plot(Tsim,vec(flux_array[109,:]))
subplot(4,4,11)
title("118: consumes")
plot(Tsim,vec(flux_array[118,:]))
subplot(4,4,12)
title("141: consumes")
plot(Tsim,vec(flux_array[141,:]))
subplot(4,4,13)
title("174: consumes 13 units")
plot(Tsim,vec(flux_array[174,:]))
subplot(4,4,14)
title("Net")
plot(Tsim,vec(-flux_array[83,:]-flux_array[84,:]-flux_array[87,:]-flux_array[93,:]-flux_array[96,:]-flux_array[100,:]-flux_array[102,:]-flux_array[105,:]+flux_array[107,:]-flux_array[109,:]-flux_array[118,:]-flux_array[141,:]-13*flux_array[174,:]))
tight_layout()






