module apollo_types

export Body, Moon, Command_Module, EarthMoonSystem

type Body{T}
    mass::T
    velocity::Vector{T}
    radius::T
    position::Vector{T}
end

# Create a new type, Moon, that has all the
# attributes of Body, but is treated as its own type
typealias Moon Body

type Command_Module{T}
    mass::T
    velocity::Vector{T}
    radius::T
    position::Vector{T}
    positionE::Vector{T}
    positionH::Vector{T}
    velocityE::Vector{T}
    velocityH::Vector{T}
end

type EarthMoonSystem # This is a non-parametric type, since it doesn't take any arguments
    time::Float64
    earth::Body # See what we did there?
    moon::Moon # Now we can do type assertion with our composite types
    command_module::Command_Module
end

end
