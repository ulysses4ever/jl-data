module CPPUtility_Extended
using Reexport

@reexport using CPPUtility
export printat

function printat(msg::AbstractString, x::Int16, y::Int16)
    currentPos = get_console_cursor_pos()
    set_console_cursor_pos(x, y)
    print(msg)
    set_console_cursor_pos(currentPos...)
end
end