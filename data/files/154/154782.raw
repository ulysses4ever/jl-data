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
	
	for it=1:1000
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



