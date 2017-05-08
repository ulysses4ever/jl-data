using Distances
using NPZ
using Iterators
using Images

verbose = true

array = convert(Array{Float64,2}, npzread("myo_footprints.npy")')


exp_schedule(t, tf) = (α0 =0.5; αf = 0.01; σ0 = 10.; σf = 1.; (α0 * exp(-t * log(αf/α0)/tf), σ0 * exp(-t * log(σf/σ0)/tf)))

gauss_transform(dmap, d, t, tf, α, σ) = α .* exp(-dmap.^2/σ^2)

tuppush(tup, value) = tuple(push!([i for i=tup], value)...)
tupunshift(tup, value) = tuple(unshift!([i for i=tup], value)...)

@everywhere function indmin_comp(a::Tuple, b::Tuple)
    da, ia = a
    db, ib = a
    mask = da .> db
    da[mask] = db[mask]
    ia[mask] = ib[mask]
    return (da, ia)
end

function findBMU(dist, vect, som, verbose=false)
    typeof(dist)<:PreMetric
    d = size(som)[1]
    mapsize = size(som)[2:end]
    vecsize = size(vect)[2]
    flatmapsize = reduce(*, mapsize)
    flatmap = reshape(som, (d, flatmapsize))
    pd = pairwise(dist, flatmap, vect)
    n = nprocs()
    if n == 1
        dmin, argmin = findmin(pd, 1)
    else
        prev = 0
        chunks = typeof(pd)
        # slower than single proc because of data copy...
        for i=map((x) -> convert(Int, round(x, 0)), linspace(1, flatmapsize, n+1)[2:end])
            #println(prev, i, size(chunks), size(pd))
            push!(chunks, pd[(prev+1):i, :])
            prev = i
        end
        @everywhere f(x) = findmin(x, 1)
        dmin, argmin = reduce(indmin_comp, pmap(f, chunks))
    end
    if vecsize == 1
        return (dmin, ind2sub(mapsize, vec(argmin)))
    else
        indflatmap, indvect = ind2sub((flatmapsize, vecsize), vec(argmin))
        indmap = ind2sub(mapsize, indflatmap)
        return (dmin, indmap)
    end
end

function mgrid(dims...)
    X = Array(Int, tuple(unshift!([i for i=dims], length(dims))...)) # Any[zeros(Int,dims...) for d in 1:length(dims)]
    for d in 1:length(dims)
        base_idx = Any[1:nd for nd in dims]
        for i in 1:dims[d]
            cur_idx = copy(base_idx)
            cur_idx[d] = i
            X[d, cur_idx...] = i
        end
    end
    #@show X
    return X
end

function SOM(input, mapsize, tf, dist, schedule, transform)
    typeof(dist)<:PreMetric
    D, N = size(input)
    true_mapsize = tupunshift(mapsize, D)
    m = minimum(input, 2)
    M = maximum(input, 2)
    som = m .+ M .* rand(true_mapsize)
    steps = [1:N]
    indices = mgrid(mapsize...)
    #get_mapdists(x::Array{Int,length(true_mapsize)}, y::Array{Int,length(true_mapsize)}) = sum(abs(x - y), 1)
    absdiff(x::Int, y::Int) = abs(x - y)
    const broadcast_absdiff = broadcast_function(absdiff)
    const broadcast_mult = broadcast_function(*)
    for t=1:tf
        if t % N == 1
            shuffle!(steps)
        end
        idx = steps[((t-1) % N) + 1]
        inpvec = input[:,[idx]]
        d, bmu = findBMU(dist, inpvec, som)
        bmu = reshape(hcat(bmu...), (bmusize = ones(Int, length(mapsize)+1); bmusize[1] = length(mapsize);tuple(bmusize...)))
        #println(" bmu ", size(bmu), " indices ", size(indices))
        mapdists = float(sum(broadcast_absdiff(indices, bmu), 1))
        α, σ = schedule(t, tf)
        Δmap = transform(mapdists, d, t, tf, α, σ)
        newsize = (shape=ones(Int, length(mapsize)+1); shape[1]=D; tuple(shape...))
        inpvec_bc = reshape(inpvec, newsize)
        som = som + broadcast_mult(inpvec_bc, Δmap)
        if verbose
            println(t,"/",tf, ": input #", idx, ", bmu: ", tuple(bmu...))
        end
    end
    return som
end

function neighbors(point, shape)
    f(x, s) = 1 <= x <= s
    return Iterators.Product([filter!((x)->f(x,s), [p-1, p, p+1]) for (p,s)=zip(point, shape)]...)
end

function umatrix(som, dist; toric=false)
    mapsize = size(som)[2:end]
    umat = zeros(mapsize)
    cartprod = Iterators.Product([[1:i] for i=mapsize]...)
    for point=cartprod
        neighb = neighbors(point, mapsize)
        c=0.
        pvec = som[:,point...]
        for n=neighb
            umat[point...] += evaluate(dist, pvec, som[:,n...])
            c += 1.
        end
        umat[point...] /= c
    end
    #indices = mgrid(mapsize...)
    return umat
end


som = SOM(array, (25,25), 500, CosineDist(), exp_schedule, gauss_transform)
umat = umatrix(som, CosineDist())
NPZ.npzwrite("umatrix.npy", umat)

bmus_distances, bmus = findBMU(CosineDist(), array, som, true)
density = zeros(size(som)[2:end])
#@show bmus
for b=zip(bmus...)
    @show b
    density[b...] += 1
end
NPZ.npzwrite("density.npy", density)


