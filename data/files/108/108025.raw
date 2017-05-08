#!/usr/bin/env julia

## I had too much fun generating names.


using ArgParse

function generate_name(range)
    vowels = "aeiouy"
    consonants = "bcdfghjklmnpqrstvwxyz"
    syllables = Array(String, rand(range))
    for ii in 1:length(syllables)
        syllables[ii] = string(randbool() ? consonants[rand(1:end)] : "",
                          vowels[rand(1:end)],
                          randbool() ? consonants[rand(1:end)] : "")
    end
    return ucfirst(string(syllables...))
end

function parsecmd()
settings = ArgParseSettings()
    settings.prog = "Name Generator"
    settings.description = "This program generates names."
    
    @add_arg_table settings begin
        "--number", "-n"
        help = "The number of names to generate."
        arg_type = Int
        default = 1000

        "--first-name-range", "-f"
        help = "The number of syllables the first name should be, minimum and maximum, inclusive"
        nargs = 2
        arg_type = Int
        default = [1,3]

        "--second-name-range", "-s"
        help = "The number of syllables the second name should be, minimum and maximum, inclusive"
        nargs = 2
        arg_type = Int
        default = [1,4]
    end
    return parse_args(settings)
end

function main()
    settings = parsecmd()
    number_of_entries = settings["number"]
    println(settings)

    first_name_range = settings["first-name-range"][1]:settings["first-name-range"][2]
    second_name_range = settings["second-name-range"][1]:settings["second-name-range"][2]
    

    for ii in 1:number_of_entries
        println(string(generate_name(first_name_range), " ", generate_name(second_name_range)))
    end
    
end

main()

