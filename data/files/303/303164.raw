type Results
  mean_beta #fixed effects
  mean_alpha #marker effects
  mean_epsi #epsilon effects
end

function get_column(X,j)
  nrow,ncol = size(X)
  if j>ncol||j<0
      error("column number is wrong!")
  end
  indx = 1 + (j-1)*nrow
  ptr = pointer(X,indx)
  pointer_to_array(ptr,nrow)
end

function sample_fixed_effects!(X,xpx,yCorr,α,meanAlpha,vRes,iIter)
    nObs,nEffects = size(X)
    for j=1:nEffects
        x = get_column(X,j)
        rhs = dot(x,yCorr) + xpx[j]*α[j,1]
        lhs      = xpx[j]
        invLhs   = 1.0/lhs
        mean     = invLhs*rhs
        oldAlpha = α[j,1]
        α[j]     = mean + randn(1)[1]*sqrt(invLhs*vRes)
        BLAS.axpy!(oldAlpha-α[j,1],x,yCorr)
        meanAlpha[j] += (α[j] - meanAlpha[j])*iIter
    end
end

function sample_effects_ycorr!(X,xpx,yCorr,α,meanAlpha,vRes,vEff,iIter)
    nObs,nEffects = size(X)
    λ    = vRes/vEff
    for j=1:nEffects
        x = get_column(X,j)
        rhs = dot(x,yCorr) + xpx[j]*α[j,1]
        lhs      = xpx[j] + λ
        invLhs   = 1.0/lhs
        mean     = invLhs*rhs
        oldAlpha = α[j,1]
        α[j]     = mean + randn(1)[1]*sqrt(invLhs*vRes)
        BLAS.axpy!(oldAlpha-α[j,1],x,yCorr)
        meanAlpha[j] += (α[j] - meanAlpha[j])*iIter
    end
end

function sample_effects_rhs!(lhs,rhs,b,vRes,bMean,iIter) #use this general function for sample epsilon(Gianola Book)
    n = size(lhs,1)                                      #argument lhs here is a sparse matrix for whole lhs
    for (i in 1:n)
        b[i] = 0.0
        rhsi = rhs[i] - lhs[i,:]*b
        lhsi = lhs[i,i]
        invLhs = 1.0/lhsi
        meani  = invLhs*rhsi[1]
        b[i] = meani + randn(1)[1]*sqrt(invLhs*vRes)
        bMean[i] += (b[i] - bMean[i])*iIter
    end
end

function sample_effects_rhsCol!(lhs,rhs,b,vRes,bMean,iIter) #use this general function for sample epsilon(Gianola Book)
    n = size(lhs,1)                                         #arguments lhs here is a array of cols of lhs
    for (i in 1:n)
        b[i] = 0.0
        rhsi = rhs[i] - lhs[i]'b
        lhsi = lhs[i][i]
        invLhs = 1.0/lhsi
        meani  = invLhs*rhsi[1]
        b[i] = meani + randn(1)[1]*sqrt(invLhs*vRes)
        bMean[i] += (b[i] - bMean[i])*iIter
    end
end

function sampleEpsi!(all_Z,Ai11,zpz,vRes,vG,yCorr,ϵ,meanEpsi,iIter)#use [Z1 ; 0] here to make it general but maybe slow
    λ = vRes/vG
    Z_1 = all_Z.Z_1

    yCorr[:] = yCorr[:] + Z_1*ϵ #add back {Z1'Z1}_{i,i} *ϵ, n3 nonzeros #here Z1 is Z11
    rhs = Z_1'yCorr #
    lhs = Z_1'Z_1+Ai11*λ
    lhsCol=[lhs[:,i] for i=1:size(lhs,1)]

    sample_effects_rhsVec!(lhsCol,rhs,ϵ,vRes,meanEpsi,iIter) #use this general function for sample epsilon(Gianola Book)

    yCorr[:] = yCorr[:] - Z_1*ϵ
    return yCorr
end

function ssGibbs(all_M,all_y,all_J,all_Z,all_X,all_W,all_A,all_num,vRes,vG,nIter;outFreq=5000)
    
    vAlpha = vG/all_num.num_markers
    
    y = all_y.y
    X = all_X.X
    W = all_W.W
    Z11 = all_Z.Z1
    Ai11 = all_A.Ai11
    mu   = mean(y)
    yCorr= y - mu

    β    = [mu, 0.0]
    α  = zeros(Float64,all_num.num_markers)
    ϵ  = zeros(Float64,all_num.num_g1)

    meanBeta  = [0.0, 0.0]
    meanAlpha = zeros(Float64,all_num.num_markers)
    meanEpsi  = zeros(Float64,all_num.num_g1)

    
    xpx = [dot(X[:,i],X[:,i]) for i=1:size(X,2)]
    wpw = [dot(W[:,i],W[:,i]) for i=1:all_num.num_markers]
    #zpz = [(Z11[:,i]'Z11[:,i])[1,1] for i=1:all_num.num_g1]
    zpz = diag(Z11'Z11)

    for iter = 1:nIter

      iIter = 1.0/iter
      # sample fixed effects
      sample_fixed_effects!(X,xpx,yCorr,β,meanBeta,vRes,iIter)
      # sample marker effects
      sample_effects_ycorr!(W,wpw,yCorr,α,meanAlpha,vRes,vAlpha,iIter)
      # sample epsilon
      sampleEpsi!(all_Z,Ai11,zpz,vRes,vG,yCorr,ϵ,meanEpsi,iIter)

      if (iter%outFreq ==0)
          println("This is iteration ",iter)
      end
    end

    mu_g = meanBeta[2]

    alpha_hat = meanAlpha
    epsi_hat  = meanEpsi
    aHat = all_J.J*mu_g+all_M.M*alpha_hat
    aHat[1:all_num.num_g1,:] += epsi_hat
    return aHat,meanAlpha,meanBeta,meanEpsi
end
