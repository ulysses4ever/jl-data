using Distributions
using DataFrames
using Docile

type CpGMethEstimate
    alpha::Float64
    beta::Float64
    methcounts::Array{Int64}
    unmethcounts::Array{Int64}
end

function issame(array)
  for i=1:length(array)
     if array[i] != array[1]
       return false
     end
  end
  return true
end

function computeBDI(a1,b1,a2,b2,nSamp=100000,alpha=0.1)
    #monte carlo approximation
    beta1 = Beta(a1,b1)
    beta2 = Beta(a2,b2)
    theta1 = rand(beta1,nSamp)
    theta2 = rand(beta2,nSamp)
    di=theta1-theta2
    qs=quantile(di,[alpha/2,1-alpha/2])
    s1=min( mean(theta1 .>=theta2), mean(theta1 .<=theta2))
    mu=mean(di)
    v=std(di)
    qs= [ s1, qs, mu, v ]
    return(qs)
end

function getBDI(alpha1,beta1,navg1,alpha2,beta2,navg2,alpha=0.1)
  na_found = all( x-> typeof(x) == nothing, [alpha1,beta1,navg1,alpha2,beta2,navg2])
  if na_found
      return( [nan, nan, nan, nan, nan] )
  else
      a1=(alpha1+1)/(alpha1-1)-1
      b1=(beta1+1)/(beta1-1)-1
      if (navg1 < 30) & (navg2 < 30)
          x1=alpha1+1
          x2=navg1+1
          # monte carlo approximation
          return  computeBDI(alpha1,beta1,alpha2,beta2 )
      else
           #use standard normal to approximate BDI for n>=30
           norm=Normal()
           mu=alpha1/(alpha1+beta1) - alpha2 / (alpha2+beta2)
           sigma= alpha1*beta1 / ( (alpha1+beta1)^2 * (alpha1+beta1+1) )
           sigma=sqrt( sigma+alpha2*beta2 / ( (alpha2+beta2)^2 * (alpha2+beta2 +1) ) )
           np=quantile(norm, (1 - alpha/2) )
           p=min( cdf(norm, mu/sigma ) ,  1- cdf( norm, mu/sigma )  ) #as.numeric(mu/sigma>=np*(1-alpha/2))-as.numeric(mu/sigma<=(-1*(np*(1-alpha/2))))
           return [p, mu-(np*sigma), mu+np*sigma, mu, sigma]
      end
  end
end

function getDCpGStatistic(cpg_meth_est1,cpg_meth_est2, sample_names)
    num_cpgs = length(cpg_meth_est1)
    differences = Any[]
    for i=1:num_cpgs
        meth_level1 = cpg_meth_est1[i].alpha /  ( cpg_meth_est1[i].alpha + cpg_meth_est1[i].beta )
        meth_level2 = cpg_meth_est2[i].alpha /  ( cpg_meth_est2[i].alpha + cpg_meth_est2[i].beta )
        ave_cov1 = ( sum( cpg_meth_est1[i].methcounts) + sum( cpg_meth_est1[i].unmethcounts) ) /2
        ave_cov2 = ( sum( cpg_meth_est2[i].methcounts) + sum( cpg_meth_est2[i].unmethcounts) ) /2
        if meth_level1 <= meth_level2
           push!(differences, getBDI(cpg_meth_est1[i].alpha,cpg_meth_est1[i].beta,ave_cov1,
                                     cpg_meth_est2[i].alpha,cpg_meth_est2[i].beta,ave_cov2))
        else
           push!(differences, getBDI(cpg_meth_est2[i].alpha,cpg_meth_est2[i].beta,ave_cov2,
                                     cpg_meth_est1[i].alpha,cpg_meth_est1[i].beta,ave_cov1) )
        end
    end
    outdf = DataFrame(
           significance            =Float64[],
           estimatedDifference1    =Float64[],
           estimatedDifference2    =Float64[],
           estimatedDifferenceMean =Float64[],
           estimatedVariance       =Float64[]
    )
    for row in differences
        push!(outdf, row)
    end
    return outdf
end


#expects vector size n=4, meth1,total1,meth2,total2
function get_beta_parametersPort(dat)
    p=[dat[1]/dat[2],dat[3]/dat[4]]
    if(p[1] == p[2])  #case one, use uninformative prior
        (max,i)=findmax(dat[ [2,4] ])
        m=dat[[1,3]][i]
        n=dat[[2,4]][i]
        return [m+1,n-m+1]
    else
        mu=(dat[1]+dat[3])/(dat[2]+dat[4])
        #weighted variance
        w=[dat[2]/(dat[2]+dat[4]),dat[4]/(dat[2]+dat[4])]#basic weights
        s2=sum(w[1]*(dat[1]/dat[2]-mu)^2+w[2]*(dat[3]/dat[4]-mu)^2)
        nm=(dat[2]+dat[4])/2#mean sample coverage
        #estimate systematic variance between replicates
        V=(s2-1/nm*(mu*(1-mu)))/(1-1/nm)
        #M=(mu*(1-mu)-s2)/(s2-1/nm*(mu*(1-mu)))
        th=(1/maximum(dat[[2,4]]))^2
    end

    println("V = $V s2 = $s2")

    if (V<th)
        M=0
    else #get M parameter
        M=mu*(1-mu)/V -1
    end
    params=[ mu*M, M*(1-mu)]
    #special treatment for overdispersion case a,b negative
    if ( (params[1] <=0 ) | (params[2] <= 0 )  )
        (max,i)=findmax(dat[ [2,4] ] )
        return [ dat[ [1,3]  ][i]+1, dat[  [2,4] ][i]-dat[  [1,3] ][i]+1 ]
    else
        return(params)
    end
