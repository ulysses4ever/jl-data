Rot_x(α::Float64) = Float64[1 0 0 0
                            0 cos(α) -sin(α) 0
                            0 sin(α) cos(α) 0
                            0 0 0 1]

Rot_y(γ::Float64) = Float64[cos(γ) 0 sin(γ) 0
                            0 1 0 0
                            -sin(γ) 0 cos(γ) 0
                            0 0 0 1]

Rot_z(θ::Float64) = Float64[cos(θ) -sin(θ) 0 0
                            sin(θ) cos(θ) 0 0
                            0 0 1 0
                            0 0 0 1]

Trans(v::Vector{Float64}) = Float64[1 0 0 v[1]
                                    0 1 0 v[2]
                                    0 0 1 v[3]
                                    0 0 0 1]

type DHLink
  a::Float64
  α::Float64
  d::Float64
  θ::Float64
  A::Matrix{Float64}
  function DHLink(a, α, d, θ)
    this = new()
    this.a = a
    this.α = α
    this.d = d
    this.θ = θ
    this.A = Rot_z(this.θ) * Trans([this.a,0,this.d]) * Rot_x(this.α)
    return this
  end
end

type DHSet
  links::Array{DHLink,1}
  function DHSet()
    this = new()
    this.links = Array(DHLink,0)
    return this
  end
end

function nextLink(link::DHLink, θ::Float64)
  return Rot_z(θ) * link.A
end

function DHOut(set::DHSet)
  @printf("\ta\t\tα\t\t\d\t\tθ\n")
  links = set.links
  for i = 1:length(links)
    @printf("%i\t%f\t%f\t\%f\t%f\n", i, links[i].a, rad2deg(links[i].α), links[i].d, rad2deg(links[i].θ))
  end
end

function plotDHSet(set::DHSet)
  area = zeros(10,10)
  #PyPlot.plt.figure(figsize=PyPlot.plt.figaspect(1)*3)
  surf(area, color="lightgray")

  A = Float64[1 0 0 0
              0 1 0 0
              0 0 1 0
              0 0 0 1]
  plotNewAxis(A)
  for i = 1:length(set.links)
    A = A*nextLink(set.links[i],0.0)
    plotNewAxis(A)
  end
end
