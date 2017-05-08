module Fasta
    type Seq
        id::String
        sequence::String
    end

    function parse(fasta::String)
        sa = split(fasta,'>',false)
        seqs = Seq[]
        for s in sa
            data = split(s,'\n')
            push!( seqs , Seq( data[1], join(data[2:end], "") ) )
        end
        seqs
    end
end
