# Misc utils

getset(coll, key, default) = coll[key] = get(coll, key, default)

# Method call syntax

tilde{V}(a::Associative{Symbol, V}, b::Symbol) = a[b]
tilde(a, b, args) = tilde(a, b)(args...)

macro ~ (args...)
  tildify(a, b) =
    isexpr(b, Symbol) ? :(tilde($a, $(Expr(:quote, b)))) :
    isexpr(b, :call) && isexpr(b.args[1], Symbol) ? :(tilde($a, $(Expr(:quote, b.args[1])),
                                                            [$(map(esc, b.args[2:end])...)])) :
    error("Bad ~ syntax")

  tildify(a, xs...) = reduce(tildify, esc(a), xs)

  tildify(args...)
end

# Vars

import Base: isdefined, fetch, show

immutable Var
  mod::Module
  name::Symbol
end

Var(name) = Var(current_module(), name)

valid(v::Var) = isdefined(v.mod, v.name)

fetch(v::Var) = v.mod.(v.name)
