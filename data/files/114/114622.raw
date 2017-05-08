function first_n_digits(filename, n::Int)
    file = open(filename)
    numbers = [parse(BigInt, str) for str in split(readall(file))]
    x = BigInt(0)
    for i in numbers
        x += i
    end
    close(file)
    string(x)[1:n]
end

first_n_digits("project_euler\\p13\\input.txt", 10)
