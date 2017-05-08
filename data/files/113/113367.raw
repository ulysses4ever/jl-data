#Compute returns
function ret(tpv)
    times = tpv[:time]
    prices = tpv[:price]

    returnsidx2pricesidx = Dict{Int,Int}()

    length(times)==0 && return DataFrame(time=[], returns=[]), returnsidx2pricesidx

    tmin, tmax = extrema(times)
    DayInterval = tmin:Dates.Millisecond(25):tmax
    returns = zeros(length(DayInterval))
    for i = 1:length(times)-1
        dt = float(times[i+1] - times[i])
        dt==0 && continue

        idx = int((times[i] - DayInterval.start)/Dates.Millisecond(25)) + 1
        returnsidx2pricesidx[idx]=i

        if dt ≤ -1 #Use forward differences
            returns[idx] = (prices[i] - prices[i+1])/0.025 #Units are currency per second
        elseif dt ≥ 1
            returns[idx] = (prices[i+1] - prices[i])/0.025 #Units are currency per second
        end
    end
    DataFrame(time=DayInterval, returns=returns), returnsidx2pricesidx
end

#Compute maximal percentage price movement in window 5min 15sec before specified time.
#Tries to reconstruct NYSE circuit breaker rules:
#
# > A security would enter a “limit state” if its price moves a certain
# > percentage – generally 5%, 10% or 20%, depending on the stock and the time of
# > day – over a five-minute period. If the market does not naturally exit the
# > limit state within 15 seconds, there would be a five-minute trading pause.
function pchange(tpv, time)
    length(tpv[:price])==0 && return 0.0
    idx = findfirst(t->t>=time, tpv[:time])
    price = idx==0 ? tpv[:price][end] : tpv[:price][idx]
    tstart = time - Dates.Minute(5) - Dates.Second(15)
    startidx=findfirst(t->t > tstart, tpv[:time]) - 1
    startidx=max(startidx, 1)
    startidx=min(startidx, length(tpv[:time]))
    #tend = time + Dates.Minute(5) + Dates.Second(15)
    #tendidx=findfirst(t->t > tend, tpv[:time])
    #tendidx=min(tendidx, length(tpv[:time]))
    #tendidx=max(tendidx, 1)
    startidx>=idx && return 0.0
    plo, phi = extrema(tpv[:price][startidx:idx])
    pctdrop = 100.0*(1.0 - price/phi)
    pctrise = 100.0*(1.0 - price/plo)
    -pctdrop > pctrise ? pctdrop : pctrise
end


#Compute realized volatility
function rvol(tpv::DataFrame;
    ftime::Symbol=:time, fprice::Symbol=:price,
    blocklength=Dates.Minute(15), interval=Dates.Minute(1),
    res=Dates.Millisecond(25))

    const times=tpv[:, ftime]
    length(times)==0 && DataFrames.DataFrame(time=[], rv=[], plo=[])
    tmin, tmax = extrema(times)
    starttimeblock = tmin
    endtimeblock = tmin+blocklength
    blocktimes = Dates.DateTime[]
    volatilities = Float64[]
    pricelows = Float64[]

    i1=1
    while starttimeblock < tmax
        t1 = sub(times, i1:size(times,1))
        i1 = findfirst(x->x>starttimeblock, t1)+i1-1
        t2 = sub(times, i1:size(times,1))
        i2 = findfirst(x->x≥endtimeblock, t2)+i1-1
        i2==i1-1 && (i2=size(tpv, 1))

        #Compute OHLC in this time interval
        pop = tpv[i1, fprice]
        pcl = tpv[i2, fprice]
        if i2>i1
            plo, phi = extrema(tpv[i1:i2, fprice])
        else
            plo = phi = pop
        end

        #Compute realized volatility over log-returns (log of prices)
        thisvol = 0.0
        if i2-i1+1 > 1
             xs = zeros(i2-i1+1)
             r0 = tpv[i1, fprice]
             for i=1:i2-i1+1
                 xs[i] = tpv[i+i1-1, fprice] - r0
             end
             thisvol = std(xs)
        end

        #Average price properly, taking into account that price is not
        #always reported in uniform time intervals
        #priceavg = nuavg(tpv, fprice, ftime, res, starttimeblock:res:endtimeblock, i1:i2, pop)
        #volatility /= priceavg

        starttimeblock += interval
        endtimeblock   += interval

        push!(blocktimes, starttimeblock)
        push!(volatilities, thisvol)
        push!(pricelows, plo)
    end
    DataFrames.DataFrame(time = blocktimes, rv = volatilities, plo = pricelows)
end