end

"""
 Estimate Alpha and Beta parameters of Beta Distribution given replicates

 ### Arguments:
     * `methcounts`:  Array  of replicate counts corresponding to methylated reads at CpG/Cytosine Position
     * `totalcounts`: Array  of replicate counts corresponding to total coverage at CpG/Cytosine Position

 ### Returns
    * Floating Point Array [alpha,beta]

"""

function get_beta_parameters(methcounts,totalcounts)
    num_reps = length(methcounts)

    # if num_reps == 1
    # then return...

    p=fill(0.0,num_reps)
    for r=1:num_reps
        p[r] = methcounts[r] / totalcounts[r]
    end

    if issame(p)
    # case one - use uninformative prior
         # where the probability estimates are
         # the same for each replicate
        (max_cov,max_cov_idx)=findmax(totalcounts)
         m = methcounts[max_cov_idx]
         n = totalcounts[max_cov_idx]
         return [m+1,n+1]
    else
    # case two
         μ = sum(methcounts) / sum(totalcounts)

         # weighted variance
         s2 = 0.0
         for r=1:num_reps
             w  = totalcounts[r] / sum(totalcounts) #basic weights
             s2 += (  w * (p[r] - μ)^2  )
         end
         # mean sample coverage
         nm= sum(totalcounts) / num_reps
         # estimate systematic variance between replicates
         V=( s2 - 1/nm * ( μ * (1 - μ )  ) ) /  ( 1 - 1/nm )
         θ = ( 1 / maximum( totalcounts  ) )^2
    end

    println("V = $V s2 = $s2")

    if(V < θ )
      M = 0
    else
      M = μ * (1-μ)/V -1
    end

    alpha = μ * M
    beta  = M*(1-μ )

    if ( (alpha <= 0) | (beta <= 0 ) )
        (max_cov,max_cov_idx)=findmax( totalcounts )
        return [ methcounts[max_cov_idx]+1, totalcounts[max_cov_idx] - methcounts[max_cov_idx] + 1 ]
    else
        return( [alpha,beta]  )
    end
end

# this differs only in the way we calculate M, which follows the formula in the
# paper - I have not done the algebra so this is just to show that we get equivalent
# values
function get_beta_parameters3(methcounts,totalcounts)
    num_reps = length(methcounts)
    s2 = 0.0
    # if num_reps == 1
    # then return...

    p=fill(0.0,num_reps)
    for r=1:num_reps
        p[r] = methcounts[r] / totalcounts[r]
    end


    if isequal(p,p)
    # case one - use uninformative prior
         # where the probability estimates are
         # the same for each replicate
        (max_cov,max_cov_idx)=findmax(totalcounts)
         m = methcounts[max_cov_idx]
         n = totalcounts[max_cov_idx]
         return [m+1,n+1]
    else
    # case two
         μ = sum(methcounts) / sum(totalcounts)

         # weighted variance
         # in the text we have this expressed as:
         #    sum( n_ij ) * (e_ij - mu_i)^2 / sum n_ij
         # which could be expressed
         #     w * (e_ij - mu_i)^2
         #   where w = n_ij / sum(n_ij)
         # So we can first just calculate the "weights"

        for r=1:num_reps
             w  = totalcounts[r] / sum(totalcounts) #basic weights
             s2  += (  w * (p[r] - μ)^2  )
         end

         # mean sample coverage
         nm= sum(totalcounts) / num_reps
         # estimate systematic variance between replicates
         V=( s2 - 1/nm * ( μ * (1 - μ )  ) ) /  ( 1 - 1/nm )
         θ = ( 1 / maximum( totalcounts  ) )^2
    end

    if(V < θ )
      M = 0
    else
      #M = μ * (1-μ)/V
      M = ( μ*(1-μ) - s^2 ) / ( s^2 - 1/nm * (μ)(1-μ) )
    end

    alpha = μ * M
    beta  = M*(1-μ )
    if ( alpha <= 0 | beta <= 0  )
        max_cov_idx=findmax( totalcounts )
        return [ methcounts[max_cov_idx]+1, totalcounts[max_cov_idx] - methcounts[max_cov_idx] + 1 ]
    else
        return( [alpha,beta]  )
    end
end
