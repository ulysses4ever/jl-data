# Automatically generated using Clang.jl wrap_c, version 0.0.0

using Compat

# const POLYLIB_BITS = 64
# const LONG_LONG_MAX = __LONG_LONG_MAX__
# const LONG_LONG_MIN = -LONG_LONG_MAX - 1
# const ULONG_LONG_MAX = LONG_LONG_MAX * 2 + 1
# const LINEAR_VALUE_STRING = "long int"
# const VALUE_FMT = "%ld"

# # Skipping MacroDefinition: VALUE_CONST ( val ) ( val ## L )

# const VALUE_NAN = LONG_MIN
# const VALUE_MIN = LONG_MIN + 1
# const VALUE_MAX = LONG_MAX

# # Skipping MacroDefinition: VALUE_SQRT_MIN int_to_value ( INT_MIN )
# # Skipping MacroDefinition: VALUE_SQRT_MAX int_to_value ( INT_MAX )

# const VALUE_ZERO = 0
# const VALUE_ONE = 1
# const VALUE_MONE = -1

# # Skipping MacroDefinition: VALUE_TO_LONG ( val ) ( val )
# # Skipping MacroDefinition: VALUE_TO_INT ( val ) ( ( int ) ( val ) )
# # Skipping MacroDefinition: VALUE_TO_FLOAT ( val ) ( ( float ) ( val ) )
# # Skipping MacroDefinition: VALUE_TO_DOUBLE ( val ) ( ( double ) ( val ) )
# # Skipping MacroDefinition: value_init ( val ) ( ( val ) = 0 )
# # Skipping MacroDefinition: value_assign ( v1 , v2 ) ( ( v1 ) = ( v2 ) )
# # Skipping MacroDefinition: value_set_si ( val , i ) ( ( val ) = ( Value ) ( i ) )
# # Skipping MacroDefinition: value_set_double ( val , d ) ( ( val ) = ( Value ) ( d ) )
# # Skipping MacroDefinition: value_clear ( val ) ( ( val ) = 0 )
# # Skipping MacroDefinition: value_read ( val , str ) ( sscanf ( ( str ) , VALUE_FMT , & ( val ) ) )
# # Skipping MacroDefinition: value_print ( Dst , fmt , val ) ( fprintf ( ( Dst ) , ( fmt ) , ( val ) ) )
# # Skipping MacroDefinition: value_swap ( v1 , v2 ) { Value tmp ; tmp = v2 ; v2 = v1 ; v1 = tmp ; }
# # Skipping MacroDefinition: int_to_value ( i ) ( ( Value ) ( i ) )
# # Skipping MacroDefinition: long_to_value ( l ) ( ( Value ) ( l ) )
# # Skipping MacroDefinition: float_to_value ( f ) ( ( Value ) ( f ) )
# # Skipping MacroDefinition: double_to_value ( d ) ( ( Value ) ( d ) )
# # Skipping MacroDefinition: value_eq ( v1 , v2 ) ( ( v1 ) == ( v2 ) )
# # Skipping MacroDefinition: value_ne ( v1 , v2 ) ( ( v1 ) != ( v2 ) )
# # Skipping MacroDefinition: value_gt ( v1 , v2 ) ( ( v1 ) > ( v2 ) )
# # Skipping MacroDefinition: value_ge ( v1 , v2 ) ( ( v1 ) >= ( v2 ) )
# # Skipping MacroDefinition: value_lt ( v1 , v2 ) ( ( v1 ) < ( v2 ) )
# # Skipping MacroDefinition: value_le ( v1 , v2 ) ( ( v1 ) <= ( v2 ) )
# # Skipping MacroDefinition: value_abs_eq ( v1 , v2 ) ( value_abs ( v1 ) == value_abs ( v2 ) )
# # Skipping MacroDefinition: value_abs_ne ( v1 , v2 ) ( value_abs ( v1 ) != value_abs ( v2 ) )
# # Skipping MacroDefinition: value_abs_gt ( v1 , v2 ) ( value_abs ( v1 ) > value_abs ( v2 ) )
# # Skipping MacroDefinition: value_abs_ge ( v1 , v2 ) ( value_abs ( v1 ) >= value_abs ( v2 ) )
# # Skipping MacroDefinition: value_abs_lt ( v1 , v2 ) ( value_abs ( v1 ) < value_abs ( v2 ) )
# # Skipping MacroDefinition: value_abs_le ( v1 , v2 ) ( value_abs ( v1 ) <= value_abs ( v2 ) )
# # Skipping MacroDefinition: value_sign ( v ) ( value_eq ( v , VALUE_ZERO ) ? 0 : value_lt ( v , VALUE_ZERO ) ? - 1 : 1 )
# # Skipping MacroDefinition: value_compare ( v1 , v2 ) ( value_eq ( v1 , v2 ) ? 0 : value_lt ( v1 , v2 ) ? - 1 : 1 )
# # Skipping MacroDefinition: value_plus ( v1 , v2 ) ( ( v1 ) + ( v2 ) )
# # Skipping MacroDefinition: value_div ( v1 , v2 ) ( ( v1 ) / ( v2 ) )
# # Skipping MacroDefinition: value_mod ( v1 , v2 ) ( ( v1 ) % ( v2 ) )
# # Skipping MacroDefinition: value_direct_multiply ( v1 , v2 ) ( ( v1 ) * ( v2 ) )
# # Skipping MacroDefinition: value_minus ( v1 , v2 ) ( ( v1 ) - ( v2 ) )
# # Skipping MacroDefinition: value_pdiv ( v1 , v2 ) ( DIVIDE ( ( v1 ) , ( v2 ) ) )
# # Skipping MacroDefinition: value_pmod ( v1 , v2 ) ( MODULO ( ( v1 ) , ( v2 ) ) )
# # Skipping MacroDefinition: value_min ( v1 , v2 ) ( value_le ( ( v1 ) , ( v2 ) ) ? ( v1 ) : ( v2 ) )
# # Skipping MacroDefinition: value_max ( v1 , v2 ) ( value_ge ( ( v1 ) , ( v2 ) ) ? ( v1 ) : ( v2 ) )
# # Skipping MacroDefinition: value_or ( v1 , v2 ) ( ( v1 ) | ( v2 ) )
# # Skipping MacroDefinition: value_and ( v1 , v2 ) ( ( v1 ) & ( v2 ) )
# # Skipping MacroDefinition: value_lshift ( v1 , v2 ) ( ( v1 ) << ( v2 ) )
# # Skipping MacroDefinition: value_rshift ( v1 , v2 ) ( ( v1 ) >> ( v2 ) )
# # Skipping MacroDefinition: value_addto ( ref , val1 , val2 ) ( ( ref ) = ( val1 ) + ( val2 ) )
# # Skipping MacroDefinition: value_add_int ( ref , val , vint ) ( ( ref ) = ( val ) + ( Value ) ( vint ) )
# # Skipping MacroDefinition: value_addmul ( ref , val1 , val2 ) ( ( ref ) += ( val1 ) * ( val2 ) )
# # Skipping MacroDefinition: value_increment ( ref , val ) ( ( ref ) = ( val ) + VALUE_ONE )
# # Skipping MacroDefinition: value_direct_product ( ref , val1 , val2 ) ( ( ref ) = ( val1 ) * ( val2 ) )
# # Skipping MacroDefinition: value_multiply ( ref , val1 , val2 ) ( ( ref ) = value_mult ( ( val1 ) , ( val2 ) ) )
# # Skipping MacroDefinition: value_subtract ( ref , val1 , val2 ) ( ( ref ) = ( val1 ) - ( val2 ) )
# # Skipping MacroDefinition: value_sub_int ( ref , val , vint ) ( ( ref ) = ( val ) - ( Value ) ( vint ) )
# # Skipping MacroDefinition: value_decrement ( ref , val ) ( ( ref ) = ( val ) - VALUE_ONE )
# # Skipping MacroDefinition: value_division ( ref , val1 , val2 ) ( ( ref ) = ( val1 ) / ( val2 ) )
# # Skipping MacroDefinition: value_divexact ( ref , val1 , val2 ) ( ( ref ) = ( val1 ) / ( val2 ) )
# # Skipping MacroDefinition: value_modulus ( ref , val1 , val2 ) ( ( ref ) = ( val1 ) % ( val2 ) )
# # Skipping MacroDefinition: value_pdivision ( ref , val1 , val2 ) ( ( ref ) = value_pdiv ( ( val1 ) , ( val2 ) ) )
# # Skipping MacroDefinition: value_pmodulus ( ref , val1 , val2 ) ( ( ref ) = value_pmod ( ( val1 ) , ( val2 ) ) )
# # Skipping MacroDefinition: value_oppose ( ref , val ) ( ( ref ) = value_uminus ( ( val ) ) )
# # Skipping MacroDefinition: value_absolute ( ref , val ) ( ( ref ) = value_abs ( ( val ) ) )
# # Skipping MacroDefinition: value_minimum ( ref , val1 , val2 ) ( ( ref ) = value_min ( ( val1 ) , ( val2 ) ) )
# # Skipping MacroDefinition: value_maximum ( ref , val1 , val2 ) ( ( ref ) = value_max ( ( val1 ) , ( val2 ) ) )
# # Skipping MacroDefinition: value_gcd ( ref , val1 , val2 ) Gcd ( ( val1 ) , ( val2 ) , & ( ref ) )
# # Skipping MacroDefinition: value_lcm ( ref , val1 , val2 ) Lcm3 ( ( val1 ) , ( val2 ) , & ( ref ) )
# # Skipping MacroDefinition: value_orto ( ref , val1 , val2 ) ( ( ref ) = ( val1 ) | ( val2 ) )
# # Skipping MacroDefinition: value_andto ( ref , val1 , val2 ) ( ( ref ) = ( val1 ) & ( val2 ) )
# # Skipping MacroDefinition: value_uminus ( val ) ( - ( val ) )
# # Skipping MacroDefinition: value_not ( val ) ( ~ ( val ) )
# # Skipping MacroDefinition: value_abs ( val ) ( value_posz_p ( val ) ? ( val ) : ( value_ne ( ( val ) , VALUE_NAN ) ? value_uminus ( val ) : ( THROW ( overflow_error ) , VALUE_NAN ) ) )
# # Skipping MacroDefinition: value_pos_p ( val ) value_gt ( val , VALUE_ZERO )
# # Skipping MacroDefinition: value_neg_p ( val ) value_lt ( val , VALUE_ZERO )
# # Skipping MacroDefinition: value_posz_p ( val ) value_ge ( val , VALUE_ZERO )
# # Skipping MacroDefinition: value_negz_p ( val ) value_le ( val , VALUE_ZERO )
# # Skipping MacroDefinition: value_zero_p ( val ) value_eq ( val , VALUE_ZERO )
# # Skipping MacroDefinition: value_notzero_p ( val ) value_ne ( val , VALUE_ZERO )
# # Skipping MacroDefinition: value_one_p ( val ) value_eq ( val , VALUE_ONE )
# # Skipping MacroDefinition: value_notone_p ( val ) value_ne ( val , VALUE_ONE )
# # Skipping MacroDefinition: value_mone_p ( val ) value_eq ( val , VALUE_MONE )
# # Skipping MacroDefinition: value_notmone_p ( val ) value_ne ( val , VALUE_MONE )
# # Skipping MacroDefinition: value_cmp_si ( val , n ) ( val - ( n ) )
# # Skipping MacroDefinition: value_min_p ( val ) value_eq ( val , VALUE_MIN )
# # Skipping MacroDefinition: value_max_p ( val ) value_eq ( val , VALUE_MAX )
# # Skipping MacroDefinition: value_notmin_p ( val ) value_ne ( val , VALUE_MIN )
# # Skipping MacroDefinition: value_notmax_p ( val ) value_ne ( val , VALUE_MAX )
# # Skipping MacroDefinition: EXCEPTION extern unsigned int
# # Skipping MacroDefinition: THROW ( what ) ( throw_exception ( what , __CURRENT_FUNCTION_NAME__ , __FILE__ , __LINE__ ) )
# # Skipping MacroDefinition: CATCH ( what ) if ( setjmp ( * push_exception_on_stack ( what , __CURRENT_FUNCTION_NAME__ , __FILE__ , __LINE__ ) ) )
# # Skipping MacroDefinition: UNCATCH ( what ) ( pop_exception_from_stack ( what , __CURRENT_FUNCTION_NAME__ , __FILE__ , __LINE__ ) )
# # Skipping MacroDefinition: RETHROW ( ) THROW ( the_last_just_thrown_exception )
# # Skipping MacroDefinition: value_protected_hard_idiv_multiply ( v , w , throw ) ( ( value_zero_p ( w ) || value_zero_p ( v ) ) ? VALUE_ZERO : value_lt ( value_abs ( v ) , value_div ( VALUE_MAX , value_abs ( w ) ) ) ? value_direct_multiply ( v , w ) : ( throw , VALUE_NAN ) )
# # Skipping MacroDefinition: value_protected_multiply ( v , w , throw ) value_protected_hard_idiv_multiply ( v , w , throw )
# # Skipping MacroDefinition: value_protected_mult ( v , w ) value_protected_multiply ( v , w , THROW ( overflow_error ) )
# # Skipping MacroDefinition: value_protected_product ( v , w ) v = value_protected_mult ( v , w )
# # Skipping MacroDefinition: value_mult ( v , w ) value_protected_mult ( v , w )
# # Skipping MacroDefinition: value_product ( v , w ) value_protected_product ( v , w )
# # Skipping MacroDefinition: value_substract ( ref , val1 , val2 ) ( value_subtract ( ( ref ) , ( val1 ) , ( val2 ) ) )
# # Skipping MacroDefinition: ABS ( x ) ( ( ( x ) >= 0 ) ? ( x ) : - ( x ) )
# # Skipping MacroDefinition: MIN ( x , y ) ( ( ( x ) >= ( y ) ) ? ( y ) : ( x ) )
# # Skipping MacroDefinition: MAX ( x , y ) ( ( ( x ) >= ( y ) ) ? ( x ) : ( y ) )
# # Skipping MacroDefinition: SIGN ( x ) ( ( ( x ) > 0 ) ? 1 : ( ( x ) == 0 ? 0 : - 1 ) )
# # Skipping MacroDefinition: DIVIDE ( x , y ) ( ( y ) > 0 ? POSITIVE_DIVIDE ( x , y ) : - POSITIVE_DIVIDE ( ( x ) , ( - ( y ) ) ) )
# # Skipping MacroDefinition: POSITIVE_DIVIDE ( x , y ) ( ( x ) > 0 ? ( x ) / ( y ) : - ( - ( x ) + ( y ) - 1 ) / ( y ) )
# # Skipping MacroDefinition: MODULO ( x , y ) ( ( y ) > 0 ? POSITIVE_MODULO ( x , y ) : POSITIVE_MODULO ( - x , - y ) )
# # Skipping MacroDefinition: POSITIVE_MODULO ( x , y ) ( ( x ) > 0 ? ( x ) % ( y ) : ( ( x ) % ( y ) == 0 ? 0 : ( ( y ) - ( - ( x ) ) % ( y ) ) ) )

