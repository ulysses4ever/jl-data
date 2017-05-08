#Updated implementation inspired by https://groups.google.com/forum/#!topic/julia-users/UPNpP91QGbE


immutable ExampleFlags
    flag::Int64;
    function ExampleFlags(f::Int64)
        @assert 1<=f && f<=2
        return new(f);
    end
end

const flag1 = ExampleFlags(1);
const flag2 = ExampleFlags(2);


function foo(input::FlaggedType)
    if input.flag == flag1
        print("Flag is flag1\n");
    elseif infput.flag == flag2
        print("Flag is flag2\n");
    end
end
