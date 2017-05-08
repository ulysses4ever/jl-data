# ==============================================================================
# SEK.jl
#
# Authors: David Koslicki (david.koslicki@math.oregonstate.edu)
#
# Takes a fasta file as input and performs the SEK Algorithm on it.
# ==============================================================================

using ArgParse
using HDF5
include("lsqnonneg.jl")
include("OMP_plus_1_mod.jl")
include("ConvertToCAMIOutput.jl")


#Parse arguments
function parse_commandline()
    s = ArgParseSettings()

    @add_arg_table s begin
        "--input_file", "-i"
			help = "Fasta file to perform the reconstruction on"
        "--nu", "-n"
			help = "nu parameter: specifies the tolerance required to adjudge the SEK algorithm having converged. Default = 0.00001"
			default = 0.00001;
		"--I", "-I"
			help = "The I parameter specifies the maximum sparsity of the returned result. Default = 100"
			default = 100;
		"--kmer_count_path", "-k"
			help = "Full path to the kmer_total_count file obtained from https://github.com/mutantturkey/dna-utils"
			default = "kmer_total_count"
        "--output_file", "-o"
			help = "Output reconstruction file"
			
    end
    return parse_args(s)
end


#Parse the args
parsed_args = parse_commandline()
input_file = parsed_args["input_file"]
nu = parsed_args["nu"]
I = int(parsed_args["I"])
output_file = parsed_args["output_file"]
kmer_count_path = parsed_args["kmer_count_path"]

#Form the 6mer counts
counts = map(x->int(strip(x)),readlines(`$kmer_count_path -i $input_file -k 6 -c`));

#normalize the counts
counts = counts/sum(counts);

#Read in the training database
A = h5read("../../data/trainset7_112011_allseqslongerthan700-SEKTrainingMatrix-bitShift100-windowLength400-N6C.h5","/data");

#Read in the block matrix to return to the trainset7_SEK basis
blockMatrix = h5read("../../data/trainset7_112011_allseqslongerthan700-SEKTrainingMatrix-bitShift100-windowLength400-blockMatrix.h5","/data");


#Perform the reconstruction
x = OMP_plus_1_mod(A, counts, nu, I);

#Return to the trainset7_SEK basis
x = blockMatrix*x;

#Normalize the output
x = x/sum(x);

#Write the output to file
output_level = 0; #Since we don't have hypothetical organisms
ConvertToCAMIOutputFunction(x, "../../data/trainset7_SEK_taxonomy.txt", output_level, output_file)









#How I saved the training data
#fid = h5open("trainset7_112011N6C.h5","w");
#fid["/data", "chunk", (512,10046), "compress", 7] = Atemp;
#close(fid)

#Convert trainset7 taxonomy with
#cat trainset7_taxonomy.txt | sed -e '4180d;4179d;3879d;3844d;3818d;3776d;3693d;3692d;3377d;3270d;3269d;3268d;3267d;3266d;3264d;3030d;3029d;2965d' > trainset7_SEK_taxonomy.txt

