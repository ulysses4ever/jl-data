# This file contains utility functions used throughout the module
# which are not to be exported to the user

function check_pa_error(err::Int32)
    if err < 0
        errtext = ccall((:Pa_GetErrorText, portaudio), Ptr{Uint8}, (Int32,), err)
        error(bytestring(errtext))
    end
end
