module Widukind

using Requests
using JSON
using TimeSeries
using Dates
using DataFrames

# For the third argument of get_series()
export TimeArray, DataFrame

include("rest.jl")
include("timeseries.jl")

# Default implementation of method get_series()
get_series(db, series_id; server = default_server) = get_series(db, series_id, TimeArray; server = default_server)

export list_categories, get_category, list_series, get_series

end # module
