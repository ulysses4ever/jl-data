f = readdlm("output.xyz")


k = size(f)
s = f[1] + 2

dt = zeros(0)
dx = zeros(0)

for i in 1:s:k[1]
	H = [f[i+3,2],f[i+3,3],f[i+3,4]]
	O = [f[i+2,2],f[i+2,3],f[i+2,4]]
	md_iter = f[i+1,3]
	d = norm(H-O)
	push!(dx,d)
	push!(dt,md_iter)
	
end

writedlm("tvb",[dt dx],'\t')

using PyPlot


plot(dt,dx)
xlim([0,1000])
xlabel(L"\mathrm{Time (fs)}")
ylabel(L"\mathrm{Bond \, Length} (\AA)")
title(L"\mathrm{Time \, variation\, of\, the\,OH\, bond\, length\, in\, the\, canonical\, ensemble}")
savefig("pyplot_tvb.svg")
