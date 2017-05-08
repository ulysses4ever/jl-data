"""
Custom type to store settings associated with the data analysis pipeline:
- source : Filename of unprocessed file
- sink : folder holding data after processing
- n_timepoints : Number of timepoints
"""
type ProjectSpecifications

    n_timepoints::Int
end

# #TODO:0 abstract preparation further. i.e. S vs. P

"""
Custom type to store information about the experiment:
- conditions::Array{AbstractString, 1}
- crossmixes::Array{AbstractString,1}
- experiment_ids::Array{AbstractString,1}
- timepoints::Dict{AbstractString, Float64}
"""
type ExperimentSpecifications

end

"""
Custom type to store information about the experiment:
- conditions::Array{AbstractString, 1}
- crossmixes::Array{AbstractString,1}
- experiment_ids::Array{AbstractString,1}
- timepoints::Dict{AbstractString, Float64}
"""
type ModelSpecifications
  model::AbstractString
  free_parameters::Dict{AbstractString,UnitRange{Int64}}
end

"""
Custom type wrapping around **ProjectSpecifications** and **ExperimentSpecifications**
"""
type PipelineSpecifications
  source::AbstractString
  sink::AbstractString
  headerpattern::AbstractString
  sampletypes::Dict{AbstractString,AbstractString}
  conditions::Array{AbstractString, 1}
  crossmixes::Array{AbstractString,1}
  experiment_ids::Array{AbstractString,1}
  timepoints::Dict{AbstractString, Float64}
  models::Array{ModelSpecifications, 1}
end

"""
Function that reads a yaml-file specified by *pathtofile*
and returns a PipelineSpecifiactions-Object

*useage:* mySpecifications = load_specification_file(pathtofile)
"""
function load_specification_file(pathtofile::AbstractString)
    d = YAML.load(open(pathtofile))
    project = ProjectSpecifications(d["project"]["source"],
                                    d["project"]["sink"],
                                    d["project"]["n_timepoints"])
    experiment = ExperimentSpecifications(d["experiment"]["conditions"],
                                          d["experiment"]["crossmixes"],
                                          d["experiment"]["experiment_ids"],
                                          d["experiment"]["timepoints"])
    return(PipelineSpecifications(project, experiment))
end
