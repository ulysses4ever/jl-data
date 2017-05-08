using JSON

function up(conn)
  try
    write(conn, "up\n")
  catch err
    print $err
  end
end

function down(conn)
  try
    write(conn, "down\n")
  catch err
    print $err
  end
end

function left(conn)
  try
    write(conn, "left\n")
  catch err
    print $err
  end
end

function right(conn)
  try
    write(conn, "right\n")
  catch err
    print $err
  end
end

function bomb(conn)
  try
    write(conn, "bomb\n")
  catch err
    print $err
  end
end

server = listen(8080)
while true
  conn = accept(server)
  @async begin
    try
      while true
        line = readline(conn)
        up(conn)
        down(conn)
        left(conn)
        right(conn)
        bomb(conn)
      end
    catch err
      print $err
    end
  end
end