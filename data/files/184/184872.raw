import JulTest: runtests

function collect()
  test_dir = "test/"
  test_dir_exists::Bool = isdir(test_dir)

  filenames::Array{String} = readdir(test_dir)
  map(x -> include("$test_dir/$x"), filenames)
end

collect()
runtests()