const FIRST_PARAMETER_NAME = 'P'
const PCHAR = FIRST_PARAMETER_NAME - 1
const MAXNOOFRAYS = 200
const P_VALUE_FMT = "%4ld "
const LB_INFINITY = 1
const UB_INFINITY = 2

# # Skipping MacroDefinition: MSB ( ( unsigned ) ( ( ( unsigned ) 1 ) << ( sizeof ( int ) * 8 - 1 ) ) )
# # Skipping MacroDefinition: TOP ( ( int ) ( MSB - 1 ) )
# # Skipping MacroDefinition: NEXT ( j , b ) { if ( ! ( ( b ) >>= 1 ) ) { ( b ) = MSB ; ( j ) ++ ; } }
# # Skipping MacroDefinition: POL_HIGH_BIT ( UINT_MAX - ( UINT_MAX >> 1 ) )

# const POL_NO_DUAL = POL_HIGH_BIT | 0x0001
# const POL_INTEGER = POL_HIGH_BIT | 0x0002

# # Skipping MacroDefinition: POL_ISSET ( flags , f ) ( ( flags & f ) == f )
# # Skipping MacroDefinition: FL_INIT ( l , f ) ( l ) = ( f )
# # Skipping MacroDefinition: FL_SET ( l , f ) ( ( l ) |= ( f ) )
# # Skipping MacroDefinition: FL_CLR ( l , f ) ( ( l ) &= ~ ( f ) )
# # Skipping MacroDefinition: FL_ISSET ( l , f ) ( ( l ) & ( f ) )
# # Skipping MacroDefinition: F_INIT ( p , f ) FL_INIT ( ( p ) -> flags , f )
# # Skipping MacroDefinition: F_SET ( p , f ) FL_SET ( ( p ) -> flags , f )
# # Skipping MacroDefinition: F_CLR ( p , f ) FL_CLR ( ( p ) -> flags , f )
# # Skipping MacroDefinition: F_ISSET ( p , f ) FL_ISSET ( ( p ) -> flags , f )

