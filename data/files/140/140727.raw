# common functions used to solve rosalind problems

function strToIntArray(s::String, delim::String)
  map((s)->int64(s), split(s, delim))
end

function openOneLine(cb::Function, s::String)
  open(function (fileIO::IOStream)
    cb(readlines(fileIO)[1])
  end, s)
end



