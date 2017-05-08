#=
Bartłomiej Sadowski 
=#

function mbisekcji(f, a::Float64, b::Float64,delta::Float64,epsilon::Float64)
#funkcja mbisekcji znajduje funkcji "f" zero na danym przedziale a,b z dokladnoscia delta/epsilon metoda bisekcji
#u-wartosc funkcji w punkcie a, uu - wartosc funkcji w punkcie f(b), r - srodek przedzialu err - 0: brak błędu; 1: funkcja nie zmienia znaku
	u=f(a)
	uu=f(b)
	e=b-a
	it =0
	if(sign(u)==sign(uu)) 
		return 0,0,0,1
	end
	
	for abs(e)<delta || abs(v)<epsilon
		e=e/2
		r=a+e
		v=f(r)
		#println(it,r,v,e)
		if(abs(e)<delta || abs(v)<epsilon) 
			return r,v,it,0
		end
		if(sign(v)!=sign(u)) 
			b=r
			uu=v
		else
			a=r
			u=v		
		end
	end
end


#=
Bartłomiej Sadowski 
=#
function msiecznych (f, x0::Float64, x1::Float64, delta::Float64, epsilon::Float64,maxit::Int)
#funkcja znajduje miejsca zerowe dla f w przedziale od a do b z precyzja delta/epsilon metoda siecznych.
#err 0:zbieżna; 1- nie udalo sie wyznaczyc pierwiastka; 2- dzielenie przez 0
	
	fa=f(x0)
	fb=f(x1)
	tmp=fa
	

	for it=it=2:maxit
		if(abs(fa)>abs(fb))
			tmp=x0
			x0=x1
			x1=tmp
			tmp=fa
			fa=fb
			fb=tmp	
		end
	if(fa==fb)
		r=x0
		v=fa
		return r,v,it,2
	end
	s=(x1-x0)/(fb-fa)
	x1=x0
	fb=fa
	x0=x0-fa*s
	fa=f(x0)
	#println(it," ",x0," ",fa)
	if(abs(fa)<epsilon || abs(x1-x0)< delta)
		r=x0
		v=fa
		return r,fa,it,0
	end
end
r=x0
v=fa
return r,v,it,1

end
#=
Bartłomiej Sadowski 
=#
function mstycznych (f,pf,x0::Float64, delta::Float64,epsilon::Float64, maxit::Int)
#funkcja znajduje miejsca zerowe dla f od miejsca x0 i pochodnej pf
#err 0:zbieżna; 1- nie udalo sie wyznaczyc pierwiastka w maxit iteracjach ; 2- pochodna bliska 0 
	v=f(x0)
	r=x0-(v/pf(x0))
	if(abs(v)<epsilon)
		return 0,x0,v,1
	end
	for it=1:maxit
		r=x0-(v/pf(x0))
		v=f(r)
		#println(it,r,v)
		if(abs(pf(x0))<epsilon)
			return r,v,it,2
		end

		if(abs(r-x0)<delta || abs(v)<epsilon)
			return r,v,it,0 
		end
		x0=r
	end
	
	return r,v,maxit,1
end
