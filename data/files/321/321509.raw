#!/usr/bin/julia

println("Simple Echo Server")
println("-------------------------")

@sync begin

    server = listen(8081)
    while true

      #blocks until connection is accepted
      conn = accept(server)

      #starts new coroutine
      @async begin
        try
         while true
            #blocks for reading one full line
            line = readline(conn)
            write(conn,line)
            if rstrip(line)==""
                quit()
            end
          end
        catch err
          print("connection ended with error $err")
        end
      end

    end
end

#nc localhost 8081

