using Gherkin
using Base.Test


function _test_tokens(f)
    result = tokenize(f)
    expected = split(open(readall, f * ".tokens"), '\n')[1:end-1]
    @test length(result) == length(expected)
    for line in 1:length(expected)
        if expected[line] !== "(41:1)Other:/\"\"\"/"
            # TODO escaped "
            continue
        elseif !ismatch(r"\(\d+:1\)Empty://", result[line])
            @test result[line] == expected[line]
        else
            @test ismatch(r"\(\d+:1\)(Other|Empty)://", expected[line])
        end
    end
end

const GOOD = joinpath(dirname(@__FILE__), "good")
for f in filter(x -> endswith(x, ".feature"), readdir(GOOD))
    _test_tokens(joinpath(GOOD, f))
end
