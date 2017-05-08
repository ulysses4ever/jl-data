using PyPlot
include("CarbonBalance.jl")
include("DictSum.jl")

labels = ["Organic Acids","Amino Acids","CAT","CO2 and other"]

X_best = readdlm("Ensemble100/Best/X")
balance_best = CarbonBalance(X_best)
reactants,organics,AA_products,CAT,co2 = DictSum(balance_best)

organics_fraction = organics/reactants
AA_fraction = AA_products/reactants
CAT_fraction = CAT/reactants
co2_fraction = co2/reactants

sizes = 100*[organics_fraction,AA_fraction,CAT_fraction,co2_fraction]
#explode = (0, 0.1, 0, 0)  # only "explode" the 2nd slice

fig_best,ax_best = subplots()
ax_best[:pie](sizes,labels=labels,autopct="%1.1f%%",startangle=90)
ax_best[:axis]("equal")  # Equal aspect ratio ensures that pie is drawn as a circle.
title("Best-fit set")
#show()

X_KO_cyd = readdlm("KO_cyd/Best/X")
balance_KO_cyd = CarbonBalance(X_KO_cyd)
reactants,organics,AA_products,CAT,co2 = DictSum(balance_KO_cyd)

organics_fraction = organics/reactants
AA_fraction = AA_products/reactants
CAT_fraction = CAT/reactants
co2_fraction = co2/reactants

sizes = 100*[organics_fraction,AA_fraction,CAT_fraction,co2_fraction]
#explode = (0, 0.1, 0, 0)  # only "explode" the 2nd slice

fig_KO_cyd,ax_KO_cyd = subplots()
ax_KO_cyd[:pie](sizes,labels=labels,autopct="%1.1f%%",startangle=90)
ax_KO_cyd[:axis]("equal")  # Equal aspect ratio ensures that pie is drawn as a circle.
title("cyd")
#show()

X_KO_nuo = readdlm("KO_nuo/Best/X")
balance_KO_nuo = CarbonBalance(X_KO_nuo)
reactants,organics,AA_products,CAT,co2 = DictSum(balance_KO_nuo)

organics_fraction = organics/reactants
AA_fraction = AA_products/reactants
CAT_fraction = CAT/reactants
co2_fraction = co2/reactants

sizes = 100*[organics_fraction,AA_fraction,CAT_fraction,co2_fraction]
#explode = (0, 0.1, 0, 0)  # only "explode" the 2nd slice

fig_KO_nuo,ax_KO_nuo = subplots()
ax_KO_nuo[:pie](sizes,labels=labels,autopct="%1.1f%%",startangle=90)
ax_KO_nuo[:axis]("equal")  # Equal aspect ratio ensures that pie is drawn as a circle.
title("nuo")
#show()

X_KO_app = readdlm("KO_app/Best/X")
balance_KO_app = CarbonBalance(X_KO_app)
reactants,organics,AA_products,CAT,co2 = DictSum(balance_KO_app)

organics_fraction = organics/reactants
AA_fraction = AA_products/reactants
CAT_fraction = CAT/reactants
co2_fraction = co2/reactants

sizes = 100*[organics_fraction,AA_fraction,CAT_fraction,co2_fraction]
#explode = (0, 0.1, 0, 0)  # only "explode" the 2nd slice

fig_KO_app,ax_KO_app = subplots()
ax_KO_app[:pie](sizes,labels=labels,autopct="%1.1f%%",startangle=90)
ax_KO_app[:axis]("equal")  # Equal aspect ratio ensures that pie is drawn as a circle.
title("app")
#show()

X_KO_all = readdlm("KO_all/Best/X")
balance_KO_all = CarbonBalance(X_KO_all)
reactants,organics,AA_products,CAT,co2 = DictSum(balance_KO_all)

organics_fraction = organics/reactants
AA_fraction = AA_products/reactants
CAT_fraction = CAT/reactants
co2_fraction = co2/reactants

sizes = 100*[organics_fraction,AA_fraction,CAT_fraction,co2_fraction]
#explode = (0, 0.1, 0, 0)  # only "explode" the 2nd slice

fig_KO_all,ax_KO_all = subplots()
ax_KO_all[:pie](sizes,labels=labels,autopct="%1.1f%%",startangle=90)
ax_KO_all[:axis]("equal")  # Equal aspect ratio ensures that pie is drawn as a circle.
title("All knockouts")
#show()



