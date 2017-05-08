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
    deltaZ_A = A*betas
    deltaZ_B = B*betas
    RS = zeros(n_vector)
    for i=1:n_vector
        RS[i] = (deltaZ_A[:,i]'*deltaZ_B[:,i]/
                sqrt((deltaZ_A[:,i]'*deltaZ_A[:,i])'*(deltaZ_B[:,i]'*deltaZ_B[:,i])))[1]
    end
    mean(RS)
end

function RS_Series (Mats::Array{Float64, 3}, Target::Array{Float64, 2})
    n, p, NP = size(Mats)
    Sim = zeros(NP)
    for i=1:NP
        Sim[i] = Random_Skewers(Mats[:,:,i],Target)
    end
    Sim
end

function RS_Sel_Type (File::String) 
    omega = dlmread("/home/diogro/julia-play/G-target.csv","\t")
    mat_cor = zeros(10, 10, 10000, 20)
    mat_var = zeros(10, 10, 10000, 20)
    Results = zeros(10000, 20)
    for i in 1:20
        dir =
        "/home/diogro/MainProject/Modularidade/MatrizB/Direcional/$(File)/IntSel$(i*10)/" 
        println(dir)
        cor_aux = (dlmread("$(dir)correlacao.txt"," "))[:,2:end] 
        var_aux = (dlmread("$(dir)varP.txt", " "))[:,2:end]
        mat_var[:,:,:,i], mat_cor[:,:,:,i] = CorrVarCreate(var_aux, cor_aux)
        Results[:,i] = RS_Series(mat_var[:,:,:,i], omega)
    end
    dlmwrite("RS_Results_$(File)", Results, ' ')
end
RS_Sel_Type("MinForModule")
RS_Sel_Type("Corridor")
