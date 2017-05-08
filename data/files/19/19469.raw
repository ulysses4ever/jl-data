# Julia wrapper for header: ./polylib-5.22.5/include/polylib/polylib64.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0

function dump_exception_stack_to_file(arg1::Ptr{FILE})
    ccall((:dump_exception_stack_to_file,polylib),Void,(Ptr{FILE},),arg1)
end

function dump_exception_stack()
    ccall((:dump_exception_stack,polylib),Void,())
end

function push_exception_on_stack(arg1::Cint,arg2::Ptr{UInt8},arg3::Ptr{UInt8},arg4::Cint)
    ccall((:push_exception_on_stack,polylib),Ptr{jmp_buf},(Cint,Ptr{UInt8},Ptr{UInt8},Cint),arg1,arg2,arg3,arg4)
end

function pop_exception_from_stack(arg1::Cint,arg2::Ptr{UInt8},arg3::Ptr{UInt8},arg4::Cint)
    ccall((:pop_exception_from_stack,polylib),Void,(Cint,Ptr{UInt8},Ptr{UInt8},Cint),arg1,arg2,arg3,arg4)
end

function throw_exception(arg1::Cint,arg2::Ptr{UInt8},arg3::Ptr{UInt8},arg4::Cint)
    ccall((:throw_exception,polylib),Void,(Cint,Ptr{UInt8},Ptr{UInt8},Cint),arg1,arg2,arg3,arg4)
end

function errormsg1(f::Ptr{UInt8},msgname::Ptr{UInt8},msg::Ptr{UInt8})
    ccall((:errormsg1,polylib),Void,(Ptr{UInt8},Ptr{UInt8},Ptr{UInt8}),f,msgname,msg)
end

function ConstraintSimplify(old::Ptr{Value},n::Ptr{Value},len::Cint,v::Ptr{Value})
    ccall((:ConstraintSimplify,polylib),Cint,(Ptr{Value},Ptr{Value},Cint,Ptr{Value}),old,n,len,v)
end

function value_alloc(want::Cint,got::Ptr{Cint})
    ccall((:value_alloc,polylib),Ptr{Value},(Cint,Ptr{Cint}),want,got)
end

function value_free(p::Ptr{Value},size::Cint)
    ccall((:value_free,polylib),Void,(Ptr{Value},Cint),p,size)
end

function Factorial(n::Cint,result::Ptr{Value})
    ccall((:Factorial,polylib),Void,(Cint,Ptr{Value}),n,result)
end

function Binomial(n::Cint,p::Cint,result::Ptr{Value})
    ccall((:Binomial,polylib),Void,(Cint,Cint,Ptr{Value}),n,p,result)
end

function CNP(a::Cint,b::Cint,result::Ptr{Value})
    ccall((:CNP,polylib),Void,(Cint,Cint,Ptr{Value}),a,b,result)
end

function Gcd(a::Value,b::Value,result::Ptr{Value})
    ccall((:Gcd,polylib),Void,(Value,Value,Ptr{Value}),a,b,result)
end

function First_Non_Zero(p::Ptr{Value},length::UInt32)
    ccall((:First_Non_Zero,polylib),Cint,(Ptr{Value},UInt32),p,length)
end

function Vector_Alloc(length::UInt32)
    ccall((:Vector_Alloc,polylib),Ptr{Vector},(UInt32,),length)
end

function Vector_Free(vector::Ptr{Vector})
    ccall((:Vector_Free,polylib),Void,(Ptr{Vector},),vector)
end

function Vector_Print(Dst::Ptr{FILE},Format::Ptr{UInt8},Vec::Ptr{Vector})
    ccall((:Vector_Print,polylib),Void,(Ptr{FILE},Ptr{UInt8},Ptr{Vector}),Dst,Format,Vec)
end

function Vector_Read()
    ccall((:Vector_Read,polylib),Ptr{Vector},())
end

function Vector_Set(p::Ptr{Value},n::Cint,length::UInt32)
    ccall((:Vector_Set,polylib),Void,(Ptr{Value},Cint,UInt32),p,n,length)
end

function Vector_Exchange(p1::Ptr{Value},p2::Ptr{Value},length::UInt32)
    ccall((:Vector_Exchange,polylib),Void,(Ptr{Value},Ptr{Value},UInt32),p1,p2,length)
end

function Vector_Copy(p1::Ptr{Value},p2::Ptr{Value},length::UInt32)
    ccall((:Vector_Copy,polylib),Void,(Ptr{Value},Ptr{Value},UInt32),p1,p2,length)
end

function Vector_Add(p1::Ptr{Value},p2::Ptr{Value},p3::Ptr{Value},length::UInt32)
    ccall((:Vector_Add,polylib),Void,(Ptr{Value},Ptr{Value},Ptr{Value},UInt32),p1,p2,p3,length)
end

function Vector_Sub(p1::Ptr{Value},p2::Ptr{Value},p3::Ptr{Value},length::UInt32)
    ccall((:Vector_Sub,polylib),Void,(Ptr{Value},Ptr{Value},Ptr{Value},UInt32),p1,p2,p3,length)
end

function Vector_Or(p1::Ptr{Value},p2::Ptr{Value},p3::Ptr{Value},length::UInt32)
    ccall((:Vector_Or,polylib),Void,(Ptr{Value},Ptr{Value},Ptr{Value},UInt32),p1,p2,p3,length)
end

function Vector_Scale(p1::Ptr{Value},p2::Ptr{Value},lambda::Value,length::UInt32)
    ccall((:Vector_Scale,polylib),Void,(Ptr{Value},Ptr{Value},Value,UInt32),p1,p2,lambda,length)
end

function Vector_AntiScale(p1::Ptr{Value},p2::Ptr{Value},lambda::Value,length::UInt32)
    ccall((:Vector_AntiScale,polylib),Void,(Ptr{Value},Ptr{Value},Value,UInt32),p1,p2,lambda,length)
end

function Vector_Oppose(p1::Ptr{Value},p2::Ptr{Value},length::UInt32)
    ccall((:Vector_Oppose,polylib),Void,(Ptr{Value},Ptr{Value},UInt32),p1,p2,length)
end

function Inner_Product(p1::Ptr{Value},p2::Ptr{Value},length::UInt32,result::Ptr{Value})
    ccall((:Inner_Product,polylib),Void,(Ptr{Value},Ptr{Value},UInt32,Ptr{Value}),p1,p2,length,result)
end

function Vector_Max(p::Ptr{Value},length::UInt32,result::Ptr{Value})
    ccall((:Vector_Max,polylib),Void,(Ptr{Value},UInt32,Ptr{Value}),p,length,result)
end

function Vector_Min(p::Ptr{Value},length::UInt32,result::Ptr{Value})
    ccall((:Vector_Min,polylib),Void,(Ptr{Value},UInt32,Ptr{Value}),p,length,result)
end

function Vector_Combine(p1::Ptr{Value},p2::Ptr{Value},p3::Ptr{Value},lambda::Value,mu::Value,length::UInt32)
    ccall((:Vector_Combine,polylib),Void,(Ptr{Value},Ptr{Value},Ptr{Value},Value,Value,UInt32),p1,p2,p3,lambda,mu,length)