# const POL_INEQUALITIES = 0x00000001
# const POL_FACETS = 0x00000002
# const POL_POINTS = 0x00000004
# const POL_VERTICES = 0x00000008
# const POL_VALID = 0x00000010

# # Skipping MacroDefinition: emptyQ ( P ) ( ( F_ISSET ( P , POL_INEQUALITIES ) && P -> NbEq > P -> Dimension ) || ( F_ISSET ( P , POL_POINTS ) && P -> NbRays == 0 ) )
# # Skipping MacroDefinition: universeQ ( P ) ( P -> Dimension == P -> NbBid )
# # Skipping MacroDefinition: FORALL_PVertex_in_ParamPolyhedron ( _V , _D , _P ) \
# #{ int _i , _ix ; unsigned _bx ; for ( _i = 0 , _ix = 0 , _bx = MSB , _V = _P -> V ; _V && ( _i < _P -> nbV ) ; _i ++ , _V = _V -> next ) { if ( _D -> F [ _ix ] & _bx ) {
# # Skipping MacroDefinition: END_FORALL_PVertex_in_ParamPolyhedron } NEXT ( _ix , _bx ) ; } \#
# }
# # Skipping MacroDefinition: FOREVER for ( ; ; )
# # Skipping MacroDefinition: POL_ENSURE_INEQUALITIES ( P ) if ( F_ISSET ( P , POL_VALID ) && ! F_ISSET ( P , POL_INEQUALITIES ) ) Polyhedron_Compute_Dual ( P ) ;
# # Skipping MacroDefinition: POL_ENSURE_POINTS ( P ) if ( F_ISSET ( P , POL_VALID ) && ! F_ISSET ( P , POL_POINTS ) ) Polyhedron_Compute_Dual ( P ) ;
# # Skipping MacroDefinition: POL_ENSURE_FACETS ( P ) if ( F_ISSET ( P , POL_VALID ) && ! F_ISSET ( P , POL_FACETS ) ) Polyhedron_Compute_Dual ( P ) ;
# # Skipping MacroDefinition: POL_ENSURE_VERTICES ( P ) if ( F_ISSET ( P , POL_VALID ) && ! F_ISSET ( P , POL_VERTICES ) ) Polyhedron_Compute_Dual ( P ) ;
# # Skipping MacroDefinition: Constraints_removeParmEqs ( a , b , c , d ) Constraints_Remove_parm_eqs ( a , b , c , d )
# # Skipping MacroDefinition: Polyhedron_removeParmEqs ( a , b , c , d , e ) Polyhedron_Remove_parm_eqs ( a , b , c , d , e )
# # Skipping MacroDefinition: show_matrix ( M ) { printf ( # M "= \n" ) ; if ( M != NULL ) { Matrix_Print ( stderr , P_VALUE_FMT , ( M ) ) ; } else { printf ( "<NULL>\n" ) ; } }
# # Skipping MacroDefinition: ensureMatrix ( M , r , c ) { if ( M == NULL ) M = Matrix_Alloc ( r , c ) ; else assert ( M -> NbRows >= r && M -> NbColumns >= c ) ; }
# # Skipping MacroDefinition: Constraints_compressLastVars ( a , b ) mpolyhedron_compress_last_vars ( a , b )
# # Skipping MacroDefinition: Constraints_eliminateFirstVars ( a , b ) mpolyhedron_eliminate_first_variables ( a , b )

