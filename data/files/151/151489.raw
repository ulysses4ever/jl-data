using BlossomV
using DataFrames

if length(ARGS) > 0
    const L = int(ARGS[1])
else
    const L = 10
end
if length(ARGS) > 1
    const tries = int(ARGS[2])
else
    const tries = 1000
end
filename = "data_L$L.csv"

abstract Code

type ToricCode <: Code
    L::Int64
    S::Matrix{Uint8}
    LO::Matrix{Uint8}
    E::Vector{Uint8}
    V::Vector{Uint8}
end

ToricCode(L::Integer) = ToricCode(L,
    zeros(Uint8, (2*L*L, 2*2*L*L)),
    zeros(Uint8, (4, 2*2*L*L)),
    zeros(Uint8, (2*2*L*L,)),
    zeros(Uint8, (2*L*L)))

function torus_distance(l)
    min(l, L-l)
end

function manhattan_distance(i, j)
    x = torus_distance(abs(i[1]-j[1]))
    y = torus_distance(abs(i[2]-j[2]))
    x + y
end

function update!(T::ToricCode)
    L = T.L
    T.V[:] = T.S * circshift(T.E, (2*L*L,)) % 2
    nothing
end

function clear!(T::ToricCode)
    fill!(T.E, 0)
    nothing
end

function apply_random_error!(T::ToricCode)
    T.E[rand(1:end)] += 1
    nothing
end

function initialize_stabilizers!(T::ToricCode)

    L = T.L
    stabilizers = reshape(T.S, (L, L, 2, 2*L, L, 2))

    for i = 1:L
        for j = 1:L
            # plaquettes
            stabilizers[i, j, 1, 2*i, j, 2] = 1
            stabilizers[i, j, 1, 2*i-1, j, 2] = 1
            stabilizers[i, j, 1, 2*i, (j % L)+1, 2] = 1
            stabilizers[i, j, 1, ((2*i) % (2*L))+1, j, 2] = 1
            # stars
            stabilizers[i, j, 2, (2*i%(2*L))+1, j, 1] = 1
            stabilizers[i, j, 2, 2*i, j%L+1, 1] = 1
            stabilizers[i, j, 2, (2*i%(2*L))+1, j%L+1, 1] = 1
            stabilizers[i, j, 2, ((2*i+1)%(2*L))+1, j%L+1, 1] = 1
        end
    end

    nothing
end

function initialize_logical_operators!(T::ToricCode)

    L = T.L
    logical_operators = reshape(T.LO, (4, 2*L, L, 2))

    for i = 1:L
        logical_operators[1, 1, i, 2] = 1
        logical_operators[2, 2*i, 1, 1] = 1
        logical_operators[3, 1, i, 1] = 1
        logical_operators[4, 2*i, 1, 2] = 1
    end

    nothing
end

function correct_x_errors!(syn, err)
    syn_x, syn_y = syn
    n = length(syn_x)

    m = Matching(int32(n), int32(n*(n-1)/2))

    function distance(k, l)
        manhattan_distance(
            (syn_x[k], syn_y[k]),
            (syn_y[l], syn_y[l]))
    end

    for k = 1:n-1
        for l = k+1:n
            add_edge(m, int32(k-1), int32(l-1), int32(distance(k, l)))
        end
    end

    solve(m)

    syndrome_list = IntSet(1:n)
    for k in syndrome_list
        #print(syn[k,:])
        #print(" matches to ")
        l = get_match(m, int32(k-1))+1
        #println(syn[l,:])
        pop!(syndrome_list, l)
        apply_x_error!(err, syn_x[k], syn_y[k], syn_x[l], syn_y[l])
    end
    nothing
end

