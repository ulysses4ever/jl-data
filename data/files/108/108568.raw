# Run graze from the command line
require("./rss.jl")


function main(arguments=ARGS)
    # run the RSS parser from the command line

    if length(arguments) != 1
        println("usage:\n  julia cli.jl URL")
        exit(1)
    end

    try
        parse(arguments[1])
    catch exception
        println("Error while parsing feed:\n$exception")
        exit(1)
    end
end


if !isinteractive()
    main()
end
