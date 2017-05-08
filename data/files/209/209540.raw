require Iterators

module Corpus

  # Words analysis
  #
  # TODO: finish
  #
  module Words
    export analyze

    type Word
      spelling::String
      files::Dict{String,Int}()
    end

    const rxword = r"[A-Za-z][A-Za-z'-]*"

    #
    function analyze(dir, max, n=3)
      stats = parse(dir, n)
      grams = bestngrams(stats, max)
      display(grams)
    end

    #
    function parse(directory)
      stats = Dict{String,Word}()
      files = corpus_files(directory)
      #total = endof(files)
      for file in files
        text = open(readall, file)
        for phrase in phrases(text)
            for word in words(phrase)
              lgram = map(x->lowercase(x), word)
              if valid(word)
                w = get(stats, word, Word(word, {}))
                v = get(w.files, file, 0)
                w.files[file] = v + 1
              end
            end
          end
        end
      end
      stats
    end

    # Collect all text files from the given directory.
    function corpus_files(directory)
      list = String[]
      paths = readdir(directory)
      for path in paths
        fullpath = joinpath(directory, path)
        if isdir(fullpath) 
          list = vcat(list, corpus_files(fullpath))
        else
          if endswith(path, ".txt")
            push!(list, fullpath)
          end
        end
      end
      list
    end

    # Returns an iterator over words.
    function words(text)
      map(x->x.match, eachmatch(rxword, text))
    end

    #
    function valid(word)
      true # todo
    end

  end

end
