using  DataFrames, RDatasets, Distributions
using MixedModels,SelectMixedModels
using SimMixedModels

betaT=[1.0,2.0];
sig10T=[1,0.9,0.9,1];
sig2T=0.1;
esigT=1.0;
timepoint=5
numsub=100
numgrp=10

fr = makedata2waylinear(timepoint,numsub,numgrp,betaT,sig10T,sig2T,esigT)

mg  = fit(lmmg( y~ time+(time|id)+(1|grp),fr))

Nsim= 1000
estimate = zeros(Nsim,9)

@time {for i in 1:Nsim

	fr = makedata2waylinear(timepoint,numsub,numgrp,betaT,sig10T,sig2T,esigT)
	#m = fit(lmm( y~ time+(time|id),fr))
	m=fit(lmmg( y~ time+(time|id)+(1|grp),fr))
    a=marBIC(m)
    b=marAIC(m)
    c=conAIC(m)
	estimate[i,1:3]=[a.likelihood a.df a.value]
	estimate[i,4:6]=[b.likelihood b.df b.value]
	estimate[i,7:9]=[c.likelihood c.df c.value]
end}


##-   rand(14314111)

mu = [0.0]
nf =2
nlvl = [4,8,10]
vc = [3.0, 2.0, 1.0]
prod(nlvl)

dat1 = CrossedDataBAL(mu,nf,nlvl,vc)
dat2 = NestedDataBAL(mu,nf,nlvl,vc)


@time m1 = fit(lmm(y ~ 1 + (1|x1)+(1|x2), dat1.dat));

@time m2 = fit(lmm(y ~ 1 + (1|x1)+(1|x2), dat2.dat));

mu = [0.0]
nf =3
nlvl = [3, 4,8,10]
vc = [2.0, 3.0, 2.0, 1.0]

dat11 = CrossedDataBAL(mu,nf,nlvl,vc)
dat22 = NestedDataBAL(mu,nf,nlvl,vc)


@time m11 = fit(lmm(y ~ 1 + (1|x1)+(1|x2)+(1|x3), dat11.dat));

@time m21 = fit(lmm(y ~ 1 + (1|x1)+(1|x2)+(1|x3), dat22.dat));



mu = [0.0]
nf =2
nlvl = [4,8,10]
vc = [0.0, 2.0, 1.0]
prod(nlvl)

dat1 = CrossedDataBAL(mu,nf,nlvl,vc)
dat2 = NestedDataBAL(mu,nf,nlvl,vc)


@time m1 = fit(lmm(y ~ 1 + (1|x1)+(1|x2), dat1.dat));

@time m2 = fit(lmm(y ~ 1 + (1|x1)+(1|x2), dat2.dat));
