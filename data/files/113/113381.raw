const datadir = joinpath(dirname(@__FILE__), "xdata", "splitup")
const gpx = Gadfly.px

include("analysis.jl")

function output_pane(ticker, date)

    dir = joinpath(datadir, Dates.format(date, "yyyymmdd"), "1", "e" * ticker)
    if !isdir(dir)
        info("Directory $dir does not exist")
        return pad(1em, "No data was found for $ticker on $date")
    end

#   returns = jldopen(joinpath(dir, "derived.jld")) do f read(f, "returns") end
#
#   ret_gesd = h5read(joinpath(dir, "gesd.jld"), "ret_gesd")
#   rv_gesd = h5read(joinpath(dir, "gesd.jld"), "rv_gesd")

    #Load data

    #Time-price-volume series
    tpv = try
        jldopen(joinpath(dir, "data.jld")) do f read(f, "tpv") end
    catch e
        warn("Error loading tpv series from $dir/data.jld")
        warn(e)
    end

    if tpv == nothing
        tpv = jldopen(joinpath(dir, "data.jld")) do f read(f, "df") end |> parse_tpv
    end

    #Returns
    returns = try
        jldopen(joinpath(dir, "derived.jld")) do f read(f, "returns") end
    catch e
        warn("Error loading returns series from $dir/derived.jld")
        warn(e)
    end

    #Realized volatility
    rv = try
        jldopen(joinpath(dir, "derived.jld")) do f read(f, "rv") end
    catch e
        warn("Error loading realized volatility series from $dir/derived.jld")
        warn(e)
    end

    #Outlier data
    ret_gesd = try
        jldopen(joinpath(dir, "gesd.jld")) do f read(f, "ret_gesd") end
    catch e
        warn("Could not load returns outlier data")
        warn(e)
        Base.show_backtrace(STDERR, catch_backtrace())
    end

    if ret_gesd==nothing && returns!=nothing
        info("Detecting outliers in returns")
        returns, returnsidx2pricesidx=ret(tpv)
        is, Gs, Gth = gesd(returns[:returns], 20, 1e-10)
        thisprice=map(i->tpv[:price][returnsidx2pricesidx[i]], is)
        thisvol=map(i->tpv[:vol][returnsidx2pricesidx[i]], is)
        ret_gesd = DataFrame(time=returns[:time][is], G=Gs,
            returns=returns[:returns][is],
            price=thisprice,
            vol=thisvol,
            pctchange=map(t->pchange(tpv, t), returns[:time][is])
        )
    end

    if ret_gesd==nothing
        info("Returns outliers are not available")
    end


    rv_gesd = try
        jldopen(joinpath(dir, "gesd.jld")) do f read(f, "rv_gesd") end
    catch e
        warn("Could not load volatility outlier data")
        warn(e)
        Base.show_backtrace(STDERR, catch_backtrace())
    end

    if rv_gesd==nothing && returns!=nothing
        info("Detecting outliers in volatility")
        is, Gs, Gth = gesd(rv[:rv], 20, 1e-10)
        rv_gesd = DataFrame(time=rv[:time][is], G=Gs, rv=rv[:rv][is],
            pricelo = rv[:plo][is],
            pctchange=map(t->pchange(tpv, t), rv[:time][is])
        )
    end

    if rv_gesd==nothing
        info("Volatility outliers are not available")
    end

    #Plot graphs

    price = try
        layers = Any[
            layer(tpv, x=:time, y=:price, Geom.line, Geom.point,
                Theme(default_point_size=0.2mm, default_color=color("black"),
                    line_width=0.05mm, highlight_width=0mm)),
        ]
        if ret_gesd!=nothing && size(ret_gesd, 1) > 0
            l = layer(ret_gesd, x=:time, y=:price, Geom.point,
                    Theme(default_point_size=0.7mm, default_color=color("red")))
            push!(layers, l)
        end

        vbox(h2("Price"),
            drawing(PNG(1100gpx, 400gpx), plot(
                Guide.xlabel("Time"), Guide.ylabel("Price"), layers...
        )))
    catch e
        warn("Could not render price data")
        warn(e)
        Base.show_backtrace(STDERR, catch_backtrace())
        pad(1em, "Price time series data is not available")
    end

    volume = try
        layers = Any[
            layer(tpv, x=:time, y=:vol, Geom.line, Geom.point,
                Theme(default_point_size=0.2mm, default_color=color("black"),
                    line_width=0.05mm, highlight_width=0gpx)
            )
        ]

        if ret_gesd!=nothing && size(ret_gesd, 1) > 0
            l = layer(ret_gesd, x=:time, y=:vol, Geom.point,
                Theme(default_point_size=0.7mm, default_color=color("red")))
            push!(layers, l)
        end

        vbox(h2("Volume"),
            drawing(PNG(1100gpx, 400gpx), plot(
            Guide.xlabel("Time"), Guide.ylabel("Tick volume"),
            layers...)))

    catch e
        warn("Could not render volume data")
        warn(e)
        Base.show_backtrace(STDERR, catch_backtrace())
        pad(1em, "Volume time series data is not available")
    end

    returns = try
        layers = Any[]

        if returns!=nothing
            push!(layers,
            layer(returns, x=:time, y=:returns, Geom.line, Geom.point,
                Theme(default_point_size=0.2mm, default_color=color("black"),
                line_width=0.05mm, highlight_width=0gpx)))
        end

        if ret_gesd!=nothing && size(ret_gesd, 1) > 0
            l = layer(ret_gesd, x=:time, y=:returns, Geom.point,
                    Theme(default_point_size=0.7mm, default_color=color("red")))
            push!(layers, l)
        end

        vbox(h2("Returns"),
            drawing(PNG(1100gpx, 400gpx), plot(
                Guide.xlabel("Time"), Guide.ylabel("Returns"),
                layers...
            )))
    catch e
        warn("Could not render returns data")
        warn(e)
        Base.show_backtrace(STDERR, catch_backtrace())
        pad(1em, "Returns data is not available")
    end

    volatility = try
        layers = Any[
             layer(rv, x=:time, y=:rv , Geom.line, Geom.point,
                    Theme(default_point_size=0.2mm, default_color=color("black"),
                    line_width=0.05mm, highlight_width=0gpx)
                ),
        ]

        if rv_gesd!=nothing && size(rv_gesd, 1) > 0
            l = layer(rv_gesd, x=:time, y=:rv, Geom.point,
                Theme(default_point_size=0.7mm, default_color=color("red")))
            push!(layers, l)
        end

        vbox(h2("Realized volatility"),
            drawing(PNG(1100gpx, 400gpx), plot(
                    Guide.xlabel("Time"), Guide.ylabel("Realized volatility"), layers...)))
    catch e
        warn("Could not render realized volatility data")
        warn(e)
        Base.show_backtrace(STDERR, catch_backtrace())
        pad(1em, "Volatility time series data is not available")
    end

    vbox(
        price,
        volume,
        returns,
        volatility,
    )
end
