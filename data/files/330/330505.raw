function renameSimNames(sim::Mamba.Chains,proteins,peptides,features,nFeatures,conditions,samples)

  logProteinReferenceAbundanceIndices = find(s->contains(s,"logProteinReferenceAbundance"),sim.names)
  if length(logProteinReferenceAbundanceIndices) > 0
    for p in 1:length(proteins)
      sim.names[logProteinReferenceAbundanceIndices[p]] = "logProteinReferenceAbundance."*string(proteins[p])
    end
  end


  logProteinAbundanceIndices = find(s->contains(s,"logProteinAbundance"),sim.names)
  if length(logProteinAbundanceIndices) > 0
    for p in 1:length(proteins)
      for c in 1:length(conditions)
        sim.names[logProteinAbundanceIndices[(p-1)*length(conditions) + c]] = "logProteinAbundance."*string(proteins[p])*"."*string(conditions[c])
      end
    end
  end

  logProteinSampleAbundanceIndices = find(s->contains(s,"logProteinSampleAbundance"),sim.names)
  if length(logProteinSampleAbundanceIndices)>0
    for p in 1:length(proteins)
      for s in 1:length(samples)
        sim.names[logProteinSampleAbundanceIndices[(p-1)*length(samples) + s]] = "logProteinSampleAbundance."*string(proteins[p])*"."*string(samples[s])
      end
    end
  end

  logPeptideSampleAbundanceIndices = find(s->contains(s,"logPeptideSampleAbundance"),sim.names)
  if length(logPeptideSampleAbundanceIndices)>0
    for p in 1:length(peptides)
      for s in 1:length(samples)
        sim.names[logPeptideSampleAbundanceIndices[(p-1)*length(samples) + s]] = "logPeptideSampleAbundance."*string(peptides[p])*"."*string(samples[s])
      end
    end
  end

  logFeatureSampleIntensityIndices = find(s->contains(s,"logFeatureSampleIntensity"),sim.names)
  if length(logFeatureSampleIntensityIndices)>0
    for f in 1:length(features)
      for s in 1:length(samples)
        sim.names[logFeatureSampleIntensityIndices[(f-1)*length(samples) + s]] = "logFeatureSampleIntensity."*string(features[f])*"."*string(samples[s])
      end
    end
  end


#=  logPeptideAbundanceIndices = find(s->contains(s,"logPeptideAbundance"),sim.names)

  for p in 1:length(peptides)
    for c in 1:length(conditions)
      sim.names[logPeptideAbundanceIndices[(p-1)*length(conditions) + c]] = "logPeptideAbundance"*"."*string(peptides[p])*"."*string(conditions[c])
    end
  end
=#

  #=logPeptideIntensityIndices = find(s->contains(s,"logPeptideIntensity"),sim.names)

  for p in 1:length(peptides)
    for c in 1:length(conditions)
      sim.names[logPeptideIntensityIndices[(p-1)*length(conditions) + c]] = "logPeptideIntensity"*"."*string(peptides[p])*"."*string(conditions[c])
    end
  end
=#

  ionisationCoeffIndices = find(s->(contains(s,"ionisationCoeff")&&!(contains(s,"raw"))),sim.names)
  if length(ionisationCoeffIndices) > 0
    c = 1
    for p in 1:length(peptides)
      a = cumsum(nFeatures)[p] - nFeatures[p] + p-1
      sim.names[ionisationCoeffIndices[a+1]] = "ionisationCoeff."*string(p)*"-MISSING"
      for f in 2:nFeatures[p]+1
        sim.names[ionisationCoeffIndices[a+f]] = "ionisationCoeff."*features[c]
        c+=1
      end
    end
  end


  logProteinFoldChangeIndices = find(s->contains(s,"logProteinFoldChange"),sim.names)
  if length(logProteinFoldChangeIndices)>0
    for p in 1:length(proteins)
      for c in 1:length(conditions)-1
        sim.names[logProteinFoldChangeIndices[(p-1)*(length(conditions)-1) + c]] = "logProteinFoldChange"*"."*string(proteins[p])*"."*string(conditions[c+1])*"vs"*string(conditions[1])
      end
    end
  end

  logRelativeProteinAbundanceIndicies = find(s->contains(s,"logRelativeProteinAbundance"),sim.names)
  if length(logRelativeProteinAbundanceIndicies) > 0
    for p in 1:length(proteins)-1
      for c in 1:length(conditions)
        sim.names[logRelativeProteinAbundanceIndicies[(p-1)*length(conditions) + c]] = "logRelativeProteinAbundance"*"."*string(proteins[p+1])*"vs"*string(proteins[1])*"."*string(conditions[c])
      end
    end
  end

  sim
end
