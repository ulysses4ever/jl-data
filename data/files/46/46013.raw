import Base.Sort: Algorithm, Forward, ReverseOrdering, ord
import Base.Order.Ordering

function test()

    function cons(t...)
        times = [t...]
        return times
    end
    replicates = 100
    origdata = rand(2^10)
    n = length(origdata)
    order = Forward
    alg = QuickSort
    skip_median_killer = false
    logn = log2(length(origdata))

    rec = {"test_type" => string(eltype(origdata)),
           "sort_alg" => string(alg)[1:end-5],
           "log_size" => isinteger(logn) ? int(logn) : logn,
           "size" => length(origdata)}

    times = @parallel (cons) for rep = 1:replicates

        print(" $rep")
        reptimes = Dict{String, Float64}()

        ## Random
        data = copy(origdata)
        gc()
        if !issorted(data, order)
            reptimes["*sort"] = @elapsed sort!(data, alg, order)
            @assert issorted(data, order)
        end

        ## Sorted
        gc()
        reptimes["/sort"] = @elapsed sort!(data, alg, order)
        @assert issorted(data, order)

        ## Reverse sorted
        reverse!(data)
        # @assert issorted(data, ReverseOrdering(order))
        gc()
        reptimes["\\sort"] = @elapsed sort!(data, alg, order)
        @assert issorted(data, order)

        ## Sorted with 3 exchanges
        for i = 1:3
            n1 = rand(1:n)
            n2 = rand(1:n)
            data[n1], data[n2] = data[n2], data[n1]
        end
        gc()
        reptimes["3sort"] = @elapsed sort!(data, alg, order)
        @assert issorted(data, order)

        ## Sorted with 10 unsorted values at end
        if length(data) >= 20
            for i = 1:10
                val = splice!(data, i:i)
                append!(data, val)
            end
            gc()
            reptimes["+sort"] = @elapsed sort!(data, alg, order)
            @assert issorted(data, order)
        end

        ## Random data with 4 unique values
        idxs = Int[]
        for i = 1:4
            idx = rand(1:n)
            while idx in idxs
                idx = rand(1:n)
            end
            push!(idxs, idx)
        end
        vals = data[idxs]
        data4 = vals[rand(1:4, n)]
        gc()
        reptimes["~sort"] = @elapsed sort!(data4, alg, order)
        @assert issorted(data, order)

        ## All values equal
        data1 = data[fill(rand(1:n), n)]
        gc()
        reptimes["=sort"] = @elapsed sort!(data1, alg, order)
        @assert issorted(data1, order)

        ## quicksort median killer: first half descending, second half ascending
        if skip_median_killer || (alg==OldQuickSort || alg==QuickSort) && !(eltype(data) <: Integer) && length(data) >= 2^18
            print("(median killer skipped) ")
        else
            last = (length(data)>>1)<<1 # make sure data length is even
            qdata = vcat(data[last:-2:2], data[1:2:last])
            gc()
            reptimes["!sort"] = @elapsed sort!(qdata, alg, order)
            @assert issorted(qdata, order)
        end
        merge(rec, reptimes)
    end

end

println(test())
