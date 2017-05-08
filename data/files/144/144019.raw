using KnowedMimeTypes
using Base.Test

# write your own tests here
@test get_mime(".pdf") != Void

mt = MimeTypes(Dict("a" => "b"))

@test get_mime(mt, "a") == "b"
