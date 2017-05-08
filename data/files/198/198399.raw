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

type Cell
  Base::Dict{UTF8String, UTF8String}
  zLayers::Array{Dict{UTF8String, UTF8String},1}
  X::Int64
  Y::Int64

  Cell() = new(Dict{UTF8String, UTF8String}(), [], 0, 0)
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
  Message::String
  Board::Array{Cell,2}
  
  Response() = new(0,0,"",0,0,0,0,0,0,0,false,Dict{UTF8String, UTF8String}(),"", Array(Cell,2,2))
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
  
	print(gamestate.Name, "\n")

catch err
  print("connection ended with error $err\n")
end


