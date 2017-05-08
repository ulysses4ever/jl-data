#
# 二分探索
#
module BinSearch

function search(a::Array{Int64}, l::Int64, u::Int64, t::Int64)
    p = None
    m = None
    while p == None
        if l == u && t == a[l]
            p = l
        elseif l > u
            p = -1
        else
            m = round(Int, (l + u) / 2)
            if a[m] < t
                l = m+1
            elseif a[m] == t
                p = m
            else
                u = m-1
            end
        end
    end
    return p
end

function main()
    x = [10,20,30,40,50,60,70,80,90,100]

    lower = 1
    upper = size(x)[1]

    println( search(x, lower, upper, 10) )
    println( search(x, lower, upper, 11) )
    println( search(x, lower, upper, 20) )
    println( search(x, lower, upper, 90) )
    println( search(x, lower, upper, 98) )
    println( search(x, lower, upper, 100) )
end

end
