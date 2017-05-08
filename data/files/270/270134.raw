module Goose

using Reexport

@reexport using Mongo
@reexport using LibBSON

export GooseDB, GooseCollection, insert

bsontypes = map((m) -> begin
  length(m.sig.types) > 2 ? m.sig.types[3] : nothing
end, methods(LibBSON.append))

bsontypes = filter((x) -> x != nothing, bsontypes)

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

  function GooseDB(cli, name)
    dbmap[name] = GooseCollection[]
    new(cli, name)
  end
end

type GooseCollection
  dbname::AbstractString
  typ::DataType
  coll::MongoCollection

  function GooseCollection(dbname, typ, coll)
    hasid = false
    for f in fieldnames(typ)
      if f == :_id
        hasid = true
      end
    end
    @assert hasid "Types need to have an _id::BSONOID field"
    c = new(dbname, typ, coll)
    push!(dbmap[dbname], c)
    c
  end
end

GooseCollection(db::GooseDB, typ::DataType, str::AbstractString) =
  GooseCollection(db.name, typ, MongoCollection(db.cli, db.name, str))

# Keep track of instantiated collections
dbmap = Dict{AbstractString,Array{GooseCollection,1}}()

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

function is_bsontype(it::Any)
  typ = typeof(it)
  is = false
  for t in bsontypes
    if typ <: t
      is = true
    end
  end
  is
end

function jl2bson(obj::Any)
  bso = BSONObject()
  for k in fieldnames(obj)
    if is_bsontype(obj.(k))
      append(bso, string(k), obj.(k))
    else
      for (db, colls) in dbmap
        for c in colls
          if c.typ == typeof(obj.(k))
            append(bso, string(k), obj.(k)._id)
          end
        end
      end
    end
  end
  bso
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
