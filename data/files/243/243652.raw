# Population creation.

export popfull, popgrow, poprhh

# ------------------------------------------------------------------------------
# Full
# Generates an entire population using the full method.
# ------------------------------------------------------------------------------

function popfull(n::Int64, funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    [treefull(funcs, consts, vars, maxdepth) for _=1:n]
end

# ------------------------------------------------------------------------------
# Grow
# Generates an entire population using the grow method.
# ------------------------------------------------------------------------------

function popgrow(n::Int64, funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    [treegrow(funcs, consts, vars, maxdepth) for _=1:n]
end

# ------------------------------------------------------------------------------
# Ramped half-and-half
# Implements the ramped half-and-half population initialization method.
# ------------------------------------------------------------------------------

function poprhh(n::Int64, funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    map(1:n) do _
        depth = rand(1:maxdepth)
        if rand() < 0.5
            initfunc = treegrow
        else
            initfunc = treefull
        end
        initfunc(funcs, consts, vars, depth)
    end
end
