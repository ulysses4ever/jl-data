module Goose

using Reexport

@reexport using Mongo
using LibBSON

export GooseDB, GooseCollection, insert

# Convert Julia type to Dict
function dict(obj::Any)
  ctyp = promote_type((typeof(obj).types)...)
  d = Dict{ASCIIString,ctyp}()
  for f in fieldnames(obj)
    d[string(f)] = obj.(f)
  end
  d
end

type GooseDB
  cli::MongoClient
  name::AbstractString
end

type GooseCollection
  typ::DataType
  coll::MongoCollection

  function GooseCollection(typ, coll)
    hasid = false
    for f in fieldnames(typ)
      if f == :_id
        hasid = true
      end
    end
    @assert hasid "Types need to have an _id::BSONOID field"
    new(typ, coll)
  end
end

GooseCollection(db::GooseDB, typ::DataType, str::AbstractString) =
  GooseCollection(typ, MongoCollection(db.cli, db.name, str))

function insert(gc::GooseCollection, obj::Any)
  @assert typeof(obj) == gc.typ
  Mongo.insert(gc.coll, dict(obj))
end

type GooseCursor
  typ::DataType
  cur::MongoCursor
end

function bson2jl(doc::BSONObject, typ::DataType)
  fields = map((f) -> doc[string(f)], fieldnames(typ))
  typ(fields...)
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
