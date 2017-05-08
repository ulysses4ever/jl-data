function make_PointND(N::Integer)
    assert(N >= 0)

    new_point = quote
        type PointND{T}
        end
    end

    N_str = string(N)

    # Rename to use the right N.
    new_point.args[2].args[2].args[1] = symbol("Point$(N_str)D")

    # Insert each x as args.
    for i = 1:N
        new_x = symbol("x$(i)")
        push!(new_point.args[2].args[3].args, :($new_x::T))
    end

    return(new_point)
end
