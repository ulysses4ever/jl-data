limit = 4000000


function sumevenfib(prev :: Int64, curr :: Int64, acc :: Int64)
    if curr > limit
        acc
    else
        sumevenfib(curr, prev + curr, acc + ((curr % 2 == 0) ? curr : 0))
    end
end

function euler2()
    sumevenfib(0, 1, 0)
end



