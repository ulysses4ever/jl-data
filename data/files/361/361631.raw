@require "jkroso/parse-json" parse

const codes = Dict{String,Uint16}()
const messages = Dict{Uint16,String}()

open(joinpath(@dirname(), "deps/codes.json")) do io
  for (key, msg) in parse(io)
    code = uint16(key)
    messages[code] = msg
    codes[msg] = code
  end
end

@test messages[404] == "Not Found"
@test codes["Not Found"] == 404
