dataset = open("./winequality-red.csv", "r")

dataset = readall(dataset)
dataset = filter(data -> length(data)>0, split(dataset, '\n'))
dataset = map(data -> split(data, ';'), dataset)
println(typeof(dataset))
titles = dataset[1]
dataset = map(data -> (map(float64, data[1:end-1]), int(data[end])), dataset[2:end])

for (feature, label) = dataset
    println(feature, label)
end

