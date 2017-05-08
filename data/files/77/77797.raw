module Phonebook

export main, mockpb

include("functions.jl")

function main()
    try
        println(dispatch(ARGS...))
    catch err
        ns = names(err)
        println(in(:msg, ns) ? err.msg : in(:val, ns) ? err.val : err)
    end
end

function dispatch(cmd, args...)
    funcs[cmd](args...)
end

function mockpb(cmd::String)
    Phonebook.dispatch(split(cmd)...)
end

end # module
