type DBRef
  ref::AbstractString
  id::BSONOID
  db::AbstractString
end

function bson(dbr::DBRef)
  bso = BSONObject()
  append(bso, "\$ref", dbr.ref)
  append(bso, "\$id", dbr.id)
  append(bso, "\$db", dbr.db)
  bso
end
