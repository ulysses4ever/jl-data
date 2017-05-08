
using PortfolioLoss


# -------------- Parameters setting --------------------

m= 100 				# number of obligors
rho=0.25 			# rho for latent variavle
sigmae=1.0 			# std for random error added to latent var. in default
sigmar=1.0 			# std for random error added to latent var. in recovery
df=12.0 			# DF for Gamma dist. for t-copula
kendall=0.1 		# Kendall's tau for correaltion btween two Gamma
defval=1.0 			# default loss
defthredconst=0.25 	# a on P(X_i > a*h(n))
defthredpower= 0.5 	# t for h(n)=n^t in P(X > a*h(n))
murecovery=-2.0 	# mean in prob for random recovery rate
lossbval=0.5 		# b in P(L > b*n )

# ----------- make input vectors for function ----------
d=1 # for simplicity, dimension of latent var. is 1
a=reshape(zeros(m*d).+rho,m,d)
cona=zeros(m).+defthredconst
hn=m^defthredpower
muc=zeros(m)+murecovery
c=zeros(m) .+ defval
	

# ----------------- Define Portfolio Loss Type  -------------
# normal
nm  = NormalPfModels(a,hn,cona,sigmae,c)               
# noraml with random recovery
rnm = RNormalPfModels(a,hn,cona,sigmae,c,a,sigmar,muc)
# t-copula 
tm  = TPfModels(a,hn,cona,sigmae,c,df)
# t-copula with random recovery                   
rtm = RTPfModels(a,hn,cona,sigmae,c,a,sigmar, muc,df, kendall)

#------------------ simulation --------------------------
B=50000 # simulation size
uuval = m*lossbval # b*n in P(L > b*n)

# all *SIMval functions return a tuple (r1,r2)
# r1 = estimate of P(L > b*n)
# r2 = sample variance of B simulation samples

#normal 
ordinarysampling2SIMval(B, nm, uuval)  # raw simulation
importantsamplingSIMval(B, nm, uuval)  # important sampling 

# noraml with random recovery
ordinarysampling2SIMval(B, rnm, uuval)  # raw simulation
importantsamplingSIMval(B, rnm, uuval)  # important sampling 

# t-copula 
ordinarysampling2SIMval(B, tm, uuval) 	# raw simulation
condmcSIMval(B, tm, uuval)				# conditional important sampling
muis0,varis0= findparais(tm, uuval)		# parametes for cond. IS with cross entropy
condmcceSIMval(B,tm,uuval,muis0,varis0) # cond. important sampling with cross entropy

# t-copula with random recovery  
ordinarysampling2SIMval(B, rtm, uuval)		  # raw simulation
condmcSIMval(B, rtm, uuval)					  # conditional important sampling
muis0,varis0,gam0 = findparais(rtm, uuval)	  # parametes for cond. IS with cross entropy
condmcceSIMval(B,rtm,uuval,muis0,varis0,gam0) # cond. important sampling with cross entropy