end

function Vector_Equal(Vec1::Ptr{Value},Vec2::Ptr{Value},n::UInt32)
    ccall((:Vector_Equal,polylib),Cint,(Ptr{Value},Ptr{Value},UInt32),Vec1,Vec2,n)
end

function Vector_Min_Not_Zero(p::Ptr{Value},length::UInt32,index::Ptr{Cint},result::Ptr{Value})
    ccall((:Vector_Min_Not_Zero,polylib),Void,(Ptr{Value},UInt32,Ptr{Cint},Ptr{Value}),p,length,index,result)
end

function Vector_Gcd(p::Ptr{Value},length::UInt32,result::Ptr{Value})
    ccall((:Vector_Gcd,polylib),Void,(Ptr{Value},UInt32,Ptr{Value}),p,length,result)
end

function Vector_Map(p1::Ptr{Value},p2::Ptr{Value},p3::Ptr{Value},length::UInt32,f::Ptr{Void})
    ccall((:Vector_Map,polylib),Void,(Ptr{Value},Ptr{Value},Ptr{Value},UInt32,Ptr{Void}),p1,p2,p3,length,f)
end

function Vector_Normalize(p::Ptr{Value},length::UInt32)
    ccall((:Vector_Normalize,polylib),Void,(Ptr{Value},UInt32),p,length)
end

function Vector_Normalize_Positive(p::Ptr{Value},length::Cint,pos::Cint)
    ccall((:Vector_Normalize_Positive,polylib),Void,(Ptr{Value},Cint,Cint),p,length,pos)
end

function Vector_Reduce(p::Ptr{Value},length::UInt32,f::Ptr{Void},result::Ptr{Value})
    ccall((:Vector_Reduce,polylib),Void,(Ptr{Value},UInt32,Ptr{Void},Ptr{Value}),p,length,f,result)
end

function Vector_Sort(vector::Ptr{Value},n::UInt32)
    ccall((:Vector_Sort,polylib),Void,(Ptr{Value},UInt32),vector,n)
end

function Vector_IsZero(v::Ptr{Value},length::UInt32)
    ccall((:Vector_IsZero,polylib),Cint,(Ptr{Value},UInt32),v,length)
end

function Matrix_Alloc(NbRows::UInt32,NbColumns::UInt32)
    ccall((:Matrix_Alloc,polylib),Ptr{Matrix},(UInt32,UInt32),NbRows,NbColumns)
end

function Matrix_Free(Mat::Ptr{Matrix})
    ccall((:Matrix_Free,polylib),Void,(Ptr{Matrix},),Mat)
end

function Matrix_Extend(Mat::Ptr{Matrix},NbRows::UInt32)
    ccall((:Matrix_Extend,polylib),Void,(Ptr{Matrix},UInt32),Mat,NbRows)
end

function Matrix_Print(Dst::Ptr{FILE},Format::Ptr{UInt8},Mat::Ptr{Matrix})
    ccall((:Matrix_Print,polylib),Void,(Ptr{FILE},Ptr{UInt8},Ptr{Matrix}),Dst,Format,Mat)
end

function Matrix_Read_Input(Mat::Ptr{Matrix})
    ccall((:Matrix_Read_Input,polylib),Void,(Ptr{Matrix},),Mat)
end

function Matrix_Read()
    ccall((:Matrix_Read,polylib),Ptr{Matrix},())
end

function right_hermite(A::Ptr{Matrix},Hp::Ptr{Ptr{Matrix}},Up::Ptr{Ptr{Matrix}},Qp::Ptr{Ptr{Matrix}})
    ccall((:right_hermite,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),A,Hp,Up,Qp)
end

function left_hermite(A::Ptr{Matrix},Hp::Ptr{Ptr{Matrix}},Qp::Ptr{Ptr{Matrix}},Up::Ptr{Ptr{Matrix}})
    ccall((:left_hermite,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),A,Hp,Qp,Up)
end

function MatInverse(M::Ptr{Matrix},MInv::Ptr{Matrix})
    ccall((:MatInverse,polylib),Cint,(Ptr{Matrix},Ptr{Matrix}),M,MInv)
end

function rat_prodmat(S::Ptr{Matrix},X::Ptr{Matrix},P::Ptr{Matrix})
    ccall((:rat_prodmat,polylib),Void,(Ptr{Matrix},Ptr{Matrix},Ptr{Matrix}),S,X,P)
end

function Matrix_Vector_Product(mat::Ptr{Matrix},p1::Ptr{Value},p2::Ptr{Value})
    ccall((:Matrix_Vector_Product,polylib),Void,(Ptr{Matrix},Ptr{Value},Ptr{Value}),mat,p1,p2)
end

function Vector_Matrix_Product(p1::Ptr{Value},mat::Ptr{Matrix},p2::Ptr{Value})
    ccall((:Vector_Matrix_Product,polylib),Void,(Ptr{Value},Ptr{Matrix},Ptr{Value}),p1,mat,p2)
end

function Matrix_Product(mat1::Ptr{Matrix},mat2::Ptr{Matrix},mat3::Ptr{Matrix})
    ccall((:Matrix_Product,polylib),Void,(Ptr{Matrix},Ptr{Matrix},Ptr{Matrix}),mat1,mat2,mat3)
end

function Matrix_Inverse(Mat::Ptr{Matrix},MatInv::Ptr{Matrix})
    ccall((:Matrix_Inverse,polylib),Cint,(Ptr{Matrix},Ptr{Matrix}),Mat,MatInv)
end

function Polyhedron_Compute_Dual(P::Ptr{Polyhedron})
    ccall((:Polyhedron_Compute_Dual,polylib),Void,(Ptr{Polyhedron},),P)
end

function DomainConstraintSimplify(P::Ptr{Polyhedron},MaxRays::UInt32)
    ccall((:DomainConstraintSimplify,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},UInt32),P,MaxRays)
end

function AddConstraints(Con::Ptr{Value},NbConstraints::UInt32,Pol::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:AddConstraints,polylib),Ptr{Polyhedron},(Ptr{Value},UInt32,Ptr{Polyhedron},UInt32),Con,NbConstraints,Pol,NbMaxRays)
end

function AddPolyToDomain(Pol::Ptr{Polyhedron},PolDomain::Ptr{Polyhedron})
    ccall((:AddPolyToDomain,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron}),Pol,PolDomain)
end

function AddRays(Ray2::Ptr{Value},NbRay2::UInt32,Pol1::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:AddRays,polylib),Ptr{Polyhedron},(Ptr{Value},UInt32,Ptr{Polyhedron},UInt32),Ray2,NbRay2,Pol1,NbMaxRays)
end

function align_context(Pol::Ptr{Polyhedron},align_dimension::Cint,NbMaxRays::Cint)
    ccall((:align_context,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Cint,Cint),Pol,align_dimension,NbMaxRays)
end

function Constraints2Polyhedron(Constraints::Ptr{Matrix},NbMaxRays::UInt32)
    ccall((:Constraints2Polyhedron,polylib),Ptr{Polyhedron},(Ptr{Matrix},UInt32),Constraints,NbMaxRays)
