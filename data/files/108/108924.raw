type Specifications
  source::AbstractString
  sink::AbstractString
  headerpattern::Regex
  sampletypes::Dict{AbstractString,Regex}
  conditions::Array{AbstractString, 1}
  crossmixes::Array{AbstractString,1}
  experiment_ids::Array{AbstractString,1}
  timepoints::Dict{AbstractString, Float64}
end

function load_specifications(projectfolder)
  S = YAML.load(open(joinpath(projectfolder, "specifications.yml")))
  source = S["source"]
  sink = S["sink"]
  headerpattern = Regex(S["headerpattern"])
  sampletypes = [sample => Regex(pattern) for (sample,pattern) in S["sampletypes"]]
  conditions = S["conditions"]
  crossmixes = S["crossmixes"]
  experiment_ids = S["experiment_ids"]
  timepoints = S["timepoints"]
  specs = Specifications(source, sink, headerpattern, sampletypes, conditions, crossmixes, experiment_ids, timepoints)
  return(specs)
end
