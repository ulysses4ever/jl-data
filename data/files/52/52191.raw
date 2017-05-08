include("/gpfs/home/fxh140/Astro585/lab7/demo/pbs.jl")
include("/gpfs/home/fxh140/Astro585/Astro585/Lab7/HW7_Q1_funcs.jl")

using ArgParse
function parse_commandline()
        s = ArgParseSettings()
        @add_arg_table s begin
                "--opt1"
                        help="get the number of nodes, processors"
                "--opt2","-o"
                        help=""
                "--flag1"
                        help=""
                        action=:store_true
                "n"
                        help="number of nodes"
                        required = true
                "p"
                        help="number of processors"
                        required = true
        end
        return parse_args(s)
end
parsed_args = parse_commandline()
N = parsed_args["n"]
P = parsed_args["p"]
output_file = string("lab7_2_",N,"n_",P,"p.csv")

function get_time()
	(a,b) = time_int_normal_pdf_functions()
	[a,b]
end

tic()
get_time()
toc()

writedlm(output_file,get_time())