end

function Disjoint_Domain(Pol::Ptr{Polyhedron},flag::Cint,NbMaxRays::UInt32)
    ccall((:Disjoint_Domain,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Cint,UInt32),Pol,flag,NbMaxRays)
end

function DomainAddConstraints(Pol::Ptr{Polyhedron},Mat::Ptr{Matrix},NbMaxRays::UInt32)
    ccall((:DomainAddConstraints,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Matrix},UInt32),Pol,Mat,NbMaxRays)
end

function DomainAddRays(Pol::Ptr{Polyhedron},Ray::Ptr{Matrix},NbMaxConstrs::UInt32)
    ccall((:DomainAddRays,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Matrix},UInt32),Pol,Ray,NbMaxConstrs)
end

function DomainConvex(Pol::Ptr{Polyhedron},NbMaxConstrs::UInt32)
    ccall((:DomainConvex,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},UInt32),Pol,NbMaxConstrs)
end

function DomainCost(Pol::Ptr{Polyhedron},Cost::Ptr{Value})
    ccall((:DomainCost,polylib),Ptr{Interval},(Ptr{Polyhedron},Ptr{Value}),Pol,Cost)
end

function DomainDifference(Pol1::Ptr{Polyhedron},Pol2::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:DomainDifference,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32),Pol1,Pol2,NbMaxRays)
end

function DomainImage(Pol::Ptr{Polyhedron},Func::Ptr{Matrix},NbMaxConstrs::UInt32)
    ccall((:DomainImage,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Matrix},UInt32),Pol,Func,NbMaxConstrs)
end

function DomainIntersection(Pol1::Ptr{Polyhedron},Pol2::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:DomainIntersection,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32),Pol1,Pol2,NbMaxRays)
end

function DomainPreimage(Pol::Ptr{Polyhedron},Func::Ptr{Matrix},NbMaxRays::UInt32)
    ccall((:DomainPreimage,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Matrix},UInt32),Pol,Func,NbMaxRays)
end

function DomainSimplify(Pol1::Ptr{Polyhedron},Pol2::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:DomainSimplify,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32),Pol1,Pol2,NbMaxRays)
end

function Stras_DomainSimplify(Pol1::Ptr{Polyhedron},Pol2::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:Stras_DomainSimplify,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32),Pol1,Pol2,NbMaxRays)
end

function DomainUnion(Pol1::Ptr{Polyhedron},Pol2::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:DomainUnion,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32),Pol1,Pol2,NbMaxRays)
end

function Domain_Copy(Pol::Ptr{Polyhedron})
    ccall((:Domain_Copy,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},),Pol)
end

function Domain_Free(Pol::Ptr{Polyhedron})
    ccall((:Domain_Free,polylib),Void,(Ptr{Polyhedron},),Pol)
end

function Domain_PrintConstraints(Dst::Ptr{FILE},Format::Ptr{UInt8},Pol::Ptr{Polyhedron})
    ccall((:Domain_PrintConstraints,polylib),Void,(Ptr{FILE},Ptr{UInt8},Ptr{Polyhedron}),Dst,Format,Pol)
end

function Empty_Polyhedron(Dimension::UInt32)
    ccall((:Empty_Polyhedron,polylib),Ptr{Polyhedron},(UInt32,),Dimension)
end

function Gauss(Mat::Ptr{Matrix},NbEq::Cint,Dimension::Cint)
    ccall((:Gauss,polylib),Cint,(Ptr{Matrix},Cint,Cint),Mat,NbEq,Dimension)
end

function lower_upper_bounds(pos::Cint,P::Ptr{Polyhedron},context::Ptr{Value},LBp::Ptr{Value},UBp::Ptr{Value})
    ccall((:lower_upper_bounds,polylib),Cint,(Cint,Ptr{Polyhedron},Ptr{Value},Ptr{Value},Ptr{Value}),pos,P,context,LBp,UBp)
end

function Polyhedron2Constraints(Pol::Ptr{Polyhedron})
    ccall((:Polyhedron2Constraints,polylib),Ptr{Matrix},(Ptr{Polyhedron},),Pol)
end

function Polyhedron2Rays(Pol::Ptr{Polyhedron})
    ccall((:Polyhedron2Rays,polylib),Ptr{Matrix},(Ptr{Polyhedron},),Pol)
end

function PolyhedronIncludes(Pol1::Ptr{Polyhedron},Pol2::Ptr{Polyhedron})
    ccall((:PolyhedronIncludes,polylib),Cint,(Ptr{Polyhedron},Ptr{Polyhedron}),Pol1,Pol2)
end

function Polyhedron_Alloc(Dimension::UInt32,NbConstraints::UInt32,NbRays::UInt32)
    ccall((:Polyhedron_Alloc,polylib),Ptr{Polyhedron},(UInt32,UInt32,UInt32),Dimension,NbConstraints,NbRays)
end

function Polyhedron_Copy(Pol::Ptr{Polyhedron})
    ccall((:Polyhedron_Copy,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},),Pol)
end

function Polyhedron_Free(Pol::Ptr{Polyhedron})
    ccall((:Polyhedron_Free,polylib),Void,(Ptr{Polyhedron},),Pol)
end

function Polyhedron_Image(Pol::Ptr{Polyhedron},Func::Ptr{Matrix},NbMaxConstrs::UInt32)
    ccall((:Polyhedron_Image,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Matrix},UInt32),Pol,Func,NbMaxConstrs)
end

function Polyhedron_Preimage(Pol::Ptr{Polyhedron},Func::Ptr{Matrix},NbMaxRays::UInt32)
    ccall((:Polyhedron_Preimage,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Matrix},UInt32),Pol,Func,NbMaxRays)
end

function Polyhedron_Print(Dst::Ptr{FILE},Format::Ptr{UInt8},Pol::Ptr{Polyhedron})
    ccall((:Polyhedron_Print,polylib),Void,(Ptr{FILE},Ptr{UInt8},Ptr{Polyhedron}),Dst,Format,Pol)
end

function Polyhedron_PrintConstraints(Dst::Ptr{FILE},Format::Ptr{UInt8},Pol::Ptr{Polyhedron})
    ccall((:Polyhedron_PrintConstraints,polylib),Void,(Ptr{FILE},Ptr{UInt8},Ptr{Polyhedron}),Dst,Format,Pol)
end

function Polyhedron_Scan(D::Ptr{Polyhedron},C::Ptr{Polyhedron},MAXRAYS::UInt32)
    ccall((:Polyhedron_Scan,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32),D,C,MAXRAYS)
end

function PolyPrint(Pol::Ptr{Polyhedron})
    ccall((:PolyPrint,polylib),Void,(Ptr{Polyhedron},),Pol)
end

function Rays2Polyhedron(Ray::Ptr{Matrix},NbMaxConstrs::UInt32)
    ccall((:Rays2Polyhedron,polylib),Ptr{Polyhedron},(Ptr{Matrix},UInt32),Ray,NbMaxConstrs)
end

