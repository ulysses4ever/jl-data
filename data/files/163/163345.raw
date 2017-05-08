include("CarbonDictionary.jl")

function CarbonBalance(X)
carbon_dictionary = CarbonDictionary()
Consumption = Dict()

for (key,species) in carbon_dictionary
    model_index = species.model_index
    carbon_number = species.carbon_number

    Consumption[key] = carbon_number*(X[1,model_index]-X[end,model_index])
end

return Consumption
end
