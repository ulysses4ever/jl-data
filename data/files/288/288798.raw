include("cell.jl")

main(window) = begin
    push!(window.assets, "codemirror")
    x = Input("")
    lift(println, x)
    lift(x) do c
        showcell(
            CodeCell("", execute_code(c)),
            x
        )
    end
end
