f = open("67.data")
data = readall(f)
pyramid =  [parseint(s) for s in split(strip(data), r"[\W+]")]
# pyramid = [3, 7, 4, 2, 4, 6, 8, 5, 9, 3]
parents = zeros(pyramid)
distances = zeros(pyramid)

# index of first element on row i
first_row(r) = sum(1:r) - (r - 1)

index(row, i) = first_row(row) + (i - 1) 

# index of last element on row i
last_row(r) = sum(1:r)

# number of elements on row i
length_row(r) = r

# The right parent of i'th child on given row
right_parent(row, i) = first_row(row) + (i - 1) - length_row(row - 1)

left_parent(row, i) = first_row(row) + (i - 1) - length_row(row)

# update parent which gives longest distance to top of an inner child.
# that is children with 2 potential parents
function visit_inner_child(row, child)
   li = left_parent(row, child)
   ri = right_parent(row, child)
   i = index(row, child)
   if distances[li] >= distances[ri]
      parents[i] = li
      distances[i] = distances[li] + pyramid[i]
   else
      parents[i] = ri
      distances[i] = distances[ri] + pyramid[i]      
   end
end

function find_no_rows(n)
   i = 1
   while n > 0
      n -= i
      i += 1
   end
   return i - 1
end

# Calculate distances and parents for all left and right edge nodes
function init_edges(no_rows)
   distances[1] = pyramid[1]
   for r in 2:no_rows
      i = first_row(r)
      ri = first_row(r - 1)
      parents[i] = ri
      distances[i] = distances[ri] + pyramid[i]
      
      j = last_row(r)
      lj = last_row(r - 1)
      parents[j] = lj
      distances[j] = distances[lj] + pyramid[j]      
   end
end

function update_inner_nodes(no_rows)
   for r in 3:no_rows
      for child in 2:(r-1)
         visit_inner_child(r, child)
      end 
   end
end

function find_longest_chain()
   no_rows = find_no_rows(length(pyramid))
   init_edges(no_rows)
   update_inner_nodes(no_rows)
   first = first_row(no_rows)
   last = last_row(no_rows)
   max = index(no_rows, indmax(distances[first:last]))
   chain = Int64[]
   i = max
   while i > 0
      push!(chain, pyramid[i])
      i = parents[i]
   end
   return distances[max], chain
end

println(find_longest_chain())