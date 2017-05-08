function read_matrix(filename, n=20)
    file = open(filename)
    nums = [parse(Int, i) for i in split(readall(file))]
    reshape(nums, 20, 20)'
end

function max_consecutive_prod(grid, n)
    max_prod = 0
    prod = 1
    len_i = size(grid, 1)
    len_j = size(grid, 2)

    # rows
    for i in 1:(len_i), j in 1:(len_j - n + 1)
        prod = 1
        for k in 0:(n-1)
            prod *= grid[i, j+k]
        end
        max_prod = max(max_prod, prod)
    end

    # columns
    for i in 1:(len_i - n + 1), j in 1:(len_j)
        prod = 1
        for k in 0:(n-1)
            prod *= grid[i+k, j]
        end
        max_prod = max(max_prod, prod)
    end

    # diagonals
    for i in 1:(len_i - n + 1), j in 1:(len_j - n + 1)
        prod = 1
        for k in 0:(n-1)
            prod *= grid[i+k, j+k]
        end
        max_prod = max(max_prod, prod)
    end

    # anti-diagonals
    for i in 1:(len_i - n + 1), j in n:len_j
        prod = 1
        for k in 0:(n-1)
            prod *= grid[i+k, j-k]
        end
        max_prod = max(max_prod, prod)
    end

    max_prod
end

const grid = read_matrix("project_euler\\src\\p11\\grid.txt")
max_consecutive_prod(grid, 4)
