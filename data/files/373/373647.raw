#
# 二分探索
#
module BinSearch

typealias DataType Int64

function search(a::Array{DataType}, t::DataType)
    l = 1
    m = 1
    u = length(a)
    while l <= u
        m = round(Int, (l+u)/2)
        println("Finding $t in $a - l=$l  m=$m, u=$u")
        if a[m] < t
            l = m+1
        elseif a[m] == t
            return m
        else
            u = m-1
        end
    end
    return -1
end

function sandbox()
    while (line = readline()) != "\n"
        m = match(r"(\d+) (\d+)", line)
        if m != nothing
            x = [i*10 for i in 1:(parse(Int, m.captures[1]))]
            t = parse(Int, m.captures[2])
            p = search(x, t)
            println("$t in $x is $p")
        else
            println("What?")
        end
    end
end

function main()
    x = [10,20,30,40,50,60,70,80,90,100]
    println( search(x, 10) )
    println( search(x, 11) )
    println( search(x, 20) )
    println( search(x, 90) )
    println( search(x, 98) )
    println( search(x, 100) )
end

end
