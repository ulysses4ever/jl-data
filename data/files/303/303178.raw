function ssMME(all_M,all_y,all_J,all_Z,all_X,all_W,all_A,all_num)
    λ1 = vRes/vG
    λ2 = vRes/vAlpha
    num_markers = all_num.num_markers

    X  =all_X.X
    M  =all_M.M
    J  =all_J.J
    W  =all_W.W
    X1 =all_X.X1
    Z1 =all_Z.Z1
    W1 =all_W.W1
    y  =all_y.y
    y1 =all_y.y1
    Ai11=all_A.Ai11
    num_nongeno=all_num.num_g1


    ###solve MME
    lhs = [hcat(X'X,    X'W,                     X1'Z1);
           hcat(W'X,    W'W+eye(num_markers)λ2,  W1'Z1);
           hcat(Z1'X1,  Z1'W1,                  Z1'Z1+Ai11*λ1 )]

    rhs = [X'y; W'y; Z1'y1]

    sol =lhs\rhs

    #get EBVs
    mu_g = sol[2]
    alpha_hat=sol[3:(3+num_markers-1)]
    epsi_hat = sol[(3+num_markers):(3+num_markers+num_nongeno-1)]

    aHat = J*mu_g+M*alpha_hat
    aHat[1:num_nongeno,:] += epsi_hat
    return aHat,alpha_hat,sol[1:2],epsi_hat
end



# df = readtable("bv.txt", eltypes =[UTF8String, Float64], separator = ' ',header=false)
# a  = Array(Float64,num_ped)
# for (i,ID) in enumerate(df[:,1])
#      j = ped.idMap[ID].seqID
#      a[j] = df[i,2]
# end
# cor(a,aHat)

# #keep (overall correlation)
# #70 0.854
# #50 0.828
# #30 0.822
# #10 0.819
# #5  0.817
# #2  0.799

# #PBLUP
# num_obs=length(y)
# pX = ones(num_obs)

# lhs = [hcat(pX'pX,    pX'Z );
#        hcat(Z'pX,    Z'Z+Ai*λ1)]
# rhs = [pX'y; Z'y]
# sol =lhs\rhs
# aHat = sol[2:length(sol)]
# cor(a,aHat)
# #PBLUP 0.813

