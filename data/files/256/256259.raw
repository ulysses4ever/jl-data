module Stat
using Barrett


#para que me de la probabilidad de muchos juegos
matrix= Any[] 
num_games=2
succesful_act=[1 2 3 4]

function prob_muchos(num_games)
	res=copy(matrix)
	for i=1:num_games
		tuple=Barrett.rep(num_games)
		sender= tuple[i][1]
		receiver=tuple[i][2]
		push!(res, Stat.product (sender,receiver))
	end
        return  mean(res), std(res)
end

#para sacar la probabilidad de una sola fila

function prob(sender)
    sender/sum(sender)
end

#te da la probabilidad del succesful_act
function product(sender,receiver)
    ms=mapslices(Stat.prob, sender ,2) 
    mr=mapslices(Stat.prob, receiver ,2) 
    probab=0.25*ms*mr
    resultado=copy(matrix)#para comparar con succesful act
    for i=1:length(succesful_act)
        push!(resultado, probab[i, succesful_act[i]])
    end
    return sum(resultado)
end


end
