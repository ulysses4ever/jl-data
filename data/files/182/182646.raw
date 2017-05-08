# This collection of functions corresponds to Rosalind problems

# Count the number of nucleotides in a given string and return the number of A,G,T,C, respectively
function count_nt(filename)
    A, C, G, T = 0
    seq = open(readall, filename)
    for i in 1:length(seq)
        if seq[i] == 'A'
            A = A + 1
        end
        if seq[i] == 'C'
            C = C + 1
        end
        if seq[i] == 'G'
            G = G + 1
        end
        if seq[i] == 'T'
            T = T + 1
        end
    end    
    return A, C, G, T
end

# Transcribe a string of DNA into RNA
function transcribe(filename)
    DNAseq = open(readall, filename)
    RNAseq = replace(DNAseq,'T','U')
    return RNAseq
end

# Print the reverse complement of a given string of DNA
function reverse_complement(filename)
    seq = reverse(chomp(open(readall, filename)))
    for i = 1:endof(seq) 
     if seq[i] == 'A'
        print('T') 
     end
     if seq[i] == 'T'
        print('A') 
     end
     if seq[i] == 'C'
        print('G') 
     end
     if seq[i] == 'G' 
        print('C')
     end
    end
end

# Calculate the GC content of a given string of DNA
function GC(seq)
    sum = 0
    for i in 1:endof(seq)
        if seq[i] == 'G' 
            sum = sum + 1
        end
        if seq[i] == 'C'
            sum = sum + 1
        end
    end
    return sum/length(seq) * 100
end

fr = FastaReader("/home/steve/Downloads/rosalind_gc.txt")
data = readall(fr)

for i in 1:length(data)
    println(data[i][1])
    gc_content = GC(data[i][2])
    println(gc_content)
end

# Calculate the Hamming's difference(the number of differences between two strings of DNA )
function hammings_diff(filename)
    total = 0
    seq = open(readlines, filename)
    for i in 1:length(seq[1])
        if seq[1][i] != seq[2][i]
            total = total + 1
        end
    end
    return total
end
