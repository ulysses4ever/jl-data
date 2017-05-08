function rand_matrix{X<:Matrix}(A::Type{X}, N, T)
    rand(T, N, N)
end
function rand_matrix{X<:FixedSizeArrays.Mat}(A::Type{X}, N, T)
    rand(A{N, N, T})
end
function rand_matrix{X<:Tuple}(A::Type{X}, N, T)
  ntuple(N) do i
    tuple(rand(T, N)...)
  end
end
function rand_matrix{X<:VecElement}(A::Type{X}, N, T)
    map(VecElement, rand_matrix(Tuple, N, T))
end

function matrix_bench(suite)
    constructors = [
        ("Array", Matrix),
        ("FSA", FixedSizeArrays.Mat),
        ("VecTuple", VecElement),
        ("Tuple", Tuple)
    ]
    element_types = (Float32, Float64)

    for (name, c) in constructors
      suite[name] = BenchmarkGroup()
      for N in (2, 4, 9), T in element_types
          a = rand_matrix(c, N, T)
          b = rand_matrix(c, N, T)
          suite[name]["matmul", N, T] = @benchmarkable a * b
          suite[name]["sum", N, T] = @benchmarkable sum(a)
      end
    end
end
