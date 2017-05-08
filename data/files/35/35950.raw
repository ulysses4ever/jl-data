type Grid
   rows::Int64
   cols::Int64
   leafs::Int64
end

function node(grid::Grid, row, col)
   if row == grid.rows && col == grid.cols
      grid.leafs += 1
      return
   end
   if row < grid.rows
      node(grid, row+1, col)
   end
   if col < grid.cols
      node(grid, row, col+1)
   end
end

type Node
   row::Int64
   col::Int64
end

function fastnode(grid::Grid)
   root = Node(0, 0)
   stack = [root] :: Vector{Node}
   # sizehint(stack, 400)
   while !isempty(stack)
      n = pop!(stack) :: Node
      if n.col == grid.cols && n.row == grid.rows
         grid.leafs += 1
         continue
      end
      if n.col < grid.cols
         push!(stack, Node(n.col+1, n.row))
      end
      if n.row < grid.rows
         push!(stack, Node(n.col, n.row+1))
      end
   end
   return grid.leafs
end


g = Grid(20, 20, 0)
 
@time node(g, 0, 0)
println(g.leafs)

# g = Grid(12, 12, 0)
#
# @time leafs = fastnode(g)
# println(leafs)