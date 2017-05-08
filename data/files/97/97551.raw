
total = function(n::Int64)
    i::Int64      = 1
    j::Int64      = 1
    result::Int64 = 0

    while n > i
        j = 1
        while i > j
            result += 1
            j += 1
        end
        i += 1
    end

    return result
end

println(total(30000))

tic()
total(30000)
toc()
