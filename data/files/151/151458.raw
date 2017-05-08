using BlossomV

const L = 60

plaquettes = trues((L, L))

stabilizers = zeros(Bool, (L, L, 2*L, L))
S = reshape(stabilizers, (L*L, 2*L*L))

for i = 1:L
    for j = 1:L
        stabilizers[i, j, 2*i, j] = 1
        stabilizers[i, j, 2*i-1, j] = 1
        stabilizers[i, j, 2*i, (j % L)+1] = 1
        stabilizers[i, j, ((2*i) % (2*L))+1, j] = 1
        #println("plaquette ($i, $j):")
        #println((2*i, j))
        #println((2*i-1, j))
        #println((2*i, (j % L)+1))
        #println((((2*i) % (2*L))+1, j))
    end
end

logical_operators = zeros(Bool, (2, 2*L, L))
LO = reshape(logical_operators, (2, 2*L*L))

for i = 1:L
    logical_operators[1, 1, i] = 1
    #logical_operators[2, 2*i, 1] = 1
end

error = zeros(Uint, 2*L, L)
E = reshape(error, (2*L*L,))

V = S * E % 2

result = reshape(V, (L, L))

for n = 1:50
    i, j = rand(Uint)%(2*L)+1, rand(Uint)%L+1
    error[i, j] += 1
    #error[:] = error % 2
    V[:] = S * E % 2
    #run(`clear`)
    #println("error at ($i, $j):")
    #println(result)
    #sleep(0.5)
end

println(result)

sy = apply((x,y,_)->[x y], findnz(result))
print(sy[1,:])

n = size(sy)[1]

m = Matching(int32(n), int32(n*(n-1)/2))

function manhattan_distance(i, j)
    x = min(abs(i[1]-j[1]), (abs(i[1]-j[1])+L) % L)
    y = min(abs(i[2]-j[2]), (abs(i[2]-j[2])+L) % L)
    x + y
end

function distance(k, l)
    manhattan_distance(sy[k,:], sy[l,:])
end

for k = 1:n-1
    for l = k+1:n
        add_edge(m, int32(k-1), int32(l-1), int32(distance(k, l)))
    end
end

solve(m)

syndrome_list = IntSet(1:n)
for k in syndrome_list
    #print(sy[k,:])
    #print(" matches to ")
    l = get_match(m, int32(k-1))+1
    #println(sy[l,:])
    pop!(syndrome_list, l)
    j = sy[k,2]
    if (abs(sy[k,1]-sy[l,1]) < L/2)
        for i = min(sy[k,1],sy[l,1]):max(sy[k,1],sy[l,1])-1
            error[(2*i)+1, j] += 1
        end
    else
        for i = 1:min(sy[k,1],sy[l,1])
            error[(2*i)-1, j] += 1
        end
        for i = max(sy[k,1],sy[l,1]):L-1
            error[(2*i)+1, j] += 1
        end
    end
    i = sy[l,1]
    if (abs(sy[k,2]-sy[l,2]) < L/2)
        for j = min(sy[k,2],sy[l,2])+1:max(sy[k,2],sy[l,2])
            error[2*i, j] += 1
        end
    else
        for j = 1:min(sy[k,2],sy[l,2])
            error[2*i, j] += 1
        end
        for j = max(sy[k,2],sy[l,2])+1:L
            error[2*i, j] += 1
        end
    end
end

#error[:] = error % 2
V[:] = S * E % 2

if findnz(result)[1] != []
    println(result)
    println("error in correction procedure")
end

logical_error = LO * E % 2

println(logical_error)

if findn(logical_error)[1] != []
    println("error correction failed")
else
    println("error correction successful")
end

