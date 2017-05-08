#! /usr/bin/julia

# Rosetta Code, Strip a set of characters from a string

function fullstrip(s::String, r::String)
    replace(s, Set(r), "")
end

tests = "She was a soul stripper. She took my heart!"
testr = "aei"

println(tests, " => ", fullstrip(tests, testr))