function SubConstraint(Con::Ptr{Value},Pol::Ptr{Polyhedron},NbMaxRays::UInt32,Pass::Cint)
    ccall((:SubConstraint,polylib),Ptr{Polyhedron},(Ptr{Value},Ptr{Polyhedron},UInt32,Cint),Con,Pol,NbMaxRays,Pass)
end

function Universe_Polyhedron(Dimension::UInt32)
    ccall((:Universe_Polyhedron,polylib),Ptr{Polyhedron},(UInt32,),Dimension)
end

function Compute_PDomains(PD::Ptr{Param_Domain},nb_domains::Cint,working_space::Cint)
    ccall((:Compute_PDomains,polylib),Void,(Ptr{Param_Domain},Cint,Cint),PD,nb_domains,working_space)
end

function GenParamPolyhedron(Pol::Ptr{Polyhedron},Rays::Ptr{Matrix})
    ccall((:GenParamPolyhedron,polylib),Ptr{Param_Polyhedron},(Ptr{Polyhedron},Ptr{Matrix}),Pol,Rays)
end

function Param_Domain_Free(PD::Ptr{Param_Domain})
    ccall((:Param_Domain_Free,polylib),Void,(Ptr{Param_Domain},),PD)
end

function Param_Polyhedron_Free(P::Ptr{Param_Polyhedron})
    ccall((:Param_Polyhedron_Free,polylib),Void,(Ptr{Param_Polyhedron},),P)
end

function Param_Vertices_Free(PV::Ptr{Param_Vertices})
    ccall((:Param_Vertices_Free,polylib),Void,(Ptr{Param_Vertices},),PV)
end

function Param_Vertices_Print(DST::Ptr{FILE},PV::Ptr{Param_Vertices},param_names::Ptr{Ptr{UInt8}})
    ccall((:Param_Vertices_Print,polylib),Void,(Ptr{FILE},Ptr{Param_Vertices},Ptr{Ptr{UInt8}}),DST,PV,param_names)
end

function PDomainDifference(Pol1::Ptr{Polyhedron},Pol2::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:PDomainDifference,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32),Pol1,Pol2,NbMaxRays)
end

function PDomainIntersection(Pol1::Ptr{Polyhedron},Pol2::Ptr{Polyhedron},NbMaxRays::UInt32)
    ccall((:PDomainIntersection,polylib),Ptr{Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32),Pol1,Pol2,NbMaxRays)
end

function Polyhedron2Param_Domain(Din::Ptr{Polyhedron},Cin::Ptr{Polyhedron},working_space::Cint)
    ccall((:Polyhedron2Param_Domain,polylib),Ptr{Param_Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},Cint),Din,Cin,working_space)
end

function Polyhedron2Param_SimplifiedDomain(Din::Ptr{Ptr{Polyhedron}},Cin::Ptr{Polyhedron},working_space::Cint,CEq::Ptr{Ptr{Polyhedron}},CT::Ptr{Ptr{Matrix}})
    ccall((:Polyhedron2Param_SimplifiedDomain,polylib),Ptr{Param_Polyhedron},(Ptr{Ptr{Polyhedron}},Ptr{Polyhedron},Cint,Ptr{Ptr{Polyhedron}},Ptr{Ptr{Matrix}}),Din,Cin,working_space,CEq,CT)
end

function Polyhedron2Param_Vertices(Din::Ptr{Polyhedron},Cin::Ptr{Polyhedron},working_space::Cint)
    ccall((:Polyhedron2Param_Vertices,polylib),Ptr{Param_Polyhedron},(Ptr{Polyhedron},Ptr{Polyhedron},Cint),Din,Cin,working_space)
end

function Print_Domain(DST::Ptr{FILE},D::Ptr{Polyhedron},param_names::Ptr{Ptr{UInt8}})
    ccall((:Print_Domain,polylib),Void,(Ptr{FILE},Ptr{Polyhedron},Ptr{Ptr{UInt8}}),DST,D,param_names)
end

function Print_Vertex(DST::Ptr{FILE},V::Ptr{Matrix},param_names::Ptr{Ptr{UInt8}})
    ccall((:Print_Vertex,polylib),Void,(Ptr{FILE},Ptr{Matrix},Ptr{Ptr{UInt8}}),DST,V,param_names)
end

function VertexCT(V::Ptr{Matrix},CT::Ptr{Matrix})
    ccall((:VertexCT,polylib),Ptr{Matrix},(Ptr{Matrix},Ptr{Matrix}),V,CT)
end

function Param_Polyhedron_Scale_Integer(PP::Ptr{Param_Polyhedron},P::Ptr{Ptr{Polyhedron}},det::Ptr{Value},MaxRays::UInt32)
    ccall((:Param_Polyhedron_Scale_Integer,polylib),Void,(Ptr{Param_Polyhedron},Ptr{Ptr{Polyhedron}},Ptr{Value},UInt32),PP,P,det,MaxRays)
end

function Read_ParamNames(_in::Ptr{FILE},m::Cint)
    ccall((:Read_ParamNames,polylib),Ptr{Ptr{UInt8}},(Ptr{FILE},Cint),_in,m)
end

function Free_ParamNames(params::Ptr{Ptr{UInt8}},m::Cint)
    ccall((:Free_ParamNames,polylib),Void,(Ptr{Ptr{UInt8}},Cint),params,m)
end

function GaussSimplify(M::Ptr{Matrix},M2::Ptr{Matrix})
    ccall((:GaussSimplify,polylib),Cint,(Ptr{Matrix},Ptr{Matrix}),M,M2)
end

function PolyhedronLTQ(P1::Ptr{Polyhedron},P2::Ptr{Polyhedron},INDEX::Cint,PDIM::Cint,MAXRAYS::Cint)
    ccall((:PolyhedronLTQ,polylib),Cint,(Ptr{Polyhedron},Ptr{Polyhedron},Cint,Cint,Cint),P1,P2,INDEX,PDIM,MAXRAYS)
end

function PolyhedronTSort(L::Ptr{Ptr{Polyhedron}},n::UInt32,index::UInt32,pdim::UInt32,time::Ptr{Cint},pvect::Ptr{Cint},MAXRAYS::UInt32)
    ccall((:PolyhedronTSort,polylib),Cint,(Ptr{Ptr{Polyhedron}},UInt32,UInt32,UInt32,Ptr{Cint},Ptr{Cint},UInt32),L,n,index,pdim,time,pvect,MAXRAYS)
end

function Polyhedron_Not_Empty(P::Ptr{Polyhedron},C::Ptr{Polyhedron},MAXRAYS::Cint)
    ccall((:Polyhedron_Not_Empty,polylib),Cint,(Ptr{Polyhedron},Ptr{Polyhedron},Cint),P,C,MAXRAYS)
end

function count_points(pos::Cint,P::Ptr{Polyhedron},context::Ptr{Value},res::Ptr{Value})
    ccall((:count_points,polylib),Void,(Cint,Ptr{Polyhedron},Ptr{Value},Ptr{Value}),pos,P,context,res)
end

function eadd(e1::Ptr{evalue},res::Ptr{evalue})
    ccall((:eadd,polylib),Void,(Ptr{evalue},Ptr{evalue}),e1,res)
end

function ecopy(e::Ptr{enode})
    ccall((:ecopy,polylib),Ptr{enode},(Ptr{enode},),e)
