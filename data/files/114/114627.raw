function collatz_length(n::Int)
    len = 1
    while n != 1
        if iseven(n)
            n = div(n, 2)
        else
            n = 3n+1
        end
        len += 1
    end
    len
end

function longest_collatz(n)
    max_len = 1
    max_num = 1
    for i in range(2, n)
        len = collatz_length(i)
        if len >= max_len
            max_len = len
            max_num = i
        end
    end
    max_num
end

# takes roughly half a second... it's possible to make it faster using hash tables
longest_collatz(10^6)
