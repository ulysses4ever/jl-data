@require "parse-json" parse

const codes = Dict{String,Uint16}()
const messages = Dict{Uint16,String}()

for (key, msg) in open(parse, "$(@dirname)/dependencies/statuses/codes.json")
  code = uint16(key)
  messages[code] = msg
  codes[msg] = code
end
