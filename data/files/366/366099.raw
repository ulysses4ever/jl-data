# IJulia is recommended for running this code as it simplifies repeated partial execution of the script

#########################################################################
#                       load classes and progam files                   #            
#########################################################################
# push!(LOAD_PATH, "") add directory if necessary
using CoreBasics_unipolar
using SampleGenerator_unipolar
using CoreBackprop_unipolar
using ModelChecker
using RuleExtractor
# using Gadfly      # for more visualisation options. slow import!
programDir = "a_logic_program.txt"
partialDir = "a_partial_program.txt"

#########################################################################
#                       set up and start training                       #
#########################################################################

# translate programs to cores
c_part = build_core(partialDir)  # to be trained
c_full  = build_core(programDir) # to generate samples

#enable Lukasiewicz semantics: C:0, C*:1, L:2
bLuka = 1    

c_part.bLukaConsequence = bLuka
c_full.bLukaConsequence = bLuka

#make samples
samp = make_samples(c_full)

#set training parameters
nEpochs = 1000
add = 0
lock = 0
#lock = 2*c_part.nClauses   # only change added neurons

stng = BPSettings(nEpochs, add, lock)

stng.bGradCheck = false     # if true, gradient checking is performed at the beginning of each epoch cycle
stng.comments = true        # if true, parameters will be printed every now and then.
stng.gradEps = 0.0001       # parameter for gradient checking
stng.maxEpochs = 10000      # after this number of iterations, training will terminate, even if the goal was not reached.

stng.lrate = 0.02
stng.momentum = 0.02

# set training goal (% of samples correctly classified)
goal = 0.80

optimize_core!(c_part, samp, stng, goal)

#train_core!(c_part, samp, stng)

#########################################################################
#                       continue training if desired                    #
#########################################################################

#= a second script like this could train the core further, after adjusting parameters.

stng.lrate = 0.01
stng.momentum = 0.01
stng.comments = true
stng.maxEpochs = 10000
stng.bGradCheck = false

newGoal = 0.95
optimize_core!(c_part, samp, stng, newGoal)

=#

#########################################################################
#                       make and save plots for later use               #
#########################################################################

#=
name = "core_identifier"
directory = "\\"

p1 = plot_aid(stng,1)
draw(PDF(directory*name*"_pcorr.pdf",
        7cm, 6cm), p1)

p2 = plot_aid(stng,2)
draw(PDF(directory*name*"_eTotal.pdf",
        7cm, 6cm), p2)

p4 = plot_aid(stng,4)
draw(PDF(directory*name*"_avgIt.pdf",
        7cm, 6cm), p4)

p5 = plot_aid(stng,5)
draw(PDF(directory*name*"_costJ.pdf",
        7cm, 6cm), p5)

=#