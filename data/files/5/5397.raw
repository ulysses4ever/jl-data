using ThingSpeak
using Base.Test

# write your own tests here
using ThingSpeak
ThingSpeak.setdefaultchannel("YBOH2D5UMGPJ50LB") #this is technically a secret but its a dedicated channel for testing
response = tsupdate(1,2,3,status="ran runtests.jl for ThingSpeak.jl")
tssuccess(response)
