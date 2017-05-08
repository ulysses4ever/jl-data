module euGENE

using Requests, DataFrames

export getGenBankIDs, getGenPeptIDs, getEntrezFasta, getUniProtFasta, parseFasta, translate, translateAll, parseORFs, reverseComplement, switchThyUra, calculateMW, cutAfter, cutBefore, calculateCharge, residueMass, bIons, yIons, fragmentationTable, fragmentationDataFrame, getResidues

RNA_CODONS = {"UUU" => 'F', "UUC" => 'F', "UUA" => 'L', "UUG" => 'L',
              "UCU" => 'S', "UCC" => 'S', "UCA" => 'S', "UCG" => 'S',
              "UAU" => 'Y', "UAC" => 'Y', "UAA" => '-', "UAG" => '-',
              "UGU" => 'C', "UGC" => 'C', "UGA" => '-', "UGG" => 'W',
              "CUU" => 'L', "CUC" => 'L', "CUA" => 'L', "CUG" => 'L',
              "CCU" => 'P', "CCC" => 'P', "CCA" => 'P', "CCG" => 'P',
              "CAU" => 'H', "CAC" => 'H', "CAA" => 'Q', "CAG" => 'Q',
              "CGU" => 'R', "CGC" => 'R', "CGA" => 'R', "CGG" => 'R',
              "AUU" => 'I', "AUC" => 'I', "AUA" => 'I', "AUG" => 'M',
              "ACU" => 'T', "ACC" => 'T', "ACA" => 'T', "ACG" => 'T',
              "AAU" => 'N', "AAC" => 'N', "AAA" => 'K', "AAG" => 'K',
              "AGU" => 'S', "AGC" => 'S', "AGA" => 'R', "AGG" => 'R',
              "GUU" => 'V', "GUC" => 'V', "GUA" => 'V', "GUG" => 'V',
              "GCU" => 'A', "GCC" => 'A', "GCA" => 'A', "GCG" => 'A',
              "GAU" => 'D', "GAC" => 'D', "GAA" => 'E', "GAG" => 'E',
              "GGU" => 'G', "GGC" => 'G', "GGA" => 'G', "GGG" => 'G'}

DNA_COMPLEMENT = {'A' => 'T', 'T' => 'A', 'C' => 'G', 'G' => 'C'}


# MW is for mass upon addition (water is already gone)
MW = {'A' => 71.03711, 'C' => 103.00919, 'D' => 115.02694, 'E' => 129.04259,
      'F' => 147.06841, 'G' => 57.02146, 'H' => 137.05891, 'I' => 113.08406,
      'K' => 128.09496, 'L' => 113.08406, 'M' => 131.04049, 'N' => 114.04293,
      'P' => 97.05276, 'Q' => 128.05858, 'R' => 156.10111, 'S' => 87.03203,
      'T' => 101.04768, 'V' => 99.06841, 'W' => 186.07931, 'Y' => 163.06333,
      # denotes carboxyamidomethylation, ~ denotes phosphorylation, @ denotes acetylation
      '#' => 57.02146, '~' => 79.96633, '@' => 42.01056}

ACID_CHAINS = {'C' => 8.14, 'D' => 3.71, 'E' => 4.15}
BASE_CHAINS = {'H' => 6.04, 'K' => 10.67, 'R' => 12.10}
SIDE_CHAINS = {'C' => 8.14, 'D' => 3.71, 'E' => 4.15, 'H' => 6.04, 'K' => 10.67, 'R' => 12.10}
AMINO_GROUPS = {'A' => 9.71, 'C' => 10.28, 'D' => 9.66, 'E' => 9.58,
                'F' => 9.09, 'G' => 9.58, 'H' => 9.09, 'I' => 9.60,
                'K' => 9.16, 'L' => 9.58, 'M' => 9.08, 'N' => 8.76,
                'P' => 10.47, 'Q' => 9.00, 'R' => 9.00, 'S' => 9.05,
                'T' => 8.96, 'V' => 9.52, 'W' => 9.34, 'Y' => 9.04}
CARBOXYL_GROUPS = {'A' => 2.33, 'C' => 1.91, 'D' => 1.95, 'E' => 2.16,
                   'F' => 2.18, 'G' => 2.34, 'H' => 1.70, 'I' => 2.26,
                   'K' => 2.15, 'L' => 2.32, 'M' => 2.16, 'N' => 2.16,
                   'P' => 1.95, 'Q' => 2.18, 'R' => 2.03, 'S' => 2.13,
                   'T' => 2.20, 'V' => 2.27, 'W' => 2.38, 'Y' => 2.24}


function getGenBankIDs(accession)
    return [n[5:end-5] for n in filter(x -> contains(x,"<Id>"),
    split(post("http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi";
               query = {"db" => "nucleotide", "term" => accession, "sort" => "relevance"}).data,r"\s"))]
end

function getGenPeptIDs(accession)
    return [n[5:end-5] for n in filter(x -> contains(x,"<Id>"),
    split(post("http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi";
               query = {"db" => "protein", "term" => accession, "sort" => "relevance"}).data,r"\s"))]
end

function getEntrezFasta(accession)
    return parseFasta(post("http://eutils.ncbi.nlm.nih.gov/entrez/eutils/efetch.fcgi";
                           query = {"db" => "protein", "id" => accession, "retmode" => "text", "rettype" => "fasta"}).data)
