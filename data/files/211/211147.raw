using FactCheck

facts("TuckerOperator") do
  A = reshape(collect(1:8), 2, 2, 2)
  B = reshape(collect(1:4), 2, 2)
  C = Matrix{Int}[B, B]
  T = Tensors.TuckerOperator(A, C)
  @fact size(T) --> (2, 2, 2)
  @fact size(T, 2) --> 2
end

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

facts("modemult") do
  A = reshape(collect(1:8), 2, 2, 2)
  B = [[1 2]; [3 4]]

  C = zeros(Int64, 2, 2, 2)
  for i=1:2, k=1:2, l=1:2, m=1:2
    C[m, k, l] += A[i, k, l] * B[m, i]
  end
  @fact Tensors.modemult(A, B, 1) --> C

  C = zeros(Int64, 2, 2, 2)
  for i=1:2, k=1:2, l=1:2, m=1:2
    C[k, m, l] += A[k, i, l] * B[m, i]
  end
  @fact Tensors.modemult(A, B, 2) --> C

  C = zeros(Int64, 2, 2, 2)
  for i=1:2, k=1:2, l=1:2, m=1:2
    C[k, l, m] += A[k, l, i] * B[m, i]
  end
  @fact Tensors.modemult(A, B, 3) --> C
end

facts("modemult_list") do
  A = reshape(collect(1:8), 2, 2, 2)
  B = [[1 2]; [3 4]]
  C = cat(3, [[27 59]; [61 133]], [[63 143]; [145 329]])
  matrix_list = [(1, B), (2, B)]
  @fact Tensors.modemult_list(A, matrix_list) --> C
end

facts("scalamult") do
  A = cat(3, [[1 3]; [2 4]], [[5 7]; [6 8]])
  B = cat(3, [[1 2]; [3 4]], [[5 6]; [7 8]])
  r = sum([1 2 3 4 5 6 7 8] .* [1 3 2 4 5 7 6 8])
  @fact Tensors.scalarmult(A, B) --> r
end

facts("left_singular_vectors") do
  A = [[1 2]; [3 4]]
  @fact size(Tensors.left_singular_vectors(A)) --> (2, 2)
  @fact size(Tensors.left_singular_vectors(A, 1)) --> (2, 1)
  @fact_throws Tensors.left_singular_vectors(A, 3)
  B = [[.404554 -.914514]; [.914514 .404554]]
  @fact norm(Tensors.left_singular_vectors(A) - B) --> roughly(0, atol=1e-5)

  A = [[1+1im 2]; [3+1im 4]]
  B = [[0.421387+0.0702312im 0.891855+0.148643im]; [0.904157 -0.4272]]
  @fact norm(Tensors.left_singular_vectors(A) - B) --> roughly(0, atol=1e-5)
end

facts("hosvd") do
end