function apply_x_error!(err, x1, y1, x2, y2)

    I, J = x1, y2

    if x1 > x2
        x1, x2 = x2, x1
    end

    if y1 > y2
        y1, y2 = y2, y1
    end

    if (abs(x1-x2) <= int(floor(L/2)))
        for i = x1:x2-1
            err[(2*i)+1, J, 1] += 1
        end
    else
        for i = 1:x1
            err[(2*i)-1, J, 1] += 1
        end
        for i = x2:L-1
            err[(2*i)+1, J, 1] += 1
        end
    end

    if (abs(y1-y2) <= int(floor(L/2)))
        for j = y1+1:y2
            err[2*I, j, 1] += 1
        end
    else
        for j = 1:y1
            err[2*I, j, 1] += 1
        end
        for j = y2+1:L
            err[2*I, j, 1] += 1
        end
    end

    nothing
end

function correct_y_errors!(syn, err)
    syn_x, syn_y = syn
    n = length(syn_x)

    m = Matching(int32(n), int32(n*(n-1)/2))

    function distance(k, l)
        manhattan_distance(
            (syn_x[k], syn_y[k]),
            (syn_y[l], syn_y[l]))
    end

    for k = 1:n-1
        for l = k+1:n
            add_edge(m, int32(k-1), int32(l-1), int32(distance(k, l)))
        end
    end

    solve(m)

    syndrome_list = IntSet(1:n)
    for k in syndrome_list
        #print(syn[k,:])
        #print(" matches to ")
        l = get_match(m, int32(k-1))+1
        #println(syn[l,:])
        pop!(syndrome_list, l)
        apply_y_error!(err, syn_x[k], syn_y[k], syn_x[l], syn_y[l])
    end
    nothing
end

function apply_y_error!(err, x1, y1, x2, y2)

    I, J = x1, y2

    if x1 > x2
        x1, x2 = x2, x1
    end

    if y1 > y2
        y1, y2 = y2, y1
    end

    if (abs(x1-x2) <= int(floor(L/2)))
        for i = x1:x2-1
            err[(2*i)+2, J%L+1, 2] += 1
        end
    else
        for i = 1:x1
            err[(2*i), J%L+1, 2] += 1
        end
        for i = x2:L-1
            err[(2*i)+2, J%L+1, 2] += 1
        end
    end

    if (abs(y1-y2) <= int(floor(L/2)))
        for j = y1+1:y2
            err[rem1(2*I+1, 2*L), j, 2] += 1
        end
    else
        for j = 1:y1
            err[rem1(2*I+1, 2*L), j, 2] += 1
        end
        for j = y2+1:L
            err[rem1(2*I+1, 2*L), j, 2] += 1
        end
    end

    nothing
end

code = ToricCode(L)
initialize_stabilizers!(code)
initialize_logical_operators!(code)

results = {}

stepsize = ceil(0.005*2*L*L)
τ = 2*L*L

function run_simulation(code::ToricCode, T::Integer)
    fail = 0
    for n = 1:tries
        if T == 0
            continue
        end

        # clear previous try
        clear!(code)

        for n = 1:T*stepsize
            apply_random_error!(code)
        end

        update!(code)
        result = reshape(code.V, (L, L, 2))
        error = reshape(code.E, (2*L, L, 2))

        sy = findn(result[:,:,1])
        correct_x_errors!(sy, error)

        sy = findn(result[:,:,2])
        correct_y_errors!(sy, error)

        update!(code)

        if findnz(result[:,:,1])[1] != []
            println(int(result[:,:,1]))
            println("error in correction procedure")
            println("error correcting x errors")
        end

        if findnz(result[:,:,2])[1] != []
            println(int(result[:,:,2]))
            println("error in correction procedure")
            println("error correcting y errors")
        end

        logical_error = code.LO * circshift(code.E, (2*L*L,)) % 2

        #println(logical_error)

        if findn(logical_error)[1] != []
            fail = fail + 1
            println("error correction failed")
        else
            println("error correction successful")
        end
    end

    println("fail probability: ", fail/tries)
    fail/tries
end

T_max = min(30, int(ceil(0.15/(stepsize/τ))))

for T = 0:T_max
    push!(results, run_simulation(code, T))
end

println(0:stepsize/τ:T_max*stepsize/τ)
println(results)

df = DataFrame(time=0:stepsize/τ:T_max*stepsize/τ,
                probability=results, L=L)

writetable(filename, df)
