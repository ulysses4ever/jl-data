using AutoDiff
using Scalar
using FactCheck



facts( "Univariate" ) do


    
    a = Dual( 1.0, 2.0 )
    @fact typeof( a ) <: Dual --> true
    @fact isa( a, Dual{Float64,Float64}) --> true
    @fact re( a ) --> 1.0
    @fact du( a ) --> 2.0


    b = Dual( 3.0, 4.0 )
    @fact typeof( a ) <: Dual --> true
    @fact isa( b, Dual{Float64,Float64}) --> true
    @fact re( b ) --> 3.0
    @fact du( b ) --> 4.0

    test_binary_op( op::Symbol, re_expected::Float64, du_expected::Float64 ) = begin
        context( string( op ) ) do
            c = eval(op)( a, b )
            @fact typeof( c ) <: Dual --> true
            @fact isa( c, Dual{Float64, Float64}) --> true
            @fact re( c ) --> re_expected
            @fact du( c ) --> du_expected
        end
    end

    test_binary_op( :+, re( a )+re( b ), du( a )+du( b ))
    test_binary_op( :-, re( a )-re( b ), du( a )-du( b ))
    test_binary_op( :*, re( a )*re( b ), re( a )*du( b )+re( b )*du( a ))
    test_binary_op( :/, re( a )/re( b ), du( a )/re( b )-du( b )*re( a )/re( b )^2 )
    test_binary_op( :^, re( a )^re( b ), du( a )*re( b )*re( a )^( re( b )-1 )+du( b )*re( a )^re( b )*log( re( a )))


    test_unary_op( op::Symbol, re_expected::Float64, du_expected::Float64 ) = begin
        context( string( op )) do
            c = eval( op )( a )
            @fact typeof( c ) <: Dual --> true
            @fact isa( c, Dual{Float64,Float64}) --> true
            @fact re( c ) --> re_expected
            @fact du( c ) --> du_expected
        end
    end

    test_unary_op( :cos, cos( re( a )), -sin( re( a ))*du( a ))
    test_unary_op( :sin, sin( re( a )), cos( re( a ))*du( a ))
    test_unary_op( :tan, tan( re( a )), (tan( re( a ))^2+1)*du( a ))
    
end

    
facts( "Multivariate" ) do
end
    
facts( "Sparse Multivariate" ) do
end

