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
