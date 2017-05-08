a = UdpSocket()
port = 53354
ip = ip"0.0.0.0"
try
    if bind(a,ip,port)
        data = recv(a)
        println(data)
    end
catch
    # catch Ctrl-C
end
close(a)
