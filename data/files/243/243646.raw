# Population creation.

function popfull(n::Int64, funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    [treefull(funcs, consts, vars, maxdepth) for _=1:n]
end

function popgrow(n::Int64, funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    [treegrow(funcs, consts, vars, maxdepth) for _=1:n]
end

function poprampedhh(n::Int64, funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
end
