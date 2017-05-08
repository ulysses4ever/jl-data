function series_date_range(j)
    start_date = Date(unix2datetime(j["start_date"]["\$date"]/1000))
    end_date = Date(unix2datetime(j["end_date"]["\$date"]/1000))

    f = j["frequency"]
    if f == "M"
        step = Dates.Month(1)
    elseif f == "Q"
        step = Dates.Month(4)
    elseif f == "Y"
        step = Dates.Year(1)
    else
        error("Unknown frequency: $(f)")
    end

    [ start_date:step:end_date ]
end

# Return the values as an array of floats (JSON gives an array of strings)
series_float_values(j) = convert(Vector{Float64}, map(parsefloat, j["values"]))

function get_series(db, series_id, ::Type{TimeArray}; server = default_server)
    j = get_series(db, series_id, Array; server = server)

    TimeArray(series_date_range(j), series_float_values(j), [ j["name"] ])
end


function get_series(db, series_id, ::Type{DataFrame}; server = default_server)
    j = get_series(db, series_id, Array; server = server)

    d = series_date_range(j)

    df = DataFrame(Date = d)

    # Replace NaN by DataFrame's NA
    df[symbol(j["name"])] = map(x -> if isnan(x); NA else x; end, series_float_values(j))

    df
end
