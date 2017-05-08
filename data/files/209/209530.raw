module Corpus

  include("ngrams.jl")

  function cli(args)
    cmd = args[1]

    if cmd == "ngrams"
      dir = args[2]
      Ngrams.report(dir, 16000, 3)
    else
      println("No such command -- $cmd")
    end
  end

end
