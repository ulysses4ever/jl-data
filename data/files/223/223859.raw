function primefactors(n::Integer)
    f = factor(n)
    return sort(collect(keys(f)))
end


function buscarMaximo(n::Integer)
	maximo = 0
	for i in primefactors(n)
		if i > maximo
			maximo = i
		end
	end
	return maximo
end

println("El factor primo mas grande es $(buscarMaximo(600851475143))")
