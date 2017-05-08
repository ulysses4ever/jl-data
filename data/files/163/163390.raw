function DictSum(dict)

Reactants = ["glucose"
"asn"
"asp"
"cys"
"gly"
"his"
"ile"
"leu"
"lys"
"met"
"phe"
"pro"
"ser"
"thr"
"trp"
"tyr"
"val"]

dict_list = Float64[]
for key in Reactants
    push!(dict_list,dict[key])
end
reactants = sum(dict_list)

Organics = ["pyr"
"lac"
"ac"
"succ"
"mal"]

dict_list = Float64[]
for key in Organics
    push!(dict_list,dict[key])
end
organics = -sum(dict_list)

AA_products = ["gln"
"ala"]

dict_list = Float64[]
for key in AA_products
    push!(dict_list,dict[key])
end
AA_products = -sum(dict_list)

CAT = -dict["cat"]

co2 = reactants-organics-AA_products-CAT

return reactants,organics,AA_products,CAT,co2
end
