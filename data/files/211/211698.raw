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
                        "<li>/meta/[dataset] : provides column names, types, num rows etc.</li>" *
                        "<li>/q/[dataset] : dump all rows</li>" *
                        #"<li>/q/<dataset>/<col_id>/<operator>/<col_val>: filter with operators like eq, gt, lt, contains, range</li>" *
                        "<li>/q/[dataset]?q=[expression] : apply expression on dataset and return result</li>" *
                    "</ul>",
                "",
                "<b>Example Expressions:</b>" *
                    "<ul><li>Total__lte__100</li><li>(Sr__lt__100)__and__((Total__gt__600)__or__(Total__lt__200))</li></ul>"
                ],
            "<br/>")
        end

        csvnames = readdir(data_dir)
        for idx in 1:length(csvnames)
            csvnames[idx] = split(csvnames[idx], '.')[1]
        end

        get(app, "/list") do req, res
            JSON.json(csvnames)
        end

        route(app, GET, "/meta/<cn::String>") do req, res
            try
                cn = routeparam(req, :cn)
                dt = get_table(data_dir, cn)
                (nothing == dt) && (res.headers["Status"] = 404; return render("404.ejl"))
                iob = IOBuffer()
                write(iob, "<html><body><pre>")
                describe(iob, dt)
                write(iob, "</pre></body></html>")
                return takebuf_string(iob)
            catch ex
                return string(ex)
            end
        end

        route(app, GET, "/q/<cn::String>") do req, res
            try
                cn = routeparam(req, :cn)
                #println("read table: $cn")

                dt = get_table(data_dir, cn)
                (nothing == dt) && (res.headers["Status"] = 404; return render("404.ejl"))

                query = urlparam(req, :expr)
                if nothing == query
                    return JSON.json(dt)
                else
                    #println("query=[$(query)]")
                    #println("query_to_expr=$(query_to_expr(query))")
                    expr = query_to_expr(query)
                    return JSON.json(dt[expr, :])
                end
            catch ex
                return string(ex)
            end
        end

        #get(app, "/*") do req, res
        #    res.headers["Status"] = 404
        #    render("404.ejl")
        #end

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

const _table_cache = Dict{String,DataFrame}()
function get_table(data_dir::String, csv::String)
    haskey(_table_cache, csv) && return _table_cache[csv]

    csvfile = joinpath(data_dir, string(csv, ".csv"))
    println("loking for file [$csvfile]")
    !isfile(csvfile) && return nothing
    _table_cache[csv] = readtable(csvfile)
end

function as_json(df::DataFrame, compact::Bool=false)
end

end
