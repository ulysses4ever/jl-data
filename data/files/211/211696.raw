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
                "Commands:",
                "/list: list hosted data files",
                "/meta/<dataset> : provides column names, types, num rows etc.",
                "/q/<dataset> : dump all rows",
                "/q/<dataset>/<col_id>/<operator>/<col_val>: filter with operators like eq, gt, lt, contains, range",
                "/q/<dataset>?expr=<expression> : apply expression on dataset and return result"
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

        for cn in csvnames
            route(app, GET, "/q/$(cn)") do req, res
                try
                    println("read table")
                    csvfile = joinpath(data_dir, string(cn, ".csv"))
                    dt = readtable(csvfile)
                    query = urlparam(req, :expr)
                    if nothing == query
                        return JSON.json(dt)
                    else
                        println("query=[$(query)]")
                        println("query_to_expr=$(query_to_expr(query))")
                        expr = query_to_expr(query)
                        return JSON.json(dt[expr, :])
                    end
                catch ex
                    return string(ex)
                end
            end

            #route(app, GET, "/q/$(cn)/<col::String>") do req, res
            #    col = routeparam(req, :col)
            #    csvfile = joinpath(data_dir, string(cn, ".csv"))
            #    dt = readtable(csvfile)
            #    JSON.json(dt)
            #end
        end

        get(app, "/*") do req, res
            res.headers["Status"] = 404
            render("404.ejl")
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

end
