#=
Bartłomiej Sadowski 
=#
function msiecznych (f, a::Float64, b::Float64, delta::Float64, epsilon::Float64,maxit::Int)
#funkcja znajduje miejsca zerowe dla f w przedziale od a do b z precyzja delta/epsilon metoda siecznych.
#err 0:zbieżna; 1- nie udalo sie wyznaczyc pierwiastka; 2- dzielenie przez 0
	
	fa=f(a)
	fb=f(b)
	tmp=fa
	println(0," ",a," ",fa)
	println(1," ",b," ",fb)
	
	for it=it=2:maxit
		if(abs(fa)>abs(fb))
			tmp=a
			a=b
			b=tmp
			tmp=fa
			fa=fb
			fb=tmp	
		end
	if(fa==fb)
		r=a
		v=fa
		return r,v,it,2
	end
	s=(b-a)/(fb-fa)
	b=a
	fb=fa
	a=a-fa*s
	fa=f(a)
	#println(it," ",a," ",fa)
	if(abs(fa)<epsilon || abs(b-a)< delta)
		r=a
		v=fa
		return r,v,it,0
	end
	end

return 0,0,0,1

end
