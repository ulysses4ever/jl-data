divisibleBy(x,y) = x%y == 0

divisibleBy3(x) = divisibleBy(x,3)
divisibleBy5(x) = divisibleBy(x,5)

indices = [divisibleBy3(i) || divisibleBy5(i) for i in 1:999]

multiples = [i*indices[i] for i in 1:999]

problem01 = sum(multiples)