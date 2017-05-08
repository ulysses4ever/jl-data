const datadir = joinpath(dirname(@__FILE__), "xdata", "splitup")
const gpx = Gadfly.px
function output_pane(ticker, date)

    dir = joinpath(datadir, Dates.format(date, "yyyymmdd"), "1", "e" * ticker)
    if !isdir(dir)
        return pad(1em, "No data was found for $ticker on $date")
    end

#   returns = jldopen(joinpath(dir, "derived.jld")) do f read(f, "returns") end
#
#   ret_gesd = h5read(joinpath(dir, "gesd.jld"), "ret_gesd")
#   rv_gesd = h5read(joinpath(dir, "gesd.jld"), "rv_gesd")

    price =
        try
            _tpv = jldopen(joinpath(dir, "data.jld")) do f read(f, "tpv") end
            if _tpv == nothing
                tpv = jldopen(joinpath(dir, "data.jld")) do f read(f, "df") end |> parse_tpv
            else
                tpv = _tpv
            end
            vbox(h2("Price over time"),
                drawing(PNG(1100gpx, 400gpx), plot(tpv,
                    x=:time, y=:price, Geom.line, Geom.point,
                    Guide.xlabel("Time"), Guide.ylabel("Price"),
                    Theme(default_point_size=0.3mm, default_color=color("black"),
                        line_width=0.05mm, highlight_width=0mm)
            )))
        catch
            pad(1em, "Price time series data is not available")
        end

    volume =
        try
            _tpv = jldopen(joinpath(dir, "data.jld")) do f read(f, "tpv") end
            if _tpv == nothing
                tpv = jldopen(joinpath(dir, "data.jld")) do f read(f, "df") end |> parse_tpv
            else
                tpv = _tpv
            end
            vbox(h2("Volume over time"),
                drawing(PNG(1100gpx, 400gpx), plot(tpv,
                x=:time, y=:vol, Geom.line, Geom.point,
                Guide.xlabel("Time"), Guide.ylabel("Tick volume"),
                Theme(default_point_size=0.3mm, default_color=color("black"),
                line_width=0.05mm, highlight_width=0gpx)
            )))
        catch
            pad(1em, "Volume time series data is not available")
        end

    returns =
        try
            returns = jldopen(joinpath(dir, "derived.jld")) do f read(f, "returns") end
            vbox(h2("Returns"),
                drawing(PNG(1100gpx, 400gpx), plot(returns,
                    x=:time, y=:returns, Geom.line, Geom.point,
                    Guide.xlabel("Time"), Guide.ylabel("Realized volatility"),
                    Theme(default_point_size=0.3mm, default_color=color("black"),
                    line_width=0.05mm, highlight_width=0gpx)
                )))
        catch
            pad(1em, "Returns data is not available")
        end

    volatility =
        try
            rv = jldopen(joinpath(dir, "derived.jld")) do f read(f, "rv") end
            vbox(h2("Realized volatility"),
                drawing(PNG(1100gpx, 400gpx), plot(rv,
                    x=:time, y=:rv , Geom.line, Geom.point,
                    Guide.xlabel("Time"), Guide.ylabel("Realized volatility"),
                    Theme(default_point_size=0.3mm, default_color=color("black"),
                    line_width=0.05mm, highlight_width=0gpx)
                )))
        catch
            pad(1em, "Volatility time series data is not available")
        end

    ret_gesd_plot = try
        ret_gesd = jldopen(joinpath(dir, "gesd.jld")) do f read(f, "ret_gesd") end
        drawing(PNG(1100gpx, 600gpx), plot(
            layer(ret_gesd, x=:time, y=:G, Geom.point, Theme(default_color=color("red"))),
            layer(ret_gesd, x=:time, y=:G, Geom.line, Theme(default_color=color("lightgrey"))),
            Guide.xlabel("Time"), Guide.ylabel("Returns"),
            Guide.title("Outliers detected by the GESD test")
        ))
    catch
        pad(1em, "GESD data is not available")
    end

    vbox(
        price,
        volume,
        returns,
        volatility,
        ret_gesd_plot,
    )
end
