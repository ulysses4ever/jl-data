# Run graze from the command line
import RSS.NotImplementedError
import RSS.parse


function main(arguments=ARGS)
    # run the RSS parser from the command line

    if length(arguments) != 1
        println("usage:\n  julia cli.jl URL")
        exit(1)
    end

    try
        parse(arguments[1])
    catch exception
        if isa(exception, NotImplementedError)
            println("That functionality hasn't been added yet")

        else:
            println("Error while parsing feed:\n$exception")
        end

        exit(1)
    end
end


if !isinteractive()
    main()
end
