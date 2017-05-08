module ThingSpeak
using Requests
immutable TSChannel
  writekey::ASCIIString
end
const updateapiurl = "https://api.thingspeak.com/update"
const updateheaders = {"Content-type"=> "application/x-www-form-urlencoded","Accept"=> "text/plain"}
defaultchannel = TSChannel("")
setdefaultchannel(s::ASCIIString) = (global defaultchannel = TSChannel(s))

function updatedata(channel::TSChannel, status::ASCIIString, fields...)
  data = "key=$(channel.writekey)"
  for (i,f) in enumerate(fields)
    data *= "&field$i=$f"
  end
  if status != ""
    length(status)>140 && error("status is limited to 140 characters in ThingSpeak API")
    data *= "&status=$status"
  end
  data
end
function tsupdate(fields::Number...;status::ASCIIString="", channel::TSChannel=defaultchannel)
  response = post(updateapiurl, data=updatedata(channel, status, fields...), headers=updateheaders)
end
tssuccess(r::Requests.Response) = r.data != "0"

export tsupdate, tssuccess
end # module

