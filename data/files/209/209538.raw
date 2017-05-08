# Corpus - Julia Rendition

type Word
  spelling::String
  files::Dict{String,Int}()
end

# Iterate through all the files in the corpus and add them to the
# dictionary.
function read_words(directory)
  dict = Dict{String,Word}()

  # collect all files in the directory
  files = corpus_files(directory)

  # read file line by line
  for file in files do
    open(file,"r") do f
      text = ""
      for line in eachline(f)
        words = matchall(/[A-Za-z][A-Za-z']*/, line)
        for word in words do
          w = get(dict, word, Word(word, {}))
          v = get(w.files, file, 0)
          w.files[file] = v + 1
        end
      end
    end
  end

  return dict
end

# Collect all text files from the given directory.
function corpus_files(directory)
  list = String[]
  paths = readdir(directory)
  for path in paths do
    if (isdir(path) do
      vcat(list, corpus_files(path))
    else
      if (endswith(path, '.txt') do
        add(list, path)
      end
    end
  end
  return list
end

#

