module Curry

export @curry


macro curry(f)

    # Function declaration
    declaration = f.args[1].args

    # Function name
    funcname = declaration[1]
    # Function body
    lambda = f.args[2]

    # For each argument, create a lambda function
    for a in reverse(declaration[3:end])
        lambda = :($a -> $lambda)
    end

    println("name: $(funcname)")
    println("arg1: $(declaration[2])")
    println("body: $(lambda)")

    # Declare function
    quote
        $(esc(quote
            $(funcname)($(declaration[2])) = $lambda
        end))
    end
end


end # module
