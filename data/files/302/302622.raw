include("opus.jl")

a = UdpSocket()
port = 53354
ip = ip"0.0.0.0"
fs = 48000
channels = 1
enc = Opus.encoder_create(fs, channels)
try
    if bind(a,ip,port)
        data = recv(a)
        println(data)
    end
catch
    # catch Ctrl-C
end
Opus.encoder_destroy(enc)
close(a)
