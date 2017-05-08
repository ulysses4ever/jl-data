#! /usr/bin/env julia

function print_args(;args...)
    # do some formatting
    str = ""
    for (key, val) in args
        str *= string(key, " " , val, " ")
    end
    println(str)
end

function arg_collector(;args...)

    # do some operation on args
    println(args)
    println(typeof(args))
    print_args(args)
end

arg_collector(x=5, y=6, z=7)

