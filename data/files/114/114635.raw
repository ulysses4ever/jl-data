"""
Outputs the first n numbers starting from 1.
"""
function num_american_names(n)
    file = open("project_euler\\src\\p17\\a000027.txt")
    readline(file)
    names = Vector{String}(n)
    for i in 1:n
        str = split(readline(file))[2]
        str = chomp(str)
        @inbounds names[i] = str
    end
    names
end

function num_brittish_name_sum(n)
    names = num_american_names(n)
    len = 0
    for i in 1:n
        len += length(names[i])
        if i > 100 && i % 100 != 0
            len += 3
        end
    end
    len
end

# this is cheating, but building the names of the numbers is really, really boring
num_brittish_name_sum(1000)
