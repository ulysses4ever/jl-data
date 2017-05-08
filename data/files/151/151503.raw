using BlossomV

abstract Code

type Point{T}
    x::T
    y::T
end

type ToricCode <: Code
    L::Int64
    S::Matrix{Uint8}
    LO::Matrix{Uint8}
    E::Vector{Uint8}
    V::Vector{Uint8}
    locations::Matrix{Uint}
    positions::Vector{Point{Uint}}
    slices::Vector{Uint}
end

ToricCode(L::Integer) = ToricCode(L,
    zeros(Uint8, (2*L*L, 2*2*L*L)),
    zeros(Uint8, (4, 2*2*L*L)),
    Array(Uint8, (2*2*L*L,)),
    Array(Uint8, (2*L*L)),
    Array(Uint, (2*L, L)),
    Array(Point{Uint}, (2*L*L)),
    Array(Uint, 8))

function torus_distance(l, L)
    min(l, L-l)
end

function manhattan_distance(i, j, L)
    x = torus_distance(abs(i[1]-j[1]), L)
    y = torus_distance(abs(i[2]-j[2]), L)
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

function apply_thermal_error!(T::ToricCode)
    L = T.L
    error = reshape(T.E, (2*L, L, 2))
    i, j, k, t  = rand(1:L), rand(1:L), rand(1:2), rand(1:2)
    stabilizers = stabilizer(T, i, j, t) + stabilizer(T,
        rem1(i + (k == 1 ? 1 : 0), L), rem1(i + (k != 1 ? 1 : 0), L), t)
    prob = 0.0
    ϵ = 0.3 # T/J
    if stabilizers == 0
        println("creating two anyons, cost = 2J")
        prob = exp(-2/ϵ)
    elseif stabilizers == 1
        println("moving one anyon, cost = 0")
        prob = ϵ*(1-exp(-2/ϵ))/2
    else
        println("annihilating two anyons, cost = -2J")
        prob = 1.0
    end
    println(prob)
    if rand() <= prob
        println("accepting the error")
        if t == 1
            if k == 1
                error[((2*i) % (2*L))+1, j, 1] += 1
            else
                error[2*i, (j % L)+1, 1] += 1
            end
        else
            if k == 1
                error[((2*i+1)%(2*L))+1, j%L+1, 2] += 1
            else
                error[(2*i%(2*L))+1, j%L+1, 2] += 1
            end
        end
    end
    nothing
end

function stabilizer(T::ToricCode, i, j, t)
    L = T.L
    error = reshape(T.E, (2*L, L, 2))
    if t == 1
        # plaquettes
        return (
            error[2*i, j, 1] +
            error[2*i-1, j, 1] +
            error[2*i, (j % L)+1, 1] +
            error[((2*i) % (2*L))+1, j, 1]
        ) % 2
    else
        # stars
        return (
            error[(2*i%(2*L))+1, j, 2] +
            error[2*i, j%L+1, 2] +
            error[(2*i%(2*L))+1, j%L+1, 2] +
            error[((2*i+1)%(2*L))+1, j%L+1, 2]
        ) % 2
    end
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

function initialize_nfold!(code::Code)
    L = code.L
    _positions = reshape(code.positions, (2*L, L))
    locations = code.locations

    k::Uint = 0
    for i::Uint = 1:2*L
        for j::Uint = 1:L
            k += 1
            locations[i, j] = k
            _positions[i, j] = Point(i, j)
        end
    end

    code.slices[1] = 1
    for i = 2:8
        code.slices[i] = 2*L*L
    end

    nothing
end

function correct_x_errors!(code::ToricCode)
    L = code.L
    result = reshape(code.V, (L, L, 2))
    syn_x, syn_y = findn(result[:,:,1])
    n = length(syn_x)

    m = Matching(int32(n), int32(n*(n-1)/2))

    for k = 1:n-1
        for l = k+1:n
            add_edge(m, int32(k-1), int32(l-1),
                int32(manhattan_distance(
                    (syn_x[k], syn_y[k]), (syn_y[l], syn_y[l]), L)))
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
        apply_x_error!(code, syn_x[k], syn_y[k], syn_x[l], syn_y[l])
    end
    nothing
end

function correct_y_errors!(code::ToricCode)
    L = code.L
    result = reshape(code.V, (L, L, 2))
    syn_x, syn_y = findn(result[:,:,2])
    n = length(syn_x)

    m = Matching(int32(n), int32(n*(n-1)/2))

    for k = 1:n-1
        for l = k+1:n
            add_edge(m, int32(k-1), int32(l-1),
                int32(manhattan_distance(
                    (syn_x[k], syn_y[k]), (syn_y[l], syn_y[l]), L)))
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
        apply_y_error!(code, syn_x[k], syn_y[k], syn_x[l], syn_y[l])
    end
    nothing
end

function apply_x_error!(code::ToricCode, x1, y1, x2, y2)
    L = code.L
    error = reshape(code.E, (2*L, L, 2))

    I, J = x1, y2

    if x1 > x2
        x1, x2 = x2, x1
    end

    if y1 > y2
        y1, y2 = y2, y1
    end

    if (abs(x1-x2) <= ifloor(L/2))
        for i = x1:x2-1
            error[(2*i)+1, J, 1] += 1
        end
    else
        for i = 1:x1
            error[(2*i)-1, J, 1] += 1
        end
        for i = x2:L-1
            error[(2*i)+1, J, 1] += 1
        end
    end

    if (abs(y1-y2) <= ifloor(L/2))
        for j = y1+1:y2
            error[2*I, j, 1] += 1
        end
    else
        for j = 1:y1
            error[2*I, j, 1] += 1
        end
        for j = y2+1:L
            error[2*I, j, 1] += 1
        end
    end

    nothing
end

function apply_y_error!(code::ToricCode, x1, y1, x2, y2)
    L = code.L
    error = reshape(code.E, (2*L, L, 2))

    I, J = x1, y2

    if x1 > x2
        x1, x2 = x2, x1
    end

    if y1 > y2
        y1, y2 = y2, y1
    end

    if (abs(x1-x2) <= ifloor(L/2))
        for i = x1:x2-1
            error[(2*i)+2, J%L+1, 2] += 1
        end
    else
        for i = 1:x1
            error[(2*i), J%L+1, 2] += 1
        end
        for i = x2:L-1
            error[(2*i)+2, J%L+1, 2] += 1
        end
    end

    if (abs(y1-y2) <= ifloor(L/2))
        for j = y1+1:y2
            error[rem1(2*I+1, 2*L), j, 2] += 1
        end
    else
        for j = 1:y1
            error[rem1(2*I+1, 2*L), j, 2] += 1
        end
        for j = y2+1:L
            error[rem1(2*I+1, 2*L), j, 2] += 1
        end
    end

    nothing
end

function initialize_code!(code::Code)
    initialize_stabilizers!(code)
    initialize_logical_operators!(code)
    nothing
end

function run_simulation!(code::ToricCode, T::Integer, tries::Integer)

    L = code.L
    fail = 0
    result = reshape(code.V, (L, L, 2))

    for n = 1:tries
        if T == 0
            continue
        end

        # clear previous try
        clear!(code)
        initialize_nfold!(code)

        for n = 1:T
            apply_random_error!(code)
        end

        update!(code)
        correct_x_errors!(code)
        correct_y_errors!(code)
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
