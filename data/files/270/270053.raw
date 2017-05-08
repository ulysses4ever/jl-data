# n x n sparse matrix laid out in a grid of sparse matrices.
type DistributedSparseMatrix
  grid::Array{RemoteRef,2}
  procs::Array{Int64,1}
  ranges::Array{UnitRange{Int64},1}
  n::Int64
end

getindex(A::DistributedSparseMatrix, i::Int, j::Int) = A.grid[i,j]

function distribute( A::SparseMatrixCSC, procs )
  n, = size(A)
  nprocs = length(procs)
  ranges = Base.splitrange(n, nprocs)
  blocks = Array(RemoteRef, nprocs, nprocs)
  @sync begin
    for j = 1:nprocs
      for i = 1:nprocs
        blocks[i,j] = @spawnat procs[j] A[ranges[i],ranges[j]]
      end
    end
  end
  DistributedSparseMatrix(blocks,procs,ranges,n)
end

spmm!( A::RemoteRef, X::RemoteRef ) = fetch(A)*fetch(X)::Array{Float64,2}

function spmm!( A::DistributedSparseMatrix, X::BlockMatrix, Y::BlockMatrix)
  @sync for i = 1:length(A.procs)
    @spawnat A.procs[i] spmm!( A, X, Y[i] )
  end
end


function spmm!( A::DistributedSparseMatrix, X::BlockMatrix, Y::RemoteRef )
  j = findfirst(A.procs,myid())
  y = fetch(Y)::Array{Float64,2}
  m,n = size(y)
  nprocs = length(A.procs)

  # Tell processors to do their blocks and send them over
  @sync begin
    for i = 1:nprocs
      @async begin
        M = remotecall_fetch(A[j,i].where, spmm!, A[j,i], X[i])::Array{Float64,2}
        for k = 1:n
          @simd for i = 1:m
            @inbounds y[i,k] += M[i,k]
          end
        end
      end
    end
  end
end

