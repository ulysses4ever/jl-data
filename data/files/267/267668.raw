using Graphs

function makeGraph(dat::DataFrame)
  v = Array{String,1}()
  peps = levels(dat[:Peptide])
  prots = levels(dat[:Protein])
  for i in 1:length(peps)
    push!(v,peps[i])
  end
  for i in 1:length(prots)
    push!(v,prots[i])
  end

  g = graph(v,[],is_directed=false)

  tmp = unique(dat[:,[:Protein,:Peptide]])
  for i in 1:size(tmp)[1]
    add_edge!(g,tmp[i,:Protein],tmp[i,:Peptide])
  end

  g
end

function summariseComponents(dat::DataFrame,g)
  comps = connected_components(g)
  d = unique(dat[:,[:Protein,:Peptide]])
  peps = levels(d[:Peptide])
  prots = levels(d[:Protein])

  compsummary = DataFrame()
  compsummary[:ID] = collect(1:length(comps))
  compsummary[:size] = [length(comps[i]) for i in 1:length(comps)]
  compsummary[:proteins] = [count((p)->(p in prots),comps[i]) for i in 1:length(comps)]
  compsummary[:peptides] = [count((p)->(p in peps),comps[i]) for i in 1:length(comps)]

  sort!(compsummary,cols=[:proteins,:peptides], rev = true)

  compgraphs = Array{Graphs.GenericGraph}(length(comps))
  for i in 1:length(comps)
    compgraphs[i] = graph(comps[i],[],is_directed=true)
    for j in 1:size(d)[1]
      if d[j,:Peptide] in comps[i] && d[j,:Protein] in comps[i]
        add_edge!(compgraphs[i],d[j,:Peptide],d[j,:Protein])
      end
    end
  end

  #Find graphs with vertices with non-identical neighbour sets
  nProteinsWUniquePeptides = [0 for i in 1:size(compsummary)[1]]
  for i in 1:size(compsummary)[1]
    cg = compgraphs[compsummary[i,:ID]]
    for v in vertices(cg)
      if v in prots
        u = false
        for n in in_neighbors(v,cg)
          u = length(out_neighbors(n,cg)) == 1
        end
        if u
          nProteinsWUniquePeptides[i] += 1
        end
      end
    end
  end


  nIdentifiableProteins = [0 for i in 1:size(compsummary)[1]]
  for i in 1:size(compsummary)[1]
    proteins = filter((v)->v in prots,vertices(compgraphs[compsummary[i,:ID]]))
    neighboringSets = [in_neighbors(proteins[j],compgraphs[compsummary[i,:ID]]) for j in 1:length(proteins)]
    differentSets = Array{Int64,2}(length(proteins),length(proteins))
    for j in 1:length(proteins)
      differentSets[j,j] = 0
    end

    for j in 1:length(proteins)-1
      for k in j+1:length(proteins)
        differentSets[j,k] = (length(setdiff(neighboringSets[j],neighboringSets[k]))==0
                              && length(setdiff(neighboringSets[k],neighboringSets[j]))==0
                              ? 0 : 1)
        differentSets[k,j] = differentSets[j,k]
      end
    end

    k=0
    for j in 1:length(proteins)
      k+= (sum(differentSets[j,:]) == length(proteins)-1 ? 1 : 0)
    end

    nIdentifiableProteins[i] = k
  end

  compsummary[:identifiable] = nIdentifiableProteins
  compsummary[:unique] = nProteinsWUniquePeptides
  compsummary[:edges] = [num_edges(compgraphs[compsummary[i,:ID]]) for i in 1:size(compsummary)[1]]

  uniquePeptides = DataFrame()
  uniquePeptides[:Protein] = levels(dat[:Protein])
  uniquePeptides[:NumUniquePeptides] = [0 for i in 1:sum(compsummary[:proteins])]

  for cg in 1:length(compgraphs)
    for p in filter((v)->in(v,levels(uniquePeptides[:Protein])),vertices(compgraphs[cg]))
      ind = findfirst(uniquePeptides[:Protein],p)
      for pep in in_neighbors(p,compgraphs[cg])
        if length(out_neighbors(pep,compgraphs[cg])) == 1
          uniquePeptides[ind,:NumUniquePeptides] += 1
        end
      end
    end
  end

  comps,compsummary,compgraphs,uniquePeptides

end
