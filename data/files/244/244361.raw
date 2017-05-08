type OCCAOnDevice
end

type OCCAOnHost
end

ondev = OCCAOnDevice();
onhost = OCCAOnHost();

immutable OCCADevFlag
    flag::Uint8;
    function OCCADevFlag(ondev::OCCAOnDevice)
        return new(convert(1,Uint8));
    end
    function OCCADevFlag(onhost::OCCAOnHost)
        return new(convert(2,Uint8));
    end
end

