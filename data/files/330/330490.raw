function renameSimNames(sim::Mamba.Chains,proteins,peptides,conditions)

    logProteinReferenceAbundanceIndices = find(s->contains(s,"logProteinReferenceAbundance"),sim.names)

    for p in 1:length(proteins)
      sim.names[logProteinReferenceAbundanceIndices[p]] = "logProteinReferenceAbundance."*string(proteins[p])
    end


    logProteinAbundanceIndices = find(s->contains(s,"logProteinAbundance"),sim.names)

    for p in 1:length(proteins)
      for c in 1:length(conditions)
        sim.names[logProteinAbundanceIndices[(p-1)*length(conditions) + c]] = "logProteinAbundance"*"."*string(proteins[p])*"."*string(conditions[c])
      end
    end

    logPeptideAbundanceIndices = find(s->contains(s,"logPeptideAbundance"),sim.names)

    for p in 1:length(peptides)
      for c in 1:length(conditions)
        sim.names[logPeptideAbundanceIndices[(p-1)*length(conditions) + c]] = "logPeptideAbundance"*"."*string(peptides[p])*"."*string(conditions[c])
      end
    end

    logProteinFoldChangeIndices = find(s->contains(s,"logProteinFoldChange"),sim.names)
    for p in 1:length(proteins)
      for c in 1:length(conditions)-1
        sim.names[logProteinFoldChangeIndices[(p-1)*(length(conditions)-1) + c]] = "logProteinFoldChange"*"."*string(proteins[p])*"."*string(conditions[c+1])*"vs"*string(conditions[1])
      end
    end

    logRelativeProteinAbundanceIndicies = find(s->contains(s,"logRelativeProteinAbundance"),sim.names)
    for p in 1:length(proteins)-1
      for c in 1:length(conditions)
        sim.names[logRelativeProteinAbundanceIndicies[(p-1)*length(conditions) + c]] = "logRelativeProteinAbundance"*"."*string(proteins[p+1])*"vs"*string(proteins[1])*"."*string(conditions[c])
      end
    end

    sim
end
