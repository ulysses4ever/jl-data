using PyCall
@pyimport matplotlib.pyplot as pl

t_loop_one_node = [3.0157,3.0073,2.9226,2.918]
t_map_one_node = [5.2058,3.9505,3.8281,3.7806]
n_core_one_node = [1.,2.,4.,8.]
pl.plot(n_core_one_node, t_loop_one_node, "bo-", label = "time loop")
pl.plot(n_core_one_node, t_map_one_node, "ro-", label = "time map")
pl.legend(("time loop","time map"))
pl.xlabel("number of cores (on one node)")
pl.ylabel("run time [s]")
pl.savefig("problem1_one_node.png")
pl.show()
