module KnowedMimeTypes

export get_mime, MIMETYPES, MimeTypes

type MimeTypes
	data

	MimeTypes(data) = new(data)
	MimeTypes() = new(Void)
end

include("mimetypes.jl")		

const MIMETYPES = MimeTypes(MIMETYPES_DICT)

Base.get(mt::MimeTypes, ext::AbstractString, default=Void) = Base.get(mt.data, ext, default)
get_mime(mt::MimeTypes, ext::AbstractString, default=Void) = Base.get(mt, ext, default)
get_mime(ext::AbstractString, default=Void) = Base.get(MIMETYPES, ext, default)

end # module
