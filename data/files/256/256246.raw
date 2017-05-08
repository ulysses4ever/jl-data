module Stat

sender= [1 1 1 399; 1 1 453 1; 1 324 1 1; 456 1 1 1]
receiver=[ 1 1 1 399; 1 1 453 1; 1 324 1 1; 234 1 1 1]
matrix= Float64[] 
num_games=1000

#para sacar la probabilidad de una sola fila

function prob(sender)
    sender/sum(sender)
end

#para multiplicar matrices
#function product(sender,receiver)
    ms=mapslices(Stat.prob, sender ,2) 
    mr=mapslices(Stat.prob, receiver ,2) 
    probab=0.25*ms*mr
#end


end


