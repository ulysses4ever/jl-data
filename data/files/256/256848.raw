module FRED

#  const API_KEY = "e3a3139530d8a6ef68e36b8b12bbc2f7"  # Please dont use this API for nefarious purposes, if you want to do something nefarious use your own api key
const BASE_URL = "http://api.stlouisfed.org/fred/"

using Requests
using JSON
using Datetime
using TimeSeries

import Base.show

export series_titles, Series

get_request(uri, query) = get("$(BASE_URL)$(uri)"; query=Base.merge({"api_key"=>API_KEY, "file_type"=>"json"}, query))  # request with API_KEY and file_type

function series_titles(series_ids::Array{ASCIIString, 1})
    # returns titles of series
    series = map(Series, series_ids)
    return [srs.title for srs in series]
end

type Series
    id::String
    realtime_start::String
    realtime_end::String
    title::String
    observation_start::String
    observation_end::String
    frequency::String  # 
    units::String
    seasonal_adjustment::String
    last_updated::String
    popularity::String
    notes::String
    time_series::TimeArray
    function Series(res::Requests.Response; get_data=false)
        println(res)
        json = JSON.parse(res.data)
        println(json)
        println(get_data)
        if get_data
            obs_res = get_request("series/observations", {"series_id"=>json["seriess"][1]["id"]})
            obs_json = JSON.parse(obs_res.data)
            time_series = TimeArray(Date[date(obs["date"]) for obs in obs_json["observations"]], Float64[float(obs["value"]) for obs in obs_json["observations"]], ["title"])
        else
            time_series = TimeArray(Date[date(1970, 1, 1)], [0], [""])
        end
        return new(json["seriess"][1]["id"],
            json["realtime_start"],
            json["realtime_end"],
            json["seriess"][1]["title"],  # seriess is plural for series?
            json["seriess"][1]["observation_start"],
            json["seriess"][1]["observation_end"],
            json["seriess"][1]["frequency"],
            json["seriess"][1]["units"],
            json["seriess"][1]["seasonal_adjustment"],
            json["seriess"][1]["last_updated"],
            json["seriess"][1]["popularity"],
            json["seriess"][1]["notes"],
            time_series
        )
    end
end
Series(series_id::String; get_data=false) = Series(get_request("series", {"series_id"=>series_id}); get_data=get_data)
import Base.convert, Base.show, Base.map
show(series::Series) = "$(series.id): $(series.title)"
convert(::Type{String}, num::Int64) = string(num)  # no idea why this conversion method is necessary but one day I'll find out

function get_data(series_id::String)
    obs_res = get_request("series/observations", {"series_id"=>series_id})
    obs_json = JSON.parse(obs_res.data)
    time_series = TimeArray(Date[Date(obs["date"]) for obs in obs_json["observations"]], Float64[float(obs["value"]) for obs in obs_json["observations"]], [series_id])
    return time_series
end
function get_data(series::Series)
    series.time_series = get_data(series.id)
end

#series_ids = ["GNPCA", "GDPC1"]
#seriess = [Series(id) for id in series_ids]

function read_json(stream)
    json_str = JSON.parse(readall(stream))
    [obs["date"] for obs in json_str["observations"]]
end

end # module
