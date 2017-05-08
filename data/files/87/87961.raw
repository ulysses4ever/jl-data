module PortNumbers



import Base: string, convert

export PortClass, EstablishedPort, RootPort, UserPort, AnyPort, PortNumber
export portmin, portmax
export PortNumber
export string, convert
export make_port_number

const ESTABLISHED_MIN_DEFAULT = 1
const ESTABLISHED_MAX_DEFAULT = 256
const ROOT_MIN_DEFAULT = 1
const ROOT_MAX_DEFAULT = 1023
const USER_MIN_DEFAULT = 1024
const USER_MAX_DEFAULT = 65535
const ANY_MIN_DEFAULT = 1
const ANY_MAX_DEFAULT = 65535

const ESTABLISHED_MIN_DEFAULT = 1
const ESTABLISHED_MAX_DEFAULT = 256
const ROOT_MIN_DEFAULT = 1
const ROOT_MAX_DEFAULT = 1023
const USER_MIN_DEFAULT = 1024
const USER_MAX_DEFAULT = 65535
const ANY_MIM_DEFAULT = 1
const ANY_MAX_DEFAULT = 65535

est_min = ESTABLISHED_MIN_DEFAULT
est_max = ESTABLISHED_MAX_DEFAULT

root_min = ROOT_MIN_DEFAULT
root_max = ROOT_MAX_DEFAULT

user_min = USER_MIN_DEFAULT
user_max = USER_MAX_DEFAULT

any_min = ANY_MIN_DEFAULT
any_max = ANY_MAX_DEFAULT




"""
### PortClass

An abstract type used as the super type
 for the various port number classes.
"""
abstract PortClass

abstract AnyPort <: PortClass
minport( ::Type{AnyPort} ) = any_min
maxport( ::Type{AnyPort} ) = any_max


abstract EstablishedPort <: PortClass
minport( ::Type{EstablishedPort} ) = est_min
maxport( ::Type{EstablishedPort} ) = est_max



abstract RootPort <: PortClass
minport( ::Type{RootPort} ) = root_min
maxport( ::Type{RootPort} ) = root_max


abstract UserPort <: PortClass
minport( ::Type{UserPort} ) = user_min
maxport( ::Type{UserPort} ) = user_max


immutable PortNumber{T<:PortClass}
    value::Integer
    function PortNumber( x::Integer )
        @assert x >= minport( T )
        @assert x <= maxport( T )
        new( x )
    end
end


convert{T<:Integer}( ::Type{T}, x::PortNumber ) = T( x.value )
string( x::PortNumber ) = Int( x ) |> string
convert{T <: AbstractString }( ::Type{T}, x::PortNumber ) = string( x ) |> T



"""
### `make_port_number( x::Integer )`

Return a port number object.

#### Example

`*julia> make_port_number( 22 )`
     
  --> `PortNumber{EstablishedPort}( 22 )`


"""
function make_port_number( x::Integer )
    @assert x >= minport( AnyPort )
    @assert x <= maxport( AnyPort )
    if x <= maxport( EstablishedPort )
        return PortNumber{EstablishedPort}( x )
    elseif x <= maxport( RootPort )
        return PortNumber{RootPort}( x )
    else
        return PortNumber{UserPort}( x )
    end
end



end # module
