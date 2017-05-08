using Distributions,DataFrames
# using Cairo, Gadfly

const n=10
const t=12
const p=2
var1=1.0
var2=1.5
sigma=(var1+var2)
rho=float64(var1/sigma)
 function vt()
 	full(Float64[ifelse(i1==j1, 1.0 , rho) for i1=1:t, j1=1:t])
 end

function cinv(a::Array{Float64,2})
	inv(cholfact(a))
end

type regression
	beta::Function
	hat::Function
	err::Function
end
rr=regression(
	(x,y,v)->inv(x'*cinv(v)*x)*(x'*cinv(v)*y),
	(x,td,v)->x*td*x',#*cinv(v),#	(x,v)->x*inv(x'*inv(v)*x)*x'*inv(v) ,
	(x,y,v)->y-x*inv(x'*cinv(v)*x)*x'*cinv(v)*y)


type dm
	dfbeta::Function
	dffit::Function
	cd::Function
end
unim=dm((x,h,e)->td*x'*cinv(v-h)*e,
	(h,e)->h*cinv(v-h)*e,
	(p,h,e)->e'*cinv(v-h)*h*cinv(v-h)*e/p)
timem=dm((td,x,as,h,e)->td*x'*as'*as*e*ttt,
	(cs,h,as,ttt,e)->cs'*h*as*as'*e/ttt,
	(ttt,as,cs,h,e)->e'*as*as'*h*as*as'*e/(p*ttt[1]^2)
	)

indm=dm((x,as,h,e)->td*x'*as*as'*e/(theta-as'*h*as)[1],
(cs,h,as,e)->cs'*h*as*as'*e/(theta-as'*h*as)[1],
(as,h,e)->e'*as*as'*h*as*as'*e/(p*(theta-as'*h*as)[1]^2))

type var
	vardb::Function
	vardf::Function
end
varu=var((td,x,h,v)->sqrt(diag(td*x'*cinv(v-h)*x*td)),
	(h,v)->sqrt(diag(h*cinv(v-h)*h)))
v=float64(vt())
x=Array(Float64,0,2)

y=Float64[]
ui=int64([(i-1)*t+1:i*t for i=1:n])
ti= int64([(i-1)*t+s for i=1:n, s=1:t])

for i=1:n
	cu=[fill(1.0,t) rand(20:80,t)]
	x=vcat(x,cu)


	cv=[cu*[5. 0.5]'+[fill(rand(Normal(0,var1)),t)]+[rand(Normal(0,var2),t)]]
	y=vcat(y,vec(cv))
end
# z=[7,77]

# x[z,2]=[100,99]
# y[z]=[68,67]
 # x[49:48+t,2]=rand(80.:100.,t)
 # y[49:48+t]=rand(50.:60.,t)
z=vec([(i-1)*t+8 for i=1:n])
 x[z,2]=rand(85:100.,n)
 y[z]=rand(60:80,n)

println([x y])
temp=rho/(1+(t-1)*rho)
theta=sigma*(1-rho)*(1-temp)
td=inv(sum([x[vec(ui[:,i0]),:]'*cinv(v)*x[vec(ui[:,i0]),:] for i0=1:n]))
e0=Float64[];de0=Float64[]
for i=1:n
	e=rr.err(x[vec(ui[:,i]),:],y[vec(ui[:,i])],v)

	push!(e0,mean(e));push!(de0,sum((e .- mean(e)) .^2)/(t-1))
end
sigma=sum(e0.^2)/n +mean(de0)


id1=Int64[];id2=Int64[];id3=Int64[]
for i=1:n
	# println("Unit- $i")
		ux=x[vec(ui[i]),:];uy=y[vec(ui[i])]
		h=rr.hat(ux,td,v);e=rr.err(ux,uy,v)
		 # isposdef(cinv(v))? println("Pd"):println("nd")
	for j =2:t-1
		as=full(Float64[l==j?1.0-temp:temp for l=1:t])
		cs=full(Float64[l==j? 1.0:0.0 for l=1:t])
		push!(plotvar,indm.dffit(cs,h,as,e)[1,1])
		# println(round([indm.dfbeta(ux,as,h,e)' indm.dffit(cs,h,as,e) indm.cd(as,h,e)],5))
		# println(round([vari.vardb(ux,as,h)' vari.vardf(h,as)],5))
		# println(round([(indm.dfbeta(ux,as,h,e)./vari.vardb(ux,as,h))' (indm.dffit(cs,h,as,e)/vari.vardf(h,as))  indm.cd(as,h,e)],5))
		push!(id1,(i-1)*t+j)
		# push!(d1,indm.dfbeta(ux,as,h,e)[1,1])
		# push!(d2,indm.dfbeta(ux,as,h,e)[2,1])
		 push!(d3,indm.dffit(cs,h,as,e)[1,1]/(sqrt(sigma)*vari.vardf(h,as)[1,1]))
		 push!(d4,indm.cd(as,h,e)[1,1])

	end
	# println("$(td*ux'*inv(v-h)*e)")
	# println(unim.dfbeta(ux,h,e))
	# println(round([unim.dfbeta(ux,h,e)]',5))
	# println(sigma)
	# d5=[d5; unim.dfbeta(ux,h,e)[:,1]]; d6=vcat(d6,unim.dfbeta(ux,h,e),[:,2])
	# # println(unitm.dffit(h1,e1))# unitm.cd(p,h,e)],5))
	push!(id2,i)
	d7=vcat(d7,vec(unim.dffit(h,e))./(sqrt(sigma)*varu.vardf(h,v)))
	 d8=vcat(d8,vec(unim.cd(p,h,e)))

end
# println("For single point deletion:\n DFFITS are $(id1[sortperm(vec(d3),by=abs)[end-2:end]])  \n
# CD are $(id1[sortperm(vec(d4),by=abs)[end-2:end]]) ")
	 writetable("siba.csv",DataFrame(OBS_NO=id1, DFFITS=d3, COOK_DIST=d4))

	# println("For unit deletion :\n DFFITS are $(id1[sortperm(vec(d7),by=abs)[end-2:end]])  \n
# CD are $(id1[sortperm(vec(d8),by=abs)[end-2:end]])")
	# writetable("sibb.csv",DataFrame( DFFITS=d7))
	# writetable("sibc.csv",DataFrame(COOK_DIST=d8))

d9=Float64[]

for j=2:t-1
	as=vec(Float64[l==j?1.0-temp:temp for l=1:t])
	cs=vec(Float64[l==j? 1.0:0.0 for l=1:t])
	# aas=kron(eye(n),as)
	# ccs=kron(eye(n),cs)
	for i=1:n
		ux=x[vec(ti[:,j]),:];uy=y[vec(ti[:,j])]
		h=rr.hat(ux,td,v);e=rr.err(ux,uy,v)
		ttt=theta-as'*h*as
		# println("Sib")
		tf=timem.dffit(cs,h,as,ttt,e)
		sd=vrnc=(as'*h*as)/sqrt(ttt)
		d9=vcat(d9,tf/sd)
		d6=vcat(d6,timem.cd(ttt,as,cs,h,e))
	end
	push!(id3,j)
end
# 	println("For time point deletion dffits and cook distance	:\n DFFITS are $(sortperm(vec(d9),by=abs)[end-2:end])  \n
# CD are $(id1[sortperm(vec(d6),by=abs)[end-2:end]])")
 writetable("sibd.csv",DataFrame( DFFITS=vec(d9)))
writetable("sibe.csv",DataFrame(COOK_DIST=d6))

# println("$(d9)    $(d6)")
	using Gadfly

function graph{T<:Float64}(x::Array{T,1}) #using DataArrays, DataFrames
	# x=rand(100)
	x2=find(abs(x) .> quantile(abs(x),0.98))
	y2=x[x2]
	x1=setdiff(1:length(x), x2)
	y1=setdiff(x,y2)
	pt=Gadfly.plot(layer(x=[x1],y=[y1],color=["blue"],Geom.point,Theme(default_point_size=0.5mm)),layer(x=[x2],y=[y2],color=["red"],Geom.point))
	##draw(PNG("pg.png",10inch,8inch),pt)
    draw(PDF("pg.pdf",10cm,8cm),pt)
end
# println(plotvar)
# graph(d3)


using PyPlot
using Distributions
using QuantEcon: meshgrid

n = 50
x = linspace(-3, 3, n)
y = x

z = Array(Float64, n, n)
f(x, y) = cos(x^2 + y^2) / (1 + x^2 + y^2)
for i in 1:n
    for j in 1:n
        z[j, i] = f(x[i], y[j])
    end
end

fig = figure(figsize=(8,6))
ax = fig[:gca](projection="3d")
ax[:set_zlim](-0.5, 1.0)
xgrid, ygrid = meshgrid(x, y)
ax[:plot_surface](xgrid, ygrid, z, rstride=2, cstride=2, cmap=ColorMap("jet"), alpha=0.7, linewidth=0.25)
