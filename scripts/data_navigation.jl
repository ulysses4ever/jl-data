#
# Navigate julia data.
# Shared by basic_counts.jl and dynamic.jl
#

using DataFrames

#
# Functions for connecting a project to its files.
#

#return a list of the files we'd like to look at for this project.
#naive solution: parse files.csv, return all file nums.
function get_file_nums(projects_dir::String)
  df = readtable("$(projects_dir)/files.csv", header = false)
  file_nums = df[5] #column that contains numbers.
  return file_nums
end

#Return a list of all the file numbers
#given a fully qualified project path
function get_file_nums_master(projects_dir::String)
  files = readtable("$(projects_dir)/files.csv", header = false)
  # we can't parse the branches csv, because its columns are uneven, so read line-by-line
  f = open("$(projects_dir)/branches.csv")
  branches = readlines(f)
  #search for master branch in branches
  master = ""
  for branch in branches
    if contains(branch, "\"master\"")
      master = branch
      break
    end
  end
  if master == ""
    error("Could not find master branch for project $(projects_dir)")
  end
  master = split(master, ",") #master now a list of strings
  master = master[4:end] #remove first three cols, which are name, commit id, date
  #connection: branches lists all the indices of the files in files.
  toReturn = [] #will contain file numbers
  for n in master
    index = parse(Int, n)
    file = files[files[:1] .== index, :] #first row is index
    if nrow(file) != 1
      error("More than one file at desired index")
    end
    push!(toReturn, file[:5][1]) #fetch file number
  end
  #(where index is not order, but first col in files)
  return toReturn
end

# return the full path to the file with the given id.
#file id format: 1234, where 1 is folder, then 1234.raw is the file within the folder
function get_file_path(file_id::Int64)
  path = "$(DATA)/files"
  file = file_id % 1000 #final three numbers
  folder = Int((file_id - file)/1000) #header numbers: what folder are we in?
  if folder != 0
    path = "$(path)/$(folder)"
  end
  path = "$(path)/$(file_id).raw"
  return path
end


#
# Functions for zipping and unzipping files.tar.gz files with all the julia code
#

#unzip the zip file in this directory
#intended use: dir is the full path to the files directory
function unzip(dir::String)
  cd(dir)
  run(`tar -x -f files.tar.xz`) #unzip tar containing this file
end

#delete all files that resulted from unzipping in this directory
function clean(dir::String)
  cd(dir)
  run(pipeline(`ls`, `grep .raw`, `xargs rm`)) #clean up unziped files
end

#run some function on each of our "files" folders
function run_on_all_file_folders(func::Function)
  #first, unzip everything in the files folder
  files_dir = "$(DATA)/files"
  func(files_dir)
  folder = 1 #first folder is 1
  while true
    file_dir = "$(DATA)/files/$(folder)"
    if isdir(file_dir)
      func(file_dir)
      folder += 1
    else
      break
    end
  end
end
