using PyPlot

function PlotNAD(Tsim,X)

figure("NAD",figsize=(14,8))
subplot(2,2,1)
plot(Tsim,X[:,100])
ylabel("NAD (mM)")
xlabel("Time (h)")
subplot(2,2,2)
plot(Tsim,X[:,101])
ylabel("NADH (mM)")
xlabel("Time (h)")
subplot(2,2,3)
plot(Tsim,X[:,102])
ylabel("NADP (mM)")
xlabel("Time (h)")
subplot(2,2,4)
plot(Tsim,X[:,103])
ylabel("NADPH (mM)")
xlabel("Time (h)")
tight_layout()

end
