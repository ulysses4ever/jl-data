include("Individual.jl")


using PyPlot
pygui(true)

function plotNewAxis(curMatrix)
  cols = {"blue","green","red"}
  Ovecs = Array(Vector{Float64},3)
  Ovecs[1] = [1.0, 0.0, 0.0]
  Ovecs[2] = [0.0, 1.0, 0.0]
  Ovecs[3] = [0.0, 0.0, 1.0]

  for i = 1:3
    AO = curMatrix*Trans(Ovecs[i])
    x = [curMatrix[1,4], AO[1,4]]
    y = [curMatrix[2,4], AO[2,4]]
    z = [curMatrix[3,4], AO[3,4]]
    plot3D(x,y,z, color=cols[i])
  end
end





function plotDHSet(indiv::Individual, set::DHSet)
  area = zeros(10,10)
  cur = indiv.chromosome
  #PyPlot.plt.figure(figsize=PyPlot.plt.figaspect(1)*3)
  surf(area, color="lightgray")

  A = Float64[1 0 0 0
              0 1 0 0
              0 0 1 0
              0 0 0 1]
  plotNewAxis(A)
  A = A*nextLink(set.links[1],0.0)
  plotNewAxis(A)

  skip = false
  x = 1
  println(length(cur))
  for i = 2:length(set.links)
    if skip
      skip = false
      continue
    end
    if cur[x+1].comp_type == 1
      A = A*nextLink(set.links[i], 0.0)
    elseif cur[x+1].change_type != 2
      A = A*nextLink(set.links[i], cur[x].angles[1])
    else
      skip = true
      A = A*nextLink(set.links[i], cur[x].angles[1])
      plotNewAxis(A)
      A = A*nextLink(set.links[i+1], 0.0)
    end
    x+=1
    println(x)
    plotNewAxis(A)
  end
end

function DHOut(indiv::Individual, set::DHSet)
  links = set.links
  @printf("\ta\t\tα\t\t\d\t\tθ\n")
  @printf("%i\t%f\t%f\t\%f\t%f\n", 1, links[1].a, rad2deg(links[1].α), links[1].d, rad2deg(links[1].θ))
  x = 2 #link counter, needs to be inc'd twice only on change_type= 2

  for i = 2:length(indiv.chromosome)
    curGene = indiv.chromosome[i]
    if curGene.change_type == 2
      @printf("%i\t%f\t%f\t\%f\tθ+%f\n", x, links[x].a, rad2deg(links[x].α), links[x].d, rad2deg(links[x].θ))
      x += 1
      @printf("%i\t%f\t%f\t\%f\t%f\n", x, links[x].a, rad2deg(links[x].α), links[x].d, rad2deg(links[x].θ))
      x += 1
    else
      @printf("%i\t%f\t%f\t\%f\tθ+%f\n", x, links[x].a, rad2deg(links[x].α), links[x].d, rad2deg(links[x].θ))
      x += 1
    end
  end
end

geneArr = Array(Gene,4)
geneArr[1] = Gene(2,1,[0.0],0.0,0.0,0)
geneArr[2] = Gene(2,1,[pi/4],0.0,0.0,2)
geneArr[3] = Gene(2,1,[0.0],0.0,0.0,0)
geneArr[4] = Gene(2,1,[0.0],0.0,0.0,0)



indiv_1 = Individual(geneArr)
newSet = getDH(indiv_1)
plotDHSet(indiv_1, newSet)
DHOut(indiv_1,newSet)



