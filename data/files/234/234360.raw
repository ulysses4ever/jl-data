# pythagorean triplet:
#   a^2 + b^2 = c^2
# find:
#   a + b + c = 1000

const N = 1000


function istrip(a, b, c)
    a^2 + b^2 == c^2
end


for a = 1:div(N,3)
    for b = a:div(N,2)
        c = N - a - b
        istrip(a, b, c) && println("$a $b $c -> $(a * b * c)")
    end
end
