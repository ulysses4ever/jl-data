using XPP

type Param
  name::AbstractString
  lower_bound::Float64
  step::Float64
  upper_bound::Float64
end
Param(D::Dict, name::AbstractString) = Param(name, D["lower_bound"], D["step"], D["upper_bound"])

type Model
  M::XPP.Model
  free_parameters::Array{Param, 1}
end

function load_model(pathtomodel)
  S = YAML.load(open(pathtomodel))
  model = XPP.Model(S["model"]["odes"],
                    S["model"]["init"],
                    S["model"]["pars"],
                    aux = S["model"]["aux"],
                    alg = S["model"]["alg"],
                    spec = S["model"]["spec"])
  params = [Param(v, k) for (k,v) in S["free_parameters"]]
  return(Model(model, params))
end
