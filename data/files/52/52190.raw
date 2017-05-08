#!/usr/global/julia/121613/usr/bin/julia
@everywhere include("/gpfs/home/fxh140/Astro585/Astro585/Lab7/HW7_Q1_funcs.jl")
@everywhere include("/gpfs/home/fxh140/Astro585/lab7/demo/pbs.jl")   # Some functions to help with pbs jobs

#require("argparse")
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

walltime = 0:10:00
writePBS(N,P,walltime)

#PBS -l nodes=N:ppn=P   
#PBS -l walltime=0:10:00   # specifies a maximum run time in format of hh:mm:ss
#PBS -l pmem=1gb           # this requests 1GB of memory per process
#PBS -j oe                 # combine the stdout and stderr into one file
#PBS -m abe                # send email on abort, begin or exit
###PBS -M fxh140@psu.edu      # send email to this address

cd(ENV["PBS_O_WORKDIR"])

# setup for a parallel job
check_pbs_tasknum_one()
proclist = addprocs_pbs()
print_node_status()

# test that can use tasks on all workers
println("# Julia says welcome from master proc ",myid()," w/ hostname ",gethostname() )
for proc in proclist
  println("# Julia says welcome from worker proc ",proc," w/ hostname ",fetch(@spawnat(proc,gethostname())) )
  flush_cstdio()
end

function get_time()
        (a,b) = time_int_normal_pdf_functions()
        [a,b]
end

tic()
get_time()
toc()

writedlm(output_file,get_time())

#n = 10000000
#@everywhere time_int_normal_pdf_functions(n)
#println("(timeloop, timemap) = ",time_int_normal_pdf_functions(n) )
