module Dolfin

using PyCall

dolfin = PyCall.pyimport_conda("dolfin", "dolfin")
operator = PyCall.pyimport_conda("operator", "operator")

dolfin_methods =
["ALE", "AdaptiveLinearVariationalSolver", "AdaptiveNonlinearVariationalSolver",
 "And", "Argument", "Arguments", "Assembler", "AssemblerBase", "AutoSubDomain",
 "BDF1", "BackwardEuler", "BasisFunction", "BlockMatrix", "BlockVector",
 "BoolParameter", "BoostGraphOrdering", "BoundaryMesh", "BoundingBoxTree",
 "BoundingBoxTree3D", "BoxMesh", "BrokenElement", "ButcherMultiStageScheme",
 "CN2", "CRITICAL", "Cell", "CellFunction", "CellFunctionBool",
"CellFunctionDouble", "CellFunctionInt", "CellFunctionSizet", "CellNormal",
"CellSize", "CellType", "CellVolume", "Circumradius", "Coefficient",
"Coefficients", "CompiledSubDomain", "Constant", "CoordinateMatrix",
"CrankNicolson", "DBG", "DEBUG", "DOLFIN_EPS", "DOLFIN_EPS_LARGE",
"DOLFIN_LINELENGTH", "DOLFIN_PI", "DOLFIN_SQRT_EPS", "DOLFIN_TERM_WIDTH",
"DOLFIN_VERSION_GIT", "DOLFIN_VERSION_MAJOR", "DOLFIN_VERSION_MICRO",
"DOLFIN_VERSION_MINOR", "DOLFIN_VERSION_RELEASE", "DOLFIN_VERSION_STRING",
"DefaultFactory", "DirichletBC", "Dn", "DofMap", "Domain", "DomainBoundary",
"DoubleArray", "DoubleParameter", "Dx", "DynamicMeshEditor", "ERK", "ERK1",
"ERK4", "ERROR", "ESDIRK3", "ESDIRK4", "Edge", "EdgeFunction",
"EdgeFunctionBool", "EdgeFunctionDouble", "EdgeFunctionInt",
"EdgeFunctionSizet", "EigenFactory", "EigenKrylovSolver",
"EigenLUSolver", "EigenMatrix", "EigenVector", "EnrichedElement",
"Equation", "ErrorControl", "Event", "ExplicitEuler",
"ExplicitMidPoint", "Expression", "Extrapolation", "Face",
"FaceFunction", "FaceFunctionBool", "FaceFunctionDouble",
"FaceFunctionInt", "FaceFunctionSizet", "Facet", "FacetArea",
"FacetCell", "FacetElement", "FacetFunction", "FacetFunctionBool",
"FacetFunctionDouble", "FacetFunctionInt", "FacetFunctionSizet",
"FacetNormal", "File", "FiniteElement", "FiniteElementBase", "Form",
"ForwardEuler", "Function", "FunctionAXPY", "FunctionAssigner",
"FunctionSpace", "FunctionSpaceBase", "FunctionSpaceFromCpp", "GRL1",
"GRL2", "GenericAdaptiveVariationalSolver", "GenericBoundingBoxTree",
"GenericDofMap", "GenericFile", "GenericFunction", "GenericLUSolver",
"GenericLinearAlgebraFactory", "GenericLinearOperator",
"GenericLinearSolver", "GenericMatrix", "GenericPreconditioner",
"GenericSparsityPattern", "GenericTensor", "GenericVector",
"GlobalParameters", "Graph", "GraphBuilder", "H1", "H2", "HCurl",
"HDF5Attribute", "HDF5File", "HDiv", "HierarchicalDirichletBC",
"HierarchicalErrorControl", "HierarchicalForm",
"HierarchicalFunction", "HierarchicalFunctionSpace",
"HierarchicalLinearVariationalProblem", "HierarchicalMesh",
"HierarchicalMeshFunctionBool", "HierarchicalMeshFunctionDouble",
"HierarchicalMeshFunctionInt", "HierarchicalMeshFunctionSizet",
"HierarchicalMeshFunctionUInt",
"HierarchicalNonlinearVariationalProblem", "INFO", "Identity",
"ImplicitEuler", "Index", "IndexSet", "IntArray",
"IntParameter", "Integral", "InteriorElement", "IntervalMesh",
"KrylovSolver", "L2", "LUSolver", "Lagrange",
"LagrangeInterpolator", "Legendre", "LinearAlgebraObject",
"LinearOperator", "LinearSolver", "LinearVariationalProblem",
"LinearVariationalSolver", "LocalAssembler", "LocalMeshData",
"LocalSolver", "MPI", "MPICH_IGNORE_CXX_SEEK", "MPIInfo",
"MPI_Comm", "Matrix", "Max", "MaxCellEdgeLength",
"MaxFacetEdgeLength", "Measure", "Mesh", "MeshColoring",
"MeshConnectivity", "MeshCoordinates", "MeshData",
"MeshDisplacement", "MeshDomains", "MeshEditor",
"MeshEntity", "MeshFunction", "MeshFunctionBool",
"MeshFunctionDouble", "MeshFunctionInt",
"MeshFunctionSizet", "MeshGeometry", "MeshHierarchy",
"MeshPartitioning", "MeshPointIntersection",
"MeshQuality", "MeshRenumbering", "MeshTopology",
"MeshTransformation", "MeshValueCollection",
"MeshValueCollectionBool", "MeshValueCollectionDouble",
"MeshValueCollectionInt", "MeshValueCollectionSizet", "Min",
"MinCellEdgeLength", "MinFacetEdgeLength", "MixedElement", "MixedFunctionSpace",
"MultiMesh", "MultiMeshAssembler", "MultiMeshDirichletBC", "MultiMeshDofMap",
"MultiMeshForm", "MultiMeshFunction", "MultiMeshFunctionSpace",
"MultiMeshSubSpace", "MultiStageScheme", "NewtonSolver", "NonlinearProblem",
"NonlinearVariationalProblem", "NonlinearVariationalSolver", "Not",
"OpenMpAssembler", "OptimisationProblem", "Or", "OuterProductCell",
"OuterProductElement", "OuterProductVectorElement", "PETScBaseMatrix",
"PETScFactory", "PETScKrylovSolver", "PETScLUSolver", "PETScLinearOperator",
"PETScMatrix", "PETScObject", "PETScOptions", "PETScPreconditioner",
"PETScSNESSolver", "PETScUserPreconditioner", "PETScVector", "PROGRESS",
"ParameterValue", "Parameters", "PeriodicBoundaryComputation",
"PermutationSymbol", "Point", "PointIntegralSolver", "PointSource",
"ProductCell", "ProductDomain", "Progress", "RK4", "RKSolver", "RL1", "RL2",
"RectangleMesh", "RestrictedElement", "Restriction", "RushLarsenScheme",
"SCOTCH", "SLEPcEigenSolver", "STLFactory", "STLMatrix", "Scalar",
"SparsityPattern", "SparsityPatternBuilder", "SpatialCoordinate",
"SpecialFacetFunction", "StringParameter", "SubDomain", "SubMesh", "SubSpace",
"SubSystemsManager", "SubsetIterator", "SystemAssembler", "TRACE", "Table",
"TableEntry", "TensorConstant", "TensorElement", "TensorFunctionSpace",
"TensorLayout", "TensorProductElement", "TestFunction", "TestFunctions",
"Time", "TimeSeries", "Timer", "TimingClear_clear", "TimingClear_keep",
"TimingType_system", "TimingType_user", "TimingType_wall", "TraceElement",
"TrialFunction", "TrialFunctions", "UFLException", "UIntArray", "UnitCubeMesh",
"UnitHexMesh", "UnitIntervalMesh", "UnitQuadMesh", "UnitSquareMesh",
"UnitTetrahedronMesh", "UnitTriangleMesh", "VTKPlotter", "Variable", "Vector",
"VectorConstant", "VectorElement", "VectorFunctionSpace", "VectorSpaceBasis",
"Vertex", "VertexFunction", "VertexFunctionBool", "VertexFunctionDouble",
"VertexFunctionInt", "VertexFunctionSizet", "WARNING", "XDMFFile",
"acos", "action",
"adapt", "adapt_markers", "add_logfile", "adjoint", "as_backend_type",
"as_cell", "as_domain", "as_matrix", "as_tensor", "as_ufl", "as_vector",
"asin", "assemble", "assemble_system", "assign", "atan", "atan_2", "avg",
 "bessel_I", "bessel_J", "bessel_K", "bessel_Y", "between",
"cell_avg", "cells", "cofac", "common", "compile_expressions",
"compile_extension_module", "compilemodules", "compute_edge_map",
"compute_vertex_map", "conditional", "cos", "cosh", "cpp",
"create_ufc_function_spaces", "cross", "curl", "dC", "dI", "dO", "dP", "dS",
"dS_h", "dS_v", "dc", "debug", "deprecation", "derivative", "det", "dev",
"diag", "diag_vector", "diff", "div", "dof_to_vertex_map", "dolfin",
"dolfin_error", "dolfin_version", "dorfler_mark", "dot", "down_cast",
"ds", "ds_b", "ds_t", "ds_tb", "ds_v", "dump_timings_to_xml", "dx", "e",
"edges", "elem_div", "elem_mult", "elem_op", "elem_pow", "energy_norm",
"entities", "eq", "erf", "error", "errornorm", "exp", "exterior_derivative",
"f", "faces", "facet", "facet_avg", "facets", "fem", "fem_solve",
"functional", "functions", "ge", "generate_error_control",
"generate_error_control_forms", "get_global_parameters", "get_handler",
"get_log_level", "get_logger", "get_tensor_type", "git_commit_hash", "grad",
"gt", "has_cholmod", "has_hdf5", "has_krylov_solver_method",
"has_krylov_solver_preconditioner", "has_linear_algebra_backend",
"has_lu_solver_method", "has_mpi", "has_openmp", "has_parmetis", "has_petsc",
"has_petsc4py", "has_scotch", "has_slepc", "has_slepc4py", "has_tao",
"has_type", "has_umfpack", "has_zlib", "hexahedron", "homogenize", "i",
"importhandler", "in_nullspace", "increase_order", "indices", "info",
"info_blue", "info_green", "info_red", "info_stream", "info_underline",
"init", "init_parent_edge_indices", "inner", "integral_types", "interactive",
"interpolate", "intersect", "interval", "inv", "io", "ipow", "j", "jit", "jump",
"k", "krylov_solver_methods", "krylov_solver_preconditioners", "l", "la",
"la_index_dtype", "la_solve", "le", "lhs", "linear_algebra_backends",
"linear_solver_methods", "list_krylov_solver_methods",
"list_krylov_solver_preconditioners", "list_linear_algebra_backends",
"list_linear_solver_methods", "list_lu_solver_methods", "list_timings", "ln",
"log", "lt", "lt_coordinate", "lu_solver_methods", "mark", "max_value",
"memory_usage", "mesh", "min_value", "monitor_memory_usage", "mpi_comm_self",
"mpi_comm_world", "multistage", "nabla_div", "nabla_grad", "ne", "near",
"norm", "normalize", "not_working_in_parallel", "old_init", "outer", "p",
"parameters", "perp", "plot", "product", "project", "q", "quadrilateral",
"r", "rand", "rank", "refine", "register_element", "register_integral_type",
"relabel", "replace", "replace_integral_domains", "residual", "rhs", "rot",
"s", "seed", "sensitivity_rhs", "set_log_active", "set_log_level",
"set_output_stream", "shape", "show_elements", "sign", "sin", "sinh",
"sizeof_la_index", "skew", "solve", "split", "sqr", "sqrt",
"supported_elements", "supported_elements_for_plotting", "sym", "system",
"tan", "tanh", "tear", "tetrahedron", "tic", "time", "timing", "timings",
"toc", "tr", "transpose", "triangle", "unit_matrices", "unit_matrix",
"unit_vector", "unit_vectors", "variable", "vertex", "vertex_to_dof_map",
"vertices", "warning", "zero"]


function __init__()
  for meth in dolfin_methods
    ex = string(meth, "=", "dolfin[\"", meth, "\"]")
    prog = parse(ex)
    eval(prog)
    eval(Expr(:export, parse(meth)))
  end
end

import Base:+, -,*,/, ==, <<
import PyCall:isequal
+(f::PyObject, g::PyObject) = operator[:add](f,g)
+(f::PyObject, g) = operator[:add](f,Constant(g))

-(f::PyObject, g::PyObject) = operator[:sub](f,g)
-(f::PyObject, g) = operator[:sub](f,Constant(g))

*(f::PyObject, g::PyObject) = operator[:mul](f,g)
*(f::PyObject, g) = operator[:mul](f,Constant(g))

/(f::PyObject, g::PyObject) = operator[:div](f,g)
/(f::PyObject, g) = operator[:div](f,Constant(g))

==(f::PyObject, g::PyObject) = operator[:eq](f,g)
-(f::PyObject) = operator[:neg](f)
<<(f::PyObject, g::PyObject) = operator[:lshift](f, g)

end
