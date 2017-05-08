function cost_gradient(θ, X, y, λ)
    m = length(y)
    return (θ::Array) -> begin 
        h = sigmoid(X * θ)   
        J = (1 / m) * sum(-y .* log(h) .- (1 - y) .* log(1 - h)) + λ / (2 * m) * sum(θ[2:end] .^ 2)         
    end, (θ::Array, storage::Array) -> begin  
        h = sigmoid(X * θ) 
        storage[:] = (1 / m) * (X' * (h .- y)) + (λ / m) * [0; θ[2:end]]        
    end
end
sigmoid(z) = 1.0 ./ (1.0 + exp(-z))

using Optim
#...
# Prerequisites:
# X size is (m,d), where d is the number of training set features
# y size is (m,1)
# λ as the regularization parameter, e.g 1.5
# ITERATIONS number of iterations, e.g. 1000
λ=1.5
ITRERATIONS=1000
function norz{T}(u::T)
  u=convert(Array,u)
rng=(maximum(u)-minimum(u))/2
(u .-mean(u)) ./rng
  #function body
end
# X=rand(Gamma(),50);#y=[zeros(25);ones(25)]
xx=readtable("./Desktop/PSB/nanodata.txt",header=false,separator='\t')
xx=convert(Array,xx)
xx1=xx[:,[2,3,6]]
X=ones(size(xx,1))
for u in collect([xx1[:,j] for j in 1:3])
       X=[X norz(u)]
       end
# fieldnames(X)=["c","T","P","D"]
X=[X map(t->t^2,X[:,2])]
X=[X map(t->t^2,X[:,3])]
X=[X map(t->t^2,X[:,4])]
X=[X map((t,s)->t*s,X[:,2],X[:,3])]
X=[X map((t,s)->t*s,X[:,3],X[:,4])]
X=[X map((t,s)->t*s,X[:,2],X[:,4])]

#X=[ones(size(X,1)) X] #add x_0=1.0 column; now X size is (m,d+1)
y=xx[:,7] ./180
initialθ = zeros(size(X,2),1) #initialTheta size is (d+1, 1)
cost, gradient! = cost_gradient(initialθ, X, y, λ)
res = optimize(cost, gradient!, initialθ, method = ConjugateGradient(), iterations = ITERATIONS);
θ = Optim.minimizer(res);


############
function mm{T<:Array{Float64,1}}(l::T,r::T)
	i=j=1; nswaps=0
	while  i<length(l) &&  j<length(r)
		if r[j]<l[i]
			nswaps+=length(l)-i+1
			j+=1
		else
			i+=1
		end
	end
	nswaps
end

x=map(Float64,x)
length(x)%2==0?l=x[1:length(x)/2]:l=[1:(length(x)+1)/2]
mm(l,setdiff(x, l))
###############
cl=Union{Float64,Int64}[]
length(cl)==1?

function ctab{S,T}(c::T="smo",d::S="dia",cuts::T=[summary(c)])
  c2=collect(["≤$(cuts[1])",["$(cuts[i])-$(cuts[i+1])" for i in 1:(end-1)],"$(cuts[end])>"])
  d2=collect(["Others","DPLD","Asthma","Asthma +AR","COPD","COPD + AR"])
  c1=Dict(zip(c2,collect(1:length(c2))))
  d1=Dict(zip(d2,collect(1:length(d2))))
  f=Array(Int64,length(c2),length(d2))
  for i in c2
    cond[i]=[cuts(i)]
    for j in d2
      f[c1[i],d1[j]]=size(dta[((eval(parse("dta[:$c]")).==i) & 
        (eval(parse("dta[:$d]")).==j)),:],1)
    end
  end
  #function body
  tab=NamedArrays.NamedArray(f,(c2,d2),(c,d))
end                     
######

function ctab{T}(c::T="smo",d::T="dia")
  c2=collect(["No","ExSmoker","G1", "G2", "G3", "G4", "G5", "Smoker"])
  d2=collect(["Others","DPLD","Asthma","Asthma +AR","COPD","COPD + AR"])
  c1=Dict(zip(c2,collect(1:length(c2))))
  d1=Dict(zip(d2,collect(1:length(d2))))
  f=Array(Int64,length(c2),length(d2))
  for i in c2
    for j in d2
      f[c1[i],d1[j]]=size(dta[((eval(parse("dta[:$c]")).==i) & 
        (eval(parse("dta[:$d]")).==j)),:],1)
    end
  end
  #function body
  tab=NamedArrays.NamedArray(f,(c2,d2),(c,d))
end
###########

using  DataFrames
dta=readtable("./Desktop/PSB/dd.csv");
dtb=complete_cases!(dta);
by(dtb, [:smo, :dia]) do d
             DataFrame(count=length(d[:age]),m = mean(d[:age]), v = var(d[:age]))
         end
for x in collect(unique(dtb[:pob]))
         dta=dtb[dtb[:pob].==x,:]
         dp=ctab()
         condis(dp)[3]
         fp=open("pb.txt","a");write(fp,"Place of Birth=$x \n")
         write(fp,"Contingency Table= \n $dp \n")
         write(fp,"Association Measure= $(condis(dp)[3]) \n");close(fp)
       end

###########################################
function logL{T,S}(beta::T,x::Union{T,S}, y::S)
    l=0.0
    for i in 1:length(y)
        pi[i] = exp( beta[1] + beta[2]* x[i])/(1 + exp( beta[1] + beta[2]* x[i]))
        l+=(y[i]*log(pi[i]) + (1-y[i])*log(1- pi[i]))
    end
    l
end

function logL{T,S}(beta::T,x::Union{T,S}, y::S)
    l=0.0
    for i in 1:length(y)
        pi[i] = exp( beta[1] + beta[2]* x[i])/(1 + exp( beta[1] + beta[2]* x[i]))
        l+=(y[i]*log(pi[i]) + (1-y[i])*log(1- pi[i]))
    end
    l
end
function σ{T}(t::T)
  1.0 ./(1.0 .+ exp(-t))
end
function newton{T}(beta::T,x::T,y::T)
  c=0;d=1.0;x=[ones(length(x)) x]
while(d>0.000001 && c<100)
z=x*beta .+ (1.0 .- σ(y.*(x*beta))) .*y
a=diagm(σ(x*beta).*(1 .- σ(x*beta)))
b=inv(x'*a*x)*(x'*a*z)
d=abs(findmax(b.-beta)[1])
c+=1
beta=b
end
beta
end


#########################
function condis{T}(t::T)
        n = size(t,1)
        m = size(t,2)
       p=sum([t[i,j]*sum([t[r,c] for r=(i+1):n, c=(j+1):m]) for i=1:(n-1), j=1:(m-1)])
        #sum(t * map((r, c)->sum(t[1<r<<=r_ndx]
       q=sum([t[i,j]*sum([t[r,c] for r=(i+1):n, c=1:(j-1)]) for i=1:n-1, j=2:m])
       return p,q,(p-q)/(p+q)
       end

       ########################################################

       function chi{T}(x::T)
       	ex=[sum(x[i,:]).*sum(x[:,j])/sum(x) for i in 1:size(x,1), j in 1:size(x,2)]
       	sum([(x[i,j]-ex[i,j])^2/ex[i,j] for i in 1:size(x,1), j in 1:size(x,2)])
       end

function cramerV{T}(x::T)
	I=size(x,1)
	J=size(x,2)
	(chi(x)/(sum(x)*min(I-1,J-1)))^0.5
end

#Goodman_Kruskal_lambda
function lambda{T}(x::T)
	e1=sum(x)-max(sum(x,1))
	e2=sum(sum(x,2)-max(x,2))
	(e1-e2)/e1
end
#	 = (sum_)ax_i(p_ij) - max_i(p_i+))/(1 - max_i(p_i+))

#tau(R|C) =
function tau{T}(x::T)
	p=map(t->t/sum(x),x)
	r=sum(p,2)
	c=sum(p,1)
	(sum([p[i,j]^2/c[j] for i in 1:size(p,1), j in 1:size(p,2)])-sum(r))/(1-sum(r))
end
# (sum_ij p^2_ij / p_+j - sum_i p_i+)/(1 - sum_i p_i+)

# U(R|C) = 
function urc{T}(x::T)
	p=map(t->t/sum(x),x)
	r=[sum(p[i,:]) for i in 1:size(p,1)]
	c=[sum(p[:,i]) for i in 1:size(p,2)]
	sum(p[i,j]*log(p[i,j]/c[j])-sum(r[i]*log(r[i])))/(-sum(r[i]*log(r[i])))
end
#  (sum_ij p_ij log (p_ij/p+j) - sum_i p_i+ log p_i+) / (-sum_i p_i+ log p_i+)

#################################################
using Distributions
samp=rand(Exponential(3.),500)
u=map(t->cdf(Exponential(3.),t),samp)
v=map(t->cdf(Normal(3.,9.),t),samp)
x=[ones(Float64,size(u,1)) map(t->log(t/(1-t)),u)]
s=inv(x'*x)

y=map(t->log(t/(1-t)),v)
e=y-x*s*x'*y
dfb


b=cor(x,y)*std(x)/std(y)
a=mean(x)-b*mean(y)

x1=map(t->(t-a)/b,y)
cor(x,x1)
################
cd("/Users/sibnarayanguria/Desktop/JULIA")
using DataFrames
d=convert(Array,readtable("trees.csv"));
y=d[:,end];x=d[:,1:(end-1)];
s=inv(x'*x);
e=y.-x*s*x'*y
loy=map(t->log(length(y[y.<=t])/length(y[y.>=t])),y)
loe=map(t->log(length(e[e.<=t])/length(e[e.>=t])),e)
cor(loy,loe)

############
macro p(n)
    if typeof(n) == Expr 
       println(n.args)
    end
    return n
end
