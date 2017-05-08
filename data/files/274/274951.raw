
using SymPy

function binary_code( f::Symbol )
    x = Sym( "x" )
    y = Sym( "y" )
    ux = Sym( "u(x)" )
    uy = Sym( "u(y)" )
    dx = Sym( "d(x)" )
    dy = Sym( "d(y)" )
    ex = eval( quote( $f( x, y ) end ))
    code1 = string( f, "{Ux,Dx,Uy,Dy}( x::Dual{Ux,Dx}, y::Dual{Uy,Dy} ) = Dual",
                   (replace( replace( ex, x, ux ), y, uy ),
                    replace( replace( dx*diff( ex, x )+dy*diff( ex, y ), x, ux), y, uy)))
    code2 = string( f, "{Ux,Dx,Y}( x::Dual{Ux,Dx}, y::Y ) = Dual",
                   (replace( replace( ex, x, ux ), y, uy ),
                    replace( replace( dx*diff( ex, x )+dy*diff( ex, y ), x, ux), y, uy)))
    code3 = string( f, "{X,Uy,Dy}( x::X, y::Dual{Uy,Dy} ) = Dual",
                   (replace( ex, y, uy ),
                    replace( replace( dx*diff( ex, x )+dy*diff( ex, y ), x, ux), y, uy)))
           
end


function binary_code( f::Symbol )
    x = Sym( "x" )
    y = Sym( "y" )
    ux = Sym( "u(x)" )
    dx = Sym( "d(x)" )
    ex = eval( quote( $f( x, y ) end ))
    string( f, "{Ux,Dx,Y}( x::Dual{Ux,Dx}, y::Y ) = Dual",
           (replace( replace( ex, x, ux ), y, uy ),
            replace( replace( dx*diff( ex, x )+dy*diff( ex, y ), x, ux), y, uy)))
end



for op in (:+, :-, :*, :/)
    binary_code( op )
end

function unary_code( f::Symbol )
    x = Sym( "x" )
    u = Sym( "u(x)" )
    d = Sym( "d(x)" )
    ex = eval( quote $f( x ) end )
    string( f, "{U,D}(x::Dual{U,D}) = Dual",
           
end

for specfun in (:sin, :cos, :tan, :cot, :sec, :csc)
    @eval unary_code( specfun )
end

for specfun in (:asin :acos, :atan, :acot, :asec, :acsc)
    @eval unary_code( specfun )
end
    
            
