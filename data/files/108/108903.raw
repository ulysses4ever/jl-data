function initialise(projectfolder)
  global specs = load_specifications(projectfolder)
  for i in specs.include
    include(joinpath(projectfolder, i))
  end
  global streams = load_streams(joinpath(projectfolder, "stream.yml"))
  return(specs, streams)
end
