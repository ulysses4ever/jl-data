module List

export SinglyLinkedList, SinglyLinkedListNode
export DoublyLinkedList, DoublyLinkedListNode
export unshift!, pop!, shift!, empty!, remove!

abstract AbstractList{T}
abstract AbstractNode{T}

#! Singly linked list node implementation
type SinglyLinkedListNode{T} <: AbstractNode{T}
  next::Union(SinglyLinkedListNode{T}, Nothing)
  val::T

  SinglyLinkedListNode(val::T) = new(nothing, val);
  SinglyLinkedListNode(next::Union(SinglyLinkedListNode, Nothing), val::T) = (
    new(next, val));
end

#! Singly linked list implementation
type SinglyLinkedList{T} <: AbstractList{T}
  head::Union(SinglyLinkedListNode{T}, Nothing)
  tail::Union(SinglyLinkedListNode{T}, Nothing)
  len::Int

  SinglyLinkedList() = new(nothing, nothing, 0);
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
    lst.len = 1;
  end
  lst.tail.next = new_node;
  lst.tail = new_node;
  lst.len += 1;
end

#! push an array of item to a singly linked list
#!
#! \param lst Singly linked list to push to
#! \param vals Array of data to be added
#! \return New length
function Base.push!{T}(lst::SinglyLinkedList{T}, vals::Array{T})
  for val in vals; push!(lst, val); end
end

#! Add an item to the beginning of a singly linked list
#!
#! \param lst Singly linked list to push to
#! \param val Data vaue in which to add
#! \return New length
function unshift!{T}(lst::SinglyLinkedList{T}, val::T)
  new_node = SinglyLinkedListNode{T}(val);
  if lst.head == nothing
    lst.head = new_node;
    lst.tail = new_node;
    lst.len = 1;
  end
  new_node.next = lst.head;
  lst.head = new_node;
  lst.len += 1;
end

#! Add an array items to the beginning of a singly linked list
#!
#! \param lst Singly linked list to push to
#! \param vals Array of data to be added
#! \return New length
function unshift!{T}(lst::SinglyLinkedList{T}, vals::Array{T})
  for val in vals; unshift!(lst, val); end
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
    shift!(lst);
  end
  for i=2:idx-1; node = node.next; end
  result = node.next;
  node.next = node.next.next;
  return result;
end

#! Remove an item from the beginning of a singly linked list
#!
#! \param lst Singly linked list
#! \return Front element
function shift!(lst::SinglyLinkedList)
  if lst.head == nothing; return nothing; end
  result = lst.head;
  lst.head = result.next;
  return result;
end

#! Remove the item from the end of a singly linked list
#!
#! \param lst Singly linked list
#! \return End element
pop!(lst::SinglyLinkedList) = remove!(lst, lst.len);

#! Doubly linked list node implementation
type DoublyLinkedListNode{T} <: AbstractNode{T}
  next::Union(DoublyLinkedListNode{T}, Nothing)
  prev::Union(DoublyLinkedListNode{T}, Nothing)
  val::T

  DoublyLinkedListNode(val::T) = new(nothing, nothing, val);
  DoublyLinkedListNode(next::Union(DoublyLinkedListNode, Nothing),
                       prev::Union(DoublyLinkedListNode, Nothing),
                       val::T) = (new(next, prev, val));
end

#! Doubly linked list implementation
type DoublyLinkedList{T} <: AbstractList{T}
  head::Union(DoublyLinkedListNode{T}, Nothing)
  tail::Union(DoublyLinkedListNode{T}, Nothing)
  len::Int

  DoublyLinkedList() = new(nothing, nothing, 0);
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
end

#! Add an item to the beginning of a doubly linked list
#!
#! \param lst Doubly linked list to push to
#! \param val Data vaue in which to add
#! \return New length
function unshift!{T}(lst::DoublyLinkedList{T}, val::T)
  new_node = DoublyLinkedListNode{T}(val);
  if lst.head == nothing
    lst.head = new_node;
    lst.tail = new_node;
    lst.len = 1;
  end
  new_node.next = lst.head;
  lst.head.prev = new_node;
  lst.head = new_node;
  lst.len += 1;
end

#! Add an array items to the beginning of a doubly linked list
#!
#! \param lst Doubly linked list to push to
#! \param vals Array of data to be added
#! \return New length
function unshift!{T}(lst::DoublyLinkedList{T}, vals::Array{T})
  for val in vals; unshift!(lst, val); end
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
  node = nothing;
  if idx == 1
    shift!(lst);
  elseif idx == lst.len
    pop!(lst);
  elseif idx < lst.len / 2
    node = lst.head.next;
    for i=2:idx-1; node = node.next; end
  else
    node = lst.tail.prev;
    for i=lst.len-1:idx-1; node = node.next; end
  end
  result = node.next;
  node.next = node.next.next;
  node.next.prev = node;
  return result;
end

#! Remove an item from a doubly linked list
#!
#! \param lst Doubly linked list
#! \param pnode Pointer to node to remove
#! \return Node that was removed
function remove!(lst::DoublyLinkedList, pnode::DoublyLinkedListNode)
  lst.len -= 1;
  if lst.head == pnode
    shift!(lst);
  elseif lst.tail == pnode
    pop!(lst);
  else
    pnode.prev.next = pnode.next;
    pnode.next.prev = pnode.prev;
    return pnode;
  end
end

#! Remove an item from the beginning of a doubly linked list
#!
#! \param lst Doubly linked list
#! \return Node that was removed from front
function shift!(lst::DoublyLinkedList)
  if lst.head != nothing
    lst.len -= 1;
    @assert lst.tail != nothing
    result = lst.head;
    lst.head = lst.head.next;
    lst.head.prev = nothing;
  else
    return nothing;
  end
end

#! Remove an item from the end of a doubly linked list
#!
#! \param lst Doubly linked list
#! \return Node that was removed from end
function pop!(lst::DoublyLinkedList)
  if lst.tail != nothing
    lst.len -= 1;
    @assert lst.head != nothing
    result = lst.tail;
    lst.tail = lst.tail.prev;
    lst.tail.next = nothing;
  else
    return nothing;
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
                      node::Union(AbstractNode{T}, Nothing))
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

end # module
