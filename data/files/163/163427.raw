Rate = readdlm("Sens/1/Rate")
Sat = readdlm("Sens/1/Sat")
Cont = readdlm("Sens/1/Cont")

i_range = 2:180
for i in i_range
    rate = readdlm("Sens/$i/Rate")
    sat = readdlm("Sens/$i/Sat")
    cont = readdlm("Sens/$i/Cont")
    Rate = [Rate rate]
    Sat = [Sat sat]
    Cont = [Cont cont]
end

Rate_m = Float64[]
Rate_s = Float64[]
for i in 1:size(Rate)[1]
    push!(Rate_m,mean(Rate[i,:]))
    push!(Rate_s,std(Rate[i,:]))
end

Sat_m = Float64[]
Sat_s = Float64[]
for i in 1:size(Sat)[1]
    push!(Sat_m,mean(Sat[i,:]))
    push!(Sat_s,std(Sat[i,:]))
end

Cont_m = Float64[]
Cont_s = Float64[]
for i in 1:size(Cont)[1]
    push!(Cont_m,mean(Cont[i,:]))
    push!(Cont_s,std(Cont[i,:]))
end

writedlm("Sens/Rate180",Rate)
writedlm("Sens/Sat180",Sat)
writedlm("Sens/Cont180",Cont)

writedlm("Sens/Rate_m",Rate_m)
writedlm("Sens/Sat_m",Sat_m)
writedlm("Sens/Cont_m",Cont_m)

writedlm("Sens/Rate_s",Rate_s)
writedlm("Sens/Sat_s",Sat_s)
writedlm("Sens/Cont_s",Cont_s)
