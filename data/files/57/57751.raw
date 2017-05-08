#! /usr/bin/env julia

f = "./test.txt"

function cb(a,b,c)
    @show a, b, c
    if b.changed
        println("$a changed")
    end
end

# I am not sure how to get this to work without calling watch_file again
while true
    a = watch_file(cb, f)
    wait(a)
end
