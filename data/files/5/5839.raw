import Base.==
_isequal{T}(a::Nullable{T}, b::Nullable{T}) = isnull(a)==true && isnull(b)==true || isnull(a) == false && isnull(b) == false && a == b
==(a::FactNode, b::FactNode) = a.line == b.line && a.name == b.name && _isequal(a.result, b.result) && _isequal(a.details, b.details)
==(a::FactsCollectionNode, b::FactsCollectionNode) = a.line == b.line && a.name == b.name && a.children == b.children
