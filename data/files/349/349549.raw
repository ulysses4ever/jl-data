
# Function that executes code and
# returns the result
execute_code(code) = begin
    try
        parse("begin " * code * " end") |> eval
    catch ex
        sprint() do io
            showerror(io, ex)
            println(io)
            Base.show_backtrace(io, catch_backtrace())
        end
    end
end

## View

# Code mirror to input some code
showinput(code;kwargs...) = begin
    s = sampler()

    @show kwargs
    codemirror(code; kwargs...) |>
    watch!(s) |>
    keypress("ctrl+enter") |>
    trigger!(s) |>
    sample(s)
end

getcode(x) = x[:code]
code_io(code, code_input; kwargs...) = begin
    addinterpreter(getcode, showinput(code; kwargs...)) >>> code_input
end

# Output area
showoutput(obj) = begin
    @show obj
    try convert(Tile, obj)
    catch codemirror(string(obj), readonly=true, linenumbers=false)
    end
end

# REPL
newrepl() = vbox(empty)
function append_execution(repl, code)
    cell_sig = Input(code)
    println(cell_sig)
    vbox(
        vcat(
            repl.tiles.tiles,
            vbox(
                code_io(code, cell_sig, linenumbers=false, name=:code),
                lift(x -> showoutput(execute_code(x)), cell_sig)
            )
        )
    )
end

main(window) = begin
    push!(window.assets, "codemirror")
    push!(window.assets, "widgets")

    selected_code = Input("")
    lift(println, selected_code)
    repl = newrepl()
    hbox(size(50vw, 100vh,
            code_io("", selected_code, linenumbers=true, name=:code)),
        vline(),
        clip(
            foldl(append_execution, repl, selected_code, typ=Any)
        ) |> size(50vw, 100vh)
    )
end
