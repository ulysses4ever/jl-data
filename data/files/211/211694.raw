module DataServer

using Morsel
using JSON
using DataFrames

const app = Morsel.app()
#const data_dir = joinpath(Pkg.dir("DataServer"), "data")
const data_dir = "../data"

get(app, "/") do req, res
    join([
        "DataServer serves CSV data files and simple queries on them.",
        "Commands:",
        "list: list hosted data files"
        ],
    "<br/>")
end

get(app, "/list") do req, res
    JSON.json(readdir(data_dir))
end

route(app, GET, "/data/<csv::String>") do req, res
    csvname = routeparam(req, :csv)
    csvfile = joinpath(data_dir, string(csvname, ".csv"))
    dt = readtable(csvfile)
    JSON.json(dt)
end

route(app, GET, "/data/<csv::String>/<col::String>") do req, res
    csvname = routeparam(req, :csv)
    col = routeparam(req, :col)
    csvfile = joinpath(data_dir, string(csvname, ".csv"))
    dt = readtable(csvfile)
    JSON.json(dt)
end

get(app, "/*") do req, res
    res.headers["Status"] = 404
    render("404.ejl")
end

start(app, 8000)

end
