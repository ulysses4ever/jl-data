module CPPUtility
using Keycodes
export getkeystate, get_async_key_state, set_console_cursor_pos, get_console_cursor_pos, getlasterror, clearscreen, set_console_cursor_visibility, getconsoledims, sendkeydown, sendkeyup, setcursorpos, getcursorpos, getactivewindow, findwindow

const dllname = "CPPUtility.dll"

immutable Coord
    X::Int16
    Y::Int16
end

getkeystate(keycode::Keycodes.KEYBOARD) = ccall((:getKeyState, dllname), Int8, (Int32,), keycode)
get_async_key_state(keycode::Keycodes.KEYBOARD) = ccall((:getAsyncKeyState, dllname), Int8, (Int32,), keycode)
getkeystate(keycode::Keycodes.MOUSE) = ccall((:getKeyState, dllname), Int8, (Int32,), keycode)
get_async_key_state(keycode::Keycodes.MOUSE) = ccall((:getAsyncKeyState, dllname), Int8, (Int32,), keycode)
set_console_cursor_pos(x::Integer, y::Integer) = ccall((:setConsoleCursorPos, dllname), Int64, (Int16, Int16), x, y)
getlasterror() = ccall((:getLastError, dllname), Int64, ())
clearscreen() = ccall((:clearScreen, dllname), Int32, ())
set_console_cursor_visibility(visible::Bool) = ccall((:setConsoleCursorVisibility, dllname), Int32, (Int32,), Int32(visible))
sendkeydown(keycode::Keycodes.KEYBOARD) = ccall((:sendKeyboardKeysDown, dllname), UInt32, (Int32,), keycode)
sendkeyup(keycode::Keycodes.KEYBOARD) = ccall((:sendKeyboardKeysUp, dllname), UInt32, (Int32,), keycode)
sendkeydown(keycode::Keycodes.MOUSE) = ccall((:sendMouseKeysDown, dllname), UInt32, (Int32,), keycode)
sendkeyup(keycode::Keycodes.MOUSE) = ccall((:sendMouseKeysUp, dllname), UInt32, (Int32,), keycode)
setcursorpos(x::Integer, y::Integer) = ccall((:setCursorPos, dllname), Int32, (Int32, Int32), x, y)
getactivewindow() = ccall((:getActiveWindow, dllname), Ptr{Void}, ())
findwindow(windowname::Nullable{AbstractString}, classname::Nullable{AbstractString} = Nullable{AbstractString}()) = ccall((:findWindow, dllname), Ptr{Void}, (Ptr{Char}, Ptr{Char}), get(classname), get(windowname))

function getcursorpos() 
    coord = ccall((:getCursorPos, dllname), Coord, ())
    (coord.X, coord.Y)
end

function get_console_cursor_pos()
    coord = ccall((:getConsoleCursorPos, dllname), Coord, ())
    (coord.X, coord.Y)
end

function getconsoledims()
    coord = ccall((:getConsoleDims, dllname), Coord, ())
    (coord.X, coord.Y)
end
end