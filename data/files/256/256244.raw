module Estad

sender= [399 1 1 1; 1 453 1 1; 1 1 324 1; 1 1 1 234]
receiver=[399 1 1 1; 1 453 1 1; 1 1 324 1; 1 1 1 234]
matrix= Float64[] 

#para sacar la probabilidad de una sola fila
function prob_array(i)
       array_s= sender[i , :]
       prob_array_s= maximum (array_s)/sum (array_s)

       ind=ind2sub(size(array_s), indmax(array_s))[2]#da la posicion del max

       array_r= receiver[ind , :]
       prob_array_r= array_r[1,i]/sum (array_r)
      return 0.25*prob_array_s*prob_array_r  
end


#para prob_game #pero me da 8 elementos en lugar de 4... hay que arreglarlo...me dice que matrix_game no está definido. 
function prob_game(matrix)
    for i=1:4
        matrix_game=copy (matrix)
        push!(matrix_game, Estad.prob_array(i))
    end
    println ("matrixgame: ", matrix_game)
    return  mean(matrix_game)
            std(matrix_game)
end

#hay que hacer la media y desviación meterlo en otro matriz donde estén todas los juegos(1000)
#prob_total

# hay que hacer la estadística de esta nueva matriz...


end
