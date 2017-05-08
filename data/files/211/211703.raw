module DataServer

using Morsel
using JSON
using DataFrames

import Morsel.start
export DataFrameServer, start

type DataFrameServer
    port::Int
    data_dir::String
    app::App
    is_running::Bool

    function DataFrameServer(data_dir::String, port::Int)
        app = Morsel.app()

        get(app, "/") do req, res
            join([
                "DataFrameServer serves CSV data files and simple queries on them.",
                "",
                "<b>Commands:</b>" *
                    "<ul>" *
                        "<li><a href=\"/list\">/list</a>: list hosted data files</li>" *
                        "<li><a href=\"/clearcache\">/clearcache</a>: refresh cached files</li>" *
                        "<li>/meta/[dataset] : provides column names, types, num rows etc.</li>" *
                        "<li>/q/[dataset]?q=[expression] : return dataset or its subset matching optional query expression</li>" *
                        "<li>/d/[dataset]?q=[expression]&filename=[name] : same as above, but returns results as downloadable CSV (filename is optional)</li>" *
                    "</ul>",
                "",
                "<b>Example Expressions:</b>" *
                    "<ul><li>Total__lte__100</li><li>(Sr__lt__100)__and__((Total__gt__600)__or__(Total__lt__200))</li></ul>"
                ],
            "<br/>")
        end

        get(app, "/list") do req, res
            res.headers["Content-Type"] = "application/json"
            csvnames = readdir(data_dir)
            for idx in 1:length(csvnames)
                csvnames[idx] = split(csvnames[idx], '.')[1]
            end
            JSON.json(csvnames)
            json_resp(0, "success", csvnames)
        end

        get(app, "/clearcache") do req, res
            res.headers["Content-Type"] = "application/json"
            empty!(_table_cache)
            json_resp(0, "cache cleared")
        end    

        route(app, GET, "/meta/<cn::String>") do req, res
            res.headers["Content-Type"] = "application/json"
            try
                cn = routeparam(req, :cn)
                dt = get_table(data_dir, cn)
                (nothing == dt) && (res.headers["Status"] = 404; return render("404.ejl"))

                return json_resp(0, "success", meta(dt))
            catch ex
                return json_resp(-1, "error: $(string(ex))")
            end
        end

        route(app, GET, "/q/<cn::String>") do req, res
            res.headers["Content-Type"] = "application/json"
            try
                dt = get_result_dataframe(req, res, data_dir)
                (nothing == dt) && (res.headers["Status"] = 404; return render("404.ejl"))

                return json_resp(0, "success", dt, false)
            catch ex
                return json_resp(-1, "error: $(string(ex))")
            end
        end

        route(app, GET, "/d/<cn::String>") do req, res
            res.headers["Content-Type"] = "text/csv"
            try
                dt = get_result_dataframe(req, res, data_dir)
                (nothing == dt) && (res.headers["Status"] = 404; return render("404.ejl"))
    
                filename = urlparam(req, :filename)
                res.headers["Content-Disposition"] = (nothing == filename) ? "attachment" : "attachment; filename=$(filename)"
                return as_csv(dt)
            catch ex
                res.headers["Status"] = 500
                return render("500.ejl")
            end
        end

        new(port, data_dir, app, false)
    end
end

const subst_exprs = {
    "__eq__" => ".==",
    "__lt__" => ".<",
    "__lte__" => ".<=",
    "__gt__" => ".>",
    "__gte__" => ".>=",
    "__and__" => ".*",
    "__or__" => ".+"
}

function get_result_dataframe(req, res, data_dir)
    cn = routeparam(req, :cn)
    #println("read table: $cn")

    dt = get_table(data_dir, cn)
    (nothing == dt) && (return nothing)

    query = urlparam(req, :q)
    (nothing == query) && (query = urlparam(req, :expr))

    if nothing != query
        #println("query=[$(query)]")
        #println("query_to_expr=$(query_to_expr(query))")
        expr = query_to_expr(query)
        dt =  dt[expr, :]
    end
    dt
end

function query_to_expr(q::String)
    for (exp,repl) in subst_exprs
        q = replace(q, exp, repl)
    end
    parse(q)
end

function start(ds::DataFrameServer)
    ds.is_running = true
    start(ds.app, ds.port)
    ds.is_running = false
end

##
# CACHING
const _table_cache = Dict{String,DataFrame}()
function get_table(data_dir::String, csv::String)
    haskey(_table_cache, csv) && return _table_cache[csv]

    csvfile = joinpath(data_dir, string(csv, ".csv"))
    #println("loking for file [$csvfile]")
    !isfile(csvfile) && return nothing
    _table_cache[csv] = readtable(csvfile)
end

##
# METADATA 
function meta(df::DataFrame)
    mdict = Dict{String,Any}()
    mdict["nrows"] = nrow(df)

    cn = colnames(df)
    mdict["columns"] = cn

    colmetas = Dict{String,Any}()
    for c in 1:ncol(df)
        colmetas[cn[c]] = column_meta(Dict{String,Any}(), df[c])
    end
    mdict["colmetas"] = colmetas
    return mdict
end

function column_meta{T<:Number}(dict::Dict{String,Any}, dv::AbstractDataVector{T})
    if all(isna(dv))
        dict["allna"] = true
        return
    end
    filtered = float(removeNA(dv))
    qs = quantile(filtered, [0, .25, .5, .75, 1])
    statNames = ["min", "qu1", "median", "mean", "qu3", "max"]
    statVals = [qs[1:3], mean(filtered), qs[4:5]]
    for i = 1:6
        dict[statNames[i]] = statVals[i]
    end
    nas = sum(isna(dv))
    dict["na_count"] = nas
    dict["na_percent"] = round(nas*100/length(dv))
    return dict
end
function column_meta{T}(dict::Dict{String,Any}, dv::AbstractDataVector{T})
    dict["is_pooled"] = isa(dv, PooledDataVector)
    dict["length"] = length(dv)
    dict["type"] = (isa(dv, PooledDataVector) ? "Pooled " : "") * string(eltype(dv))
    dict["na_count"] = sum(isna(dv))
    dict["na_percent"] = round(sum(isna(dv))*100/length(dv), 2)
    dict["unique_count"] = length(unique(dv))
    return dict
end


##
# FORMATTING
function as_rows(df::DataFrame)
    nr = nrow(df)
    cnames = colnames(df)
    res_arr = Array(Dict{String,Any}, nr)
    for idx in 1:nr
        row_dict = Dict{String,Any}()
        for cidx in 1:length(cnames)
            cn = cnames[cidx]
            row_dict[cn] = df[cidx][idx]
        end
        res_arr[idx] = row_dict
    end
    res_arr
end

function as_csv(df::DataFrame)
    iob = IOBuffer()
    printtable(iob, df)
    takebuf_string(iob)
end

function json_resp(resp_code::Int, resp_msg::String, data::Any=nothing, compact::Bool=false)
    resp = Dict{String, Any}()
    resp["code"] = resp_code
    resp["msg"] = resp_msg
    if nothing != data
        if isa(data, DataFrame) 
            resp["data"] = compact ? data : as_rows(data)
        else
            resp["data"] = data
        end
    end
    JSON.json(resp)
end

end # module

