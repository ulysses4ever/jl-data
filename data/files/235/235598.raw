using Sims
using NineML
using Winston

al = NineML.parse_ComponentClass("IzhikevichFS_AL.xml")
uls = NineML.parse_Components("IzhikevichFS_UL.xml")

tf = 100.0
dt = 0.025

for ul in uls

    
    NineML.eval_Dynamics(al.dynamics, ul.name, ul.parameterValues, ul.initialValues, al.parameters, al.states, al.ports)
    modelname = ul.name

    izhfs = eval(quote $modelname () end)
    izhfs_s = create_sim(izhfs)
    izhfs_ptr = setup_sunsim(izhfs_s)
    
    izhfs_yout = sunsim(izhfs_ptr, tf, int(tf/dt))
    f = figure()
    pl = plot (izhfs_yout.y[:,1], izhfs_yout.y[:,2])
    display(pl)
end

