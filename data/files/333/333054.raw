module Goose

using Reexport

@reexport using Mongo

export GooseCollection, insert

# Convert Julia type to Dict
function dict(obj::Any)
  ctyp = promote_type((typeof(obj).types)...)
  d = Dict{ASCIIString,ctyp}()
  for f in fieldnames(obj)
    d[string(f)] = obj.(f)
  end
  d
end

type GooseCollection
  typ::DataType
  coll::MongoCollection
end

function insert(gc::GooseCollection, obj::Any)
  @assert typeof(obj) == gc.typ
  Mongo.insert(gc.coll, dict(obj))
end

end # module
