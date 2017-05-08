using BioFeatures
using DataFrames
# Make some coordinates
region_lengths = rand(100)*1000
starts = int( 1:1000:100000 )
stops = int(  starts + region_lengths )

# Read these into a BioFeature
regions = DataFrame(start = starts, stop = stops)
F = Features( regions )

seq_ids = keys( F.features )
s = nothing
for seq_id in keys(F.features)
   s = F.features[seq_id]
end

for v = values(s)
  println(v[:start])
end

