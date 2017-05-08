type FILE
end

typealias MPI_Datatype Cint
typealias MPI_Comm Cint
typealias MPI_Request Cint
typealias MPI_Group Cint

typealias MPI_Info Cint
typealias MPI_Aint Clong
typealias MPI_Fint Cint
typealias MPI_Count Clonglong
typealias MPI_Offset Clonglong

immutable Array_2_Cint
    d1::Cint
    d2::Cint
end

zero(::Type{Array_2_Cint}) = Array_2_Cint(fill(zero(Cint),2)...)

type MPI_Status
    MPI_SOURCE::Cint
    MPI_TAG::Cint
    MPI_ERROR::Cint
    count::MPI_Count
    cancelled::Cint
    abi_slush_fund::Array_2_Cint
end