end

function getUniProtFasta(accession)
    return parseFasta(post("http://www.uniprot.org/uniprot/" * accession * ".fasta").data)
end

function parseFasta(fasta)
    return join(filter(x -> !contains(x,">"),split(fasta,"\n")))
end

# list comprehension version, uses same algorithm
function translate(rna)
    return join([RNA_CODONS[rna[n-2:n]] for n in 3:3:length(rna)])
end

# returns array of 5'->3' frame 1, 5'->3' frame 2, 5'->3' frame 3, 3'->5' frame 1, 3'->5' frame 2, 3'->5' frame 3
function translateAll(rna)
    return [translate(rna), translate(rna[2:end]), translate(rna[3:end]),
            translate(reverseComplement(rna)), translate(reverseComplement(rna)[2:end]), translate(reverseComplement(rna)[3:end])]
end

# list comprehension version, uses same algorithm
function parseORFs(translation)
    return [frame[search(frame,r"M.*")] for frame in filter(x -> contains(x,"M"),split(translation,"-"))]
end

function reverseComplement(sequence)
    if contains(sequence,"T")
        return join([DNA_COMPLEMENT[nucleotide] for nucleotide in reverse(sequence)])
    else
        return switchThyUra(join([DNA_COMPLEMENT[nucleotide] for nucleotide in reverse(switchThyUra(sequence))]))
    end
end

# if both T and U are in the sequence, it will still switch them (no judgments here)
function switchThyUra(sequence)
    return replace(replace(replace(uppercase(sequence),"T","~"),"U","T"),"~","U")
end

function calculateMW(sequence)
    return 18.053 + sum([residueMass(aa) for aa in collect(sequence)])
end

function calculatePI(sequence)
    pKas = [SIDE_CHAINS[n] for n in filter(x -> in(x,"CDEHKR"), collect(sequence))]
    push!(pKas,AMINO_GROUPS[sequence[1]])
    push!(pKas,CARBOXYL_GROUPS[sequence[end]])
    sort!(pKas)
    positive = 1 + count(x -> in(x,"HKR"), collect(sequence))
    return (pKas[positive] + pKas[positive+1]) / 2
end

function cutAfter(sequence,residues)
    fragments = [convert(ASCIIString,n) for n in matchall(Regex("[^$residues]*[$residues]"),sequence)]
    if length(join(fragments)) != length(sequence)
        push!(fragments,sequence[length(join(fragments))+1:end])
    end
    return fragments
end

function cutBefore(sequence,residues)
    fragments = [convert(ASCIIString,n) for n in matchall(Regex("[$residues][^$residues]*"),sequence)]
    if length(join(fragments)) != length(sequence)
        unshift!(fragments,sequence[1:length(sequence) - length(join(fragments))])
    end
    return fragments
end

function calculateCharge(sequence)
    return 1 + count(c -> in(c,"RK"), collect(sequence))
end

function residueMass(residue)
    return sum([MW[residue[n]] for n in 1:length(residue)])
end

function bIonMZ(sequence)
    return (sum([residueMass(aa) for aa in collect(sequence)]) + calculateCharge(sequence) * 1.00794) / calculateCharge(sequence)
end

function bIonMZ(sequence,charge)
    return (sum([residueMass(aa) for aa in collect(sequence)]) + charge * 1.00794) / charge
end

function yIonMZ(sequence)
    return (sum([residueMass(aa) for aa in collect(sequence)]) + calculateCharge(sequence) * 1.00794 + 18.01) / calculateCharge(sequence)
end

function yIonMZ(sequence,charge)
    return (sum([residueMass(aa) for aa in collect(sequence)]) + charge * 1.00794 + 18.01) / charge
end

function bIons(sequence)
    residues = getResidues(sequence)
    return [bIonMZ(stringJoin(residues[1:n])) for n in 1:1:length(residues)]
end

function bIons(sequence,charge)
    residues = getResidues(sequence)
    return [bIonMZ(stringJoin(residues[1:n]),charge) for n in 1:1:length(residues)]
end

function yIons(sequence)
    residues = getResidues(sequence)
    return [yIonMZ(stringJoin(reverse(residues[1:n]))) for n in 1:1:length(residues)]
end

function yIons(sequence,charge)
    residues = getResidues(sequence)
    return [yIonMZ(stringJoin(reverse(residues[1:n])),charge) for n in 1:1:length(residues)]
end

function fragmentationTable(sequence,charge)
    residues = getResidues(sequence)
    b = bIons(sequence,charge)
    y = reverse(yIons(sequence,charge))
    return [[residues[n],b[n],y[n]] for n in 1:1:length(sequence)]
end

function fragmentationDataFrame(sequence,charge)
    return DataFrame(Seq = getResidues(sequence), b = bIons(sequence,charge), y = reverse(yIons(sequence,charge)))
end

function getResidues(sequence)
    indices = Int[]
    for n in 1:length(sequence)
        if !in(sequence[n],"@~#")
            push!(indices,n)
        end
    end
    residues = [sequence[indices[n]:(indices[n+1]-1)] for n in 1:(length(indices)-1)]
    push!(residues,sequence[indices[end]:end])
    return residues
end

function stringJoin(array)
    buffer = ""
    for n in 1:length(array)
        buffer *= array[n]
    end
    return buffer
end

# module end
end