end

function edot(v1::Ptr{enode},v2::Ptr{enode},res::Ptr{evalue})
    ccall((:edot,polylib),Void,(Ptr{enode},Ptr{enode},Ptr{evalue}),v1,v2,res)
end

function new_enode(_type::enode_type,size::Cint,pos::Cint)
    ccall((:new_enode,polylib),Ptr{enode},(enode_type,Cint,Cint),_type,size,pos)
end

function free_evalue_refs(e::Ptr{evalue})
    ccall((:free_evalue_refs,polylib),Void,(Ptr{evalue},),e)
end

function Polyhedron_Enumerate(P::Ptr{Polyhedron},C::Ptr{Polyhedron},MAXRAYS::UInt32,pname::Ptr{Ptr{UInt8}})
    ccall((:Polyhedron_Enumerate,polylib),Ptr{Enumeration},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32,Ptr{Ptr{UInt8}}),P,C,MAXRAYS,pname)
end

function print_enode(DST::Ptr{FILE},p::Ptr{enode},pname::Ptr{Ptr{UInt8}})
    ccall((:print_enode,polylib),Void,(Ptr{FILE},Ptr{enode},Ptr{Ptr{UInt8}}),DST,p,pname)
end

function print_evalue(DST::Ptr{FILE},e::Ptr{evalue},pname::Ptr{Ptr{UInt8}})
    ccall((:print_evalue,polylib),Void,(Ptr{FILE},Ptr{evalue},Ptr{Ptr{UInt8}}),DST,e,pname)
end

function reduce_evalue(e::Ptr{evalue})
    ccall((:reduce_evalue,polylib),Void,(Ptr{evalue},),e)
end

function Enumeration_Free(en::Ptr{Enumeration})
    ccall((:Enumeration_Free,polylib),Void,(Ptr{Enumeration},),en)
end

function Ehrhart_Quick_Apx(M::Ptr{Matrix},C::Ptr{Matrix},Validity_Lattice::Ptr{Ptr{Matrix}},MAXRAYS::UInt32)
    ccall((:Ehrhart_Quick_Apx,polylib),Ptr{Enumeration},(Ptr{Matrix},Ptr{Matrix},Ptr{Ptr{Matrix}},UInt32),M,C,Validity_Lattice,MAXRAYS)
end

function Enumeration_zero(nbParms::UInt32,maxRays::UInt32)
    ccall((:Enumeration_zero,polylib),Ptr{Enumeration},(UInt32,UInt32),nbParms,maxRays)
end

function Domain_Enumerate(D::Ptr{Polyhedron},C::Ptr{Polyhedron},MAXRAYS::UInt32,pn::Ptr{Ptr{UInt8}})
    ccall((:Domain_Enumerate,polylib),Ptr{Enumeration},(Ptr{Polyhedron},Ptr{Polyhedron},UInt32,Ptr{Ptr{UInt8}}),D,C,MAXRAYS,pn)
end

function new_eadd(e1::Ptr{evalue},res::Ptr{evalue})
    ccall((:new_eadd,polylib),Void,(Ptr{evalue},Ptr{evalue}),e1,res)
end

function compute_evalue(e::Ptr{evalue},list_args::Ptr{Value})
    ccall((:compute_evalue,polylib),Cdouble,(Ptr{evalue},Ptr{Value}),e,list_args)
end

function compute_poly(en::Ptr{Enumeration},list_args::Ptr{Value})
    ccall((:compute_poly,polylib),Ptr{Value},(Ptr{Enumeration},Ptr{Value}),en,list_args)
end

function in_domain(P::Ptr{Polyhedron},list_args::Ptr{Value})
    ccall((:in_domain,polylib),Cint,(Ptr{Polyhedron},Ptr{Value}),P,list_args)
end

function SolveDiophantine(M::Ptr{Matrix},U::Ptr{Ptr{Matrix}},X::Ptr{Ptr{Vector}})
    ccall((:SolveDiophantine,polylib),Cint,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Vector}}),M,U,X)
end

function AffineHermite(A::Ptr{Lattice},H::Ptr{Ptr{Lattice}},U::Ptr{Ptr{Matrix}})
    ccall((:AffineHermite,polylib),Void,(Ptr{Lattice},Ptr{Ptr{Lattice}},Ptr{Ptr{Matrix}}),A,H,U)
end

function AffineSmith(A::Ptr{Lattice},U::Ptr{Ptr{Lattice}},V::Ptr{Ptr{Lattice}},Diag::Ptr{Ptr{Lattice}})
    ccall((:AffineSmith,polylib),Void,(Ptr{Lattice},Ptr{Ptr{Lattice}},Ptr{Ptr{Lattice}},Ptr{Ptr{Lattice}}),A,U,V,Diag)
end

function ChangeLatticeDimension(A::Ptr{Lattice},dimension::Cint)
    ccall((:ChangeLatticeDimension,polylib),Ptr{Lattice},(Ptr{Lattice},Cint),A,dimension)
end

function EmptyLattice(dimension::Cint)
    ccall((:EmptyLattice,polylib),Ptr{Lattice},(Cint,),dimension)
end

function ExtractLinearPart(A::Ptr{Lattice})
    ccall((:ExtractLinearPart,polylib),Ptr{Lattice},(Ptr{Lattice},),A)
end

function FindHermiteBasisofDomain(A::Ptr{Polyhedron},B::Ptr{Ptr{Matrix}})
    ccall((:FindHermiteBasisofDomain,polylib),Cint,(Ptr{Polyhedron},Ptr{Ptr{Matrix}}),A,B)
end

function Homogenise(A::Ptr{Lattice},Forward::Bool)
    ccall((:Homogenise,polylib),Ptr{Lattice},(Ptr{Lattice},Bool),A,Forward)
end

function intcompare(a::Ptr{Void},b::Ptr{Void})
    ccall((:intcompare,polylib),Cint,(Ptr{Void},Ptr{Void}),a,b)
end

function isEmptyLattice(A::Ptr{Lattice})
    ccall((:isEmptyLattice,polylib),Bool,(Ptr{Lattice},),A)
end

function isfulldim(m::Ptr{Matrix})
    ccall((:isfulldim,polylib),Bool,(Ptr{Matrix},),m)
end

function IsLattice(m::Ptr{Matrix})
    ccall((:IsLattice,polylib),Bool,(Ptr{Matrix},),m)
end

function isLinear(A::Ptr{Lattice})
    ccall((:isLinear,polylib),Bool,(Ptr{Lattice},),A)
end

function LatticeDifference(A::Ptr{Lattice},B::Ptr{Lattice})
    ccall((:LatticeDifference,polylib),Ptr{LatticeUnion},(Ptr{Lattice},Ptr{Lattice}),A,B)
end

function LatticeImage(A::Ptr{Lattice},M::Ptr{Matrix})
    ccall((:LatticeImage,polylib),Ptr{Lattice},(Ptr{Lattice},Ptr{Matrix}),A,M)
end

function LatticeIncludes(A::Ptr{Lattice},B::Ptr{Lattice})
    ccall((:LatticeIncludes,polylib),Bool,(Ptr{Lattice},Ptr{Lattice}),A,B)
