module List

export SinglyLinkedList, SinglyLinkedListNode
export DoublyLinkedList, DoublyLinkedListNode
export remove!, front, back

abstract AbstractList{T}
abstract AbstractNode{T}

#! Singly linked list node implementation
type SinglyLinkedListNode{T} <: AbstractNode{T}
  next::Union{SinglyLinkedListNode{T}, Void}
  val::T

  SinglyLinkedListNode(val::T) = new(nothing, val);
  SinglyLinkedListNode(next::Union{SinglyLinkedListNode, Void}, val::T) = (
    new(next, val));
end

#! Singly linked list implementation
type SinglyLinkedList{T} <: AbstractList{T}
  head::Union{SinglyLinkedListNode{T}, Void}
  tail::Union{SinglyLinkedListNode{T}, Void}
  len::Int

  SinglyLinkedList() = new(nothing, nothing, 0);

  #! Construction using argument list
  function SinglyLinkedList(args...)
    lst = new(nothing, nothing, 0);
    for arg in args; push!(lst, arg); end
    return lst;
  end
end

#! push an item to a singly linked list
#!
#! \param lst Singly linked list to push to
#! \param val Data vaue in which to add
#! \return New length
function Base.push!{T}(lst::SinglyLinkedList{T}, val::T)
  new_node = SinglyLinkedListNode{T}(val);
  if lst.head == nothing
    lst.head = new_node;
    lst.tail = new_node;
    return lst.len = 1;
  end
  lst.tail.next = new_node;
  lst.tail = new_node;
  return lst.len += 1;
end

#! push an array of item to a singly linked list
#!
#! \param lst Singly linked list to push to
#! \param vals Array of data to be added
#! \return New length
function Base.push!{T}(lst::SinglyLinkedList{T}, vals::Array{T})
  for val in vals; push!(lst, val); end
  return length(lst);
end

#! Add an item to the beginning of a singly linked list
#!
#! \param lst Singly linked list to push to
#! \param val Data vaue in which to add
#! \return New length
function Base.unshift!{T}(lst::SinglyLinkedList{T}, val::T)
  new_node = SinglyLinkedListNode{T}(val);
  if lst.head == nothing
    lst.head = new_node;
    lst.tail = new_node;
    return lst.len = 1;
  end
  new_node.next = lst.head;
  lst.head = new_node;
  return lst.len += 1;
end

#! Add an array items to the beginning of a singly linked list
#!
#! \param lst Singly linked list to push to
#! \param vals Array of data to be added
#! \return New length
function Base.unshift!{T}(lst::SinglyLinkedList{T}, vals::Array{T})
  for val in vals; unshift!(lst, val); end
  return length(lst);
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
  if idx == 1
    return shift!(lst);
  elseif idx == lst.len
    return pop!(lst);
  end
  lst.len -= 1;
  node = lst.head;
  for i=2:idx-1; node = node.next; end
  result = node.next;
  node.next = node.next.next;
  return result;
end

#! Remove an item from the beginning of a singly linked list
#!
#! \param lst Singly linked list
#! \return Front element
function Base.shift!(lst::SinglyLinkedList)
  if lst.head == nothing; return nothing; end
  lst.len -= 1;
  if lst.head == lst.tail
    result = lst.head;
    lst.head = nothing;
    lst.tail = nothing;
    return result;
  end
  result = lst.head;
  lst.head = result.next;
  return result;
end

#! Remove the item from the end of a singly linked list
#!
#! \param lst Singly linked list
#! \return End element
function Base.pop!(lst::SinglyLinkedList)
  if lst.head == nothing; return nothing; end
  lst.len -= 1;
  if lst.head == lst.tail
    result = lst.head;
    lst.head = nothing;
    lst.tail = nothing;
    return result;
  end
  node = lst.head;
  while node.next.next != nothing
    node = node.next;
  end
  result = node.next;
  node.next = nothing;
  lst.tail = node;
  return result;
end

#! Doubly linked list node implementation
type DoublyLinkedListNode{T} <: AbstractNode{T}
  next::Union{DoublyLinkedListNode{T}, Void}
  prev::Union{DoublyLinkedListNode{T}, Void}
  val::T

  DoublyLinkedListNode(val::T) = new(nothing, nothing, val);
  DoublyLinkedListNode(next::Union{DoublyLinkedListNode, Void},
                       prev::Union{DoublyLinkedListNode, Void},
                       val::T) = (new(next, prev, val));
end

#! Doubly linked list implementation
type DoublyLinkedList{T} <: AbstractList{T}
  head::Union{DoublyLinkedListNode{T}, Void}
  tail::Union{DoublyLinkedListNode{T}, Void}
  len::Int

  DoublyLinkedList() = new(nothing, nothing, 0);

  #! Construction using argument list
  function DoublyLinkedList(args...)
    lst = new(nothing, nothing, 0);
    for arg in args; push!(lst, arg); end
    return lst;
  end
end

