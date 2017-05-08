using DataStructures


# Given a Vector{V}
container_key{V}(::Type{Vector{V}})=Int
container_value{V}(::Type{Vector{V}})=V
container_construct{V}(::Type{Vector{V}})=Array(V, 0)
container_push{V}(c::Vector{V}, v::V)=begin push!(c, v); length(c) end
container_add{V}(c::Vector{V}, args...)=begin v=V(args...); push!(c, v); v end
container_add_key{V}(c::Vector{V}, args...)=begin push!(c, V(args...)); length(c) end
container_get{V}(c::Vector{V}, k::Int)=c[k]
container_set{V}(c::Vector{V}, k::Int, v::V)=begin c[k]=v; k end
container_iter{V}(c::Vector{V})=1:length(c)
container_value_iter{V}(c::Vector{V})=c

# Given a Deque
container_key{V}(::Type{Deque{V}})=V
container_value{V}(::Type{Deque{V}})=V
container_construct{V}(::Type{Deque{V}})=Deque{V}()
container_push{V}(c::Deque{V}, v::V)=begin push!(c, v); v end
container_add{V}(c::Deque{V}, args...)=begin v=V(args...); push!(c, v); v end
container_add_key{V}(c::Deque{V}, args...)=container_add(c, args...)
container_get{V}(c::Deque{V}, k::V)=k
container_set{V}(c::Deque{V}, k::V, v::V)=begin c[k]=v; v end
container_iter{V}(c::Deque{V})=c
container_value_iter{V}(c::Deque{V})=c

# Given a Set
container_key{V}(::Type{Set{V}})=V
container_value{V}(::Type{Set{V}})=V
container_construct{V}(::Type{Set{V}})=Set{V}()
container_push{V}(c::Set{V}, v::V)=begin push!(c, v); v end
container_add{V}(c::Deque{V}, args...)=begin v=V(args...); push!(c, v); v end
container_add_key{V}(c::Deque{V}, args...)=container_add(c, args...)
container_get{V}(c::Set{V}, k::V)=k
container_set{V}(c::Set{V}, k::V, v::V)=begin c[k]=v; v end
container_iter{V}(c::Set{V})=c
container_value_iter{V}(c::Set{V})=c

# Given a curried Dict, for instance:
# typealias IntDict{V} Dict{Int,V}
container_key{K,V}(::Type{Dict{K,V}})=K
container_value{K,V}(::Type{Dict{K,V}})=V
container_construct{K,V}(::Type{Dict{K,V}})=Dict{K,V}()
container_push{K,V}(c::Dict{K,V}, k::K, v::V)=begin c[k]=v; k end
container_add{K,V}(c::Dict{K,V}, k::K, args...)=(v=V(args...); c[k]=v; v)
container_add_key{K,V}(c::Dict{K,V}, k::K, args...)=(v=V(args...); c[k]=v; k)
container_get{K,V}(c::Dict{K,V}, k::K)=c[k]
container_set{K,V}(c::Dict{K,V}, k::K, v::V)=begin c[k]=v; k end
container_iter{K,V}(c::Dict{K,V})=keys(c)
container_value_iter{K,V}(c::Dict{K,V})=values(c)

