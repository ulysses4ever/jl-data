function writeBinary(x::Array,file_name)
        s = open(file_name,"w+");
        n = length(x);
        y = Array(ASCIIString,n);
        for i = 1:n
                y[i] = bin(x[i]);
        end
        writecsv(file_name,y)
        close(s);
end

function readBinary(file_name)
        s = open(file_name,"r");
        readline(s);
        close(s);
end

function getTime()
    x = 127*rand(10);	#create an array of random number from 0 to 127
    x = int(x);
    file_name = "/Users/feifeihuang/lab3/file_binary.txt";
    print(x);
    println("time to write binary to file = ", @elapsed writeBinary(x,file_name));
    println("time to read binary from file = ", @elapsed readBinary(file_name));
    println("time to read binary from file = ", @elapsed readBinary(file_name));
    println("time to read binary from file = ", @elapsed readBinary(file_name));
end

getTime()