end

function LatticeIntersection(X::Ptr{Lattice},Y::Ptr{Lattice})
    ccall((:LatticeIntersection,polylib),Ptr{Lattice},(Ptr{Lattice},Ptr{Lattice}),X,Y)
end

function LatticePreimage(L::Ptr{Lattice},G::Ptr{Matrix})
    ccall((:LatticePreimage,polylib),Ptr{Lattice},(Ptr{Lattice},Ptr{Matrix}),L,G)
end

function LatticeSimplify(latlist::Ptr{LatticeUnion})
    ccall((:LatticeSimplify,polylib),Ptr{LatticeUnion},(Ptr{LatticeUnion},),latlist)
end

function LatticeUnion_Alloc()
    ccall((:LatticeUnion_Alloc,polylib),Ptr{LatticeUnion},())
end

function LatticeUnion_Free(Head::Ptr{LatticeUnion})
    ccall((:LatticeUnion_Free,polylib),Void,(Ptr{LatticeUnion},),Head)
end

function PrintLatticeUnion(fp::Ptr{FILE},format::Ptr{UInt8},Head::Ptr{LatticeUnion})
    ccall((:PrintLatticeUnion,polylib),Void,(Ptr{FILE},Ptr{UInt8},Ptr{LatticeUnion}),fp,format,Head)
end

function sameAffinepart(A::Ptr{Lattice},B::Ptr{Lattice})
    ccall((:sameAffinepart,polylib),Bool,(Ptr{Lattice},Ptr{Lattice}),A,B)
end

function sameLattice(A::Ptr{Lattice},B::Ptr{Lattice})
    ccall((:sameLattice,polylib),Bool,(Ptr{Lattice},Ptr{Lattice}),A,B)
end

function Lattice2LatticeUnion(X::Ptr{Lattice},Y::Ptr{Lattice})
    ccall((:Lattice2LatticeUnion,polylib),Ptr{LatticeUnion},(Ptr{Lattice},Ptr{Lattice}),X,Y)
end

function Lcm3(a::Value,b::Value,c::Ptr{Value})
    ccall((:Lcm3,polylib),Void,(Value,Value,Ptr{Value}),a,b,c)
end

function AddANullColumn(M::Ptr{Matrix})
    ccall((:AddANullColumn,polylib),Ptr{Matrix},(Ptr{Matrix},),M)
end

function AddANullRow(M::Ptr{Matrix})
    ccall((:AddANullRow,polylib),Ptr{Matrix},(Ptr{Matrix},),M)
end

function ExchangeColumns(M::Ptr{Matrix},Column1::Cint,Column2::Cint)
    ccall((:ExchangeColumns,polylib),Void,(Ptr{Matrix},Cint,Cint),M,Column1,Column2)
end

function ExchangeRows(M::Ptr{Matrix},Row1::Cint,Row2::Cint)
    ccall((:ExchangeRows,polylib),Void,(Ptr{Matrix},Cint,Cint),M,Row1,Row2)
end

function findHermiteBasis(M::Ptr{Matrix},Result::Ptr{Ptr{Matrix}})
    ccall((:findHermiteBasis,polylib),Cint,(Ptr{Matrix},Ptr{Ptr{Matrix}}),M,Result)
end

function Identity(size::UInt32)
    ccall((:Identity,polylib),Ptr{Matrix},(UInt32,),size)
end

function isinHnf(A::Ptr{Matrix})
    ccall((:isinHnf,polylib),Bool,(Ptr{Matrix},),A)
end

function isIntegral(A::Ptr{Matrix})
    ccall((:isIntegral,polylib),Bool,(Ptr{Matrix},),A)
end

function Lcm(i::Value,j::Value)
    ccall((:Lcm,polylib),Ptr{Value},(Value,Value),i,j)
end

function Matrix_Copy(Src::Ptr{Matrix})
    ccall((:Matrix_Copy,polylib),Ptr{Matrix},(Ptr{Matrix},),Src)
end

function PutColumnFirst(X::Ptr{Matrix},Columnnumber::Cint)
    ccall((:PutColumnFirst,polylib),Void,(Ptr{Matrix},Cint),X,Columnnumber)
end

function PutColumnLast(X::Ptr{Matrix},Columnnumber::Cint)
    ccall((:PutColumnLast,polylib),Void,(Ptr{Matrix},Cint),X,Columnnumber)
end

function PutRowFirst(X::Ptr{Matrix},Rownumber::Cint)
    ccall((:PutRowFirst,polylib),Void,(Ptr{Matrix},Cint),X,Rownumber)
end

function PutRowLast(X::Ptr{Matrix},Rownumber::Cint)
    ccall((:PutRowLast,polylib),Void,(Ptr{Matrix},Cint),X,Rownumber)
end

function RemoveNColumns(M::Ptr{Matrix},FirstColumnnumber::Cint,NumColumns::Cint)
    ccall((:RemoveNColumns,polylib),Ptr{Matrix},(Ptr{Matrix},Cint,Cint),M,FirstColumnnumber,NumColumns)
end

function RemoveColumn(M::Ptr{Matrix},Columnnumber::Cint)
    ccall((:RemoveColumn,polylib),Ptr{Matrix},(Ptr{Matrix},Cint),M,Columnnumber)
end

function RemoveRow(M::Ptr{Matrix},Rownumber::Cint)
    ccall((:RemoveRow,polylib),Ptr{Matrix},(Ptr{Matrix},Cint),M,Rownumber)
end

function Transpose(A::Ptr{Matrix})
    ccall((:Transpose,polylib),Ptr{Matrix},(Ptr{Matrix},),A)
end

function Smith(A::Ptr{Matrix},U::Ptr{Ptr{Matrix}},V::Ptr{Ptr{Matrix}},Product::Ptr{Ptr{Matrix}})
    ccall((:Smith,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),A,U,V,Product)
end

function Hermite(A::Ptr{Matrix},H::Ptr{Ptr{Matrix}},U::Ptr{Ptr{Matrix}})
    ccall((:Hermite,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),A,H,U)
end

function CanonicalForm(Zpol::Ptr{ZPolyhedron},Result::Ptr{Ptr{ZPolyhedron}},Basis::Ptr{Ptr{Matrix}})
    ccall((:CanonicalForm,polylib),Void,(Ptr{ZPolyhedron},Ptr{Ptr{ZPolyhedron}},Ptr{Ptr{Matrix}}),Zpol,Result,Basis)
end

function EmptyZPolyhedron(dimension::Cint)
    ccall((:EmptyZPolyhedron,polylib),Ptr{ZPolyhedron},(Cint,),dimension)
end

function IntegraliseLattice(A::Ptr{ZPolyhedron})
    ccall((:IntegraliseLattice,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},),A)
end

function isEmptyZPolyhedron(Zpol::Ptr{ZPolyhedron})
    ccall((:isEmptyZPolyhedron,polylib),Bool,(Ptr{ZPolyhedron},),Zpol)
end

function ZDomainDifference(A::Ptr{ZPolyhedron},B::Ptr{ZPolyhedron})
    ccall((:ZDomainDifference,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},Ptr{ZPolyhedron}),A,B)
