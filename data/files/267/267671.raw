function renameSimNames(sim::Mamba.Chains,proteins,peptides,conditions)
    logProteinIntensityIndices = find(s->contains(s,"logProteinIntensity"),sim.names)

    for p in 1:length(proteins)
      for c in 1:length(conditions)
        sim.names[logProteinIntensityIndices[(p-1)*length(conditions) + c]] = "logProteinIntensity"*"."*string(proteins[p])*"."*string(conditions[c])
      end
    end

    logPeptideIntensityIndices = find(s->contains(s,"logPeptideIntensity"),sim.names)

    for p in 1:length(peptides)
      for c in 1:length(conditions)
        sim.names[logPeptideIntensityIndices[(p-1)*length(conditions) + c]] = "logPeptideIntensity"*"."*string(peptides[p])*"."*string(conditions[c])
      end
    end

    logProteinFoldChangeIndices = find(s->contains(s,"logProteinFoldChange"),sim.names)
    for p in 1:length(proteins)
      for c in 1:length(conditions)-1
        sim.names[logProteinFoldChangeIndices[(p-1)*(length(conditions)-1) + c]] = "logProteinFoldChange"*"."*string(proteins[p])*"."*string(conditions[c+1])*"vs"*string(conditions[1])
      end
    end

    logRelativeProteinIntensityIndicies = find(s->contains(s,"logRelativeProteinIntensity"),sim.names)
    for p in 1:length(proteins)-1
      for c in 1:length(conditions)
        sim.names[logRelativeProteinIntensityIndicies[(p-1)*length(conditions) + c]] = "logRelativeProteinIntensity"*"."*string(proteins[p+1])*"vs"*string(proteins[1])*"."*string(conditions[c])
      end
    end

    sim
end
