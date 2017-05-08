export DeviceInfo, defaultInputDevice, defaultOutputDevice, deviceCount

function DeviceInfo(devid::Integer)
    devinfo = ccall((:Pa_GetDeviceInfo, portaudio), Ptr{DeviceInfo}, (Int32,), devid)
    if devinfo == C_NULL
        error("Could not get device info")
    end
    return unsafe_load(devinfo)
end

function defaultInputDevice()
    devid = ccall((:Pa_GetDefaultInputDevice, portaudio), Int32, ())
    if devid < 0
        error("No default input device")
    end
    return devid
end

function defaultOutputDevice()
    devid = ccall((:Pa_GetDefaultOutputDevice, portaudio), Int32, ())
    if devid < 0
        error("No default output device")
    end
    return devid
end

function deviceCount()
    devcount = ccall((:Pa_GetDeviceCount, portaudio), Int32, ())
    check_pa_error(devcount)
    return devcount
end
