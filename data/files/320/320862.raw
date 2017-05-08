module CPPUtility_Extended
using Reexport, Keycodes

@reexport using CPPUtility
export printat

function printat_helper(printFunction::Function, msg::AbstractString, x::Integer, y::Integer)
    currentPos = get_console_cursor_pos()
    set_console_cursor_pos(x, y)
    printFunction(msg)
    set_console_cursor_pos(currentPos...)
end

function printat(msg::AbstractString, x::Integer, y::Integer)
    printat_helper(print, msg, x, y)
end

function printat(msg::AbstractString, x::Integer, y::Integer, color::Symbol)
    printat_helper(str -> print_with_color(color, str), msg, x, y)
end

function sendkeypress(keycode::Keycodes.KEYCODE, delay_secconds::Number = 0)
    sendkeydown(keycode)
    if delay >= 0.001 sleep(delay) end
    sendkeyup(keycode)
end
end