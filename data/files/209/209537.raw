# N-Gram Word Analysis
#
module Ngrams
  export analyze

  import Iterators

  const rxphrase = r"[\w\s'-]+"
  const rxword = r"[A-Za-z][A-Za-z'-]*"

  #
  function analyze(dir, max, n=3)
    stats = parse(dir, n)
    grams = bestngrams(stats, max)
    display(grams)
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

  #
  function parse(directory, n=3)
    stats = Dict{String,Integer}()
    files = corpus_files(directory)
    #total = endof(files)
    for file in files
      text = open(readall, file)
      for phrase in phrases(text)
        for i in 2:n
          for gram in partition(words(phrase), i, 1)
            lgram = map(x->lowercase(x), gram)
            if valid(lgram)
              subgram = join(lgram, " ")
              oldstat = get(stats, subgram, 0)
              push!(stats, subgram, oldstat + 1)
            end
          end
        end
      end
    end
    stats
  end

  #
  function bestngrams(stats, max)
    stats_tupled = collect(stats)
    stats_sorted = reverse(sort(stats_tupled, by=x->x[2]))
    stats_sorted[1:max]
  end

  #
  function display(stats)
    for (ngram, rank) in sort(stats)
      #println("$rank $ngram")
      println(ngram)
    end
  end

  # Returns an iterator over word phrases.
  function phrases(text)
    map(x->x.match, eachmatch(rxphrase, text))
  end

  # Returns an iterator over words.
  function words(text)
    map(x->x.match, eachmatch(rxword, text))
  end

  function valid(gram)
    first(gram) != "the"
  end

end
