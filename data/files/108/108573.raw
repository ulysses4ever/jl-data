#!/usr/bin/env julia
#=
Run Graze from the command line.

Usage:
graze URL
=#
import RSS: parse, FeedError, HTTPError, NotImplementedError


function main(arguments=ARGS)
    #=
    Run Graze.

    input:
        arguments: An array of command line arguments.
    =#
    if length(arguments) != 1
        println("USAGE:\n\tcli.jl URL")
        exit(1)
    end

    feed = parse(arguments[1])

    try
        feed = parse(arguments[1])
    catch exception
        if isa(exception, HTTPError)
            println("Unable to access '$(arguments[1])'")
        elseif isa(exception, FeedError)
            println("Error while parsing feed")
        elseif isa(exception, NotImplementedError)
            println("Looks like I'm not done making this yet")
        else
            println("Something went wrong:\n$exception")
        end

        exit(1)
    end

    println(feed)
end


if !isinteractive()
    #  It's not quite __name__ == '__main__', but it will do
    main()
end
