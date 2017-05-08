#!/usr/bin/env julia

## 23 May 2014 Challenge #168 Final Grades Test Data
## (first name) , (last name) (score 1) (score 2) (score 3) (score 4) (score 5)

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
    settings.prog = "Challenge 168"
    settings.description = "This is for challenge 168."
    
    @add_arg_table settings begin
        "--number", "-n"
        help = "The number of entries to generate."
        arg_type = Int
        default = 1000
    end
    return parse_args(settings)
end

function generate_data(range, dim)
    random_scores = Array(Union(Integer, String), dim * 2)
    fill!(random_scores, " ")
    random_scores[1:2:end] = rand(range, dim)
    return string(generate_name(1:3), " , ", generate_name(1:4), "\t", random_scores...)
end

function main()
    settings = parsecmd()
    number_of_entries = settings["number"]

    for ii in 1:number_of_entries
        println(generate_data(1:100, 5))
    end
    
end

main()