typealias FILE Void
typealias Value Clong
typealias exception_callback_t Ptr{Void}

type Vector
    Size::UInt32
    p::Ptr{Value}
end

# type matrix
#     NbRows::UInt32
#     NbColumns::UInt32
#     p::Ptr{Ptr{Value}}
#     p_Init::Ptr{Value}
#     p_Init_size::Cint
# end

type Matrix
    NbRows::UInt32
    NbColumns::UInt32
    p::Ptr{Ptr{Value}}
    p_Init::Ptr{Value}
    p_Init_size::Cint
end

# type polyhedron
#     Dimension::UInt32
#     NbConstraints::UInt32
#     NbRays::UInt32
#     NbEq::UInt32
#     NbBid::UInt32
#     Constraint::Ptr{Ptr{Value}}
#     Ray::Ptr{Ptr{Value}}
#     p_Init::Ptr{Value}
#     p_Init_size::Cint
#     next::Ptr{polyhedron}
#     flags::UInt32
# end

type Polyhedron
    Dimension::UInt32
    NbConstraints::UInt32
    NbRays::UInt32
    NbEq::UInt32
    NbBid::UInt32
    Constraint::Ptr{Ptr{Value}}
    Ray::Ptr{Ptr{Value}}
    p_Init::Ptr{Value}
    p_Init_size::Cint
    next::Ptr{Polyhedron}
    flags::UInt32
