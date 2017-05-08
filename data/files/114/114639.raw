function read_triangle(filename)
    file = open(filename)
    lines = [split(line) for line in readlines(file)]
    close(file)
    num_lines = [map(x -> parse(Int, x), line) for line in lines]
    matrix = zeros(Int64, length(num_lines), length(num_lines))
    for i = 1:length(num_lines)
        for j = 1:length(num_lines[i])
            matrix[i, j] = num_lines[i][j]
        end
    end
    matrix
end

function max_path_dp!(matrix)
    len = size(matrix)[1]

    # base: j = 1
    for i = 2:len
        matrix[i, 1] += matrix[i-1][1]
    end

    # base: i = j
    for k = 2:len
        matrix[k, k] += matrix[k-1, k-1]
    end

    # fill
    for i = 3:len, j=2:(i-1)
        matrix[i, j] += max(matrix[i-1, j-1], matrix[i-1, j])
    end
    matrix
end

function extract_max_path_value(matrix)
    len = size(matrix)[1]
    max(matrix[len, :]...)
end

function solve(filename)
    matrix = read_triangle(filename)
    max_path_dp!(matrix)
    extract_max_path_value(matrix)
end

const p18_filename = "project_euler\\src\\p18_p67\\triangle_p18.txt"
const p67_filename = "project_euler\\src\\p18_p67\\triangle_p67.txt"
@time solve(p18_filename)
@time solve(p67_filename)
