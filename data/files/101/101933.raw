#Node Superclass
abstract _Node{K,V}

#Internal Node - binary version
type Node{K,V} <: _Node{K,V}
    key::K
    value::V
    left::_Node{K,V}
    right::_Node{K,V}
end

#Leaf class, might be too formal
type Leaf{K,V} <: _Node{K,V}
end

#constructors for node class
Node{K,V}(key::K, value::V) = Node{K,V}(key, value, Leaf{K,V}(), Leaf{K,V}())
Node{K,V}(key::K, value::V, left::Node{K,V}) = Node{K,V}(key, value, left, Leaf{K,V}())

#Binary Tree container
type BinaryTree{K,V}
    root::_Node{K,V}
end

#Constructor function
function BinaryTree(TKey, TValue)
    if (typeof(TKey) == DataType) & (typeof(TValue) == DataType)
        BinaryTree{TKey, TValue}(Leaf{TKey,TValue}())
    else
        error("TKey and TValue must be DataType's, found TKey::" * string(typeof(TKey)) * " TValue::" * string(typeof(TValue)))
    end
end
type BinaryTreeIterator{K,V}
    tree::BinaryTree{K,V}
    nodeStack::Array{_Node{K,V}}
end

function BinaryTreeIterator{K,V}( tree::BinaryTree{K,V} )
    iter = BinaryTreeIterator(tree, Array(_Node{K,V},0))
    push!(iter.nodeStack, tree.root)
    iter
end

type StepVector{K,V}
    tree::BinaryTree{K,V}
end

function StepVector(TKey, TValue)
    ret = StepVector(BinaryTree(TKey, TValue))
    insert(ret.tree, convert(TKey, 0), convert( TValue, 0))
    ret
end

function Base.string(x::StepVector)
    ret = "StepVector("
    for node in x.tree
        ret = ret * string(node.key) * ":" * string(node.value) * ","
    end
    return(ret * ")")
end
Base.print(io::IO, x::StepVector) = print(io, string(x))
Base.show(io::IO, x::StepVector) = print(io, string(x))

type GenomicInterval
    chrom
    start
    stop
end

type GenomicArray
    contigs::Dict
end

type Alignment
    readName
    flag
    refID
    pos
    mapq
    cigar
    nextRefID
    nextPos
    tLen
    seq
    qual
    optionalFields
end

type CigarOperation
    opcode
    size::Uint32
    interval::GenomicInterval
end

type BAMReference
    name::String
    length::Int32
end
BAMReference() = BAMReference("None", -1)

type BAMReader
    filename::String
    stream::GZip.GZipStream
    headerText::String
    references
end
BAMReader(filename::String) = initializeBAMReader( filename )

type GenomicArray{CType, VType}
    map::BinaryTree{CType, StepVector{Uint64, VType}}
end
function GenomicArray( VType )
    GenomicArray(BinaryTree(ASCIIString, StepVector{Uint64, VType}))
end

