abstract LinkedList{T}

type Nil{T} <: LinkedList{T}
end

type Cons{T} <: LinkedList{T}
  head::T
  tail::LinkedList{T}
end

cons{T}(h, t::LinkedList{T}) = Cons{T}(h, t)

nil(T) = Nil{T}()

nil() = nil(Any)

list() = nil()

list(t::DataType) = nil(t)

function list(elts...)
  l = nil()
  for i=Base.length(elts):-1:1
      l = cons(elts[i],l)
  end
  return l
end

function list{T}(elts::T...)
  l = nil(T)
  for i=Base.length(elts):-1:1
    l = cons(elts[i],l)
  end
  return l
end

#Iterator
start{T}(l::Nil{T}) = l
start{T}(l::Cons{T}) = l
done{T}(l::Cons{T}, state::Cons{T}) = false
done{T}(l::LinkedList, state::Nil{T}) = true
next{T}(l::Cons{T}, state::Cons{T}) = (state.head, state.tail)

#operations
first(x::Cons) = x.head
rest(x::Cons) = x.tail
length(l::Nil) = 0

function length(l::Cons)
  len = 0
  for i in l
    len += 1
  end
  len
end