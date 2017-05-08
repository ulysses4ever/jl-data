using DataFrames, Distributions, APhill

function GenerateSimulatedData(
  nProteins,#::Integer,
  nPeptides,#::Integer,
  nFeatures::Array{Int64,1},
  ionisationCoeff::Array{Float64,1},
  protToPepMatrix,#::Array{Integer,2}(nPeptides,nProteins),
  nConditions,#::Integer,
  nSamples,#::Integer,
  proteinAbundance,#::Array{Real,2}(nProteins,nConditions)
)

  sampleSD = 0.1

  N = sum(nFeatures) * nSamples * nConditions

  prots = [intToHexavigesimal(i) for i in 1:nProteins]
  peps = [string(i) for i in 1:nPeptides]

  feats = Array{String,1}(sum(nFeatures))
  k=1
  for p in 1:nPeptides
    for f in 1:nFeatures[p]
      feats[k] = peps[p]*"-F"*string(f)
      k+=1
    end
  end

  conds = ["Ctl"]
  if nConditions > 1
    for i in 1:nConditions-1
      push!(conds,"Trt"*string(i))
    end
  end

  samps = [string(i) for i in 1:nSamples]
  samples = [conds[Integer(ceil(i/nSamples))]*"."*samps[(i-1)%nSamples+1] for i in 1:nConditions*nSamples]

  proteinSampleAbundance = Array{Real,3}(nProteins,nConditions,nSamples)

  for p in 1:nProteins
    for c in 1:nConditions
      #proteinSampleAbundance[p,(c-1)*nSamples+1:c*nSamples] = rand(LogNormal(log(proteinAbundance[p,c]),sampleSD),nSamples)
      proteinSampleAbundance[p,c,1:nSamples] = rand(LogNormal(log(proteinAbundance[p,c]),sampleSD),nSamples)
    end
  end

  proteinData = DataFrame()
  proteinData[:Protein] = repeat(prots,inner=[nSamples*nConditions],outer=[1])
  proteinData[:Condition] = repeat(conds,inner=[nSamples],outer=[nProteins])
  proteinData[:Sample] = repeat(samples, inner=[1],outer=[nProteins])

  proteinIntensities = Array{Float64,1}(size(proteinData)[1])
  for i in 1:size(proteinData)[1]
    p = findfirst(prots,proteinData[i,:Protein])
    c = findfirst(conds,proteinData[i,:Condition])
    s = parse(split(proteinData[i,:Sample],".")[2])
    proteinIntensities[i] = proteinSampleAbundance[p,c,s]
  end
  proteinData[:Intensity] = proteinIntensities


  peptideSampleAbundance = Array{Real,3}(nPeptides,nConditions,nSamples)
  for c in 1:nConditions
    for s in 1:nSamples
      peptideSampleAbundance[:,c,s] = protToPepMatrix * proteinSampleAbundance[:,c,s]
    end
  end


  peptideData = DataFrame()
  peptideData[:Peptide] = repeat(peps,inner=[nSamples*nConditions],outer=[1])
  peptideData[:Condition] = repeat(conds,inner=[nSamples],outer=[nPeptides])
  peptideData[:Sample] = repeat(samples, inner=[1],outer=[nPeptides])

  peptideIntensities = Array{Float64,1}(size(peptideData)[1])
  for i in 1:size(peptideData)[1]
    p = findfirst(peps,peptideData[i,:Peptide])
    c = findfirst(conds,peptideData[i,:Condition])
    s = parse(split(peptideData[i,:Sample],".")[2])
    peptideIntensities[i] = peptideSampleAbundance[p,c,s]
  end
  peptideData[:Intensity] = peptideIntensities



  ionisationMatrix = zeros(sum(nFeatures),nPeptides)

  k=1
  for p in 1:nPeptides
    for f in 1:nFeatures[p]
      ionisationMatrix[k,p] = ionisationCoeff[k]
      k += 1
    end
  end

  featureSampleIntensity = Array{Real,3}(sum(nFeatures),nConditions,nSamples)
  for c in 1:nConditions
    for s in 1:nSamples
      featureSampleIntensity[:,c,s] = ionisationMatrix * peptideSampleAbundance[:,c,s]
    end
  end

  featureData = DataFrame()
  featureData[:Feature] = repeat(feats,inner=[nSamples*nConditions],outer=[1])
  featureData[:Condition] = repeat(conds,inner=[nSamples],outer=[sum(nFeatures)])
  featureData[:Sample] = repeat(samples, inner=[1],outer=[sum(nFeatures)])

  tmpPeptides = Array{String,1}(size(featureData)[1])
  for i in 1:length(tmpPeptides)
    tmpPeptides[i] = split(featureData[i,:Feature],"-")[1]
  end

  featureData[:Peptide] = tmpPeptides

  featureIntensities = Array{Float64,1}(size(featureData)[1])
  for i in 1:size(featureData)[1]
    f = findfirst(feats,featureData[i,:Feature])
    c = findfirst(conds,featureData[i,:Condition])
    s = parse(split(featureData[i,:Sample],".")[2])
    featureIntensities[i] = featureSampleIntensity[f,c,s]
  end
  featureData[:Intensity] = featureIntensities


  intensity = Array{Int64,1}(N)

  dat = DataFrame()
  dat[:Feature] = repeat(feats,inner=[nSamples*nConditions],outer=[1])
  dat[:Condition] = repeat(conds,inner=[nSamples],outer=[sum(nFeatures)])
  dat[:Sample] = repeat(samples,inner=[1],outer=[sum(nFeatures)])
  #data[:Digestion] = repeat(samples,inner=[1],outer=[nPeptides])
  dat[:Population] = repeat(["ALL"],inner=[1],outer=[N])

  dat[:Peptide] = [split(dat[i,:Feature],"-")[1] for i in 1:size(dat)[1]]

  for i in 1:N
    f = findfirst(feats,dat[i,:Feature])
    c = findfirst(conds,dat[i,:Condition])
    s = parse(split(dat[i,:Sample],".")[2])

    intensity[i] = rand(Poisson(featureSampleIntensity[f,c,s]))
  end

  dat[:Count] = intensity

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

  dat = join(dat,tmp,on=[:Peptide])

  dat,prots,peps,feats,conds
end
