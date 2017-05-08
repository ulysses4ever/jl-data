using Graphs
using DataStructures
#to use connected components, must implement: vertex_list,vertex_map,adjacency_list

type road #start coordinates are always closer to (1,1) than end coordinates
  start_x::Int64
  start_y::Int64
  end_x::Int64
  end_y::Int64
  net_id::Int64
end

function gen_test()
  hold = Deque{road}()
  push!(hold,road(5,3,5,3,rand(Int64)))
  push!(hold,road(11,1,11,6,rand(Int64)))
  push!(hold,road(10,3,13,3,rand(Int64)))
  push!(hold,road(5,3,10,3,rand(Int64)))
  push!(hold,road(11,6,11,20,rand(Int64)))
  push!(hold,road(1,3,5,3,rand(Int64)))
  push!(hold,road(20,20,25,20,rand(Int64)))
  push!(hold,road(25,20,25,30,rand(Int64)))
  return hold
end

function intersects(a::road,b::road) #requires that 2 roads overlap
  if (a.start_x <= b.end_x && b.start_x <= a.start_x)||(b.start_x <= a.end_x && a.start_x <= b.start_x)
    if  (a.start_y <= b.end_y && b.start_y <= a.start_y)||(b.start_y <= a.end_y && a.start_y <= b.start_y)
      return true
    else
      return false
    end
  end
  return false
end

function islonely(a::road)
  if (a.start_y == a.end_y) && (a.start_x == a.end_x)
    return true
  end
  return false
end

function ishorizontal(a::road) #returns true if either a is horizontal or a is one tile
  if a.start_y == a.end_y || (a.start_y ==a.end_y && a.start_x == a.end_x)
    return true
  end
  return false
end

function length(road)
  return sqrt((road.start_x-road.end_x)^2+(road.start_y-road.end_y)^2)
end

function merge(a::road,b::road)
  return road(minimum([a.start_x,b.start_x]),minimum([a.start_y,b.start_y]),
              maximum([a.end_x,b.end_x]),maximum([a.end_y,b.end_y]),rand(Int64))
end

function merge_roads!(roads::Deque{road}) #empties roads of all elements
  fixed = Deque{road}()
  hold = Deque{road}()
  while !isempty(hold) || !isempty(roads)
    while !isempty(hold)
      push!(roads,shift!(hold))
    end
    x = shift!(roads)
    merged = false
    while  !isempty(roads)
      y = shift!(roads)
      if intersects(x,y) && (islonely(x)||islonely(y)||(ishorizontal(x) == ishorizontal(y)))
        x = merge(x,y)
        merged = true
      else
        push!(hold,y)
      end
    end
    if !merged
      push!(fixed,x)
    else
      push!(roads,x)
    end
  end
  return fixed
end

function make_graph!(roads::Deque{road}) #assume roads has already been 'fixed'
  hold = Deque{KeyVertex{road}}()
  g = adjlist(KeyVertex{road},is_directed=false)
  while !isempty(roads)
    x = shift!(roads)
    push!(hold,add_vertex!(g,x))
  end
  done = Deque{KeyVertex{road}}()
  osci = Deque{KeyVertex{road}}()
  from_hold = true
  while !isempty(hold) || !isempty(osci)
    if from_hold
      x = shift!(hold)
      while !isempty(hold)
        y = shift!(hold)
        if intersects(x.key,y.key)
          add_edge!(g,x,y)
        end
        push!(osci,y)
      end
      from_hold = false
    else
      x = shift!(osci)
      while !isempty(osci)
        y = shift!(osci)
        if intersects(x.key,y.key)
          add_edge!(g,x,y)
        end
        push!(hold,y)
      end
      from_hold = true
    end
  end
  return g
end

function set_net_id!(connected_components)
  for i in connected_components
    x = rand(Int64)
    for j in i
      j.key.net_id = x
    end
  end
end