#! push an item to a doubly linked list
#!
#! \param lst Doubly linked list to push to
#! \param va Data vaue in which to add
#! \return New length
function Base.push!{T}(lst::DoublyLinkedList{T}, val::T)
  new_node = DoublyLinkedListNode{T}(val);
  if lst.head == nothing
    @assert lst.tail == nothing;
    lst.head = new_node;
    lst.tail = new_node;
    return lst.len += 1;
  end
  new_node.prev = lst.tail;
  lst.tail.next = new_node;
  lst.tail = new_node;
  lst.len += 1;
end

#! push an item to a doubly linked list
#!
#! \param lst Doubly linked list to push to
#! \param vals Array of data to be added
#! \return New length
function Base.push!{T}(lst::DoublyLinkedList{T}, vals::Array{T})
  for val in vals; push!(lst, val); end
  return length(lst);
end

#! Add an item to the beginning of a doubly linked list
#!
#! \param lst Doubly linked list to push to
#! \param val Data vaue in which to add
#! \return New length
function Base.unshift!{T}(lst::DoublyLinkedList{T}, val::T)
  new_node = DoublyLinkedListNode{T}(val);
  if lst.head == nothing
    lst.head = new_node;
    lst.tail = new_node;
    return lst.len = 1;
  end
  new_node.next = lst.head;
  lst.head.prev = new_node;
  lst.head = new_node;
  return lst.len += 1;
end

#! Add an array items to the beginning of a doubly linked list
#!
#! \param lst Doubly linked list to push to
#! \param vals Array of data to be added
#! \return New length
function Base.unshift!{T}(lst::DoublyLinkedList{T}, vals::Array{T})
  for val in vals; unshift!(lst, val); end
  return length(lst);
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
  if idx == 1
    return shift!(lst);
  elseif idx == lst.len
    return pop!(lst);
  else
    lst.len -= 1;
    if idx < lst.len / 2
      node = lst.head.next;
      for i=2:idx-1; node = node.next; end
      result = node;
      node.prev.next = node.next;
      node.next.prev = node.prev;
      return result;
    else
      node = lst.tail.prev;
      for i=idx+1:lst.len; node = node.prev; end
      result = node;
      node.prev.next = node.next;
      node.next.prev = node.prev;
      return result;
    end
  end
end

#! Remove an item from a doubly linked list
#!
#! \param lst Doubly linked list
#! \param pnode Pointer to node to remove
#! \return Node that was removed
function remove!(lst::DoublyLinkedList, pnode::DoublyLinkedListNode)
  if lst.head == pnode
    return shift!(lst);
  elseif lst.tail == pnode
    return pop!(lst);
  else
    lst.len -= 1;
    pnode.prev.next = pnode.next;
    pnode.next.prev = pnode.prev;
    return pnode;
  end
end

#! Remove an item from the beginning of a doubly linked list
#!
#! \param lst Doubly linked list
#! \return Node that was removed from front
function Base.shift!(lst::DoublyLinkedList)
  if lst.head == nothing
    return nothing
  elseif lst.head == lst.tail
    lst.len = 0;
    result = lst.head;
    lst.head = nothing;
    lst.tail = nothing;
    return result;
  else
    lst.len -= 1;
    @assert lst.tail != nothing
    result = lst.head;
    lst.head = lst.head.next;
    lst.head.prev = nothing;
    return result;
  end
end

#! Remove an item from the end of a doubly linked list
#!
#! \param lst Doubly linked list
#! \return Node that was removed from end
function Base.pop!(lst::DoublyLinkedList)
  if lst.tail == nothing
    return nothing;
  elseif lst.tail == lst.head
    return shift!(lst);
  else
    lst.len -= 1;
    @assert lst.head != nothing
    result = lst.tail;
    lst.tail = lst.tail.prev;
    lst.tail.next = nothing;
    return result;
  end
end

#! Empty a list
#!
#! \param Singly linked list to empty
function Base.empty!(lst::AbstractList)
  lst.len = 0;
  lst.head = nothing;
  lst.tail = nothing;
end

#! Start iteration
function Base.start{T}(lst::AbstractList{T})
  return lst.head;
end

#! Next item in iteration
function Base.next{T}(lst::AbstractList{T}, node::AbstractNode{T})
  return (node, node.next);
end

#! Terminate iteration
function Base.done{T}(lst::AbstractList{T},
                      node::Union{AbstractNode{T}, Void})
  if node == nothing
    return true;
  end
  return false;
end

#! Empty a list
#!
#! \param List to empty
function Base.empty!(lst::AbstractList)
  lst.len = 0;
  lst.head = nothing;
  lst.tail = nothing;
end

Base.length(lst::AbstractList) = lst.len;
front(lst::AbstractList) = lst.head;
back(lst::AbstractList) = lst.tail;
function Base.show(io::IOStream, lst::AbstractList)
  if lst.head == nothing
    @assert lst.tail == nothing
    print(io, "list()");
  end
  print(io, "list(");
  cnode = lst.head;
  while cnode.next != nothing
    print(io, cnode.val, ", ");
  end
  print(io, lst.tail.val, ")");
end
Base.show(lst::AbstractList) = show(STDOUT, lst);

end # module
