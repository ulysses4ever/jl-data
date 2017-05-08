require("src/mem.jl")

@async begin

    #server = listen(34440)

    #sock = accept(server)
    #println("Connection recieved")

    try
        @async Handler.startStreaming(open("files/data.example.csv")#=, sock=#)
    catch e
        println("Client disconected: $e")
    end
end

wait()