end

function ZDomainImage(A::Ptr{ZPolyhedron},Func::Ptr{Matrix})
    ccall((:ZDomainImage,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},Ptr{Matrix}),A,Func)
end

function ZDomainIncludes(A::Ptr{ZPolyhedron},B::Ptr{ZPolyhedron})
    ccall((:ZDomainIncludes,polylib),Bool,(Ptr{ZPolyhedron},Ptr{ZPolyhedron}),A,B)
end

function ZDomainIntersection(A::Ptr{ZPolyhedron},B::Ptr{ZPolyhedron})
    ccall((:ZDomainIntersection,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},Ptr{ZPolyhedron}),A,B)
end

function ZDomainPreimage(A::Ptr{ZPolyhedron},Func::Ptr{Matrix})
    ccall((:ZDomainPreimage,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},Ptr{Matrix}),A,Func)
end

function ZDomainPrint(fp::Ptr{FILE},format::Ptr{UInt8},A::Ptr{ZPolyhedron})
    ccall((:ZDomainPrint,polylib),Void,(Ptr{FILE},Ptr{UInt8},Ptr{ZPolyhedron}),fp,format,A)
end

function ZDomainSimplify(ZDom::Ptr{ZPolyhedron})
    ccall((:ZDomainSimplify,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},),ZDom)
end

function ZDomainUnion(A::Ptr{ZPolyhedron},B::Ptr{ZPolyhedron})
    ccall((:ZDomainUnion,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},Ptr{ZPolyhedron}),A,B)
end

function ZDomain_Copy(Head::Ptr{ZPolyhedron})
    ccall((:ZDomain_Copy,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},),Head)
end

function ZDomain_Free(Head::Ptr{ZPolyhedron})
    ccall((:ZDomain_Free,polylib),Void,(Ptr{ZPolyhedron},),Head)
end

function ZPolyhedronIncludes(A::Ptr{ZPolyhedron},B::Ptr{ZPolyhedron})
    ccall((:ZPolyhedronIncludes,polylib),Bool,(Ptr{ZPolyhedron},Ptr{ZPolyhedron}),A,B)
end

function ZPolyhedron_Alloc(Lat::Ptr{Lattice},Poly::Ptr{Polyhedron})
    ccall((:ZPolyhedron_Alloc,polylib),Ptr{ZPolyhedron},(Ptr{Lattice},Ptr{Polyhedron}),Lat,Poly)
end

function SplitZpolyhedron(ZPol::Ptr{ZPolyhedron},B::Ptr{Lattice})
    ccall((:SplitZpolyhedron,polylib),Ptr{ZPolyhedron},(Ptr{ZPolyhedron},Ptr{Lattice}),ZPol,B)
end

function Smith(A::Ptr{Matrix},U::Ptr{Ptr{Matrix}},V::Ptr{Ptr{Matrix}},Product::Ptr{Ptr{Matrix}})
    ccall((:Smith,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),A,U,V,Product)
end

function Hermite(A::Ptr{Matrix},H::Ptr{Ptr{Matrix}},U::Ptr{Ptr{Matrix}})
    ccall((:Hermite,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),A,H,U)
end

function Smith(A::Ptr{Matrix},U::Ptr{Ptr{Matrix}},V::Ptr{Ptr{Matrix}},Product::Ptr{Ptr{Matrix}})
    ccall((:Smith,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),A,U,V,Product)
end

function Hermite(A::Ptr{Matrix},H::Ptr{Ptr{Matrix}},U::Ptr{Ptr{Matrix}})
    ccall((:Hermite,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),A,H,U)
end

function Equalities_integerSolution(Eqs::Ptr{Matrix},sol::Ptr{Ptr{Matrix}})
    ccall((:Equalities_integerSolution,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}}),Eqs,sol)
end

function Equalities_validityLattice(Eqs::Ptr{Matrix},a::Cint,vl::Ptr{Ptr{Matrix}})
    ccall((:Equalities_validityLattice,polylib),Void,(Ptr{Matrix},Cint,Ptr{Ptr{Matrix}}),Eqs,a,vl)
end

function Equalities_intModBasis(B::Ptr{Matrix},C::Ptr{Matrix},d::Ptr{Matrix},imb::Ptr{Ptr{Matrix}})
    ccall((:Equalities_intModBasis,polylib),Void,(Ptr{Matrix},Ptr{Matrix},Ptr{Matrix},Ptr{Ptr{Matrix}}),B,C,d,imb)
end

function Constraints_fullDimensionize(M::Ptr{Ptr{Matrix}},C::Ptr{Ptr{Matrix}},VL::Ptr{Ptr{Matrix}},Eqs::Ptr{Ptr{Matrix}},ParmEqs::Ptr{Ptr{Matrix}},elimVars::Ptr{Ptr{UInt32}},elimParms::Ptr{Ptr{UInt32}},maxRays::Cint)
    ccall((:Constraints_fullDimensionize,polylib),Void,(Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Ptr{Ptr{UInt32}},Ptr{Ptr{UInt32}},Cint),M,C,VL,Eqs,ParmEqs,elimVars,elimParms,maxRays)
end

function Constraints_Remove_parm_eqs(M::Ptr{Ptr{Matrix}},Ctxt::Ptr{Ptr{Matrix}},renderSpace::Cint,elimParms::Ptr{Ptr{UInt32}})
    ccall((:Constraints_Remove_parm_eqs,polylib),Ptr{Matrix},(Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}},Cint,Ptr{Ptr{UInt32}}),M,Ctxt,renderSpace,elimParms)
end

function Constraints_removeElimCols(M::Ptr{Matrix},nbVars::UInt32,elimParms::Ptr{UInt32},newM::Ptr{Ptr{Matrix}})
    ccall((:Constraints_removeElimCols,polylib),Void,(Ptr{Matrix},UInt32,Ptr{UInt32},Ptr{Ptr{Matrix}}),M,nbVars,elimParms,newM)
end

function Lattice_extractSubLattice(lat::Ptr{Matrix},k::UInt32,subLat::Ptr{Ptr{Matrix}})
    ccall((:Lattice_extractSubLattice,polylib),Void,(Ptr{Matrix},UInt32,Ptr{Ptr{Matrix}}),lat,k,subLat)
end

function Polyhedron_Remove_parm_eqs(P::Ptr{Ptr{Polyhedron}},C::Ptr{Ptr{Polyhedron}},renderSpace::Cint,elimParms::Ptr{Ptr{UInt32}},maxRays::Cint)
    ccall((:Polyhedron_Remove_parm_eqs,polylib),Ptr{Polyhedron},(Ptr{Ptr{Polyhedron}},Ptr{Ptr{Polyhedron}},Cint,Ptr{Ptr{UInt32}},Cint),P,C,renderSpace,elimParms,maxRays)
end

function int_ker(M::Ptr{Matrix})
    ccall((:int_ker,polylib),Ptr{Matrix},(Ptr{Matrix},),M)
end

