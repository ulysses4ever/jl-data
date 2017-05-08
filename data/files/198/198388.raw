server = listen(8080)
while true
  conn = accept(server)
  @async begin
    try
      write(conn, "Hello Client!\n")
      while true
        line = readline(conn)

        # a sample JSON document
        json = """{"json":"hello"}\n\n"""
        write(conn, json)
      end
    catch err
      print ("$err\n")
    end
  end
end