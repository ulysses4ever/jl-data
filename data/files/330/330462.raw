#generate simulated data
using DataFrames, Distributions

function GenerateSimulatedData(
  nProteins,#::Integer,
  nPeptides,#::Integer,
  protToPepMatrix,#::Array{Integer,2}(nPeptides,nProteins),
  nConditions,#::Integer,
  nSamples,#::Integer,
  proteinIntensity,#::Array{Real,2}(nProteins,nConditions)
)

  sigmaRes = 0.1

  N = nPeptides * nSamples * nConditions

  prots = [intToHexavigesimal(i) for i in 1:nProteins]
  peps = [string(i) for i in 1:nPeptides]
  #conds = [intToHexavigesimal(i) for i in 1:nConditions]

  conds = ["Ctl"]
  if nConditions > 1
    for i in 1:nConditions-1
      push!(conds,"Trt"*string(i))
    end
  end

  samps = [string(i) for i in 1:nSamples]
  samples = [conds[Integer(ceil(i/nSamples))]*"."*samps[(i+2)%nSamples+1] for i in 1:nConditions*nSamples]

  peptideIntensity = Array{Float64,2}(nPeptides,nConditions)
  for j in 1:nConditions
    peptideIntensity[:,j] = protToPepMatrix * proteinIntensity[:,j]
  end

  logI = Array{Float64,1}(N)

  data = DataFrame()
  data[:Peptide] = repeat(peps,inner=[nSamples*nConditions],outer=[1])
  data[:Condition] = repeat(conds,inner=[nSamples],outer=[nPeptides])
  data[:Sample] = repeat(samples,inner=[1],outer=[nPeptides])
  data[:Digestion] = repeat(samples,inner=[1],outer=[nPeptides])
  data[:Population] = repeat(["ALL"],inner=[1],outer=[N])

  for i in 1:N
    c = findfirst((k)->contains(data[i,:Condition],k),levels(data[:Condition]))
    b = log(peptideIntensity[findfirst((k)->(k == data[i,:Peptide]),levels(data[:Peptide])),c])# + epsilonDigest[i] + epsilonSample[findfirst((k)->(k == data[i,:Sample]),levels(data[:Sample]))]
  #logI[i] = b + sigmaRes*rand(TDist(3))
	  logI[i] = b + sigmaRes*rand(Normal(0,1))
  end

  data[:LogIntensity] = logI

  tmp = DataFrame()

  proteins = Array{String,1}(Integer(sum(protToPepMatrix)))
  peptides = Array{String,1}(Integer(sum(protToPepMatrix)))

  tmpInd = 1
  for i in 1:nPeptides
    for j in 1:nProteins
      if protToPepMatrix[i,j] > 0
        proteins[tmpInd] = prots[j]
        peptides[tmpInd] = peps[i]
        tmpInd += 1
      end
    end
  end

  tmp[:Protein] = proteins
  tmp[:Peptide] = peptides

  data = join(data,tmp,on=[:Peptide])

  return data, prots, peps

end
