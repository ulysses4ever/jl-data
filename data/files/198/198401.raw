using JSON

function up(conn)
  try
    write(conn, "up\n")
  catch err
    print $err
    close(conn)
  end
end

function down(conn)
  try
    write(conn, "down\n")
  catch err
    print $err
    close(conn)
  end
end

function left(conn)
  try
    write(conn, "left\n")
  catch err
    print $err
    close(conn)
  end
end

function right(conn)
  try
    write(conn, "right\n")
  catch err
    print $err
    close(conn)
  end
end

function bomb(conn)
  try
    write(conn, "bomb\n")
  catch err
    print $err
    close(conn)
  end
end


type Response
  Turn::Int64
  TurnDuration::Int64
  Name::UTF8String
  X::Int64
  Y::Int64
  LastX::Int64
  LastY::Int64
  Bombs::Int64
  MaxBomb::Int64
  MaxRadius::Int64
  Alive::Bool
  GameObject::Dict{UTF8String, UTF8String}
  Message::UTF8String
  Board::Array{UTF8String,2}
  
  Response() = new(0,0,"",0,0,0,0,0,0,0,false,Dict{UTF8String, UTF8String}(),"", Array(UTF8String,51,23))
end

type Jason
  Name::String

  Jason() = new("")
end

GAMEIP = "0.0.0.0"
GAMEPORT = 40000
 
function tparse(json::Dict{String,Any})
    r = Response()
    r.Turn = json["Turn"]
    r.TurnDuration = json["TurnDuration"]
    r.Name = json["Name"]
    r.X = json["X"]
    r.Y = json["Y"]
    r.LastX = json["LastX"]
    r.LastY = json["LastY"]
    r.Bombs = json["Bombs"]
    r.MaxBomb = json["MaxBomb"]
    r.MaxRadius = json["MaxRadius"]
    r.Alive = json["Alive"]
    r.GameObject["Name"] = json["GameObject"]["Name"]
    r.Message = json["Message"]
    #r.Board = json["Board"]
    for i = 1:51
      for j = 1:23
        r.Board[i,j] = json["Board"][i][j]["Name"]
      end
    end

    return r
end

try
	#client = connect(8080)
  #print(readline(client))
  #up(client)

  client = connect (GAMEIP, GAMEPORT)

  #gamestate = JSON.parse(readline(client))
  #gamestate = Response()
  gamestate = tparse(JSON.parse(readline(client)))

  #gamestate = reshape(1:16, 4, 4)
  
	#print(gamestate, "\n")

  #gamestate[1,2] = 19

  print(gamestate, "\n")

catch err
  print("connection ended with error $err\n")
end


