function CorrVarCreate(data_var::Array{Float64,2}, data_cor::Array{Float64,2})
    NP, tr = size(data_var)
    mat_corr = zeros((tr, tr, NP))
    mat_var = zeros((tr, tr, NP))
    for k in 1:NP
        l = 1
        for i in 1:tr
            mat_corr[i, i, k] =  1.0
            for j in 1:i-1
                mat_corr[i, j, k] = data_cor[k, l]
                mat_corr[j, i, k] = mat_corr[i, j, k]
                l = l+1
            end
        end
    end
    for k in 1:NP
        mat_var[:,:,k] = mat_corr[:,:,k].*(data_var[k,:]'*data_var[k,:])
    end
    mat_var, mat_corr
end

function Random_Skewers(A::Array{Float64, 2}, B::Array{Float64, 2})
    n, p = size(A)
    n_vector = 1000
    betas = rand(n, n_vector)
    deltaZ_A = distribute(A*betas, 2)
    deltaZ_B = distribute(B*betas, 2)
    RS = dzeros(n_vector)
    @parallel for i=1:n_vector
        RS[i] = (deltaZ_A[:,i]'*deltaZ_B[:,i]/
                sqrt((deltaZ_A[:,i]'*deltaZ_A[:,i])*(deltaZ_B[:,i]'*deltaZ_B[:,i])))[1]
    end
    mean(RS)
end

function RS_Series (Mats::Array{Float64, 3}, Target::Array{Float64, 2})
    n, p, NP = size(Mats)
    Sim = dzeros(NP)
    #    DMats = distribute(Mats)
    DMats = Mats
    #    @parallel for i=1:NP
    for i=1:NP
        Sim[i] = Random_Skewers(DMats[:,:,i],Target)
    end
    Sim
end

omega = dlmread("./G-target.csv","\t")
mat_cor = zeros(10, 10, 10000, 20)
mat_var = zeros(10, 10, 10000, 20)
for i in 1:20
    dir =
    "/home/diogro/MainProject/Modularidade/MatrizB/Direcional/IntensidadeSelecao/IntSel$(i*10)/" 
    println(dir)
    cor_aux = (dlmread("$(dir)correlacao.txt"," "))[:,2:end] 
    var_aux = (dlmread("$(dir)varP.txt", " "))[:,2:end]
    mat_var[:,:,:,i], mat_cor[:,:,:,i] = CorrVarCreate(var_aux, cor_aux)
end
Results = [RS_Series(mat_var[:,:,:,i], omega) for i in 1:20]
