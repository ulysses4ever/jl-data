include("path/lab3.jl");
function printAscii(x::Array)
    x = uint8(x)
    print(ascii(x), "\n")
end

x = 55*ones(1024);
printAscii(x);
print (@elapsed printAscii(x));
