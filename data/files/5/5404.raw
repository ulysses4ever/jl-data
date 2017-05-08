using ThingSpeak
using Base.Test

# write your own tests here
using ThingSpeak
global apikey
try
  apikey = ENV["THINGSPEAK_API_KEY"]
  println("Loading API Key from environment variable THINGSPEAK_API_KEY")
catch
  println("Loading API Key from testingapikey file")
  apikey = open("testingapikey") do f
    strip(readline(f))
  end
end

ThingSpeak.setdefaultchannel(apikey) #this is technically a secret but its a dedicated channel for testing
response = tsupdate(1,2,3,status="ran runtests.jl for ThingSpeak.jl")
tssuccess(response)
