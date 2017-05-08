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

function search_rec(a, t::Int64, base_p::Int64)
    u = length(a)
    m = round(Int, u/2)+1

    # println(a)
    println("Searching... $m, based $base_p")

    if a[m] == t
        p = m
    elseif a[m] < t && m < u
        p = search_rec(sub(a, m+1:u), t, m)
    elseif t < a[m] && m > 1
        p = search_rec(sub(a, 1:m-1), t, 0)
    else
        p = -1
    end

    if p == -1
        -1
    else
        p + base_p
    end
end

function main()
    x = [10,20,30,40,50,60,70,80,90,100]

    lower = 1
    upper = size(x)[1]

    println("Normal")
    println( search(x, lower, upper, 10) )
    println( search(x, lower, upper, 11) )
    println( search(x, lower, upper, 20) )
    println( search(x, lower, upper, 90) )
    println( search(x, lower, upper, 98) )
    println( search(x, lower, upper, 100) )

    println("Recurcive")
    println( search_rec(x, 10, 0) )
    println( search_rec(x, 11, 0) )
    println( search_rec(x, 20, 0) )
    println( search_rec(x, 70, 0) )
    println( search_rec(x, 77, 0) )
    println( search_rec(x, 90, 0) )
    println( search_rec(x, 98, 0) )
    println( search_rec(x, 100,0) )
end

end
