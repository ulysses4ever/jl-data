using FactCheck

include(Pkg.dir("BioFeatures", "src","Features.jl"))

# makedata

df1 = DataFrame( region_id = ["R1","R1","R2"], start = [1,100,1], stop = [50,300,600] )
df2 = DataFrame( region_id = ["R2","R2","R3"], start = [700,1000,60], stop = [800,1200,500] )
df3 = DataFrame( region_id = ["R4","R4","R5"])
df4 = DataFrame( region_id = ["R10","R11","R12"],  start = [700,1000,60], stop = [800,1200,500] )
F = Features(df1, region_id_field = :region_id)
F_keys = collect( keys( F.features))
F_R2_vals = collect(F.features["R2"])

facts("Initialisation Insertions") do
   @fact length(F_keys) => 2
   @fact length(F_R2_vals)=>1
end

add_dataframe_to_features!(F,df2,region_id_field = :region_id)
F_keys = collect( keys( F.features))
F_R2_vals = collect(F.features["R2"])

facts("Appending Features") do
   @fact length(F_keys) => 3
   @fact length(F_R2_vals)=>3
end

# Adds just regions -- even though no start and stop positions
F1 =  Features( df3 )

# Adds region_ids with uninitialised interval trees
# Adds the region into the description
F2 =  Features(df4, region_id_field=:region_id, regions=true )
F2.description
#facts()
