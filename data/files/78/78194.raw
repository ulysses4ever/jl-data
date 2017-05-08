#==============================================================================
Problem
Figure 2. Palindromic recognition site

A DNA string is a reverse palindrome if it is equal to its reverse complement. 
For instance, GCATGC is a reverse palindrome because its reverse complement is 
GCATGC. See Figure 2.

Given: A DNA string of length at most 1 kbp in FASTA format.
Return: The position and length of every reverse palindrome in the string 
having length between 4 and 12. You may return these pairs in any order.
Sample Dataset
>Rosalind_24
TCAATGCATGCGGGTCTATATGCAT
Sample Output
4 6
5 4
6 6
7 4
17 4
18 4
20 6
21 4
==============================================================================#

include("ComplementingaStrandofDNA.jl")
include("bioutils.jl")

type Palindrome
    ind::Int
    len::Int
end

function palindromes(fasta)
    seqs = Fasta.parse(fasta)
    pal = Palindrome[]
    for seq in seqs
        for (i,c) in enumerate(seq.sequence)
            for j in 3:11
                if i+j <= length(seq.sequence)
                    rseq = rev_complement(seq.sequence[i:i+j])
                    if rseq == seq.sequence[i:i+j]
                        push!(pal, Palindrome(i,j+1))
                    end
                end
            end
        end
    end
    pal
end