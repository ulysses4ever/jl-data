# nums = [(a,b,c) for a in 1:1000, for b in 1:1000, for c in 1:1000]
# valids = filter(e -> sum(e) == 1000)

function pythagorean_triplet()
    for c in 998:-1:3
        for a in 1:c
            for b in 1:c
                if a + b + c == 1000 && a < b < c && a^2 + b^2 == c^2
                    return (a, b, c)
                end
            end
        end
    end
end
