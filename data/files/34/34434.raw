cd(string(dirname(@__FILE__)))

file = open("p079_keylog.txt")
keys = readlines(file)
close(file)
keys = [strip(key) for key in keys]


total = join(keys)
D = Set([c for c in total])
keys

order = zeros(10,10)
for key in keys
  a,b,c = [int(string(k)) for k in key]
  order[a+1,b+1] = 1
  order[a+1,c+1] = 1
  order[b+1,c+1] = 1
end
order
code = "73162890"


counts = zeros(10,3)
for key in keys
  a,b,c = [int(string(k)) for k in key]
  counts[a+1,1] += 1
  counts[b+1,2] += 1
  counts[c+1,3] += 1
end
counts