end

# type interval
#     MaxN::Value
#     MaxD::Value
#     MinN::Value
#     MinD::Value
#     MaxI::Cint
#     MinI::Cint
# end

type Interval
    MaxN::Value
    MaxD::Value
    MinN::Value
    MinD::Value
    MaxI::Cint
    MinI::Cint
end

# type _Param_Vertex
#     Vertex::Ptr{Matrix}
#     Domain::Ptr{Matrix}
#     Facets::Ptr{UInt32}
#     next::Ptr{_Param_Vertex}
# end

type Param_Vertices
    Vertex::Ptr{Matrix}
    Domain::Ptr{Matrix}
    Facets::Ptr{UInt32}
    next::Ptr{Param_Vertices}
end

# type _Param_Domain
#     F::Ptr{UInt32}
#     Domain::Ptr{Polyhedron}
#     next::Ptr{_Param_Domain}
# end

type Param_Domain
    F::Ptr{UInt32}
    Domain::Ptr{Polyhedron}
    next::Ptr{Param_Domain}
end

# type _Param_Polyhedron
#     nbV::Cint
#     V::Ptr{Param_Vertices}
#     D::Ptr{Param_Domain}
#     Constraints::Ptr{Matrix}
#     Rays::Ptr{Matrix}
# end

type Param_Polyhedron
    nbV::Cint
    V::Ptr{Param_Vertices}
    D::Ptr{Param_Domain}
    Constraints::Ptr{Matrix}
    Rays::Ptr{Matrix}
