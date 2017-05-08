type BlockMatrix
  blocks::Array{RemoteRef,1}
  procs::Array{Int64,1}
  ranges::Array{UnitRange{Int64},1}
  m::Int64
  n::Int64
end

getindex( A::BlockMatrix, i::Integer ) = A.blocks[i]
getindex( A::BlockMatrix, I::AbstractVector ) = BlockMatrix( A.blocks[I],
  A.procs[I], A.ranges[I], sum(map(length,A.ranges[I])), A.n)

nblocks( A::BlockMatrix ) = length(A.blocks)

function randn!( A::BlockMatrix )
  @sync begin
    for i = 1:length(A.blocks)
      @spawnat A.blocks.where randn(fetch(A.blocks[i]))
    end
  end
end

function blkrandn( dims, procs )
  m,n = dims
  nprocs = length(procs)
  # Assumed that # procs divides m
  ranges = Base.splitrange( m, nprocs )
  @sync begin
    blocks = [@spawnat procs[i] randn(length(ranges[i]),n) for i in 1:nprocs]
  end
  BlockMatrix(blocks,procs,ranges,m,n)
end

function blkzeros( dims, procs )
  m,n = dims
  nprocs = length(procs)
  # Assumed that # procs divides m
  ranges = Base.splitrange( m, nprocs )
  @sync begin
    blocks = [@spawnat procs[i] zeros(length(ranges[i]),n) for i in 1:nprocs]
  end
  BlockMatrix(blocks,procs,ranges,m,n)
end

function full( A::BlockMatrix )
  vcat([fetch(A[i]) for i in 1:length(A.blocks)]...)
end
