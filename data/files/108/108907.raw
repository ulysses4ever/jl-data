type Param
  name::AbstractString
  lower_bound::Float64
  step::Float64
  upper_bound::Float64
end

type Model
  M::XPP.Model
  free_parameters::Array{Param, 1}
  states::Dict
end

# 
# function load_models(path_to_model_file)
#   for (n, v) in
