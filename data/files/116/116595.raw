include("path/lab3.jl");
function printAscii(x::Array)
    x = uint8(x)
    @printf(STDOUT,"%s",ascii(x))
end

x = 127*rand(1024);
printAscii(x);
print ("\n", @elapsed printAscii(x));
