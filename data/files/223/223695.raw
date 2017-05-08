module SparkCloud

using HTTPClient.HTTPC
using JSON

export SparkCore, callfunction, readvariable, flashtinker, Tinker, @sparkfunction, @sparkvariable, info, cores, AccessToken, lstokens, rmtoken

const CLOUD_ERRORS = Dict{Int,String}({
400=>"Bad Request - Your request is not understood by the Core, or the requested subresource (variable/function) has not been exposed.",
401=>"Unauthorized - Your access token is not valid.",
403=>"Forbidden - Your access token is not authorized to interface with this Core.",
404=>"Not Found - The Core you requested is not currently connected to the cloud.",
408=>"Timed Out - The cloud experienced a significant delay when trying to reach the Core.",
500=>"Server error - Unexpected error from Spark Cloud API"
})

const HTTP_ERRORS = Dict{Int,String}({
400=>"Bad Request",
401=>"Unauthorized",
403=>"Forbidden",
404=>"Not Found",
408=>"Timed Out",
500=>"Server error"
})

function handle_error(fn::Function, response::Response, ERRS::Dict{Int,String})
  if response.http_code==200
    fn()
  else
    explain = get(ERRS, response.http_code, "Unknown Error")
    error("$(response.http_code) $explain\n$(bytestring(response.body))")
  end
end

type AccessToken
  value::String
  AccessToken(value::String) = new(value)
end

function authorization(username::String, password::String)
  options = RequestOptions()
  auth = base64("$username:$password")
  push!(options.headers, ("Authorization", "Basic $auth"))
  return options
end

function AccessToken(username::String, password::String, temporary::Bool=true)
  data = {"grant_type"=>"password",
          "username"=>username,
          "password"=>password}
  response = post("https://api.spark.io/oauth/token",
                  data, authorization("spark","spark"))
  this = handle_error(response, HTTP_ERRORS) do
    AccessToken(JSON.parse(bytestring(response.body))["access_token"])
  end
  temporary && finalizer(this,
                         function (token::AccessToken)
                           rmtoken(username, password, token)
                         end)
  return this
end

function Base.show(io::IO, token::AccessToken)
  print(io, "AccessToken(\""*
            ("x"^length(token.value[1:end-4])*token.value[end-3:end])*
            "\")")
end

function lstokens(username::String, password::String)
  response = get("https://api.spark.io/v1/access_tokens",
                 authorization(username, password))
  retval = handle_error(response, HTTP_ERRORS) do 
    JSON.parse(bytestring(response.body))
  end
  for row in retval
    row["token"] = AccessToken(row["token"])
  end
  return retval
end

function rmtoken(username::String, password::String, token::AccessToken)
  response = delete("https://api.spark.io/v1/access_tokens/$(token.value)",
                    authorization(username, password))
  return handle_error(response, HTTP_ERRORS) do
    JSON.parse(bytestring(response.body))["ok"]
  end
end

immutable SparkCore
  deviceid::String
  accesstoken::AccessToken
  SparkCore(deviceid::String, token::AccessToken) = new(deviceid, token)
  SparkCore(deviceid::String, token::String) = new(deviceid, AccessToken(token))
  SparkCore(deviceid::String, uid::String, pwd::String) = new(deviceid, AccessToken(uid, pwd))
end

Base.show(io::IO, core::SparkCore) = print(io,"SparkCore(\"$(core.deviceid)\")")

function authorization(token::AccessToken)
  options = RequestOptions()
  push!(options.headers, ("Authorization", "Bearer $(token.value)"))
  return options
end

authorization(core::SparkCore) = authorization(core.accesstoken)

function cores(token::AccessToken)
  response = get("https://api.spark.io/v1/devices", authorization(token))
  cores = handle_error(response, CLOUD_ERRORS) do
    JSON.parse(bytestring(response.body))
  end
  retval = Dict{String,Dict{String,Any}}()
  for info in cores
    key = pop!(info, "name")
    info["id"] = SparkCore(info["id"], token)
    retval[key] = info
  end
  return retval
end

cores(core::SparkCore) = cores(core.accesstoken)

function info(core::SparkCore)
  response = get("https://api.spark.io/v1/devices/$(core.deviceid)",
                 authorization(core))
  retval = handle_error(response, CLOUD_ERRORS) do
    JSON.parse(bytestring(response.body))
  end
  pop!(retval, "id")
  return retval
end

function callfunction(core::SparkCore, func::String, params...)
  data = {"params"=>join(params,",")}
  response = post("https://api.spark.io/v1/devices/$(core.deviceid)/$func",
                  data, authorization(core))
  return handle_error(response, CLOUD_ERRORS) do
    JSON.parse(bytestring(response.body))["return_value"]
  end
end

function readvariable(core::SparkCore, var::String)
  response = get("https://api.spark.io/v1/devices/$(core.deviceid)/$var",
                 authorization(core))
  return handle_error(response, CLOUD_ERRORS) do
    return JSON.parse(bytestring(response.body))["result"]
  end
end

function flashtinker(core::SparkCore)
  response = put("https://api.spark.io/v1/devices/$(core.deviceid)",
                 {"app"=>"tinker"}, authorization(core))
  return handle_error(response, CLOUD_ERRORS) do
    JSON.parse(bytestring(response.body))
  end
end

macro sparkfunction(name::Symbol, args::Symbol...)
  retval = quote
    function $(esc(name))(core::SparkCore)
      callfunction(core, $(string(name)))
    end
  end

  if length(args)>0
    append!(retval.args[2].args[1].args, Any[args...])
    append!(retval.args[2].args[2].args[2].args, Any[args...])
  end
  
  retval
end

macro sparkvariable(name::Symbol)
  quote
    function $(esc(name))(core::SparkCore)
      readvariable(core, $(string(name)))
    end
  end
end

module Tinker
import SparkCloud.@sparkfunction
@sparkfunction digitalwrite pin value
@sparkfunction analogwrite pin value
@sparkfunction digitalread pin
@sparkfunction analogread pin
end

end

