using DataFrames

df1 = readtable("dados/cenario1.csv");
df2 = readtable("dados/cenario2.csv");
df3 = readtable("dados/cenario3.csv");
df4 = readtable("dados/cenario4.csv");

eval(parse(df1[1, 1]))
df1_means = [sum(df1[i] / N)/35 for i in 3:15]
df1_var   = [sum((df1[i] - N*df1_means[i-2]) .^ 2)/N /35 for i in 3:15]
df1_h     = [sum(2 * df1[i] .* (N - df1[i]) / N^2) / 35  for i in 3:15]

eval(parse(df2[1, 1]))
df2_means = [sum(df2[i] / N)/35 for i in 3:15]
df2_var   = [sum((df2[i] - N*df2_means[i-2]) .^ 2)/N /35 for i in 3:15]
df2_h     = [sum(2 * df2[i] .* (N - df2[i]) / N^2) / 35  for i in 3:15]

eval(parse(df3[1, 1]))
df3_means = [sum(df3[i] / N)/35 for i in 3:15]
df3_var   = [sum((df3[i] - N*df3_means[i-2]) .^ 2)/N /35 for i in 3:15]
df3_h     = [sum(2 * df3[i] .* (N - df3[i]) / N^2) / 35  for i in 3:15]

eval(parse(df4[1, 1]))
df4_means = [sum(df4[i] / N)/35 for i in 3:15]
df4_var   = [sum((df4[i] - N*df4_means[i-2]) .^ 2)/N /35 for i in 3:15]
df4_h     = [sum(2 * df4[i] .* (N - df4[i]) / N^2) / 35  for i in 3:15]

using PyPlot
generations = collect(0:12)

# PLOT DAS FREQUÊNCIAS ALÉLICAS MÉDIAS
plot(generations, df1_means, label="Cenário 1")
plot(generations, df2_means, label="Cenário 2")
plot(generations, df3_means, label="Cenário 3")
plot(generations, df4_means, label="Cenário 4")
title("Frequências Alélicas Médias")
xlabel("Gerações")
ylabel("Frequência de Indivíduos Marrons")
legend(loc="upper left")
ylim(0.2, 0.8)
savefig("graficos/mean_freq_allele.png")
close()

# PLOT DAS VARIÃNCIAS ALÉLICAS MÉDIAS
plot(generations, df1_var, label="Cenário 1")
plot(generations, df2_var, label="Cenário 2")
plot(generations, df3_var, label="Cenário 3")
plot(generations, df4_var, label="Cenário 4")
title("Variâncias Alélicas Médias")
xlabel("Gerações")
ylabel("Variância de Indivíduos Marrons")
legend(loc="upper left")
# ylim(0.2, 0.8)
savefig("graficos/mean_var_allele.png")
close()

# PLOT DAS TAXAS DE HETEROZIGOSE MÉDIAS
plot(generations, df1_h, label="Cenário 1")
plot(generations, df2_h, label="Cenário 2")
plot(generations, df3_h, label="Cenário 3")
plot(generations, df4_h, label="Cenário 4")
title("Taxas de Heterozigoses Médias")
xlabel("Gerações")
ylabel("Taxa de Heterozigose")
legend(loc="upper right")
# ylim(0.2, 0.8)
savefig("graficos/mean_heterozigose.png")
close()
