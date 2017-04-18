#
# Count number of lines in a file, number of method definitions
# Static analysis only. Parses per-file, but can collect project-wide statistics.
#
# note that this script relies extensively on the formatting provided by
# ght-pipeline.
#

using DataFrames # for parsing CSV files
include("data_navigation.jl")
include("Static.jl")

#hardcode path to data folder
DATA = "/afs/athena.mit.edu/user/g/l/glnpease/jl-proj/ght-pipeline/data"

#if debug, we only run on the first 10 files.
#note: this does require looking in the nested folders (proj 8)
DEBUG = false

#
# Functions for running analysis on a single project. A project gets a list
# of files to look at, then runs analysis on each project.
#

# returns a dataframe with lines of code. TODO could include many more metrics
function count_project(project_dir::String)
  file_nums = get_file_nums_master(project_dir)
  total_loc = 0
  types = 0
  for num in file_nums
    total_loc += get_loc(num)
    types += Static.process_file(get_file_path(num))[:type]
  end
  return DataFrame(LOC = [total_loc], type_decs = [types])
end

### interface for getters: return one number, which must be a column in the output_df


#for a file number, count its lines of code
#assume that the file container has been unzipped
#return lines in that file
function get_loc(file_id::Int64)
  path = get_file_path(file_id)
  #open file and count lines
  f = open(path)
  a = readlines(f)
  return length(a)
end

#
# The actual script ~~~ run analysis
#


#run_on_all_file_folders(unzip)


#for project folder in projects:
#  open and parse files csv
output_df = DataFrame(LOC = Int64[], type_decs = Int64[], Project = Int64[])
projects_dir = "$(DATA)/projects"
project = 0
while true
  if DEBUG && project > 100 # TODO this is a garbage statement just here b/c working with subset of data
    break
  end
  project_dir = "$(projects_dir)/project_$(project)"
#  if project == 15 || project == 37 || project == 51 #project 15 is empty. idk why.
  if isdir(project_dir) && length(readdir(project_dir)) == 0 #some projects weren't pulled correctly 
    project += 1
    continue
  end
  if isdir(project_dir)
    try 
    project_df = count_project(project_dir)
    project_df[:Project] = [project]
    append!(output_df, project_df) #append this project's data to the entire data
    project += 1
    catch e 
    project += 1
    continue 
    end 
  else #not a project
    break
  end
end

#println(output_df) #TODO write this to an output csv
writetable("$(DATA)/output.csv", output_df)

#run_on_all_file_folders(clean)


#exprs = Static.parse_file("/home/glnpease/julia-usage/workflow-try/1000.raw")
#println(exprs)
