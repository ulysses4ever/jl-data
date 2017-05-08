module Corpus

  # Command line interface
  #
  module Cli
    export run

    #
    function run(args)
      cmd = args[1]

      if cmd == "ngrams"
        dir = args[2]
        ngrams(dir)
      else
        println("No such command -- $cmd")
      end
    end

    # Run ngrams analysis.
    #
    # TODO: options for sizes
    function ngrams(dir)
      Ngrams.analyze(dir, 16000, 3)
    end

    # todo
    function words(dir)
    end

    # todo
    function letters(dir)
    end

  end

end
