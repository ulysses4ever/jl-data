import Base.==

==(a::FactNode, b::FactNode) = a.line == b.line && a.name == b.name &&a.result == b.result && a.details == b.details
==(a::FactsCollectionNode, b::FactsCollectionNode) = a.line == b.line && a.name == b.name && a.children == b.children
==(a::ContextNode, b::ContextNode) = a.line == b.line && a.name == b.name && a.children == b.children
==(a::RootNode, b::RootNode) = a.children == b.children
