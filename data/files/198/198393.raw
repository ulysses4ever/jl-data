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
  Base::Dict{String, String}
  zLayers::Array{Dict{String, String}}
  X::Int
  Y::Int
end

type Board
  Array{Cell}
  Array{Dict{String, String}}
  Array{Cell}
end


type Response
  Turn::Int
  TurnDuration::Int
  Name::String
  X::Int
  Y::Int
  LastX::Int
  LastY::Int
  Bombs::Int
  MaxBomb::Int
  MaxRadius::Int
  Alive::Bool
  GameObject::Dict{String, String}
  Message::String
  Board::Board
  
  Response() = new(0,0,"",0,0,0,0,0,0,0,false,Dict{String, String}(),"",Board())
end

GAMEIP = "0.0.0.0"
GAMEPORT = 40000

try
	client = connect(GAMEIP,GAMEPORT)
  gamestate = JSON.parse(readline(client))
	print(gamestate)

catch err
  print("connection ended with error $err\n")
end


