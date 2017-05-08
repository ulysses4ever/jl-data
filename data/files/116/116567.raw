include("path/lab3_2a.jl");
function convertToAscii(x::Array)
    x = uint8(x)
    return ascii(x)
end

x = 127*rand(1024);	#create an array of random number from 0 to 127
@printf(STDOUT,"%s",convertToAscii(x))
print ("\n", @elapsed printAscii(x));
