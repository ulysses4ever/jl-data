module MethImp

using Lazy

import Base: show

include("weakset.jl")
include("meta.jl")

# Methods

typealias Method Symbol

# Implementations

typealias Implementation Function

name(f::Implementation) = f.env.name
triggers(f::Implementation) = Set([name(f)])
λ(f::Implementation) = f

# Objects

type Class
#   var::Var
  imps::Set{Implementation}
  tags::Set{Symbol}
  init::Function
end

typealias MethodSet Dict{Method, Set{Implementation}}

type Object{T}
  methods::MethodSet
  tags::Set{Symbol}
  data::T
end

# Construction & Manipulation

typealias Objects WeakSet{Object}

function collectmethods(imps)
  methods = MethodSet()
  for imp in imps
    for method in triggers(imp)
      push!(getset(methods, method, Set{Implementation}()), imp)
    end
  end
  return methods
end

function Object(class::Class, args...)
  Object(collectmethods(class.imps),
         class.tags,
         class.init(args...))
end

function call(obj::Object, method, args...)
  imps = get(obj.methods, method, Set{Implementation}())
  for imp in imps
    imp(obj, args...)
  end
end

tilde(object::Object, method::Symbol) = (args...) -> call(object, method, args...)
tilde(object::Object, method::Symbol, args) = call(object, method, args...)

# Testing

selfie(self) = println(self)

end # module
