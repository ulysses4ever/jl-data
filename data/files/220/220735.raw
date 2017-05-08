#A function that constructs an epi-spline trend based on observed
#The first column is time, the last is the quantity to be predicted
#The other columns are independent variables assumed to predict the process

#t_exp is exponent in the t-variable
#naughty_exp is the exponent in the other independent variables
#num_part is the number of equally spaced-partitions for the 
#non-time independent variables

include("polyfun.jl")
include("genreg.jl")
include("evalreg.jl")

function reg_info(Data, t_exp, naughty_exp, num_part)
	
w=size(Data,2)-2 #number of non-time explanatory variable

#segment the non-time explanatory variables

cut=zeros(num_part+1,w) #the cut-points of the partition
step=zeros(w) #the step length of a partition in each direction
S=Array(Array{Int32}, num_part, w) #The indices in a particular slice

for i=1:w
        step[i] = (maximum(Data[:,i+1])-minimum(Data[:,i+1]))/num_part
        cut[1,i] = minimum(Data[:,i+1])

        for j = 1:num_part
                cut[j+1,i]=cut[1,i] + step[i]*j
                S[j,i]=find(x -> cut[j,i] <= x <= cut[j+1,i], Data[:,i+1])
        end
end

reg_array=zeros(num_part^w, (t_exp+1)*(naughty_exp)^w)
#there are some issues with total degree

FS=Array(Array{Int32}, num_part^w)

for k=0:num_part^w-1
        A=digits(k,num_part,w)
        for i= 1:w
                if i==1
                        FS[k+1] = S[A[i]+1,i]  #indices in the final cut
                else
                        FS[k+1] = intersect(FS[k+1],S[A[i]+1,i])
                end
        end
        reg_array[k+1, :]=genreg(Data[FS[k+1], 1:w+1], Data[FS[k+1], w+2],t_exp,naughty_exp)
#What if FS[k+1] is empty?!
end

return (reg_array,cut)

end

@debug function epi_trend(Data, t_exp, naughty_exp, num_part)

(reg_array, cut) = reg_info(Data, t_exp, naughty_exp, num_part) 
return X -> evalreg(reg_array, X[:,1:size(X,2)-1], cut, t_exp, naughty_exp)
end

