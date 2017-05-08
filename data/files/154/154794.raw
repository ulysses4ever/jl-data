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
