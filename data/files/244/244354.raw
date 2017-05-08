type Flag1
end

type Flag2
end

flag1 = Flag1();
flag2 = Flag2();



immutable ExampleFlags
    flag::Uint8;
    function ExampleFlags(flag1::Flag1)
        return new(convert(Uint8,1));
    end
    function ExampleFlags(flag2::Flag2)
        return new(convert(Uint8,2));
    end
end


type FlaggedType
    data;
    flag::ExampleFlags;
end



function foo(input::FlaggedType)
    if input.flag == ExampleFlags(flag1)
        print("Flag is flag1\n");
    elseif infput.flag == ExampleFlags(flag2)
        print("Flag is flag2\n");
    end
end
