function fib()
    a, b = 0, 1
    while true
        produce(b)
        a, b = b, a+b
    end
end

f = Task(fib)
consume(f) # 1
consume(f) # 1
consume(f) # 2
consume(f) # 3
consume(f) # 5
consume(f) # 8
