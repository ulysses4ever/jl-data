## Model

# Function that executes code and
# returns the result
execute_code(code) = begin
    parse("begin " * code * " end") |> eval
end

immutable CodeCell
    code::String
    output::Any
end
CodeCell(code::String) = CodeCell(code, execute_code(code))

## View

# Code mirror to input some code
showinput(code) = begin
    s = sampler()

    codemirror(code, linenumbers=false, name=:code) |>
    watch!(s) |>
    keypress("ctrl+enter") |>
    trigger!(s) |>
    sample(s)
end

# Output area
showoutput(obj) = begin
    try convert(Tile, obj)
    catch string(obj) |> codeblock
    end
end

getcode(x) = x[:code]
showcell(cell::CodeCell, code_input) = begin
    code = addinterpreter(getcode, showinput(cell.code)) >>> code_input
    vbox(
        code,
        hline(),
        showoutput(cell.output),
    ) |> pad(0.5em)
end

