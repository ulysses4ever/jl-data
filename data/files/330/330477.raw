using LightGraphs

function makeGraph(dat::DataFrame)
  peps = levels(dat[:Peptide])
  prots = levels(dat[:Protein])

  nVertices = length(prots) + length(peps)

  stringToVertexMap = Dict{String,Int64}()
  vertexToStringMap = Dict{Int64,String}()

  for i in 1:length(prots)
    stringToVertexMap[prots[i]] = i
    vertexToStringMap[i] = prots[i]
  end
  for i in 1:length(peps)
    stringToVertexMap[peps[i]] = i + length(prots)
    vertexToStringMap[i + length(prots)] = peps[i]
  end

  g = DiGraph(nVertices)

  tmp = unique(dat[:,[:Protein,:Peptide]])
  for i in 1:size(tmp)[1]
    add_edge!(
      g,
      stringToVertexMap[tmp[i,:Protein]],
      stringToVertexMap[tmp[i,:Peptide]]
    )
  end

  g,stringToVertexMap,vertexToStringMap
end

function summariseComponents(dat::DataFrame,g,stringToVertexMap,vertexToStringMap)
  comps = weakly_connected_components(g)
  d = unique(dat[:,[:Protein,:Peptide]])
  peps = convert(Array,levels(d[:Peptide]))
  prots = convert(Array,levels(d[:Protein]))

  compsummary = DataFrame()
  compsummary[:ID] = collect(1:length(comps))
  compsummary[:size] = [length(comps[i]) for i in 1:length(comps)]
  compsummary[:proteins] = [count((p)->(vertexToStringMap[p] in prots),comps[i]) for i in 1:length(comps)]
  compsummary[:peptides] = [count((p)->(vertexToStringMap[p] in peps),comps[i]) for i in 1:length(comps)]

  sort!(compsummary,cols=[:proteins,:peptides], rev = true)

  compgraphs = Array{
                Tuple{
                  LightGraphs.DiGraph,
                  Dict{String,Int64},
                  Dict{Int64,String}
                  }
                }(length(comps))
  for i in 1:length(comps)
    compgraphs[compsummary[i,:ID]] = (DiGraph(length(comps[compsummary[i,:ID]])),Dict{String,Int64}(),Dict{Int64,String}())

    componentProts = filter((s)->(stringToVertexMap[s] in comps[compsummary[i,:ID]]), prots)
    componentPeps = filter((s)->(stringToVertexMap[s] in comps[compsummary[i,:ID]]), peps)
    componentVertices = [componentProts;componentPeps]

    for ind in 1:length(componentVertices)
      compgraphs[compsummary[i,:ID]][2][componentVertices[ind]] = ind
      compgraphs[compsummary[i,:ID]][3][ind] = componentVertices[ind]
    end

    for j in 1:size(d)[1]
      if stringToVertexMap[d[j,:Peptide]] in comps[compsummary[i,:ID]] && stringToVertexMap[d[j,:Protein]] in comps[compsummary[i,:ID]]
        add_edge!(
          compgraphs[compsummary[i,:ID]][1],
          compgraphs[compsummary[i,:ID]][2][d[j,:Protein]],
          compgraphs[compsummary[i,:ID]][2][d[j,:Peptide]]
        )
      end
    end

  end

  #Find graphs with vertices with non-identical neighbour sets
  nProteinsWUniquePeptides = [0 for i in 1:size(compsummary)[1]]
  for i in 1:size(compsummary)[1]
    cg = compgraphs[compsummary[i,:ID]][1]
    for v in vertices(cg)
      if compgraphs[i][3][v] in prots
        u = false
        for n in out_neighbors(cg,v)
          u = length(in_neighbors(cg,n)) == 1
        end
        if u
          nProteinsWUniquePeptides[i] += 1
        end
      end
    end
  end

  nIdentifiableProteins = [0 for i in 1:size(compsummary)[1]]
  for i in 1:size(compsummary)[1]
    proteins = filter(
                 (v)->compgraphs[i][3][v] in prots,
                 vertices(compgraphs[compsummary[i,:ID]][1])
               )

    #print("proteins: ")
    #println(proteins)

    neighboringSets = Array{Array{Int64,1},1}(length(proteins))
    for j in 1:length(proteins)
      neighboringSets[j] = out_neighbors(compgraphs[compsummary[i,:ID]][1],proteins[j])
    end
    #[in_neighbors(compgraphs[compsummary[i,:ID]][1],proteins[j]) for j in 1:length(proteins)]
    #print("neighboringSets: ")
    #println(neighboringSets)

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

    #print("differentSets: ")
    #println(differentSets)

    k=0
    for j in 1:length(proteins)
      k+= (sum(differentSets[j,:]) == length(proteins)-1 ? 1 : 0)
    end

    nIdentifiableProteins[i] = k
  end

  compsummary[:identifiable] = nIdentifiableProteins
  compsummary[:unique] = nProteinsWUniquePeptides
  compsummary[:edges] = [length(edges(compgraphs[compsummary[i,:ID]][1])) for i in 1:size(compsummary)[1]]

  uniquePeptides = DataFrame()
  uniquePeptides[:Protein] = levels(dat[:Protein])
  uniquePeptides[:NumUniquePeptides] = [0 for i in 1:sum(compsummary[:proteins])]

  for cg in 1:length(compgraphs)
    for p in filter((v)->in(compgraphs[cg][3][v],levels(uniquePeptides[:Protein])),vertices(compgraphs[cg][1]))
      #println("p: "*string(p))
      ind = findfirst(uniquePeptides[:Protein],compgraphs[cg][3][p])
      for pep in out_neighbors(compgraphs[cg][1],p)
        if length(in_neighbors(compgraphs[cg][1],pep)) == 1
          uniquePeptides[ind,:NumUniquePeptides] += 1
        end
      end
    end
  end

  comps,compsummary,compgraphs,uniquePeptides

end

function GenerateLocations(nProteins,nPeptides)
  loc_x = [repeat([-1.0],inner=[nProteins]); repeat([1.0],inner=[nPeptides])]
  loc_y = [collect(-1.0:(2.0/(nProteins-1)):1.0); collect(-1.0:(2.0/(nPeptides-1)):1.0)]
  return loc_x,loc_y
end

function plotGraph(g::Union{LightGraphs.Graph,LightGraphs.DiGraph},proteins,peptides,outputfile)
  loc_x,loc_y = GenerateLocations(length(proteins),length(peptides))
  am = transpose(full(adjacency_matrix(g)))
  try mkdir("tmp") end
  GraphLayout.draw_layout_adj(am,loc_x,loc_y,filename="tmp/tmpgraph.svg",labels=[proteins;peptides])
  run(`rsvg-convert -f pdf -o $outputfile tmp/tmpgraph.svg`)
  rm("tmp/tmpgraph.svg")
end
