module InfluxDB

using HTTPClient.HTTPC
using JSON

export InfluxDBClient

# package code goes here
type InfluxDBClient
  host::String
  port::Int64
  username::String
  password::String
  database::String
  #ssl::Bool
  #verifyssl
  #udp
  #scheme
  baseurl::String
  headers::Dict{String, String}

  function InfluxDBClient(host::String, port::Int64, username::String, password::String, database::String)
	baseurl = "$host:$port"
	headers = {"Content-Type" => "application/json"}
	new(host, port, username, password, database, baseurl, headers)
  end

end # InfluxDBClient





end # module
