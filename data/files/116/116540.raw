include("/Users/feifeihuang/lab3/lab3_2a.jl");
include("/Users/feifeihuang/lab3/lab3_2b.jl");

function getArrayAndTime()
    x = 127*rand(1024);	#create an array of random number from 0 to 127
    file_name = "/Users/feifeihuang/lab3/file_ascii.txt";
    println("\n","time to print ASCII to STDOUT = ", @elapsed printSTDOUT(convertToAscii(x)));
    println("\n","time to write ASCII to file = ", @elapsed writeASCII(x,file_name));
    println("\n","time to read ASCII = ", @elapsed readASCII(file_name));
    println("\n","time to read ASCII = ", @elapsed readASCII(file_name));
    println("\n","time to read ASCII = ", @elapsed readASCII(file_name));
end

getArrayAndTime()
