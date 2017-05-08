export initialize, terminate

function initialize()
    err = ccall((:Pa_Initialize, portaudio), Int32, ())
    check_pa_error(err)
end

function terminate()
    err = ccall((:Pa_Terminate, portaudio), Int32, ())
    check_pa_error(err)
end

function initialize(f::Function)
    initialize()
    f()
    terminate()
end
