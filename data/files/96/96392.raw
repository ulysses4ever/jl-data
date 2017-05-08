using Graphs
using Gaston

# array of tuples of the type (x, y, z)
points = [(1, 1, 0),
          (2, 2, 0),
          (2.5, 2, 0.5),
          (3.14, 2, -0.5),
          (4, 4, 0)]

xs = map((p)-> p[1], points)
ys = map((p)-> p[2], points)
zs = map((p)-> p[3], points)

function euclidian_distance(p1, p2)
  x = (p1[1] - p2[1]) ^ 2
  y = (p1[2] - p2[2]) ^ 2
  sqrt(x + y)
end

# gets (x, y) from (x, y, z)
function twoD(p)
  (p[1], p[2])
end

# function that is used on a sorted in ascending order array. It will add the value after the first element (looking from backward) that is lower than it. Never changes the size of the array. (If a new element is added, the highest from the old ones will be removed)
function add_priority_queue(arr, x)
  i = length(arr)

  if x[3] > arr[i][3]
      return arr
  end

  while i > 0 && x[3] < arr[i][3]
    i -= 1
  end

  for j = 1:length(arr) - i - 1
    arr[length(arr) - j + 1] = arr[length(arr) - j]
  end

  arr[i + 1] = x
  arr
end

# given a number of points (x, y, z) will return n*floor(sqrt(n)) edges of the type (index, index, weight). The direction of the edge is from the point represented with the first index to the point represented with the second.
function edges(points)
  degree = int(sqrt(length(points)))
  pairs = (Int64, Int64, Float64)[]
  for i = 1:length(points)
    queue = fill((0, 0, Inf), degree)

    for j = 1:length(points)
      if i != j
        queue = add_priority_queue(queue, (i, j, euclidian_distance(points[i], points[j])))
      end
    end

    for i in queue
      push!(pairs, i)
    end
  end
  pairs
end

# as the edges() function may return a graph with some vertexes that aren't pointed by any edge, this function ensures that every vertex is reachable. It will do so by adding the inverted edges of edges that start from this vertex.
function ensure_graph_correctness(edges, points)
  # local copy of points
  lpoints = copy(points)
  for edge in edges
    lpoints[edge[2]] = (0, 0, Inf)
  end

  for i = 1:length(lpoints)
    if lpoints[i] != (0, 0, Inf)
      for edge in edges
        if edge[1] == i
          push!(edges, (edge[2], edge[1], edge[3]))
        end
      end
    end
  end
  edges
end

# BFStates stands for BellmanFordStates
function path(BFStates, from, to)
  curr_path = Int64[]
  push!(curr_path, to)
  pos = BFStates.parents[to]
  while pos != from
    push!(curr_path, pos)
    pos = BFStates.parents[pos]
  end
  push!(curr_path, from)
  (reverse(curr_path), BFStates.dists[to])
end

println(points)
wedges = edges(points)
println(wedges)
wedges = ensure_graph_correctness(wedges, points)
println(wedges)

graph = simple_inclist(length(points))

wedges_len = length(wedges)
weights = zeros(wedges_len)
for i = 1:wedges_len
  wedge = wedges[i]
  add_edge!(graph, wedge[1], wedge[2])
  weights[i] = wedge[3]
end

res = bellman_ford_shortest_paths(graph, weights, [1])
println(res)
println()
println(path(res, 1, 5))

function llama(x, y)
  for point in points
    println(typeof(point), typeof((x, y)))
    if point[1] == x && point[2] == y
      return point[3]
    end
  end
  return 0
end


figure()
axes = Gaston.AxesConf()
curve = Gaston.CurveConf()
curve.plotstyle = "points"
Gaston.addconf(axes)
for edge in wedges
  p1, p2 = edge
  x1, y1, z1 = points[p1]
  x2, y2, z2 = points[p2]
  # really lame api forces me to add 4 identical points instead of just one
  Gaston.addcoords([x1, x1], [y1, y1], [z1 z1; z1 z1], curve)
  Gaston.addcoords([x2, x2], [y2, y2], [z2 z2; z2 z2], curve)
end
Gaston.llplot()
sleep(3600)
