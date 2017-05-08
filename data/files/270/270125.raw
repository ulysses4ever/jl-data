bsontypes = map((m) -> begin
  length(m.sig.types) > 2 ? m.sig.types[3] : nothing
end, methods(LibBSON.append))

bsontypes = filter((x) -> x != nothing, bsontypes)

function is_bsontype(dt::DataType)
  is = false
  for t in bsontypes
    if dt <: t
      is = true
    end
  end
  is
end

function is_bsontype(it::Any)
  typ = typeof(it)
  is_bsontype(typ)
end

function isdbref(bso::BSONObject)

end

function bson2jl(doc::BSONObject, typ::DataType)
  fields = map((f) -> begin
    it = doc[string(f[1])]
    @show f[1]
    if is_bsontype(f[2])
      it
    else
      if typeof(it) == BSONObject && isdbref(it)

      end
    end
  end, zip(fieldnames(typ), typ.types))
  typ(fields...)
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
            ref = DBRef(c.name, obj.(k)._id, c.dbname)
            append(bso, string(k), bson(ref))
          end
        end
      end
    end
  end
  bso
end

json_serializers = Dict{DataType,Function}(
  Real => identity,
  AbstractString => identity,
  DateTime => (d) -> Dates.format(d, ISODateTimeFormat),
  Date => (d) -> Dates.format(d, ISODateFormat),
  BSONOID => string,
  Any => (a) -> error("Type $(typeof(a)) not supported")
)

function json_convert(t::Type, o::Any)
  if haskey(json_serializers, t)
    return json_serializers[t](o)
  else
    return json_convert(super(t), o)
  end
end

json_convert(o) = json_convert(typeof(o), o)

function jl2json(obj::Any)
  d = Dict{Symbol,Any}()
  for k in fieldnames(obj)
    d[k] = json_convert(obj.(k))
  end
  d
end
