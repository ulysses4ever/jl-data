using Sims
using NineML
using Winston

al = NineML.parse_ComponentClass("IaF.xml")
uls = NineML.parse_Components("IaF_UL.xml")

tf = 100.0
dt = 0.025

ul= uls[1]
NineML.eval_Dynamics(al.dynamics, ul.name, ul.parameterValues, ul.initialValues, al.parameters, al.states, al.ports)
model = ul.name

iaf = eval(quote $model () end)
iaf_s = create_sim(iaf)
iaf_ptr = setup_sunsim(iaf_s)

iaf_yout = sunsim(iaf_ptr, tf, int(tf/dt))
f = figure()
pl = plot (iaf_yout.y[:,1], iaf_yout.y[:,2])
display(pl)


