# Read a csv file and anonymize its context for all cells except 
#   if it matches a date => leave it
#   if it matches a given set of entries => leave it.

# Create an anonymous version of a value, trying to keep its "format".

function anonymize_with_structure(s, yearshift = -17)
  s # Default is to not anonymize
end

function rand_char_of_same_type(c::Char)
  ic = int(c)
  if 'a' <= ic <= 'z'
    return char(rand(int('a'):int('z')))
  elseif 'A' <= ic <= 'Z'
    return char(rand(int('A'):int('Z')))
  elseif '0' <= ic <= '9'
    return char(rand(int('0'):int('9')))
  else
    return c
  end
end

function anonymize_with_structure(s::String, yearshift = -17)
  m = match(r"^(\d+)/(\d+)/(\d{4})\s+(\d+:\d+)", s)
  if m == nothing
    join(map((i) -> rand_char_of_same_type(s[i]), 1:length(s)))
  else
    currentyear = int(m.captures[3])
    newyear = string(currentyear - yearshift)
    "$(m.captures[1])/$(m.captures[2])/$(newyear) $(m.captures[4])"
  end
end

function anonymize_with_structure(i::Int64, yearshift = -17)
  numdigits = length(string(i))
  int(join([string(rand(1:9)), map((i) -> string(rand(0:9)), 2:numdigits)]))
end

function anonymize(df::DataFrame, exceptions = [], yearshift = -17)
  anondf = copy(df)
  anonmap = Dict{Any, Any}()
  numrows, numcols = size(df)
  for i in 1:numrows
    for j in 1:numcols
      value = anondf[i, j]
      if haskey(anonmap, value)
        newvalue = anonmap[value]
        println("Value $value already in hash, mapping to $newvalue")
      elseif in(value, exceptions)
        println("Exception for value $value")
        newvalue = value
      else
        newvalue = anonymize_with_structure(value, yearshift)
        anonmap[value] = newvalue
        println("Value $value not in hash, mapping to $newvalue")
      end
      anondf[i, j] = newvalue
    end
  end
  return anondf, anonmap
end