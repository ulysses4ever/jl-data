module Goose

using Reexport

@reexport using Mongo
@reexport using LibBSON

export GooseDB, GooseCollection, insert

include("DBRef.jl")
include("bson.jl")


type GooseDB
  cli::MongoClient
  name::AbstractString

  function GooseDB(cli, name)
    dbmap[name] = GooseCollection[]
    new(cli, name)
  end
end

type GooseCollection
  name::AbstractString
  dbname::AbstractString
  typ::DataType
  coll::MongoCollection

  function GooseCollection(name, dbname, typ, coll)
    hasid = false
    for f in fieldnames(typ)
      if f == :_id
        hasid = true
      end
    end
    @assert hasid "Types need to have an _id::BSONOID field"
    c = new(name, dbname, typ, coll)
    push!(dbmap[dbname], c)
    c
  end
end

GooseCollection(db::GooseDB, typ::DataType, str::AbstractString) =
  GooseCollection(str, db.name, typ, MongoCollection(db.cli, db.name, str))

# Keep track of instantiated collections
dbmap = Dict{AbstractString,Array{GooseCollection,1}}()

function insert(gc::GooseCollection, obj::Any)
  @assert typeof(obj) == gc.typ
  Mongo.insert(gc.coll, jl2bson(obj))
end

type GooseCursor
  typ::DataType
  cur::MongoCursor
end


Base.start(gc::GooseCursor) = begin
  start(gc.cur)
  false
end

Base.done(gc::GooseCursor, state) = begin
  done(gc.cur, nothing)
  state
end

Base.next(gc::GooseCursor, state) = begin
  doc, _ = next(gc.cur, nothing)
  bson2jl(doc, gc.typ), false
end

import Base.find
Base.find(gc::GooseCollection, x...; kwargs...) = begin
  cur = find(gc.coll, x...; kwargs...)
  GooseCursor(gc.typ, cur)
end

end # module
