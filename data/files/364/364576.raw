function writeFloat(output, num::Float64)
        write(output,@sprintf("%.3f", num))
end

function writeMatr(output,matr::Array{Float64})
        (r,c)= size(matr)
        for i=1:r
                for j = 1:c
                        writeFloat(output,matr[i,j])
                        if j != c
                                write(output, " ")
                        end
                end
                write(output,'\n')
        end
end

function writeThetas(outputF,Theta1, Theta2)
        writeMatr(output,Theta1)
        writeMatr(output,Theta2)
end
