module List

export SinglyLinkedList, SinglyLinkedListNode
export DoublyLinkedList, DoublyLinkedListNode
export append!, remove!

abstract AbstractList{T}
abstract AbstractNode{T}

type SinglyLinkedListNode{T} <: AbstractNode{T}
  next::Union(SinglyLinkedListNode{T}, Nothing)
  val::T

  SinglyLinkedListNode(val::T) = new(nothing, val);
  SinglyLinkedListNode(next::Union(SinglyLinkedListNode, Nothing), val::T) = (
    new(next, val));
end

type SinglyLinkedList{T} <: AbstractList{T}
  head::Union(SinglyLinkedListNode{T}, Nothing)
  tail::Union(SinglyLinkedListNode{T}, Nothing)
  len::Int

  SinglyLinkedList() = new(nothing, nothing, 0);
end

#! Append an item to a singly linked list
#!
#! \param lst Singly linked list to append to
#! \param val Data vaue in which to add
#! \return New length
function append!{T}(lst::SinglyLinkedList{T}, val::T)
  new_node = SinglyLinkedListNode{T}(val);
  if lst.head == nothing
    lst.head = new_node;
    lst.tail = new_node;
    lst.len = 1;
  end
  lst.tail.next = new_node;
  lst.tail = new_node;
  lst.len += 1;
end

#! Append an item to a singly linked list
#!
#! \param lst Singly linked list to append to
#! \param vals Array of data to be added
#! \return New length
function append!{T}(lst::SinglyLinkedList{T}, vals::Array{T})
  for val in vals; append!(lst, val); end
end

#! Remove an item from a singly linked list
#!
#! \param lst Singly linked list
#! \param idx Index of item to remove
#! \return Node that was removed
function remove!(lst::SinglyLinkedList, idx::Int)
  if idx > lst.len
    return nothing;
  end
  lst.len -= 1;
  node = lst.head;
  if idx == 1
    lst.head = lst.head.next;
    return node;
  end
  for i=2:idx-1; node = node.next; end
  result = node.next;
  node.next = node.next.next;
  return result;
end

#! Empty a list
#!
#! \param Singly linked list to empty
function Base.empty!(lst::SinglyLinkedList)
  lst.len = 0;
  lst.head = nothing;
  lst.tail = nothing;
end

#=
type DoublyLinkedListNode{T} <: AbstractNode{T}
  next::Union(DoublyLinkedListNode{T}, Nothing)
  prev::Union(DoublyLinkedListNode{T}, Nothing)
  val::T

  DoublyLinkedListNode(val::T) = new(nothing, nothing, val);
  DoublyLinkedListNode(next::Union(DoublyLinkedListNode, Nothing),
                       prev::Union(DoublyLinkedListNode, Nothing),
                       val::T) = (new(next, prev, val));
end

type DoublyLinkedList{T} <: AbstractList{T}
  head::Union(DoublyLinkedListNode{T}, Nothing)
  tail::Union(DoublyLinkedListNode{T}, Nothing)
  len::Int

  DoublyLinkedList() = new(nothing, nothing, 0);
end

#! Append an item to a doubly linked list
#!
#! \param lst Doubly linked list to append to
#! \param va Data vaue in which to add
#! \return New length
function append!{T}(lst::DoublyLinkedList{T}, val::T)
  new_node = DoublyLinkedListNode{T}(val);
  new_node.prev = lst.tail;
  lst.tail.next = new_node;
  lst.tail = new_node;
  lst.len += 1;
end

#! Append an item to a doubly linked list
#!
#! \param lst Doubly linked list to append to
#! \param vals Array of data to be added
#! \return New length
function append!{T}(lst::DoublyLinkedList{T}, vals::Array{T})
  for val in vals; append!(lst, val); end
end

#! Remove an item from a doubly linked list
#!
#! \param lst Doubly linked list
#! \param idx Index of item to remove
#! \return Node that was removed
function remove!(lst::DoublyLinkedList, idx::Int)
  if idx > lst.len
    return nothing;
  end
  lst.len -= 1;
  if idx == 1
    node = lst.head;
    list.head = list.head.next;
  if idx == 1
    lst.head = lst.head.next;
    return node;
  end
  for i=2:idx-1; node = node.next; end
  result = node.next;
  node.next = node.next.next;
  return result;
end
=#
#! Empty a list
#!
#! \param Singly linked list to empty
function Base.empty!(lst::SinglyLinkedList)
  lst.len = 0;
  lst.head = nothing;
end
#! Start iteration
function Base.start{T}(lst::SinglyLinkedList{T})
  return lst.head;
end

#! Next item in iteration
function Base.next{T}(lst::SinglyLinkedList{T}, state::SinglyLinkedListNode{T})
  return (state.val, state.next);
end

#! Terminate iteration
function Base.done{T}(lst::SinglyLinkedList{T},
                      state::Union(SinglyLinkedListNode{T}, Nothing))
  if state == nothing
    return true;
  end
  return false;
end

Base.length(lst::AbstractList) = lst.len;
front(lst::AbstractList) = lst.head;
back(lst::AbstractList) = lst.tail;

end # module
