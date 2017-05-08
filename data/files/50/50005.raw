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

function refresh!(os)
  for o in os
    refresh!(o)
  end
end

typealias Objects WeakSet{Object}

const objsbytag = Dict{Any, Objects}()

bytag(tag) = Set{Any}(get(objsbytag, tag, []))
bytag(tag::TagAnd) = intersect(bytag(tag.a), bytag(tag.b))
bytag(tag::TagOr) = union(bytag(tag.a), bytag(tag.b))

refreshtag!(t) = refresh!(bytag(t))

function addtags(o, ts...)
  for t in ts
    push!(tags(o), t)
    push!(get!(objsbytag, t, Objects()), o)
  end
  refresh!(o)
end

function rmtags(o, ts...)
  for t in ts
    delete!(tags(o), t)
    delete!(get(objsbytag, t, Objects()), o)
  end
  refresh!(o)
end

function msg(obj::Object, method, args...)
  imps = get(obj.methods, method, Set())
  for imp in imps
    imp(obj, args...)
  end
end

tilde(object::Object, method::Symbol) = (args...) -> msg(object, method, args...)
tilde(object::Object, method::Symbol, args) = msg(object, method, args...)
