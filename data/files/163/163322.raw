function CalcSat(experiment_data_dictionary,X)

saturation_constants = zeros(103,1)

for i in 1:length(saturation_constants) # Set all saturation constants equal to average simulation value
    saturation_constants[i] = mean(X[:,i])
end

for (key,value) in experiment_data_dictionary # Overwrite for species for which data exist
    array = experiment_data_dictionary[key].raw_measurement_array
    index = experiment_data_dictionary[key].model_index
    saturation_constants[index] = mean(array[:,2])
end

return saturation_constants

end

