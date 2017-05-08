include("path/lab3_2a.jl");
function convertToAscii(x::Array)
    x = uint8(x)
    return ascii(x)
end

function printSTDOUT(x::String)
    @printf(STDOUT,"%s",convertToAscii(x))

x = 127*rand(1024);	#create an array of random number from 0 to 127
printSTDOUT(x);
print ("\n", @elapsed printSTDOUT(x));