function full_dimensionize(M::Ptr{Matrix},nb_parms::Cint,Validity_Lattice::Ptr{Ptr{Matrix}})
    ccall((:full_dimensionize,polylib),Ptr{Matrix},(Ptr{Matrix},Cint,Ptr{Ptr{Matrix}}),M,nb_parms,Validity_Lattice)
end

function affine_periods(M::Ptr{Matrix},d::Ptr{Matrix})
    ccall((:affine_periods,polylib),Ptr{Matrix},(Ptr{Matrix},Ptr{Matrix}),M,d)
end

function int_mod_basis(Bp::Ptr{Matrix},Cp::Ptr{Matrix},d::Ptr{Matrix})
    ccall((:int_mod_basis,polylib),Ptr{Matrix},(Ptr{Matrix},Ptr{Matrix},Ptr{Matrix}),Bp,Cp,d)
end

function compress_parms(E::Ptr{Matrix},nb_parms::Cint)
    ccall((:compress_parms,polylib),Ptr{Matrix},(Ptr{Matrix},Cint),E,nb_parms)
end

function nb_bits(x::Culonglong)
    ccall((:nb_bits,polylib),UInt32,(Culonglong,),x)
end

function permutation_inverse(perm::Ptr{UInt32},nb_elems::UInt32)
    ccall((:permutation_inverse,polylib),Ptr{UInt32},(Ptr{UInt32},UInt32),perm,nb_elems)
end

function mtransformation_permute(transf::Ptr{Matrix},permutation::Ptr{UInt32})
    ccall((:mtransformation_permute,polylib),Ptr{Matrix},(Ptr{Matrix},Ptr{UInt32}),transf,permutation)
end

function mpolyhedron_permute(polyh::Ptr{Matrix},permutation::Ptr{UInt32})
    ccall((:mpolyhedron_permute,polylib),Ptr{Matrix},(Ptr{Matrix},Ptr{UInt32}),polyh,permutation)
end

function Constraints_permute(C::Ptr{Matrix},perm::Ptr{UInt32},Cp::Ptr{Ptr{Matrix}})
    ccall((:Constraints_permute,polylib),Void,(Ptr{Matrix},Ptr{UInt32},Ptr{Ptr{Matrix}}),C,perm,Cp)
end

function eliminable_vars(Eqs::Ptr{Matrix},start::UInt32,_end::UInt32)
    ccall((:eliminable_vars,polylib),Culonglong,(Ptr{Matrix},UInt32,UInt32),Eqs,start,_end)
end

function find_a_permutation(Eqs::Ptr{Matrix},nb_parms::UInt32)
    ccall((:find_a_permutation,polylib),Ptr{UInt32},(Ptr{Matrix},UInt32),Eqs,nb_parms)
end

function permutation_for_full_dim2(vars_to_keep::Ptr{UInt32},nb_keep::UInt32,nb_vars_parms::UInt32,nb_parms::UInt32)
    ccall((:permutation_for_full_dim2,polylib),Ptr{UInt32},(Ptr{UInt32},UInt32,UInt32,UInt32),vars_to_keep,nb_keep,nb_vars_parms,nb_parms)
end

function constraintsView(P::Ptr{Polyhedron})
    ccall((:constraintsView,polylib),Ptr{Matrix},(Ptr{Polyhedron},),P)
end

function constraintsView_Free(M::Ptr{Matrix})
    ccall((:constraintsView_Free,polylib),Void,(Ptr{Matrix},),M)
end

function split_constraints(M::Ptr{Matrix},Eqs::Ptr{Ptr{Matrix}},Ineqs::Ptr{Ptr{Matrix}})
    ccall((:split_constraints,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Ptr{Matrix}}),M,Eqs,Ineqs)
end

function Identity_Matrix(dim::UInt32)
    ccall((:Identity_Matrix,polylib),Ptr{Matrix},(UInt32,),dim)
end

function Matrix_identity(dim::UInt32,I::Ptr{Ptr{Matrix}})
    ccall((:Matrix_identity,polylib),Void,(UInt32,Ptr{Ptr{Matrix}}),dim,I)
end

function mtransformation_inverse(transf::Ptr{Matrix},inv::Ptr{Ptr{Matrix}},g::Ptr{Value})
    ccall((:mtransformation_inverse,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}},Ptr{Value}),transf,inv,g)
end

function mpolyhedron_simplify(polyh::Ptr{Matrix})
    ccall((:mpolyhedron_simplify,polylib),Void,(Ptr{Matrix},),polyh)
end

function mpolyhedron_inflate(polyh::Ptr{Matrix},nb_parms::UInt32)
    ccall((:mpolyhedron_inflate,polylib),Void,(Ptr{Matrix},UInt32),polyh,nb_parms)
end

function mpolyhedron_deflate(polyh::Ptr{Matrix},nb_parms::UInt32)
    ccall((:mpolyhedron_deflate,polylib),Void,(Ptr{Matrix},UInt32),polyh,nb_parms)
end

function eliminate_var_with_constr(Eliminator::Ptr{Matrix},eliminator_row::UInt32,Victim::Ptr{Matrix},victim_row::UInt32,var_to_elim::UInt32)
    ccall((:eliminate_var_with_constr,polylib),Void,(Ptr{Matrix},UInt32,Ptr{Matrix},UInt32,UInt32),Eliminator,eliminator_row,Victim,victim_row,var_to_elim)
end

function mpolyhedron_compress_last_vars(M::Ptr{Matrix},compression::Ptr{Matrix})
    ccall((:mpolyhedron_compress_last_vars,polylib),Void,(Ptr{Matrix},Ptr{Matrix}),M,compression)
end

function mpolyhedron_eliminate_first_variables(Eqs::Ptr{Matrix},Ineqs::Ptr{Matrix})
    ccall((:mpolyhedron_eliminate_first_variables,polylib),UInt32,(Ptr{Matrix},Ptr{Matrix}),Eqs,Ineqs)
end

function Matrix_subMatrix(M::Ptr{Matrix},sr::UInt32,sc::UInt32,nbR::UInt32,nbC::UInt32,sub::Ptr{Ptr{Matrix}})
    ccall((:Matrix_subMatrix,polylib),Void,(Ptr{Matrix},UInt32,UInt32,UInt32,UInt32,Ptr{Ptr{Matrix}}),M,sr,sc,nbR,nbC,sub)
end

function Matrix_clone(M::Ptr{Matrix},Cl::Ptr{Ptr{Matrix}})
    ccall((:Matrix_clone,polylib),Void,(Ptr{Matrix},Ptr{Ptr{Matrix}}),M,Cl)
end

function Matrix_copySubMatrix(M1::Ptr{Matrix},sr1::UInt32,sc1::UInt32,nbR::UInt32,nbC::UInt32,M2::Ptr{Matrix},sr2::UInt32,sc2::UInt32)
    ccall((:Matrix_copySubMatrix,polylib),Void,(Ptr{Matrix},UInt32,UInt32,UInt32,UInt32,Ptr{Matrix},UInt32,UInt32),M1,sr1,sc1,nbR,nbC,M2,sr2,sc2)
end

function Matrix_oppose(M::Ptr{Matrix})
    ccall((:Matrix_oppose,polylib),Void,(Ptr{Matrix},),M)
end
