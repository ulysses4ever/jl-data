
module Estad

sender= [399 1 1 1; 1 453 1 1; 1 1 324 1; 1 1 1 234]
receiver=[399 1 1 1; 1 453 1 1; 1 1 324 1; 1 1 1 234]

i=1

#function prob_array(i)
     array_s= sender[i , :]
       prob_array_s= maximum (array_s)/sum (array_s)

ind=ind2sub(size(array), indmax(array))[2]#da la posicion del max

       array_r= receiver[ind , :]
       prob_array_r= array_r[1,i]/sum (array_r)

0.25*prob_array_s*prob_array_r

end
