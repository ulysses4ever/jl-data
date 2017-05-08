module CPPUtility
using Keycodes
export getkeystate, get_async_key_state, set_console_cursor_pos, get_console_cursor_pos, getlasterror, clearscreen, set_console_cursor_visibility, getconsoledims, sendkeydown, sendkeyup

const dllName = "CPPUtility.dll"

immutable Coord
    X::Int16
    Y::Int16
end

getkeystate(keycode::Keycodes.KEYCODE) = ccall((:getKeyState, dllName), Int8, (Int32,), keycode)
get_async_key_state(keycode::Keycodes.KEYCODE) = ccall((:getAsyncKeyState, dllName), Int8, (Int32,), keycode)
set_console_cursor_pos(x::Integer, y::Integer) = ccall((:setConsoleCursorPos, dllName), Int64, (Int16, Int16), x, y)
getlasterror() = ccall((:getLastError, dllName), Int64, ())
clearscreen() = ccall((:clearScreen, dllName), Int32, ())
set_console_cursor_visibility(visible::Bool) = ccall((:setConsoleCursorVisibility, dllName), Int32, (Int32,), Int32(visible))
sendkeydown(keycode::Keycodes.KEYCODE) = ccall((:sendKeyDown, dllName), UInt32, (Int32,), keycode)
sendkeyup(keycode::Keycodes.KEYCODE) = ccall((:sendKeyUp, dllName), UInt32, (Int32,), keycode)

function get_console_cursor_pos()
    coord = ccall((:getConsoleCursorPos, dllName), Coord, ())
    (coord.X, coord.Y)
end

function getconsoledims()
    coord = ccall((:getConsoleDims, dllName), Coord, ())
    (coord.X, coord.Y)
end
end