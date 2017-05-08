module CPPUtility
export getKeyState, getAsyncKeyState, setCursorPos, getLastError, clearScreen, setConsoleCursorVisibility

const dllName = "CPPUtility.dll"

getKeyState(keycode::Int32) = ccall((:getKeyState, dllName), Int8, (Int32,), keycode)
getAsyncKeyState(keycode::Int32) = ccall((:getAsyncKeyState, dllName), Int8, (Int32,), keycode)
setCursorPos(x::Int16, y::Int16) = ccall((:setCursorPos, dllName), Int64, (Int16, Int16), x, y)
getLastError() = ccall((:getLastError, dllName), Int64, ())
clearScreen() = ccall((:clearScreen, dllName), Int32, ())
setConsoleCursorVisibility(visible::Bool) = ccall((:setConsoleCursorVisibility, dllName), Int32, (Int32,), Int32(visible))
end