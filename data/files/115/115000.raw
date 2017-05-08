module CorpusTools


    import Greps: grep_count, grep_context, Files, load_files, to_file
    import Fisher: right_tail_p, left_tail_p, two_tail_p
    import PortStemmer: stem
    import Collocations: collocations
    import SimpleTokenizer: detag, tokenize
    import Stats: fisher

    export
        grep_count,
        grep_context,
        right_tail_p,
        left_tail_p,
        two_tail_p,
        stem,
        collocations,
        Files,
        detag,
        tokenize,
        load_files,
        to_file,
        fisher

    include("Greps.jl")
    include("Fisher.jl")
    include("SimpleTokenizer.jl")
    include("Collocations.jl")
    include("PortStemmer.jl")
    include("Stats.jl")

end
