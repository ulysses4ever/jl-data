using PyCall
@pyimport matplotlib.pyplot as pl

t_loop_two_node = [3.1467,3.0127,2.8924,3.0441]
t_map_two_node = [4.1845,4.6291,3.7602,4.0598]
n_core_two_node = [2.,4.,8.,16.]
pl.plot(n_core_two_node, t_loop_two_node, "bo-", label = "time loop")
pl.plot(n_core_two_node, t_map_two_node, "ro-", label = "time map")
pl.legend(("time loop","time map"))
pl.xlabel("number of cores (on two node)")
pl.ylabel("run time [s]")
pl.savefig("problem1_two_node.png")
pl.show()
