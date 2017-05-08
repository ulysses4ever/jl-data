function Randomize(data_dictionary_orig,bound)

data_dictionary = deepcopy(data_dictionary_orig)

rate_bound = bound
rate_orig = data_dictionary_orig["RATE_CONSTANT_ARRAY"][1:163]
rate_low = log(1/rate_bound)
rate_up = log(rate_bound)
rate_factor = exp(rate_low+rand(size(rate_orig)).*(rate_up-rate_low))
rate = rate_orig.*rate_factor
data_dictionary_orig["RATE_CONSTANT_ARRAY"][1:163] = rate

sat_bound = bound
sat_orig = data_dictionary_orig["SATURATION_CONSTANT_ARRAY"]
sat_low = log(1/sat_bound)
sat_up = log(sat_bound)
sat_factor = exp(sat_low+rand(size(sat_orig)).*(sat_up-sat_low))
sat = sat_orig.*sat_factor
data_dictionary_orig["SATURATION_CONSTANT_ARRAY"] = sat

#cont_bound = bound
#cont_orig = data_dictionary_orig["CONTROL_PARAMETER_ARRAY"]
#cont_low = log(1/cont_bound)
#cont_up = log(cont_bound)
#cont_factor = exp(cont_low+rand(size(cont_orig)).*(cont_up-cont_low))
#cont = cont_orig.*cont_factor
#data_dictionary_orig["CONTROL_PARAMETER_ARRAY"] = cont

return data_dictionary
end
