module Stat

sender= [1 1 1 399; 1 1 453 1; 1 324 1 1; 456 1 1 1]
receiver=[ 1 1 1 399; 1 1 453 1; 1 324 1 1; 234 1 1 1]
matrix= Float64[] 
num_games=1000
succesful_act=[1 2 3 4]

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
    return p= sum(resultado)
   
end


end
