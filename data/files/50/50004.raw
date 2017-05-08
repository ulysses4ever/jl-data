# type Class
#   tags::Set{Any}
#   imps::Set{Any}
#   init::Function
# end

type Object{T}
  tags::Set{Any}
  methods::Methods
  data::T
end

tags(o::Object) = o.tags
methodset(o::Object) = o.methods
data(o::Object) = o.data

Object{T}(data::T) = Object{T}(Set(), Methods(), data)
Object() = Object(@d())

function refresh!(o::Object)
  o.methods = methodset(o.tags)
  return
end

function addtags(o, ts...)
  for t in ts
    push!(tags(o), t)
  end
  refresh!(o)
end

# o = Object(@d())

# addtags(o, :julia, :editor)

# o

# typealias Objects WeakSet{Any}

# function Object(class::Class, args...)
#   Object(collectmethods(class.imps),
#          class.tags,
#          class.init(args...))
# end

# function call(obj::Object, method, args...)
#   imps = get(obj.methods, method, Set{Implementation}())
#   for imp in imps
#     imp(obj, args...)
#   end
# end

# tilde(object::Object, method::Symbol) = (args...) -> call(object, method, args...)
# tilde(object::Object, method::Symbol, args) = call(object, method, args...)
