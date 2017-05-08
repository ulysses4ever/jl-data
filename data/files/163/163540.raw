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

figure(figsize=(16,12))
subplot(4,4,1)
title("26: ATP-->AMP")
plot(Tsim,vec(flux_array[26,:]))
subplot(4,4,2)
title("65: ATP-->AMP")
plot(Tsim,vec(flux_array[65,:]))
subplot(4,4,3)
title("83: 2ATP-->ADP+AMP")
plot(Tsim,vec(flux_array[83,:]))
subplot(4,4,4)
title("87: ATP-->AMP")
plot(Tsim,vec(flux_array[87,:]))
subplot(4,4,5)
title("90: IMP-->AMP")
plot(Tsim,vec(flux_array[90,:]))
subplot(4,4,6)
title("91: AMP-->ATP")
plot(Tsim,vec(flux_array[91,:]))
subplot(4,4,7)
title("92: 2ADP-->ATP+AMP")
plot(Tsim,vec(flux_array[92,:]))
subplot(4,4,8)
title("93: 3ATP-->2ADP+AMP")
plot(Tsim,vec(flux_array[93,:]))
subplot(4,4,9)
title("100: 4ATP-->3ADP+AMP")
plot(Tsim,vec(flux_array[100,:]))
subplot(4,4,10)
title("102: ATP-->AMP")
plot(Tsim,vec(flux_array[102,:]))
subplot(4,4,11)
title("103: ATP-->AMP")
plot(Tsim,vec(flux_array[103,:]))
subplot(4,4,12)
title("155: 219ATP-->219AMP")
plot(Tsim,vec(flux_array[155,:]))
subplot(4,4,13)
title("156: AMP-->ATP")
plot(Tsim,vec(flux_array[156,:]))
subplot(4,4,14)
title("157: AMP-->ATP")
plot(Tsim,vec(flux_array[157,:]))
#subplot(4,4,15)
#title("Net")
#plot(Tsim,vec(flux_array[26,:]+flux_array[65,:]+flux_array[83,:]+flux_array[87,:]+flux_array[90,:]-flux_array[91,:]+flux_array[92,:]+flux_array[93,:]+flux_array[100,:]+flux_array[102,:]+flux_array[103,:]+219*flux_array[130,:]-flux_array[131,:]-flux_array[132,:]))
tight_layout()






