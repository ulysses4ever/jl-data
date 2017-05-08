module ConcatOperator

VERSION < v"0.4.0-dev+6294" && error("""
    Cannot load ConcatOperator module.
    This version of Julia does not support parsing "++"
    """)

export ++

"""
Concatenation operator for strings, characters, and vectors.
"x ++ y ++ z ++ ..." is transformed by the parser to "++(x,y,z,...)".
"""
++(ss::Union{AbstractString,Char}...) = string(ss...)
++(x1::Vector, xs::Vector...) = vcat(x1, xs...)

end