end

# begin enum ANONYMOUS_1
typealias ANONYMOUS_1 UInt32
const polynomial = (UInt32)(0)
const periodic = (UInt32)(1)
const evector = (UInt32)(2)
# end enum ANONYMOUS_1

# begin enum enode_type
typealias enode_type UInt32
const polynomial = (UInt32)(0)
const periodic = (UInt32)(1)
const evector = (UInt32)(2)
# end enum enode_type

# type _evalue
#     d::Value
#     x::Void
# end

type evalue
    d::Value
    x::Void
end

immutable Array_1_evalue
    d1::evalue
end

zero(::Type{Array_1_evalue}) = begin  # /home/liu/.julia/v0.4/Clang/src/wrap_c.jl, line 266:
        Array_1_evalue(fill(zero(evalue),1)...)
    end

# type _enode
#     _type::enode_type
#     size::Cint
#     pos::Cint
#     arr::Array_1_evalue
# end

type enode
    _type::enode_type
    size::Cint
    pos::Cint
    arr::Array_1_evalue
end

# type _enumeration
#     ValidityDomain::Ptr{Polyhedron}
#     EP::evalue
#     next::Ptr{_enumeration}
# end

type Enumeration
    ValidityDomain::Ptr{Polyhedron}
    EP::evalue
    next::Ptr{Enumeration}
end

# begin enum ANONYMOUS_2
typealias ANONYMOUS_2 UInt32
const False = (UInt32)(0)
const True = (UInt32)(1)
# end enum ANONYMOUS_2

# begin enum Bool
typealias Bool UInt32
const False = (UInt32)(0)
const True = (UInt32)(1)
# end enum Bool

typealias Lattice Matrix

type LatticeUnion
    M::Ptr{Lattice}
    next::Ptr{LatticeUnion}
end

type ZPolyhedron
    Lat::Ptr{Lattice}
    P::Ptr{Polyhedron}
    next::Ptr{ZPolyhedron}
end
