using FactCheck

facts("unfold") do
  A = reshape(collect(1:8), 2, 2, 2)
  @fact unfold(A, 1) --> [[1 3 5 7]; [2 4 6 8]]
  @fact unfold(A, 2) --> [[1 2 5 6]; [3 4 7 8]]
  @fact unfold(A, 3) --> [[1 2 3 4]; [5 6 7 8]]
end

facts("fold") do
  A = reshape(collect(1:8), 2, 4)
  @fact fold(A, [2, 2, 2], 1) --> cat(3, [[1 3]; [2 4]], [[5 7]; [6 8]])
  @fact fold(A, [2, 2, 2], 2) --> cat(3, [[1 2]; [3 4]], [[5 6]; [7 8]])
  @fact fold(A, [2, 2, 2], 3) --> cat(3, [[1 5]; [3 7]], [[2 6]; [4 8]])
end
