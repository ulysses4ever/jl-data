using ThingSpeak
using Base.Test

# write your own tests here
using ThingSpeak
function loadsecret(name="TEST_SECRET")
  if name in keys(ENV)
    println("Loading $name from environment variable")
    return ENV[name]
  else
    println("Loading $name from file")
    return open(name) do f
      strip(readline(f))
    end
  end
end

ThingSpeak.setdefaultchannel(loadsecret("THINGSPEAK_API_KEY")) #this is technically a secret but its a dedicated channel for testing
response = tsupdate({3=>3.5},status="ran runtests.jl for ThingSpeak.jl")
response = tsupdate(1.1,2.2)

tssuccess(response)
