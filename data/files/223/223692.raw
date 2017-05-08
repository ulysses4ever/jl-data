module SparkCloud

using HTTPClient.HTTPC
using JSON

export SparkCore, functioncall, Tinker, @sparkfunction

immutable SparkCore
  deviceid::String
  accesstoken::String
  SparkCore(deviceid::String, accesstoken::String) = new(deviceid, accesstoken)
end

function SparkCore(deviceid::String, username::String, password::String)
  data = {"grant_type"=>"password",
          "username"=>username,
          "password"=>password}
  options = RequestOptions()
  push!(options.headers, ("Authorization", "Basic c3Bhcms6c3Bhcms="))
  response = post("https://api.spark.io/oauth/token", data, options)
  if response.http_code!=200
    error(bytestring(response.body))
  else
    accesstoken = JSON.parse(bytestring(response.body))["access_token"]
    return SparkCore(deviceid, accesstoken)
  end
end

function functioncall(core::SparkCore, func::String, params...)
  data = {"params"=>join(params,",")}
  options = RequestOptions()
  push!(options.headers, ("Authorization", "Bearer $(core.accesstoken)"))
  response = post("https://api.spark.io/v1/devices/$(core.deviceid)/$(func)",
                  data, options)
  if response.http_code!=200
    error(bytestring(response.body))
  else
    return JSON.parse(bytestring(response.body))["return_value"]
  end
end

macro sparkfunction(name::Symbol, args::Symbol...)
  retval = quote
    function $(esc(name))(core::SparkCore)
      functioncall(core, $(string(name)))
    end
  end

  if length(args)>0
    append!(retval.args[2].args[1].args, Any[args...])
    append!(retval.args[2].args[2].args[2].args, Any[args...])
  end
  
  retval
end

module Tinker
import SparkCloud.@sparkfunction
@sparkfunction digitalwrite pin value
@sparkfunction analogwrite pin value
@sparkfunction digitalread pin
@sparkfunction analogread pin
end

end # module
