module ArgMinimist

export parse_args, parse_args!, parse_named_args, parse_named_args!

intRegex = r"^\d+$"
floatRegex = r"^\d*\.\d+$"
argNameRegex = r"^(\-*)(\w+)$"

function get_arg_value(arg::String)
  if ismatch(intRegex, arg)
    return parseint(arg)
  elseif ismatch(floatRegex, arg)
    return parsefloat(arg)
  else
    return arg
  end
end

function parse_args()
  parse_args(ARGS)
end

function parse_args!(keyword::Dict{Symbol,Any})
  parse_args!(ARGS, keyword)
end
function get_arg_name(arg::String)
  symbol(match(argNameRegex, arg).captures[2])
end

function parse_args{T<:String}(args::Vector{T})
  keyword = Dict{Symbol,Any}()
  parse_args!(args, keyword)
end

function parse_args!{T<:String}(args::Vector{T}, keyword::Dict{Symbol,Any})

  no_prefix = "--no"
  yes_prefix = "--with"

  positional = Any[]

  pos = 1

  while pos <= length(args)

    argp = args[pos]

    if beginswith(argp, "-")

      if beginswith(argp, "--")

        if contains(argp, "=")
          # This is a compound keyword argument
          argname, argval = split(argp,"=")
          keyword[ get_arg_name(argname) ] = get_arg_value(argval)
        else

          if beginswith(argp, no_prefix)
            keyword[ get_arg_name(replace(argp, no_prefix, "")) ] = false
          elseif beginswith(argp, yes_prefix) || pos == length(args) || beginswith(args[pos+1],"-")
            # This is a true flag if any of these are true:
            #   has the correct prefix
            #   is the last argument
            #   is followed by a keyword argument
            keyword[ get_arg_name(replace(argp, yes_prefix,"")) ] = true
          else
            # Ok, this is the name value and the next argument
            # is the actual argument value
            keyword[ get_arg_name(argp) ] = get_arg_value(args[pos+1])
            pos += 1
          end
        end

      else

        # Process as options to set
        for k in replace(argp,"-","")
          keyword[ symbol(k) ] = true
        end

      end
    else
      push!(positional, get_arg_value(argp))
    end

    pos += 1
  end

  return positional, keyword
end

function parse_named_args{T<:String}(names::Vector{T})
  parse_named_args(names, ARGS, Dict{Symbol,Any}())
end

function parse_named_args{T<:String}(names::Vector{T}, args::Vector{T})
  keyword = Dict{Symbol,Any}()
  parse_named_args!(names,args,keyword)
end

function parse_named_args!{T<:String}(names::Vector{T}, args::Vector{T}, keyword::Dict{Symbol,Any})

  positional, keyword = parse_args!(args, keyword)
  symbols = map(symbol, names)
  match_symbols = filter((s)-> !haskey(keyword, s), symbols)

  if length(match_symbols) > length(positional)

    println("\n\tExpecting arguments: ",join(names, " "))
    exit(-1)

  else

    for (s,v) in zip(match_symbols, positional)
      keyword[s] = v
    end

    if length(match_symbols) < length(positional)
      positional = positional[length(match_symbols)+1:end]
    else
      # Empty because all were matched
      positional = Any[]
    end
  end

  return positional, keyword
end

end # module
