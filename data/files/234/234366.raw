function sum_square(n::Integer)
    s = 0
    for i=1:n
        s += i^2
    end
    s
end


function square_sum(n::Integer)
    sum(1:n)^2
end


function sum_diff(n::Integer)
    square_sum(n) - sum_square(n)
end


sum_diff(100) |> println
