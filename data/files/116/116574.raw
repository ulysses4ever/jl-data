function convertToAscii(x::Array)
    x = uint8(x)
    x = ascii(x)
    return ascii(x)
end

function printSTDOUT(x::Array)
    @printf(STDOUT,"%s",convertToAscii(x))
end

x = 127*rand(1024);	#create an array of random number from 0 to 127
printSTDOUT(x);
println("\n","time = ", @elapsed printSTDOUT(x));
