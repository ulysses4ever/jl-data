function balance!(split::Split,
                  scales::Scales,
                  n::Int,
                  metric::Function)
    tic()
    oldmetric = getmetrics(scales, current(split), metric)
    log = [:start => oldmetric,
           :n => n,
           :approach => typeof(split),
           :metric => metric.env.name]
           
    ups = Array((Int, Float64), 0)
    for i in 1:n
        newmetric = getmetrics(scales, proposed!(split), metric)
        if newmetric < oldmetric
            push!(ups, (i, newmetric))
            oldmetric = newmetric
            accept!(split)
        else
            reject!(split)
        end
    end

    log[:ups] = ups
    log[:time] = toq()
    log
end
